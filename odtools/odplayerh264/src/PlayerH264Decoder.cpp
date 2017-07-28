/**
 * odplayerh264 - Tool for replaying video streams encoded with h264.
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

// Fix for FFMPEG on Ubuntu 14.04 but exclude MacOS.
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
    #ifndef __APPLE__
        #if ((__GNUC__ * 100) + __GNUC_MINOR__) < 600
            #define av_frame_alloc  avcodec_alloc_frame
            #define av_frame_free   avcodec_free_frame
        #endif
    #endif
#endif

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/io/tcp/TCPFactory.h>
#include <opendavinci/odcore/strings/StringToolbox.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

#include "opendavinci/generated/odcore/data/image/H264Frame.h"

#include "PlayerH264Decoder.h"

namespace odplayerh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::io::tcp;
    using namespace odtools::player;

    PlayerH264Decoder::PlayerH264Decoder() :
        PlayerH264Decoder(0) {}

    PlayerH264Decoder::PlayerH264Decoder(const uint32_t &port) :
        m_connection(),
        m_hasConnectionMutex(),
        m_hasConnection(false),
        m_initialized(false),
        m_ready(true),
        m_mySharedMemory(NULL),
        m_mySharedImage(),
        m_frameCounter(0),
        m_internalBuffer(),
        m_inputFile(NULL),
        m_positionInFile(0),
        m_decodeContext(NULL),
        m_parser(NULL),
        m_picture(NULL),
        m_pixelTransformationContext(NULL),
        m_frameBGR(NULL) {
        if (0 < port) {
            // Try to connect to odplayerh264 process to exchange Containers to encode.
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
                cerr << "[odplayerh264] Could not connect to odplayerh264: " << exception << endl;
            }
        }
    }

    PlayerH264Decoder::~PlayerH264Decoder() {
        stopAndCleanUpDecoding();
    }

    bool PlayerH264Decoder::hasConnection() {
        Lock l(m_hasConnectionMutex);
        return m_hasConnection;
    }

    void PlayerH264Decoder::handleConnectionError() {
        Lock l(m_hasConnectionMutex);
        m_hasConnection = false;
        stopAndCleanUpDecoding();
        cerr << "[odplayerh264] Lost connection to odplayerh264." << endl;
    }

    void PlayerH264Decoder::stopAndCleanUpDecoding() {
        if (m_ready) {
            // Release shared memory.
            m_mySharedMemory.reset();
            m_ready = false;

            // Close decoder.
            av_parser_close(m_parser);
            avcodec_close(m_decodeContext);

            // Free acquired memory.
            av_free(m_decodeContext);
            av_free(m_picture);
            av_free(m_frameBGR);

            // Close input file.
            fclose(m_inputFile);

            // Free buffer.
            m_internalBuffer.clear();
            cout << "[odplayerh264] Cleaned h264 decoding child." << endl;
        }
    }

    void PlayerH264Decoder::nextString(const std::string &s) {
        Container in;
        Container out;

        {
            stringstream sstr(s);
            sstr >> in;
        }

        if (m_ready) {
            out = process(in);
        }

        {
            stringstream sstr;
            sstr << out;
            m_connection->send(sstr.str());
        }
    }

    Container PlayerH264Decoder::process(Container &c) {
        Container replacementContainer;

        // Translate an H264Frame message into a proper SharedImage one.
        if (c.getDataType() == odcore::data::image::H264Frame::ID()) {
            odcore::data::image::H264Frame h264frame = c.getData<odcore::data::image::H264Frame>();
            m_mySharedImage = h264frame.getAssociatedSharedImage();

            // If not initialized, initialze the h.264 decoder structure.
            if (!m_initialized) {
                m_initialized = initialize(h264frame.getH264Filename());
            }

            // If we have a valid shared memory segment, decode next frame.
            if (m_mySharedMemory->isValid()) {
                if (getNextFrame(h264frame.getFrameSize())) {
                    replacementContainer = Container(m_mySharedImage);
                    replacementContainer.setSentTimeStamp(c.getSentTimeStamp());
                    replacementContainer.setReceivedTimeStamp(c.getReceivedTimeStamp());
                    replacementContainer.setSampleTimeStamp(c.getSampleTimeStamp());
                }
            }
        }

        return replacementContainer;
    }

    bool PlayerH264Decoder::initialize(const string &filename) {
        bool retVal = false;

        // Acquire shared memory.
        if (m_mySharedMemory.get() == NULL) {
            m_mySharedMemory = odcore::wrapper::SharedMemoryFactory::createSharedMemory(m_mySharedImage.getName(), m_mySharedImage.getSize());
        }

        if (m_mySharedMemory->isValid()) {
            // Allocating memory to hold resulting image.
            m_frameBGR = av_frame_alloc();
            if (!m_frameBGR) {
                cerr << "[odplayerh264] Could not allocate buffer for resulting frame." << endl;
                return false;
            }

            // Acquire memory for raw picture.
            const uint32_t BYTES = avpicture_get_size(AVPixelFormat::AV_PIX_FMT_BGR24, m_mySharedImage.getWidth(), m_mySharedImage.getHeight());
            uint8_t *myPixelBuffer = static_cast<uint8_t*>(av_malloc(BYTES * sizeof(uint8_t)));
            avpicture_fill(reinterpret_cast<AVPicture*>(m_frameBGR),
                           myPixelBuffer, AVPixelFormat::AV_PIX_FMT_BGR24,
                           m_mySharedImage.getWidth(), m_mySharedImage.getHeight());

            // Image pixel transformation context to transform from YUV420p to BGR24.
            m_pixelTransformationContext = sws_getContext(m_mySharedImage.getWidth(), m_mySharedImage.getHeight(),
                                 AVPixelFormat::AV_PIX_FMT_YUV420P, m_mySharedImage.getWidth(), m_mySharedImage.getHeight(),
                                 AVPixelFormat::AV_PIX_FMT_BGR24, 0, 0, 0, 0);

            // Find proper decoder for h264.
            AVCodec *decodeCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
            if (!decodeCodec) {
                cerr << "[odplayerh264] Codec h264 not found." << endl;
                return false;
            }

            // Configure decoding context.
            m_decodeContext = avcodec_alloc_context3(decodeCodec);

            // Allow partial data handed over from file to decoder.
            if (decodeCodec->capabilities & CODEC_CAP_TRUNCATED) {
                m_decodeContext->flags |= CODEC_FLAG_TRUNCATED;
            }

            // Open actual codec.
            if (avcodec_open2(m_decodeContext, decodeCodec, NULL) < 0) {
                cerr << "[odplayerh264] Could not open codec h264 with given parameters." << endl;
                return false;
            }

            // Open video file.
            m_inputFile = fopen(filename.c_str(), "rb");
            if (!m_inputFile) {
                cerr << "[odplayerh264] Could not open " << filename << endl;
                return false;
            }

            // Allocate picture buffer.
            m_picture = av_frame_alloc();

            // Initialize decoding parser.
            m_parser = av_parser_init(AV_CODEC_ID_H264);
            if (!m_parser) {
                cerr << "[odplayerh264] Could not create h264 parser." << endl;
                return false;
            }

            clog << "[odplayerh264] h264 decoder initialized." << endl;
            retVal = true;
        }
        return retVal;
    }

    bool PlayerH264Decoder::getNextFrame(const uint32_t &bytesToRead) {
        if (feof(m_inputFile)) {
            cerr << "[odplayerh264] Cannot read from file." << endl;
            return false;
        }

        if (!m_inputFile) {
            cerr << "[odplayerh264] Cannot read from file." << endl;
            return false;
        }

        if (0 == bytesToRead) {
            return false;
        }

        m_internalBuffer.reserve(m_internalBuffer.size() + bytesToRead);
        uint8_t *buffer = new uint8_t[bytesToRead];
cout << "pos before = " << ftell(m_inputFile) << endl;
        int nbytes = fread(buffer, sizeof(uint8_t), bytesToRead, m_inputFile);
cout << "pos after = " << ftell(m_inputFile) << ", read " << nbytes << endl;
        if (0 > nbytes) {
            return false;
        }
        if (static_cast<uint32_t>(nbytes) != bytesToRead) {
            cerr << "[odplayerh264] Cannot read " << bytesToRead << " from file." << endl;
            return false;
        }
        copy(buffer, buffer + bytesToRead, back_inserter(m_internalBuffer));
        delete [] buffer;

        uint8_t* data = NULL;
        int size = 0;
        int length = av_parser_parse2(m_parser, m_decodeContext, &data, &size,
                                      &m_internalBuffer[0], m_internalBuffer.size(),
                                      0, 0, AV_NOPTS_VALUE);

        if ((size == 0) && (length >= 0)) {
            cerr << "[odplayerh264] Need to read more bytes: length = " << length << ", size = " << size << endl;
            return false;
        }

        if (length > 0) {
cout << "s = " << size << ", l = " << length << endl;
            decodeFrame(&m_internalBuffer[0], size);
            m_internalBuffer.erase(m_internalBuffer.begin(), m_internalBuffer.begin() + length);
            return true;
        }

        return false;
    }

    void PlayerH264Decoder::decodeFrame(uint8_t *data, uint32_t size) {
        AVPacket packet;
        int gotPicture = 0;
        int length = 0;

        av_init_packet(&packet);
        packet.data = data;
        packet.size = size;

        length = avcodec_decode_video2(m_decodeContext, m_picture, &gotPicture, &packet);
        if (length < 0) {
            cerr << "[odplayerh264] Error while decoding a frame." << endl;
        }
        else {
            if (gotPicture) {
                m_frameCounter++;

                // Transform from YUV420p into BGR24 format.
                sws_scale(m_pixelTransformationContext, m_picture->data, m_picture->linesize, 0, m_mySharedImage.getHeight(), m_frameBGR->data, m_frameBGR->linesize);

                // Copy resulting frame into the shared memory segment.
                if (m_mySharedMemory->isValid()) {
                    Lock l(m_mySharedMemory);
                    memcpy(m_mySharedMemory->getSharedMemory(), m_frameBGR->data[0], m_mySharedImage.getWidth() * m_mySharedImage.getHeight() * m_mySharedImage.getBytesPerPixel());
                }
            }
        }
    }

} // odplayerh264
