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

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendlv/data/scenario/BoundingBox.h"
#include "opendlv/data/scenario/ComplexModel.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Shape.h"
#include "opendlv/data/scenario/Vertex3.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            ComplexModel::ComplexModel() :
                    m_modelFile(""),
                    m_position(),
                    m_rotation(),
                    m_boundingBox() {
                Shape::setType(Shape::COMPLEXMODEL);
            }

            ComplexModel::ComplexModel(const ComplexModel &obj) :
                    Shape(obj),
                    m_modelFile(obj.m_modelFile),
                    m_position(obj.m_position),
                    m_rotation(obj.m_rotation),
                    m_boundingBox(obj.m_boundingBox) {}

            ComplexModel::~ComplexModel() {}

            ComplexModel& ComplexModel::operator=(const ComplexModel &obj) {
                Shape::operator=(obj);
                setModelFile(obj.getModelFile());
                setPosition(obj.getPosition());
                setRotation(obj.getRotation());
                setBoundingBox(obj.getBoundingBox());
                return (*this);
            }

            void ComplexModel::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_position.accept(visitor);
                m_rotation.accept(visitor);
                m_boundingBox.accept(visitor);
            }

            const string ComplexModel::getModelFile() const {
                return m_modelFile;
            }

            void ComplexModel::setModelFile(const string &modelFile) {
                m_modelFile = modelFile;
            }

            const Vertex3& ComplexModel::getPosition() const {
                return m_position;
            }

            void ComplexModel::setPosition(const Vertex3 &position) {
                m_position = position;
            }

            const Vertex3& ComplexModel::getRotation() const {
                return m_rotation;
            }

            void ComplexModel::setRotation(const Vertex3 &rotation) {
                m_rotation = rotation;
            }

            const BoundingBox& ComplexModel::getBoundingBox() const {
                return m_boundingBox;
            }

            void ComplexModel::setBoundingBox(const BoundingBox &bb) {
                m_boundingBox = bb;
            }

            int32_t ComplexModel::getID() const {
                return 829;
            }

            const string ComplexModel::getShortName() const {
                return "ComplexModel";
            }

            const string ComplexModel::getLongName() const {
                return "hesperia.data.scenario.ComplexModel";
            }

            const string ComplexModel::toString() const {
                stringstream s;
                s << Shape::toString() << ", Modelfile: '" << m_modelFile << "', Position: " << m_position.toString() << ", Rotation:" << m_rotation.toString() << ", BoundingBox: " << m_boundingBox.toString();
                return s.str();
            }

            ostream& ComplexModel::operator<<(ostream &out) const {
                // Serializer super class.
                Shape::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_modelFile);

                s->write(2, m_position);

                s->write(3, m_rotation);

                s->write(4, m_boundingBox);

                return out;
            }

            istream& ComplexModel::operator>>(istream &in) {
                // Deserializer super class.
                Shape::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_modelFile);

                d->read(2, m_position);

                d->read(3, m_rotation);

                d->read(4, m_boundingBox);

                return in;
            }

        }
    }
} // opendlv::data::scenario
