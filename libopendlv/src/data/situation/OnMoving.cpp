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

#include <memory>
#include <ostream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendlv/data/situation/OnMoving.h"
#include "opendlv/data/situation/SituationVisitor.h"
#include "opendlv/data/situation/StartType.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;

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

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getIdentifier());

                return out;
            }

            istream& OnMoving::operator>>(istream &in) {
                // Deserializer super class.
                StartType::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_identifier);

                return in;
            }

        }
    }
} // opendlv::data::situation
