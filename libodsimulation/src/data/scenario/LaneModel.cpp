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

#include <istream>
#include <string>
#include <vector>

#include "core/opendavinci.h"
#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/Serializable.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/data/SerializableData.h"
#include "hesperia/data/scenario/Connector.h"
#include "hesperia/data/scenario/LaneAttribute.h"
#include "hesperia/data/scenario/LaneModel.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/TrafficControl.h"
#include "hesperia/data/scenario/TrafficLight.h"
#include "hesperia/data/scenario/TrafficSign.h"

namespace hesperia {
    namespace data {
        namespace scenario {

class Lane;

            using namespace std;
            using namespace core::base;
            using namespace scenario;

            LaneModel::LaneModel() :
                    m_lane(NULL),
                    m_laneAttribute(),
                    m_type(LaneModel::ARC),
                    m_listOfTrafficControls(),
                    m_listOfConnectors() {}

            LaneModel::LaneModel(const LaneModel &obj) :
                    SerializableData(),
                    m_lane(obj.getLane()),
                    m_laneAttribute(obj.getLaneAttribute()),
                    m_type(obj.getType()),
                    m_listOfTrafficControls(),
                    m_listOfConnectors() {
                // Clean up.
                cleanUp();

                // Create deep copy.
                deepCopy(obj);
            }

            LaneModel::~LaneModel() {
                // Clean up.
                cleanUp();
            }

            LaneModel& LaneModel::operator=(const LaneModel &obj) {
                // Clean up.
                cleanUp();

                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void LaneModel::deepCopy(const LaneModel &obj) {
                const vector<TrafficControl*>& listOfTrafficControls = obj.getListOfTrafficControls();
                vector<TrafficControl*>::const_iterator it = listOfTrafficControls.begin();
                while (it != listOfTrafficControls.end()) {
                    TrafficControl *tc = (*it++);

                    switch (tc->getType()) {
                    case TrafficControl::TRAFFICLIGHT: {
                            TrafficLight *tl = new TrafficLight(*(dynamic_cast<TrafficLight*>(tc)));
                            addTrafficControl(tl);
                            break;
                        }
                    case TrafficControl::TRAFFICSIGN: {
                            TrafficSign *ts = new TrafficSign(*(dynamic_cast<TrafficSign*>(tc)));
                            addTrafficControl(ts);
                            break;
                        }
                    }
                }

                const vector<Connector>& listOfConnectors = obj.getListOfConnectors();
                vector<Connector>::const_iterator jt = listOfConnectors.begin();
                while (jt != listOfConnectors.end()) {
                    addConnector((*jt++));
                }
            }

            void LaneModel::cleanUp() {
                vector<TrafficControl*>::iterator it = m_listOfTrafficControls.begin();
                while (it != m_listOfTrafficControls.end()) {
                    TrafficControl *tc = (*it++);
                    OPENDAVINCI_CORE_DELETE_POINTER(tc);
                }
                m_listOfTrafficControls.clear();

                m_listOfConnectors.clear();
            }

            void LaneModel::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_laneAttribute.accept(visitor);

                vector<TrafficControl*>::iterator it = m_listOfTrafficControls.begin();
                while (it != m_listOfTrafficControls.end()) {
                    TrafficControl *tc = (*it++);
                    if (tc != NULL) {
                        tc->accept(visitor);
                    }
                }

                vector<Connector>::iterator jt = m_listOfConnectors.begin();
                while (jt != m_listOfConnectors.end()) {
                    (*jt++).accept(visitor);
                }
            }

            const LaneAttribute& LaneModel::getLaneAttribute() const {
                return m_laneAttribute;
            }

            void LaneModel::setLaneAttribute(const LaneAttribute &la) {
                m_laneAttribute = la;
            }

            enum LaneModel::LANEMODELTYPE LaneModel::getType() const {
                return m_type;
            }

            void LaneModel::setType(const enum LaneModel::LANEMODELTYPE  &type) {
                m_type = type;
            }

            const vector<TrafficControl*>& LaneModel::getListOfTrafficControls() const {
                return m_listOfTrafficControls;
            }

            void LaneModel::addTrafficControl(TrafficControl *c) {
                if (c != NULL) {
                    m_listOfTrafficControls.push_back(c);
                }
            }

            const vector<Connector>& LaneModel::getListOfConnectors() const {
                return m_listOfConnectors;
            }

            void LaneModel::addConnector(const Connector &c) {
                m_listOfConnectors.push_back(c);
            }

