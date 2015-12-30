/**
 * hesperia - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <cmath>
#include <istream>
#include <string>

#include "core/platform.h"
#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/data/SerializableData.h"
#include "core/strings/StringToolbox.h"
#include "generated/cartesian/Constants.h"
#include "generated/cartesian/Matrix3x3.h"
#include "hesperia/data/environment/Point3.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace core::base;
            using namespace core::data;

            const double Point3::EPSILON = 1e-7;

            Point3::Point3() :
                    m_x(0),
                    m_y(0),
                    m_z(0) {}

            Point3::Point3(const double &x, const double &y, const double &z) :
                    m_x(x),
                    m_y(y),
                    m_z(z) {}

            Point3::Point3(const string &s) :
                    m_x(0),
                    m_y(0),
                    m_z(0) {
                string trimmedString(s);
                core::strings::StringToolbox::trim(trimmedString);
                stringstream sstr(trimmedString);
                char ignore;

                sstr >> ignore; // '('
                sstr >> m_x;

                sstr >> ignore; // ';'
                sstr >> m_y;

                sstr >> ignore; // ';'
                sstr >> m_z;
            }

            Point3::Point3(const Point3 &obj) :
                    SerializableData(),
                    m_x(obj.m_x),
                    m_y(obj.m_y),
                    m_z(obj.m_z) {}

            Point3::~Point3() {}

            Point3& Point3::operator=(const Point3 &obj) {
                m_x = obj.m_x;
                m_y = obj.m_y;
                m_z = obj.m_z;

                return (*this);
            }

            double Point3::getX() const {
                return m_x;
            }

            void Point3::setX(const double &x) {
                m_x = x;
            }

            double Point3::getY() const {
                return m_y;
            }

            void Point3::setY(const double &y) {
                m_y = y;
            }

            double Point3::getZ() const {
                return m_z;
            }

            void Point3::setZ(const double &z) {
                m_z = z;
            }

            Point3 Point3::operator+(const Point3 &other) const {
                Point3 cc(getX() + other.getX(),
                          getY() + other.getY(),
                          getZ() + other.getZ());

                return cc;
            }

            Point3& Point3::operator+=(const Point3 &other) {
                m_x += other.getX();
                m_y += other.getY();
                m_z += other.getZ();
                return (*this);
            }

            Point3 Point3::operator-(const Point3 &other) const {
                Point3 cc(getX() - other.getX(),
                          getY() - other.getY(),
                          getZ() - other.getZ());

                return cc;
            }

            Point3& Point3::operator-=(const Point3 &other) {
                m_x -= other.getX();
                m_y -= other.getY();
                m_z -= other.getZ();
                return (*this);
            }

            Point3 Point3::operator*(const double &a) const {
                Point3 cc(getX() * a,
                          getY() * a,
                          getZ() * a);

                return cc;
            }

            Point3& Point3::operator*=(const double &a) {
                m_x *= a;
                m_y *= a;
                m_z *= a;
                return (*this);
            }

/*
            Point3 Point3::operator*(Matrix &m) const {
                const double x = getX() * m.getData()[0] + getY() * m.getData()[1] + getZ() * m.getData()[2];
                const double y = getX() * m.getData()[3] + getY() * m.getData()[4] + getZ() * m.getData()[5];
                const double z = getX() * m.getData()[6] + getY() * m.getData()[7] + getZ() * m.getData()[8];

                Point3 cc(x, y, z);
                return cc;
            }
*/

            Point3 Point3::operator*(const cartesian::Matrix3x3 &m) const {
                const double x = getX() * m.getXX() + getY() * m.getXY() + getZ() * m.getXZ();
                const double y = getX() * m.getYX() + getY() * m.getYY() + getZ() * m.getYZ();
                const double z = getX() * m.getZX() + getY() * m.getZY() + getZ() * m.getZZ();

                Point3 cc(x, y, z);
                return cc;
            }

            Point3& Point3::operator*=(const cartesian::Matrix3x3 &m) {
                Point3 cc = (*this) * m;
                m_x = cc.getX();
                m_y = cc.getY();
                m_z = cc.getZ();
                return (*this);
            }

            double Point3::operator*(const Point3 &other) const {
                return getX()*other.getX() + getY()*other.getY() + getZ()*other.getZ();
            }

            bool Point3::operator==(const Point3 &other) const {
                Point3 cc = (*this) - other;
                return ( fabs(cc.getX()) < Point3::EPSILON ) &&
                       ( fabs(cc.getY()) < Point3::EPSILON ) &&
                       ( fabs(cc.getZ()) < Point3::EPSILON );
            }

            bool Point3::operator!=(const Point3 &other) const {
                return !((*this) == other);
            }

            double Point3::length() const {
                return sqrt(operator*((*this)));
            }

            double Point3::lengthXY() const {
                return sqrt(getX()*getX() + getY()*getY());
            }

            void Point3::normalize() {
                operator*=(1.0 / length());
            }

            void Point3::normalizeXY() {
                m_z = 0;
                normalize();
            }

            Point3& Point3::rotateX(const double &angle) {
                double y = cos(angle) * getY() - sin(angle) * getZ();
                double z = sin(angle) * getY() + cos(angle) * getZ();
                setY(y);
                setZ(z);

                return (*this);
            }

            Point3& Point3::rotateY(const double &angle) {
                double x = cos(angle) * getX() - sin(angle) * getZ();
                double z = sin(angle) * getX() + cos(angle) * getZ();
                setX(x);
                setZ(z);

                return (*this);
            }

            Point3& Point3::rotateZ(const double &angle) {
                double x = cos(angle) * getX() - sin(angle) * getY();
                double y = sin(angle) * getX() + cos(angle) * getY();
                setX(x);
                setY(y);

                return (*this);
            }

            Point3& Point3::rotate(const Point3 direction, const double &angle) {
                const double cosTheta = cos(angle);
                const double sinTheta = sin(angle);
                const double x = direction.getX();
                const double y = direction.getY();
                const double z = direction.getZ();

                Point3 p;
                double newX = (cosTheta + (1 - cosTheta) * x * x) * m_x;
                newX += ((1 - cosTheta) * x * y - z * sinTheta) * m_y;
                newX += ((1 - cosTheta) * x * z + y * sinTheta) * m_z;

                double newY = ((1 - cosTheta) * x * y + z * sinTheta) * m_x;
                newY += (cosTheta + (1 - cosTheta) * y * y) * m_y;
                newY += ((1 - cosTheta) * y * z - x * sinTheta) * m_z;

                double newZ = ((1 - cosTheta) * x * z - y * sinTheta) * m_x;
                newZ += ((1 - cosTheta) * y * z + x * sinTheta) * m_y;
                newZ += (cosTheta + (1 - cosTheta) * z * z) * m_z;

                setX(newX);
                setY(newY);
                setZ(newZ);

                return *this;
            }

            Point3 Point3::cross(const Point3 &other) const {
                Point3 cc(getY()*other.getZ() - getZ()*other.getY(),
                          getZ()*other.getX() - getX()*other.getZ(),
                          getX()*other.getY() - getY()*other.getX());
                return cc;
            }

            double Point3::getAngleXY() const {
                return atan2(getY(), getX());
            }

            double Point3::getSquaredDistanceTo(const Point3 &other) const {
                return (other.getX() - getX())*(other.getX() - getX()) +
                       (other.getY() - getY())*(other.getY() - getY()) +
                       (other.getZ() - getZ())*(other.getZ() - getZ());
            }

            double Point3::getSquaredXYDistanceTo(const Point3 &other) const {
                Point3 cc1(*this);
                cc1.setZ(0);

                Point3 cc2(other);
                cc2.setZ(0);

                return cc1.getSquaredDistanceTo(cc2);
            }

            double Point3::getDistanceTo(const Point3 &other) const {
                return sqrt(getSquaredDistanceTo(other));
            }

            double Point3::getXYDistanceTo(const Point3 &other) const {
                return sqrt(getSquaredXYDistanceTo(other));
            }

            bool Point3::isInFront(const Point3 &p, const double &angleXY) const {
                double angleDelta = (p - *this).getAngleXY() - angleXY;

                // Normalize angle to interval -PI .. PI.
                while (angleDelta < -cartesian::Constants::PI) {
                    angleDelta += 2.0*cartesian::Constants::PI;
                }
                while (angleDelta > cartesian::Constants::PI) {
                    angleDelta -= 2.0*cartesian::Constants::PI;
                }

                return (fabs(angleDelta) < (cartesian::Constants::PI/2.0));
            }

            const string Point3::toString() const {
                stringstream s;
                s << "(" << m_x << "; " << m_y << "; " << m_z << ")";
                return s.str();
            }

            ostream& Point3::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();;

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                stringstream rawData;
                rawData.precision(10);

                rawData << m_x << endl << m_y << endl << m_z;

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                        rawData.str());

                return out;
            }

            istream& Point3::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();;

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                string data;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                       data);

                stringstream rawData;
                rawData.precision(10);
                rawData.str(data);

                rawData >> m_x >> m_y >> m_z;

                return in;
            }

        }
    }
} // hesperia::data::environment
