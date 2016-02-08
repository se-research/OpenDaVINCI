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

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"
#include "opendavinci/core/data/SerializableData.h"
#include "hesperia/data/scenario/Ground.h"
#include "hesperia/data/scenario/HeightImage.h"
#include "hesperia/data/scenario/Image.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/Surroundings.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;

            Ground::Ground() :
                    m_name(""),
                    m_aerialImage(),
                    m_heightImage(),
                    m_surroundings() {}

            Ground::Ground(const Ground &obj) :
                    SerializableData(),
                    m_name(obj.m_name),
                    m_aerialImage(obj.m_aerialImage),
                    m_heightImage(obj.m_heightImage),
                    m_surroundings(obj.m_surroundings) {}

            Ground::~Ground() {}

            Ground& Ground::operator=(const Ground &obj) {
                setName(obj.getName());
                setAerialImage(obj.getAerialImage());
                setHeightImage(obj.getHeightImage());
                setSurroundings(obj.getSurroundings());
                return (*this);
            }

            void Ground::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_aerialImage.accept(visitor);
                m_heightImage.accept(visitor);
                m_surroundings.accept(visitor);
            }

            const string Ground::getName() const {
                return m_name;
            }

            void Ground::setName(const string &name) {
                m_name = name;
            }

            const Image& Ground::getAerialImage() const {
                return m_aerialImage;
            }

            void Ground::setAerialImage(const Image &ai) {
                m_aerialImage = ai;
            }

            const HeightImage& Ground::getHeightImage() const {
                return m_heightImage;
            }

            void Ground::setHeightImage(const HeightImage &hi) {
                m_heightImage = hi;
            }

            const Surroundings& Ground::getSurroundings() const {
                return m_surroundings;
            }

            void Ground::setSurroundings(const Surroundings &s) {
                m_surroundings = s;
            }

            const string Ground::toString() const {
                stringstream s;
                s << "Ground's name: " << m_name;
                return s.str();
            }

            ostream& Ground::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                        m_name);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('a', 'e', 'r', 'i', 'a', 'l') >::RESULT,
                        m_aerialImage);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'i', 'g', 'h', 't') >::RESULT,
                        m_heightImage);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('s', 'u', 'r', 'r', 'o', 'u', 'n', 'd') >::RESULT,
                        m_surroundings);

                return out;
            }

            istream& Ground::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                       m_name);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('a', 'e', 'r', 'i', 'a', 'l') >::RESULT,
                       m_aerialImage);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'i', 'g', 'h', 't') >::RESULT,
                       m_heightImage);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('s', 'u', 'r', 'r', 'o', 'u', 'n', 'd') >::RESULT,
                       m_surroundings);

                return in;
            }

        }
    }
} // hesperia::data::scenario
