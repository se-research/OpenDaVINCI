/**
 * hesperia - Simulation environment
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

#include "core/opendavinci.h"
#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/situation/OnMoving.h"
#include "hesperia/data/situation/SituationVisitor.h"
#include "hesperia/data/situation/StartType.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace core::base;

            OnMoving::OnMoving() :
                    StartType(),
                    m_identifier(0) {
                setType(StartType::ONMOVING);
            }

            OnMoving::OnMoving(const OnMoving &obj) :
                    StartType(obj),
                    m_identifier(obj.getIdentifier()) {}

            OnMoving::~OnMoving() {}

            OnMoving& OnMoving::operator=(const OnMoving &obj) {
                StartType::operator=(obj);
                setIdentifier(obj.getIdentifier());
                return (*this);
            }

            void OnMoving::accept(SituationVisitor &visitor) {
                visitor.visit(*this);
            }

            uint32_t OnMoving::getIdentifier() const {
                return m_identifier;
            }

            void OnMoving::setIdentifier(const uint32_t &id) {
                m_identifier = id;
            }

            int32_t OnMoving::getID() const {
                return 866;
            }

            const string OnMoving::getShortName() const {
                return "OnMoving";
            }

            const string OnMoving::getLongName() const {
                return "hesperia.data.situation.OnMoving";
            }

            const string OnMoving::toString() const {
                stringstream s;
                s << "Type: " << getType() << " on moving ID: " << getIdentifier();
                return s.str();
            }

            ostream& OnMoving::operator<<(ostream &out) const {
                // Serializer super class.
                StartType::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        getIdentifier());

                return out;
            }

            istream& OnMoving::operator>>(istream &in) {
                // Deserializer super class.
                StartType::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_identifier);

                return in;
            }

        }
    }
} // hesperia::data::situation
