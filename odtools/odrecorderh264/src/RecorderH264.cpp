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

// Include files to open a capturing device.
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// Include files from FFMPEG to have h264 encoding.
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

#include <cstring>
#include <iostream>
#include <string>


#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"
#include "opendavinci/generated/odcore/data/image/H264Frame.h"

#include "RecorderH264.h"

namespace odrecorderh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odtools::recorder;

    // Specify image dimensions.
    uint32_t width = 0;
    uint32_t height = 0;
    const bool lossless = true;
    const string outputFilename = "output.mp4";
    AVCodec *encodeCodec = NULL;
    AVCodecContext *encodeContext = NULL;
    SwsContext *pixelTransformationContext = NULL;
    FILE *f = NULL;
    AVFrame *frame = NULL;

    RecorderH264::RecorderH264(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData) :
        Recorder(url, memorySegmentSize, numberOfSegments, threading, dumpSharedData),
        m_frameCounter(0),
        m_hasAttachedToSharedImageMemory(false),
        m_sharedImageMemory() {
        registerRecorderDelegate(odcore::data::image::SharedImage::ID(), this);
    }

    RecorderH264::~RecorderH264() {
        registerRecorderDelegate(odcore::data::image::SharedImage::ID(), NULL);

        // Process any delayed frames in the encoder (feeding NULL images).
        for (int succeeded = 1; succeeded; m_frameCounter++) {
            AVPacket packet;
            av_init_packet(&packet);
            packet.data = NULL;
            packet.size = 0;

            // Feeding NULL to indicate end-of-stream.
            int ret = avcodec_encode_video2(encodeContext, &packet, NULL, &succeeded);
            if (ret < 0) {
                cout << "Error encoding frame." << endl;
                break;
            }
            if (succeeded) {
                cout << "Delayed writing frame " << m_frameCounter++ << ", size = " << packet.size << endl;
                fwrite(packet.data, 1, packet.size, f);
                av_free_packet(&packet);
            }
        }

        // Close file.
        fclose(f);

        // Cleanup.
        avcodec_close(encodeContext);
        av_free(encodeContext);
        av_freep(&frame->data[0]);
        av_frame_free(&frame);
    }

    int RecorderH264::initialize() {
        // Register all codecs from FFMPEG.
        avcodec_register_all();

        // Find proper encoder for h264.
        encodeCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
        if (!encodeCodec) {
            cout << "Codec h264 not found." << endl;
            return -2;
        }

        // Configure encoding context.
        encodeContext = avcodec_alloc_context3(encodeCodec);
        encodeContext->width = width;
        encodeContext->height = height;
        encodeContext->pix_fmt = AV_PIX_FMT_YUV420P; // Pixel format.

        // Setup h264-specific parameters.
        AVDictionary *param = NULL;
        if (lossless) {
            av_dict_set(&param, "qp", "0", 0);
        }
        av_dict_set(&param, "preset", "ultrafast", 0);

        // Try to open codec.
        if (avcodec_open2(encodeContext, encodeCodec, &param) < 0) {
            cout << "Could not open codec h264 with given parameters." << endl;
            return -3;
        }

        // Setup output file.
        f = fopen(outputFilename.c_str(), "wb");
        if (!f) {
            cout << "Could not open " << outputFilename << endl;
            return -4;
        }

        // Allocate memory to transfer raw uncompressed image data to encoder.
        frame = av_frame_alloc();
        if (!frame) {
            cout << "Could not allocate video frame." << endl;
            return -5;
        }
        frame->width  = encodeContext->width;
        frame->height = encodeContext->height;
        frame->format = encodeContext->pix_fmt;

        // Allocate raw picture buffer.
        int ret = av_image_alloc(frame->data, frame->linesize, encodeContext->width, encodeContext->height, encodeContext->pix_fmt, 32);
        if (ret < 0) {
            cout << "Could not allocate raw picture buffer." << endl;
            return -6;
        }

        // Image pixel transformation context.
        pixelTransformationContext = sws_getContext(width, height,
                                                    AV_PIX_FMT_BGR24, width, height,
                                                    AV_PIX_FMT_YUV420P, 0, 0, 0, 0);

        return 0;
    }

    Container RecorderH264::process(Container &c) {
        static bool firstCall = true;

        Container retVal;

        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
            cout << "RecorderH264: Got called for " << c.getDataType() << endl;

            odcore::data::image::SharedImage si = c.getData<odcore::data::image::SharedImage>();
            width = si.getWidth();
            height = si.getHeight();


            if (firstCall) {
                initialize();
                firstCall = false;
            }

            {
                int succeeded = 0;

                // This variable contains the encoded packets to be written to file.
                AVPacket packet;
                av_init_packet(&packet);
                packet.data = NULL;
                packet.size = 0;

                // Frame counter.
                frame->pts = m_frameCounter;

                // Transform frame from BGR to YUV420P for encoding.
                if (!m_hasAttachedToSharedImageMemory) {
                    m_sharedImageMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
                    m_hasAttachedToSharedImageMemory = true;
                }

                // Check if we could successfully attach to the shared memory.
                if (m_sharedImageMemory->isValid()) {
                    // Lock the memory region to gain exclusive access using a scoped lock.
                    {
                        Lock l(m_sharedImageMemory);

                        uint8_t *inData[1] = { (uint8_t*)(m_sharedImageMemory->getSharedMemory()) };
                        int inLinesize[1] = { (int)(si.getBytesPerPixel() * si.getWidth()) };
                        sws_scale(pixelTransformationContext, inData, inLinesize, 0, height, frame->data, frame->linesize);
                    }

                    // Encoding image.
                    int ret = avcodec_encode_video2(encodeContext, &packet, frame, &succeeded);
                    if (ret < 0) {
                        cout << "Error encoding frame." << endl;
                        return retVal;
                    }
                    if (succeeded) {
                        cout << "Writing frame " << m_frameCounter << ", size = " << packet.size << endl;
                        fwrite(packet.data, 1, packet.size, f);

                        odcore::data::image::H264Frame h264Frame;
                        h264Frame.setH264Filename("output.mp4");
                        h264Frame.setFrameIdentifier(m_frameCounter);
                        h264Frame.setFrameSize(packet.size);
                        h264Frame.setAssociatedSharedImage(si);

cout << "F: " << h264Frame.toString() << endl;

                        retVal = Container(h264Frame);
                        retVal.setSentTimeStamp(c.getSentTimeStamp());
                        retVal.setReceivedTimeStamp(c.getReceivedTimeStamp());

                        // Release packet.
                        av_free_packet(&packet);
                    }
                }
            }
            m_frameCounter++;
        }

        return retVal;
    }

} // odrecorderh264