            void LaneModel::setLane(const Lane *l) {
                m_lane = l;
            }

            const Lane* LaneModel::getLane() const {
                return m_lane;
            }

            int32_t LaneModel::getID() const {
                return 841;
            }

            const string LaneModel::getShortName() const {
                return "LaneModel";
            }

            const string LaneModel::getLongName() const {
                return "hesperia.data.scenario.LaneModel";
            }

            const string LaneModel::toString() const {
                stringstream s;
                s << "Type: " << getType() << " with " << static_cast<uint32_t>(m_listOfConnectors.size()) << " connectors and " << static_cast<uint32_t>(m_listOfTrafficControls.size()) << " traffic controls, attributes: " << getLaneAttribute().toString();
                return s.str();
            }

            ostream& LaneModel::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('l', 'a', 't', 't', 'r') >::RESULT,
                        getLaneAttribute());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
                        static_cast<uint32_t>(m_type));

                // Serialize traffic controls.
                uint32_t numberOfTrafficControls = 0;
                vector<TrafficControl*>::const_iterator it = m_listOfTrafficControls.begin();
                while (it != m_listOfTrafficControls.end()) {
                    TrafficControl *tc = (*it++);
                    if (tc != NULL) {
                        numberOfTrafficControls++;
                    }
                }
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 't', 'r', 'a', 'f', 'c') >::RESULT,
                        numberOfTrafficControls);

                // Write traffic controls to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < m_listOfTrafficControls.size(); i++) {
                    TrafficControl *tc = m_listOfTrafficControls.at(i);
                    if (tc != NULL) {
                        // Write data to stringstream.
                        sstr << static_cast<uint32_t>(tc->getType())
                        << *tc
                        << endl;
                    }
                }

                // Write traffic controls.
                if (numberOfTrafficControls > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('t', 'r', 'a', 'f', 'c', 's') >::RESULT,
                            sstr.str());
                }

                // Serialize connectors.
                uint32_t numberOfConnectors = static_cast<uint32_t>(m_listOfConnectors.size());
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'c', 'o', 'n', 'n', 's') >::RESULT,
                        numberOfConnectors);

                // Write connectors to stringstream.
                sstr.str("");
                for (uint32_t i = 0; i < numberOfConnectors; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfConnectors.at(i);
                }

                // Write lanes.
                if (numberOfConnectors > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('c', 'o', 'n', 'n') >::RESULT,
                            sstr.str());
                }

                return out;
            }

            istream& LaneModel::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                // Clean up.
                cleanUp();

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('l', 'a', 't', 't', 'r') >::RESULT,
                       m_laneAttribute);

                uint32_t type = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
                       type);

                m_type = static_cast<enum LaneModel::LANEMODELTYPE>(type);

                // Deserialize traffic controls.
                uint32_t numberOfTrafficControls = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 't', 'r', 'a', 'f', 'c') >::RESULT,
                       numberOfTrafficControls);

                if (numberOfTrafficControls > 0) {
                    string str;
                    // Read traffic controls into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('t', 'r', 'a', 'f', 'c', 's') >::RESULT,
                           str);

                    stringstream sstr(str);

                    // Read traffic controls from stringstream.
                    for (uint32_t i = 0; i < numberOfTrafficControls; i++) {
                        type = 0;
                        sstr >> type;
                        enum TrafficControl::TRAFFICCONTROLTYPE trafficControlType = static_cast<enum TrafficControl::TRAFFICCONTROLTYPE>(type);

                        switch (trafficControlType) {
                        case TrafficControl::TRAFFICLIGHT: {
                                TrafficLight *tl = new TrafficLight();

                                sstr >> *tl;

                                addTrafficControl(tl);
                                break;
                            }
                        case TrafficControl::TRAFFICSIGN: {
                                TrafficSign *ts = new TrafficSign();

                                sstr >> *ts;

                                addTrafficControl(ts);
                                break;
                            }
                        }
                    }
                }

                // Deserialize connectors.
                uint32_t numberOfConnectors = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'c', 'o', 'n', 'n', 's') >::RESULT,
                       numberOfConnectors);

                if (numberOfConnectors > 0) {
                    string str;
                    // Read connectors into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('c', 'o', 'n', 'n') >::RESULT,
                           str);

                    stringstream sstr(str);

                    // Read connectors from stringstream.
                    for (uint32_t i = 0; i < numberOfConnectors; i++) {
                        Connector c;
                        sstr >> c;
                        addConnector(c);
                    }
                }

                return in;
            }

        }
    }
} // hesperia::data::scenario
