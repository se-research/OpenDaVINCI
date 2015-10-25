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

#include "core/macros.h"
#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/scenario/Arc.h"
#include "hesperia/data/scenario/Clothoid.h"
#include "hesperia/data/scenario/Lane.h"
#include "hesperia/data/scenario/PointModel.h"
#include "hesperia/data/scenario/StraightLine.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;
            using namespace scenario;

            Lane::Lane() :
                    m_id(0),
                    m_road(NULL),
                    m_laneModel(NULL) {}

            Lane::Lane(const Lane &obj) :
                    SerializableData(),
                    m_id(obj.getID()),
                    m_road(obj.getRoad()),
                    m_laneModel(NULL) {
                // Create deep copy.
                deepCopy(obj);
            }

            Lane::~Lane() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_laneModel);
            }

            Lane& Lane::operator=(const Lane &obj) {
                setID(obj.getID());
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

            uint32_t Lane::getID() const {
                return m_id;
            }

            void Lane::setID(const uint32_t &id) {
                m_id = id;
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

            const string Lane::toString() const {
                stringstream s;
                s << "ID: " << getID();
                return s.str();
            }

            ostream& Lane::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        getID());

                // Check if we have to serialize a lane model.
                bool hasLaneModel = (getLaneModel() != NULL);
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('h', 'a', 's', 'l', 'a', 'm', 'd') >::RESULT,
                        hasLaneModel);

                if (hasLaneModel) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('l', 'a', 'n', 'e', 'm', 'd', 'l') >::RESULT,
                            static_cast<uint32_t>(getLaneModel()->getType()));

                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', 'o', 'd', 'e', 'l') >::RESULT,
                            *getLaneModel());
                }

                return out;
            }

            istream& Lane::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                OPENDAVINCI_CORE_DELETE_POINTER(m_laneModel);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_id);

                // Check if we have to deserialize a lane model.
                bool hasLaneModel = false;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('h', 'a', 's', 'l', 'a', 'm', 'd') >::RESULT,
                       hasLaneModel);

                if (hasLaneModel) {
                    uint32_t type = 0;
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('l', 'a', 'n', 'e', 'm', 'd', 'l') >::RESULT,
                           type);

                    enum LaneModel::LANEMODELTYPE laneModelType = static_cast<enum LaneModel::LANEMODELTYPE>(type);
                    switch (laneModelType) {
                    case LaneModel::ARC: {
                            Arc *a = new Arc();

                            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', 'o', 'd', 'e', 'l') >::RESULT,
                                   *a);

                            setLaneModel(a);
                            break;
                        }
                    case LaneModel::CLOTHOID: {
                            Clothoid *c = new Clothoid();

                            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', 'o', 'd', 'e', 'l') >::RESULT,
                                   *c);

                            setLaneModel(c);
                            break;
                        }
                    case LaneModel::POINTMODEL: {
                            PointModel *pm = new PointModel();

                            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', 'o', 'd', 'e', 'l') >::RESULT,
                                   *pm);

                            setLaneModel(pm);
                            break;
                        }
                    case LaneModel::STRAIGHTLINE: {
                            StraightLine *sl = new StraightLine();

                            d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', 'o', 'd', 'e', 'l') >::RESULT,
                                   *sl);

                            setLaneModel(sl);
                            break;
                        }
                    }
                }

                return in;
            }

        }
    }
} // hesperia::data::scenario
