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

// Include files from FFMPEG to have h264 encoding.
extern "C" {
    #include <libavcodec/avcodec.h>
}

#include <iostream>

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/io/URL.h"
#include "opendavinci/odcore/strings/StringToolbox.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"

#include "RecorderH264.h"

namespace odrecorderh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odtools::recorder;

    RecorderH264::RecorderH264(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData, const bool &lossless) :
        Recorder(url, memorySegmentSize, numberOfSegments, threading, dumpSharedData),
        m_filenameBase(""),
        m_lossless(lossless),
        m_mapOfEncodersPerSharedImageSourceMutex(),
        m_mapOfEncodersPerSharedImageSource() {
        odcore::io::URL u(url);
        m_filenameBase = u.getResource();

        // Register all codecs from FFMPEG.
        avcodec_register_all();

        // This instance is handling all SharedImages by delegating to the corresponding entry in the map.
        registerRecorderDelegate(odcore::data::image::SharedImage::ID(), this);
    }

    RecorderH264::~RecorderH264() {
        // Unregister us.
        registerRecorderDelegate(odcore::data::image::SharedImage::ID(), NULL);

        // Clean up map.
        m_mapOfEncodersPerSharedImageSource.clear();
    }

    Container RecorderH264::process(Container &c) {
        Lock l(m_mapOfEncodersPerSharedImageSourceMutex);

        Container retVal;

        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
            odcore::data::image::SharedImage si = c.getData<odcore::data::image::SharedImage>();

            // Find existing or create new encoder.
            shared_ptr<RecorderH264Encoder> encoder;
            auto delegateEntry = m_mapOfEncodersPerSharedImageSource.find(si.getName());
            if (delegateEntry != m_mapOfEncodersPerSharedImageSource.end()) {
                encoder = m_mapOfEncodersPerSharedImageSource[si.getName()];
            }
            else {
                if (m_mapOfEncodersPerSharedImageSource.size() == 0) {
                    // Create a new encoder for this SharedImage.
                    const string FILENAME = m_filenameBase + "-" + odcore::strings::StringToolbox::replaceAll(si.getName(), ' ', '_') + ".mp4";
                    encoder = shared_ptr<RecorderH264Encoder>(new RecorderH264Encoder(FILENAME, m_lossless));
                    m_mapOfEncodersPerSharedImageSource[si.getName()] = encoder;
                }
                else {
                    // TODO: Fix multi-source handling.
                    cerr << "[odrecorderh264] Multi-source processing not fully supported yet; discarding " << si.getName() << endl;
                }
            }

            if (encoder.get() != NULL) {
                // Use encoder for this SharedImage to encode next frame.
                retVal = encoder->process(c);
            }
        }

        return retVal;
    }

} // odrecorderh264
