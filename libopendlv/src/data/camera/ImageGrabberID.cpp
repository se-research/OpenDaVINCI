/**
 * OpenDLV - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#include <iosfwd>
#include <string>

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/camera/ImageGrabberID.h"

namespace opendlv {
    namespace data {
        namespace camera {

            using namespace std;
            using namespace odcore::base;


            ImageGrabberID::ImageGrabberID(const string &name) :
                    m_name(name) {}

            ImageGrabberID::ImageGrabberID(const ImageGrabberID &obj) :
                    m_name(obj.m_name) {}

            ImageGrabberID::~ImageGrabberID() {}

            ImageGrabberID& ImageGrabberID::operator=(const ImageGrabberID &obj) {
                m_name = obj.getName();

                return (*this);
            }

            const string ImageGrabberID::getName() const {
                return m_name;
            }

            ostream& ImageGrabberID::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                        m_name);

                return out;
            }

            istream& ImageGrabberID::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                       m_name);

                return in;
            }

            const string ImageGrabberID::toString() const {
                return m_name;
            }
        }
    }
} // opendlv::data::camera
