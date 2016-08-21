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

#include <istream>
#include <memory>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendlv/data/situation/Behavior.h"
#include "opendlv/data/situation/Immediately.h"
#include "opendlv/data/situation/OnEnteringPolygon.h"
#include "opendlv/data/situation/OnMoving.h"
#include "opendlv/data/situation/PointID.h"
#include "opendlv/data/situation/PointIDDriver.h"
#include "opendlv/data/situation/ReturnToStart.h"
#include "opendlv/data/situation/SituationVisitor.h"
#include "opendlv/data/situation/StartType.h"
#include "opendlv/data/situation/Stop.h"
#include "opendlv/data/situation/StopType.h"
#include "opendlv/data/situation/WarpToStart.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;

            PointIDDriver::PointIDDriver() :
                    Behavior(),
                    m_startType(NULL),
                    m_stopType(NULL),
                    m_constantAcceleration(0),
                    m_constantVelocity(0),
					m_listOfPointIDs() {
                setType(Behavior::POINTIDDRIVER);
            }

            PointIDDriver::PointIDDriver(const PointIDDriver &obj) :
                    Behavior(obj),
                    m_startType(NULL),
                    m_stopType(NULL),
                    m_constantAcceleration(obj.getConstantAcceleration()),
                    m_constantVelocity(obj.getConstantVelocity()),
					m_listOfPointIDs() {
                // Clean up.
                cleanUp();

                // Create deep copy.
                deepCopy(obj);
            }

            PointIDDriver::~PointIDDriver() {
                // Clean up.
                cleanUp();
            }

            PointIDDriver& PointIDDriver::operator=(const PointIDDriver &obj) {
                Behavior::operator=(obj);
                setConstantAcceleration(obj.getConstantAcceleration());
                setConstantVelocity(obj.getConstantVelocity());

                // Clean up.
                cleanUp();

                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void PointIDDriver::deepCopy(const PointIDDriver &obj) {
                StartType *start = obj.getStartType();
                if (start != NULL) {
                    switch (start->getType()) {
                    case StartType::IMMEDIATELY: {
                            Immediately *i = new Immediately(dynamic_cast<Immediately&>(*start));
                            setStartType(i);
                            break;
                        }
                    case StartType::ONMOVING: {
                            OnMoving *om = new OnMoving(dynamic_cast<OnMoving&>(*start));
                            setStartType(om);
                            break;
                        }
                    case StartType::ONENTERINGPOLYGON: {
                            OnEnteringPolygon *oep = new OnEnteringPolygon(dynamic_cast<OnEnteringPolygon&>(*start));
                            setStartType(oep);
                            break;
                        }
                    case StartType::UNDEFINED:
                        break;
                    }
                }

                StopType *stop = obj.getStopType();
                if (stop != NULL) {
                    switch (stop->getType()) {
                    case StopType::STOP: {
                            Stop *s = new Stop(dynamic_cast<Stop&>(*stop));
                            setStopType(s);
                            break;
                        }
                    case StopType::RETURNTOSTART: {
                            ReturnToStart *rts = new ReturnToStart(dynamic_cast<ReturnToStart&>(*stop));
                            setStopType(rts);
                            break;
                        }
                    case StopType::WARPTOSTART: {
                            WarpToStart *wts = new WarpToStart(dynamic_cast<WarpToStart&>(*stop));
                            setStopType(wts);
                            break;
                        }
                    case StopType::UNDEFINED:
                        break;
                    }
                }

                m_listOfPointIDs.clear();
                m_listOfPointIDs = obj.getListOfPointIDs();
            }

            void PointIDDriver::cleanUp() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_startType);
                OPENDAVINCI_CORE_DELETE_POINTER(m_stopType);
            }

            void PointIDDriver::accept(SituationVisitor &visitor) {
                visitor.visit(*this);

                if (getStartType() != NULL) {
                    getStartType()->accept(visitor);
                }
                if (getStopType() != NULL) {
                    getStopType()->accept(visitor);
                }
            }

            StartType* PointIDDriver::getStartType() const {
                return m_startType;
            }

            void PointIDDriver::setStartType(StartType *st) {
                m_startType = st;
            }

            StopType* PointIDDriver::getStopType() const {
                return m_stopType;
            }

            void PointIDDriver::setStopType(StopType *st) {
                m_stopType = st;
            }

            double PointIDDriver::getConstantAcceleration() const {
                return m_constantAcceleration;
            }

            void PointIDDriver::setConstantAcceleration(const double &a) {
                m_constantAcceleration = a;
            }

            double PointIDDriver::getConstantVelocity() const {
                return m_constantVelocity;
            }

            void PointIDDriver::setConstantVelocity(const double &v) {
                m_constantVelocity = v;
            }

            void PointIDDriver::addPointID(const PointID &p) {
            	m_listOfPointIDs.push_back(p);
            }

            vector<PointID> PointIDDriver::getListOfPointIDs() const {
            	return m_listOfPointIDs;
            }

            int32_t PointIDDriver::getID() const {
                return 865;
            }

            const string PointIDDriver::getShortName() const {
                return "PointIDDriver";
            }

            const string PointIDDriver::getLongName() const {
                return "hesperia.data.situation.PointIDDriver";
            }

            const string PointIDDriver::toString() const {
                stringstream s;
                s << "Type: " << getType() << ", start type: " << ((getStartType() != NULL) ? getStartType()->toString() : "" ) << ", stop type: " << ((getStopType() != NULL) ? getStopType()->toString() : "" ) << ", constant acceleration: " << getConstantAcceleration() << ", constant velocity: " << getConstantVelocity();

                vector<PointID>::const_iterator it = m_listOfPointIDs.begin();
                while (it != m_listOfPointIDs.end()) {
                	s << ", " << (*it).toString();
                	it++;
                }

                return s.str();
            }

            ostream& PointIDDriver::operator<<(ostream &out) const {
                // Serializer super class.
                Behavior::operator<<(out);

                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, (m_startType != NULL));

                if (m_startType != NULL) {
                    // Write data to stringstream.
                    stringstream sstr;
                    sstr << static_cast<uint32_t>(m_startType->getType())
                    << *m_startType;

                    s->write(2, sstr.str());
                }

                s->write(3, (m_stopType != NULL));

                if (m_stopType != NULL) {
                    // Write data to stringstream.
                    stringstream sstr;
                    sstr << static_cast<uint32_t>(m_stopType->getType())
                    << *m_stopType;

                    s->write(4, sstr.str());
                }

                s->write(5, m_constantAcceleration);

                s->write(6, m_constantVelocity);

                uint32_t numberOfPointIDs = static_cast<uint32_t>(m_listOfPointIDs.size());
                s->write(7, numberOfPointIDs);

                // Write PointIDs to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfPointIDs; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfPointIDs.at(i);
                }

                // Write PointIDs.
                if (numberOfPointIDs > 0) {
                    s->write(8, sstr.str());
                }

                return out;
            }

            istream& PointIDDriver::operator>>(istream &in) {
                // Deserializer super class.
                Behavior::operator>>(in);

                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                bool hasStartType = false;
                d->read(1, hasStartType);

                if (hasStartType) {
                    string str;
                    // Read shapes into stringstream.
                    d->read(2, str);

                    stringstream sstr(str);

                    // Read shape from stringstream.
                    uint32_t type = 0;
                    sstr >> type;
                    enum StartType::STARTTYPE startType = static_cast<enum StartType::STARTTYPE>(type);

                    switch (startType) {
                    case StartType::IMMEDIATELY: {
                            Immediately *i = new Immediately();
                            sstr >> *i;
                            setStartType(i);
                            break;
                        }
                    case StartType::ONMOVING: {
                            OnMoving *om = new OnMoving();
                            sstr >> *om;
                            setStartType(om);
                            break;
                        }
                    case StartType::ONENTERINGPOLYGON: {
                            OnEnteringPolygon *oep = new OnEnteringPolygon();
                            sstr >> *oep;
                            setStartType(oep);
                            break;
                        }
                    case StartType::UNDEFINED:
                        break;
                    }
                }

                bool hasStopType = false;
                d->read(3, hasStopType);

                if (hasStopType) {
                    string str;
                    // Read shapes into stringstream.
                    d->read(4, str);

                    stringstream sstr(str);

                    // Read shape from stringstream.
                    uint32_t type = 0;
                    sstr >> type;
                    enum StopType::STOPTYPE stopType = static_cast<enum StopType::STOPTYPE>(type);

                    switch (stopType) {
                    case StopType::STOP: {
                            Stop *stop = new Stop();
                            sstr >> *stop;
                            setStopType(stop);
                            break;
                        }
                    case StopType::RETURNTOSTART: {
                            ReturnToStart *rts = new ReturnToStart();
                            sstr >> *rts;
                            setStopType(rts);
                            break;
                        }
                    case StopType::WARPTOSTART: {
                            WarpToStart *wts = new WarpToStart();
                            sstr >> *wts;
                            setStopType(wts);
                            break;
                        }
                    case StopType::UNDEFINED:
                        break;
                    }
                }

                d->read(5, m_constantAcceleration);

                d->read(6, m_constantVelocity);

                uint32_t numberOfPointIDs = 0;
                d->read(7, numberOfPointIDs);

                if (numberOfPointIDs > 0) {
                    string str;
                    // Read identifiable vertices into stringstream.
                    d->read(8, str);

                    stringstream sstr(str);

                    // Read PointIDs from stringstream.
                    for (uint32_t i = 0; i < numberOfPointIDs; i++) {
                        PointID pid;
                        sstr >> pid;
                        addPointID(pid);
                    }
                }

                return in;
            }

        }
    }
} // opendlv::data::situation
