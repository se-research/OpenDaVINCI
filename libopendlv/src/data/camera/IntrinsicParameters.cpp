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

#include <sstream>
#include <string>

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/camera/IntrinsicParameters.h"
#include "opendlv/data/environment/Point3.h"

namespace opendlv {
    namespace data {
        namespace camera {

            using namespace std;

            using namespace odcore::base;
            using namespace opendlv::data::environment;

            IntrinsicParameters::IntrinsicParameters() :
                    m_principlePoint(),
                    m_focalLength(),
                    m_focalDistance(0),
                    m_alpha(0) {}

            IntrinsicParameters::IntrinsicParameters(const IntrinsicParameters &obj) :
                    m_principlePoint(obj.getPrinciplePoint()),
                    m_focalLength(obj.getFocalLength()),
                    m_focalDistance(obj.getFocalDistance()),
                    m_alpha(obj.getAlpha()) {}

            IntrinsicParameters::~IntrinsicParameters() {}

            IntrinsicParameters& IntrinsicParameters::operator=(const IntrinsicParameters &obj) {
                setPrinciplePoint(obj.getPrinciplePoint());
                setFocalLength(obj.getFocalLength());
                setFocalDistance(obj.getFocalDistance());
                setAlpha(obj.getAlpha());

                return (*this);
            }

            const Point3 IntrinsicParameters::getPrinciplePoint() const {
                return m_principlePoint;
            }

            void IntrinsicParameters::setPrinciplePoint(const Point3 &principlePoint) {
                m_principlePoint = principlePoint;

                // Enforce two-dimensional point by setting z-component to 0.
                m_principlePoint.setZ(0);
            }

            const Point3 IntrinsicParameters::getFocalLength() const {
                return m_focalLength;
            }

            void IntrinsicParameters::setFocalLength(const Point3 &focalLength) {
                m_focalLength = focalLength;

                // Enforce two-dimensional point by setting z-component to 0.
                m_focalLength.setZ(0);
            }

            double IntrinsicParameters::getFocalDistance() const {
                return m_focalDistance;
            }

            void IntrinsicParameters::setFocalDistance(const double &focalDistance) {
                m_focalDistance = focalDistance;
            }

            double IntrinsicParameters::getAlpha() const {
                return m_alpha;
            }

            void IntrinsicParameters::setAlpha(const double &alpha) {
                m_alpha = alpha;
            }

            ostream& IntrinsicParameters::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('p', 'r', 'i', 'n', 'c', 'i', 'p', 'l') >::RESULT,
                        m_principlePoint);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('f', 'o', 'c', 'a', 'l', 'l', 'e', 'n') >::RESULT,
                        m_focalLength);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('f', 'o', 'c', 'd', 'i', 's', 't') >::RESULT,
                        m_focalDistance);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('a', 'l', 'p', 'h', 'a') >::RESULT,
                        m_alpha);

                return out;
            }

            istream& IntrinsicParameters::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('p', 'r', 'i', 'n', 'c', 'i', 'p', 'l') >::RESULT,
                       m_principlePoint);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('f', 'o', 'c', 'a', 'l', 'l', 'e', 'n') >::RESULT,
                       m_focalLength);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('f', 'o', 'c', 'd', 'i', 's', 't') >::RESULT,
                       m_focalDistance);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('a', 'l', 'p', 'h', 'a') >::RESULT,
                       m_alpha);

                return in;
            }

            const string IntrinsicParameters::toString() const {
                stringstream sstr;
                sstr << "principle point = " << m_principlePoint.toString() << ", focal length = " << m_focalLength.toString() << ", focal distance = " << m_focalDistance << ", alpha = " << m_alpha;
                return sstr.str();
            }

        }
    }
} // core::data::camera
