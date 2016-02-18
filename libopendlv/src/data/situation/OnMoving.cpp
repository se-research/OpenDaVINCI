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

#include <ostream>
#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"
#include "opendlv/data/situation/OnMoving.h"
#include "opendlv/data/situation/SituationVisitor.h"
#include "opendlv/data/situation/StartType.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace core::base;

            OnMoving::OnMoving() :
                    StartType(),
                    m_id(0) {
                setType(StartType::ONMOVING);
            }

            OnMoving::OnMoving(const OnMoving &obj) :
                    StartType(obj),
                    m_id(obj.getID()) {}

            OnMoving::~OnMoving() {}

            OnMoving& OnMoving::operator=(const OnMoving &obj) {
                StartType::operator=(obj);
                setID(obj.getID());
                return (*this);
            }

            void OnMoving::accept(SituationVisitor &visitor) {
                visitor.visit(*this);
            }

            uint32_t OnMoving::getID() const {
                return m_id;
            }

            void OnMoving::setID(const uint32_t &id) {
                m_id = id;
            }

            const string OnMoving::toString() const {
                stringstream s;
                s << "Type: " << getType() << " on moving ID: " << getID();
                return s.str();
            }

            ostream& OnMoving::operator<<(ostream &out) const {
                // Serializer super class.
                StartType::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        getID());

                return out;
            }

            istream& OnMoving::operator>>(istream &in) {
                // Deserializer super class.
                StartType::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_id);

                return in;
            }

        }
    }
} // opendlv::data::situation
