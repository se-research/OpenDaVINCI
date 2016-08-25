/**
 * odrecorderh264 - Tool for recording data and encoding video streams with h264.
 * Copyright (C) 2016 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <cstring>
#include <iostream>
#include <string>

// Include files from FFMPEG to have h264 encoding.
extern "C" {
    #include <libavutil/avutil.h>
    #include <libavutil/mem.h>
}

// Fix for FFMPEG on Ubuntu 14.04
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
    #define av_frame_alloc  avcodec_alloc_frame
    #define av_frame_free   avcodec_free_frame
#endif

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/io/tcp/TCPFactory.h>
#include <opendavinci/odcore/strings/StringToolbox.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include <opendavinci/generated/odcore/data/image/H264Frame.h>

#include "RecorderH264Encoder.h"

namespace odrecorderh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::io::tcp;
    using namespace odtools::recorder;

    RecorderH264Encoder::RecorderH264Encoder(const string &filenameBase, const bool &lossless, const uint32_t &port) :
        m_connection(),
        m_hasConnectionMutex(),
        m_hasConnection(false),
        m_filenameBase(filenameBase),
        m_filename(),
        m_lossless(lossless),
        m_hasAttachedToSharedImageMemory(false),
        m_sharedImageMemory(),
        m_frameCounter(0),
        m_encodeCodec(NULL),
        m_encodeContext(NULL),
        m_pixelTransformationContext(NULL),
        m_outputFile(NULL),
        m_frame(NULL) {
        // Try to connect to odrecorderh264 process to exchange Containers to encode.
        try {
            m_connection = shared_ptr<TCPConnection>(TCPFactory::createTCPConnectionTo("127.0.0.1", port));
            m_connection->setConnectionListener(this);
            m_connection->setStringListener(this);
            m_connection->start();
            {
                Lock l(m_hasConnectionMutex);
                m_hasConnection = true;
            }
        }
        catch(string &exception) {
            cerr << "[odrecorderh264] Could not connect to odrecorderh264: " << exception << endl;
        }
    }

    RecorderH264Encoder::~RecorderH264Encoder() {
        stopAndCleanUpEncoding();
    }

    bool RecorderH264Encoder::hasConnection() {
        Lock l(m_hasConnectionMutex);
        return m_hasConnection;
    }

    void RecorderH264Encoder::handleConnectionError() {
        Lock l(m_hasConnectionMutex);
        m_hasConnection = false;
        stopAndCleanUpEncoding();
        cerr << "[odrecorderh264] Lost connection to odrecorderh264." << endl;
    }

    void RecorderH264Encoder::stopAndCleanUpEncoding() {
        // Process any delayed frames in the encoder (feeding NULL images).
        for (int succeeded = 1; succeeded; m_frameCounter++) {
            AVPacket packet;
            av_init_packet(&packet);
            packet.data = NULL;
            packet.size = 0;

            // Feeding NULL to indicate end-of-stream.
            int ret = avcodec_encode_video2(m_encodeContext, &packet, NULL, &succeeded);
            if (ret < 0) {
                cerr << "[odrecorderh264] Error encoding frame." << endl;
                break;
            }
            if (succeeded) {
                cout << "[odrecorderh264] Delayed writing frame " << m_frameCounter++ << ", size = " << packet.size << endl;
                fwrite(packet.data, 1, packet.size, m_outputFile);
                av_free_packet(&packet);
            }
        }

        // Close file.
        fclose(m_outputFile);

        // Cleanup.
        avcodec_close(m_encodeContext);
        av_free(m_encodeContext);
        av_freep(&m_frame->data[0]);
        av_frame_free(&m_frame);
    }

    void RecorderH264Encoder::nextString(const std::string &s) {
        Container in;
        Container out;

        {
            stringstream sstr(s);
            sstr >> in;
        }

        out = process(in);

        {
            stringstream sstr;
            sstr << out;
            m_connection->send(sstr.str());
        }
    }

    int RecorderH264Encoder::initialize(const uint32_t &width, const uint32_t &height) {
        // Find proper encoder for h264.
        m_encodeCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
        if (!m_encodeCodec) {
            cerr << "[odrecorderh264] Codec h264 not found." << endl;
            return -2;
        }

        // Configure encoding context.
        m_encodeContext = avcodec_alloc_context3(m_encodeCodec);
        m_encodeContext->width = width;
        m_encodeContext->height = height;
        m_encodeContext->pix_fmt = AVPixelFormat::AV_PIX_FMT_YUV420P; // Output pixel format.

        // Setup h264-specific parameters.
        AVDictionary *param = NULL;
        if (m_lossless) {
            av_dict_set(&param, "qp", "0", 0);
        }
        av_dict_set(&param, "preset", "ultrafast", 0);

        // Try to open codec.
        if (avcodec_open2(m_encodeContext, m_encodeCodec, &param) < 0) {
            cerr << "[odrecorderh264] Could not open codec h264 with given parameters." << endl;
            return -3;
        }

        // Setup output file.
        m_outputFile = fopen(m_filename.c_str(), "wb");
        if (!m_outputFile) {
            cerr << "[odrecorderh264] Could not open " << m_filename << endl;
            return -4;
        }

        // Allocate memory to transfer raw uncompressed image data to encoder.
        m_frame = av_frame_alloc();
        if (!m_frame) {
            cerr << "[odrecorderh264] Could not allocate video frame." << endl;
            return -5;
        }
        m_frame->width  = m_encodeContext->width;
        m_frame->height = m_encodeContext->height;
        m_frame->format = m_encodeContext->pix_fmt;

        // Allocate raw picture buffer.
        int ret = av_image_alloc(m_frame->data, m_frame->linesize,
                                 m_encodeContext->width, m_encodeContext->height, m_encodeContext->pix_fmt, 32);
        if (ret < 0) {
            cerr << "[odrecorderh264] Could not allocate raw picture buffer." << endl;
            return -6;
        }

        // Image pixel transformation context.
        m_pixelTransformationContext = sws_getContext(width, height,
                                                      AVPixelFormat::AV_PIX_FMT_BGR24, width, height,
                                                      AVPixelFormat::AV_PIX_FMT_YUV420P, 0, 0, 0, 0);

        return 0;
    }

    Container RecorderH264Encoder::process(Container &c) {
        static bool isInitialized = false;

        Container retVal;

        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
            odcore::data::image::SharedImage si = c.getData<odcore::data::image::SharedImage>();

            if (!isInitialized) {
                m_filename = m_filenameBase + "-" + odcore::strings::StringToolbox::replaceAll(si.getName(), ' ', '_') + ".h264";
                initialize(si.getWidth(), si.getHeight());
                isInitialized = true;
            }

            if (isInitialized) {
                int succeeded = 0;

                // This variable contains the encoded packets to be written to file.
                AVPacket packet;
                av_init_packet(&packet);
                packet.data = NULL;
                packet.size = 0;

                // Transform frame from BGR to YUV420P for encoding.
                if (!m_hasAttachedToSharedImageMemory) {
                    m_sharedImageMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
                    m_hasAttachedToSharedImageMemory = true;
                }

                // Check if we could successfully attach to the shared memory.
                if (m_sharedImageMemory->isValid()) {
                    // Lock the memory region to gain exclusive access using a scoped lock.
                    {
                        Lock l2(m_sharedImageMemory);

                        uint8_t *inData[1] = { static_cast<uint8_t*>(m_sharedImageMemory->getSharedMemory()) };
                        int inLinesize[1] = { static_cast<int>(si.getBytesPerPixel() * si.getWidth()) };
                        sws_scale(m_pixelTransformationContext, inData, inLinesize, 0, si.getHeight(), m_frame->data, m_frame->linesize);
                    }

                    // Frame counter.
                    m_frame->pts = m_frameCounter;
                    m_frameCounter++;

                    // Encoding image.
                    int ret = avcodec_encode_video2(m_encodeContext, &packet, m_frame, &succeeded);
                    if (ret < 0) {
                        cerr << "[odrecorderh264] Error encoding frame." << endl;
                        return retVal;
                    }
                    if (succeeded) {
                        fwrite(packet.data, sizeof(uint8_t), packet.size, m_outputFile);

                        odcore::data::image::H264Frame h264Frame;
                        h264Frame.setH264Filename(m_filename);
                        h264Frame.setFrameIdentifier(m_frameCounter);
                        h264Frame.setFrameSize(packet.size);
                        h264Frame.setAssociatedSharedImage(si);

                        retVal = Container(h264Frame);
                        retVal.setSentTimeStamp(c.getSentTimeStamp());
                        retVal.setReceivedTimeStamp(c.getReceivedTimeStamp());

                        // Release packet.
                        av_free_packet(&packet);
                    }
                }
            }
        }

        return retVal;
    }

} // odrecorderh264
