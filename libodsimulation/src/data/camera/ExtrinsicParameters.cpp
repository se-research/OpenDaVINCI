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

#include <sstream>
#include <string>

#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "generated/cartesian/Matrix3x3.h"
#include "hesperia/data/camera/ExtrinsicParameters.h"
#include "hesperia/data/environment/Point3.h"

namespace hesperia {
    namespace data {
        namespace camera {

            using namespace std;
            using namespace core::base;
            using namespace hesperia::data::environment;

            ExtrinsicParameters::ExtrinsicParameters() :
                    m_translation(),
                    m_rotation() {}

            ExtrinsicParameters::ExtrinsicParameters(const Point3 &translation, const cartesian::Matrix3x3 &rotation) :
                    m_translation(translation),
                    m_rotation(rotation) {}

            ExtrinsicParameters::ExtrinsicParameters(const ExtrinsicParameters &obj) :
                    m_translation(obj.getTranslation()),
                    m_rotation(obj.getRotation()) {}

            ExtrinsicParameters::~ExtrinsicParameters() {}

            ExtrinsicParameters& ExtrinsicParameters::operator=(const ExtrinsicParameters &obj) {
                m_translation = obj.getTranslation();
                m_rotation = obj.getRotation();

                return (*this);
            }

            const Point3 ExtrinsicParameters::getTranslation() const {
                return m_translation;
            }

            void ExtrinsicParameters::setTranslation(const Point3 &translation) {
                m_translation = translation;
            }

            const cartesian::Matrix3x3 ExtrinsicParameters::getRotation() const {
                return m_rotation;
            }

            void ExtrinsicParameters::setRotation(const cartesian::Matrix3x3 &rotation) {
                m_rotation = rotation;
            }

            ostream& ExtrinsicParameters::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('t', 'r', 'a', 'n', 's') >::RESULT,
                        m_translation);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('r', 'o', 't') >::RESULT,
                        m_rotation);

                return out;
            }

            istream& ExtrinsicParameters::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('t', 'r', 'a', 'n', 's') >::RESULT,
                       m_translation);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('r', 'o', 't') >::RESULT,
                       m_rotation);

                return in;
            }

            const string ExtrinsicParameters::toString() const {
                stringstream sstr;
                sstr << "T=" << m_translation.toString() << "/R=" << m_rotation.toString();
                return sstr.str();
            }

        }
    }
} // core::data::camera
