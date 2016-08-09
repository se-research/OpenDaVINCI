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
        m_mapOfDecodersMutex(),
        m_mapOfDecoders() {
        // Register all codecs from FFMPEG.
        avcodec_register_all();

        // Register us as delegate to handle odcore::data::image::H264Frame messages.
        registerPlayerDelegate(odcore::data::image::H264Frame::ID(), this);
    }

    PlayerH264::~PlayerH264() {
        // Unregister us as delegate to handle odcore::data::image::H264Frame messages.
        registerPlayerDelegate(odcore::data::image::H264Frame::ID(), NULL);

        m_mapOfDecoders.clear();
    }

    Container PlayerH264::process(Container &c) {
//        static uint32_t decodersCounter = 0;

        Lock l(m_mapOfDecodersMutex);

        Container replacementContainer;

        // Translate an H264Frame message into a proper SharedImage one.
        if (c.getDataType() == odcore::data::image::H264Frame::ID()) {
            odcore::data::image::H264Frame h264frame = c.getData<odcore::data::image::H264Frame>();
//            odcore::data::image::SharedImage si = h264frame.getAssociatedSharedImage();

//            if (decodersCounter == 0) {
//                si.setName("WebCam");
//                h264frame.setH264Filename("recorder-rec.WebCam.mp4");
//                h264frame.setAssociatedSharedImage(si);
//            }
//            if (decodersCounter == 1) {
//                si.setName("odsimcamera");
//                h264frame.setH264Filename("recorder-rec.odsimcamera.mp4");
//                h264frame.setAssociatedSharedImage(si);
//            }
//cout << "Replaying: " << h264frame.toString() << endl;
//            ++decodersCounter;
//            decodersCounter %= 2;

            // Find existing or create new decoder.
            shared_ptr<PlayerH264Decoder> decoder;
            auto delegateEntry = m_mapOfDecoders.find(h264frame.getH264Filename());
            if (delegateEntry != m_mapOfDecoders.end()) {
                decoder = m_mapOfDecoders[h264frame.getH264Filename()];
            }
            else {
                if (m_mapOfDecoders.size() == 0) {
                    // Create a new decoder for this H264Frame.
                    decoder = shared_ptr<PlayerH264Decoder>(new PlayerH264Decoder());
                    m_mapOfDecoders[h264frame.getH264Filename()] = decoder;
                }
                else {
                    // TODO: Fix multi-source handling.
                    cerr << "[odplayerh264] Multi-source processing not fully supported yet; discarding " << h264frame.toString() << endl;
                }
            }

            if (decoder.get() != NULL) {
                // Use encoder for this SharedImage to encode next frame.
                replacementContainer = decoder->process(c);
            }
        }

        return replacementContainer;
    }

} // odplayerh264
