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
#include "opendavinci/odtools/player/Player.h"
#include "opendavinci/generated/odcore/data/image/H264Frame.h"

#include "PlayerH264.h"

namespace odplayerh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odtools::player;

    const uint32_t BUFFER_SIZE = 16384;

    PlayerH264::PlayerH264(const odcore::io::URL &url, const bool &autoRewind, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading) :
        Player(url, autoRewind, memorySegmentSize, numberOfMemorySegments, threading),
        m_mySharedMemory(NULL),
        m_mySharedImage(),
        filename(),
        frameCounter(0),
        inbuf(NULL),
        buffer(),
        f(NULL),
        decodeContext(NULL),
        parser(NULL),
        picture(NULL),
        pixelTransformationContext(NULL),
        frameBGR(NULL) {
        // Register all codecs from FFMPEG.
        avcodec_register_all();

        inbuf = new uint8_t[BUFFER_SIZE + FF_INPUT_BUFFER_PADDING_SIZE];

        registerPlayerDelegate(odcore::data::image::H264Frame::ID(), this);
    }

    PlayerH264::~PlayerH264() {
        registerPlayerDelegate(odcore::data::image::H264Frame::ID(), NULL);

        // Cleanup.
        av_parser_close(parser);
        avcodec_close(decodeContext);
        av_free(decodeContext);
        av_free(picture);
        av_free(frameBGR);
        fclose(f);

        if (inbuf != NULL) {
            delete [] inbuf;
            inbuf = NULL;
        }
    }

    Container PlayerH264::process(Container &c) {
        static bool isInitialized = false;

        Container replacementContainer;

        cout << "PlayerH264 called for " << c.getDataType() << endl;

        if (c.getDataType() == odcore::data::image::H264Frame::ID()) {
            odcore::data::image::H264Frame h264frame = c.getData<odcore::data::image::H264Frame>();
            m_mySharedImage = h264frame.getAssociatedSharedImage();

            cout << "Replace " << h264frame.toString() << endl;

            if (!isInitialized) {
                filename = h264frame.getH264Filename();
                isInitialized = initialize();
            }

            if (getNextFrame()) {
                replacementContainer = Container(m_mySharedImage);
                replacementContainer.setSentTimeStamp(c.getSentTimeStamp());
                replacementContainer.setReceivedTimeStamp(c.getReceivedTimeStamp());
            }
        }

        return replacementContainer;
    }

    bool PlayerH264::initialize() {
        if (m_mySharedMemory.get() == NULL) {
            m_mySharedMemory = odcore::wrapper::SharedMemoryFactory::createSharedMemory(m_mySharedImage.getName(), m_mySharedImage.getSize());
        }

        // Allocating memory to hold resulting image.
        frameBGR = av_frame_alloc();
        if (!frameBGR) {
            cout << "Could not allocate buffer for resulting frame." << endl;
            return false;
        }

        // Acquire memory for raw picture.
        const uint32_t bytes = avpicture_get_size(PIX_FMT_BGR24, m_mySharedImage.getWidth(), m_mySharedImage.getHeight());
        uint8_t *buf = static_cast<uint8_t*>(av_malloc(bytes * sizeof(uint8_t)));
        avpicture_fill((AVPicture *)frameBGR, buf, PIX_FMT_BGR24, m_mySharedImage.getWidth(), m_mySharedImage.getHeight());

        // Image pixel transformation context.
        pixelTransformationContext = sws_getContext(m_mySharedImage.getWidth(), m_mySharedImage.getHeight(),
                             AV_PIX_FMT_YUV420P, m_mySharedImage.getWidth(), m_mySharedImage.getHeight(),
                             AV_PIX_FMT_BGR24, 0, 0, 0, 0);

        // Find proper decoder for h264.
        AVCodec *decodeCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
        if (!decodeCodec) {
            cout << "Codec h264 not found." << endl;
            return false;
        }

        // Configure decoding context.
        decodeContext = avcodec_alloc_context3(decodeCodec);

        // Allow partial data handover to decoder.
        if (decodeCodec->capabilities & CODEC_CAP_TRUNCATED) {
            decodeContext->flags |= CODEC_FLAG_TRUNCATED;
        }

        // Open codec.
        if (avcodec_open2(decodeContext, decodeCodec, NULL) < 0) {
            cout << "Could not open codec h264 with given parameters." << endl;
            return false;
        }

        // Open video file.
        f = fopen(filename.c_str(), "rb");
        if (!f) {
            cout << "Could not open " << filename << endl;
            return false;
        }

        // Allocate picture.
        picture = av_frame_alloc();

        // Initialize parser.
        parser = av_parser_init(AV_CODEC_ID_H264);
        if (!parser) {
            cout << "Could not create H264 parser." << endl;
            return false;
        }

        // Fill buffer.
        fillBuffer();

        return true;
    }

    bool PlayerH264::getNextFrame() {
        bool readMore = false;

        while (!update(readMore)) {
            if (readMore) {
                fillBuffer();
            }
            if (feof(f)) {
                return false;
            }
        }

        return true;
    }

    int PlayerH264::fillBuffer() {
        int32_t nbytes = (int)fread(inbuf, 1, BUFFER_SIZE, f);

        if (nbytes > 0) {
            copy(inbuf, inbuf + nbytes, back_inserter(buffer));
        }

        return nbytes;
    }

    bool PlayerH264::update(bool &readMoreBytes) {
        readMoreBytes = false;

        if (feof(f)) {
            return false;
        }

        if (!f) {
            cout << "Cannot read from file." << endl;
            return false;
        }

        if (buffer.size() == 0) {
            readMoreBytes = true;
            return false;
        }
     
        uint8_t* data = NULL;
        int size = 0;
        int len = av_parser_parse2(parser, decodeContext, &data, &size, &buffer[0], buffer.size(), 0, 0, AV_NOPTS_VALUE);

        if (size == 0 && len >= 0) {
            readMoreBytes = true;
            return false;
        }

        if (len) {
            decodeFrame(&buffer[0], size);
            buffer.erase(buffer.begin(), buffer.begin() + len);
            return true;
        }

        return false;
    }

    void PlayerH264::decodeFrame(uint8_t *data, uint32_t size) {
        AVPacket packet;
        int gotPicture = 0;
        int len = 0;

        av_init_packet(&packet);
        packet.data = data;
        packet.size = size;

        len = avcodec_decode_video2(decodeContext, picture, &gotPicture, &packet);
        if (len < 0) {
            cout << "Error while decoding a frame." << endl;
        }
        else {
            if (gotPicture) {
                frameCounter++;
                cout << "Read frame " << picture->pts << endl;

                // Transform from YUV420p into BGR24 format.
                sws_scale(pixelTransformationContext, picture->data, picture->linesize, 0, m_mySharedImage.getHeight(), frameBGR->data, frameBGR->linesize);

                // Copy resulting frame into the shared memory segment.
                if (m_mySharedMemory->isValid()) {
                    Lock l(m_mySharedMemory);
                    memcpy(m_mySharedMemory->getSharedMemory(), frameBGR->data[0], m_mySharedImage.getWidth() * m_mySharedImage.getHeight() * m_mySharedImage.getBytesPerPixel());
                }
            }
        }
    }

} // odplayerh264
