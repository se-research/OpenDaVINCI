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
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/Arc.h"
#include "opendlv/data/scenario/Clothoid.h"
#include "opendlv/data/scenario/Lane.h"
#include "opendlv/data/scenario/LaneModel.h"
#include "opendlv/data/scenario/PointModel.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/StraightLine.h"

namespace opendlv {
    namespace data {
        namespace scenario {

class Road;

            using namespace std;
            using namespace odcore::base;
            using namespace scenario;

            Lane::Lane() :
                    m_identifier(0),
                    m_road(NULL),
                    m_laneModel(NULL) {}

            Lane::Lane(const Lane &obj) :
                    SerializableData(),
                    m_identifier(obj.getIdentifier()),
                    m_road(obj.getRoad()),
                    m_laneModel(NULL) {
                // Create deep copy.
                deepCopy(obj);
            }

            Lane::~Lane() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_laneModel);
            }

            Lane& Lane::operator=(const Lane &obj) {
                setIdentifier(obj.getIdentifier());
                setRoad(obj.getRoad());

                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void Lane::deepCopy(const Lane &obj) {
                OPENDAVINCI_CORE_DELETE_POINTER(m_laneModel);

                if (obj.getLaneModel() != NULL) {
                    switch (obj.getLaneModel()->getType()) {
                    case LaneModel::ARC: {
                            setLaneModel(new Arc(*(dynamic_cast<Arc*>(obj.getLaneModel()))));
                            break;
                        }
                    case LaneModel::CLOTHOID: {
                            setLaneModel(new Clothoid(*(dynamic_cast<Clothoid*>(obj.getLaneModel()))));
                            break;
                        }
                    case LaneModel::POINTMODEL: {
                            setLaneModel(new PointModel(*(dynamic_cast<PointModel*>(obj.getLaneModel()))));
                            break;
                        }
                    case LaneModel::STRAIGHTLINE: {
                            setLaneModel(new StraightLine(*(dynamic_cast<StraightLine*>(obj.getLaneModel()))));
                            break;
                        }
                    }
                }
            }

            void Lane::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                if (m_laneModel != NULL) {
                    m_laneModel->accept(visitor);
                }
            }

            uint32_t Lane::getIdentifier() const {
                return m_identifier;
            }

            void Lane::setIdentifier(const uint32_t &id) {
                m_identifier = id;
            }

            LaneModel* Lane::getLaneModel() const {
                return m_laneModel;
            }

            void Lane::setLaneModel(LaneModel *lm) {
                if (lm != NULL) {
                    lm->setLane(this);
                }
                m_laneModel = lm;
            }

            void Lane::setRoad(const Road *r) {
                m_road = r;
            }

            const Road* Lane::getRoad() const {
                return m_road;
            }

            int32_t Lane::getID() const {
                return 831;
            }

            const string Lane::getShortName() const {
                return "Lane";
            }

            const string Lane::getLongName() const {
                return "hesperia.data.scenario.Lane";
            }

            const string Lane::toString() const {
                stringstream s;
                s << "ID: " << getIdentifier();
                return s.str();
            }

            ostream& Lane::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getIdentifier());

                // Check if we have to serialize a lane model.
                bool hasLaneModel = (getLaneModel() != NULL);
                s->write(2, hasLaneModel);

                if (hasLaneModel) {
                    s->write(3, static_cast<uint32_t>(getLaneModel()->getType()));

                    s->write(4, *getLaneModel());
                }

                return out;
            }

            istream& Lane::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                OPENDAVINCI_CORE_DELETE_POINTER(m_laneModel);

                d->read(1, m_identifier);

                // Check if we have to deserialize a lane model.
                bool hasLaneModel = false;
                d->read(2, hasLaneModel);

                if (hasLaneModel) {
                    uint32_t type = 0;
                    d->read(3, type);

                    enum LaneModel::LANEMODELTYPE laneModelType = static_cast<enum LaneModel::LANEMODELTYPE>(type);
                    switch (laneModelType) {
                    case LaneModel::ARC: {
                            Arc *a = new Arc();

                            d->read(4, *a);

                            setLaneModel(a);
                            break;
                        }
                    case LaneModel::CLOTHOID: {
                            Clothoid *c = new Clothoid();

                            d->read(4, *c);

                            setLaneModel(c);
                            break;
                        }
                    case LaneModel::POINTMODEL: {
                            PointModel *pm = new PointModel();

                            d->read(4, *pm);

                            setLaneModel(pm);
                            break;
                        }
                    case LaneModel::STRAIGHTLINE: {
                            StraightLine *sl = new StraightLine();

                            d->read(4, *sl);

                            setLaneModel(sl);
                            break;
                        }
                    }
                }

                return in;
            }

        }
    }
} // opendlv::data::scenario
