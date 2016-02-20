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

#include <cmath>
#include <sstream>
#include <string>

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"
#include "hesperia/data/environment/Line.h"
#include "hesperia/data/environment/Point3.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace core::base;
            using namespace hesperia::data::environment;

            const double Line::EPSILON = 1e-10;

            Line::Line() :
                m_A(),
                m_B() {}

            Line::Line(const Point3 &A, const Point3 &B) :
                m_A(A),
                m_B(B) {}

            Line::Line(const Line &obj) :
                m_A(obj.m_A),
                m_B(obj.m_B) {}

            Line::~Line() {}

            Line& Line::operator=(const Line &obj) {
                setA(obj.getA());
                setB(obj.getB());

                return (*this);
            }

            Point3 Line::getA() const {
                return m_A;
            }

            void Line::setA(const Point3 &A) {
                m_A = A;
            }

            Point3 Line::getB() const {
                return m_B;
            }

            void Line::setB(const Point3 &B) {
                m_B = B;
            }

            double Line::det(const double &a, const double &b, const double &c, const double &d) const {
                return (a * d - b * c);
            } 

            bool Line::intersectIgnoreZ(const Line &l, Point3 &result) const {
                bool retVal = false;
                Point3 thisA(m_A); thisA.setZ(1);
                Point3 thisB(m_B); thisB.setZ(1);
                Point3 otherA(l.getA()); otherA.setZ(1);
                Point3 otherB(l.getB()); otherB.setZ(1);

                Point3 line1 = thisA.cross(thisB);
                Point3 line2 = otherA.cross(otherB);

                // Compute result by crossing line1 and line2.
                result = line1.cross(line2);

                if (fabs(result.getZ()) < Line::EPSILON) {
                    retVal = false;
                }
                else {
                    result *= 1/result.getZ();
                    result.setZ(0);
                    
                    const double thisDX = thisB.getX() - thisA.getX();
                    const double thisDY = thisB.getY() - thisA.getY();


                    const double det_a = det(otherA.getX() - thisA.getX(), otherA.getY() - thisA.getY(), thisDX, thisDY);
                    const double det_b = det(otherB.getX() - thisA.getX(), otherB.getY() - thisA.getY(), thisDX, thisDY);

                    // Different signs --> line segments intersect.
                    if ( (-1 * det_a > Line::EPSILON && det_b > Line::EPSILON) || (det_a > Line::EPSILON && -1 * det_b > Line::EPSILON) ) {
                        retVal = true;
                    }
                    else {
                        if ( abs(det_a) < Line::EPSILON ) {
                            if ( abs(det_b) < Line::EPSILON ) {
                                // Both cross products are zero.
                                retVal = true;
                            }
                            else if ( (abs(otherB.getX() - otherA.getX()) < Line::EPSILON) && (abs(otherB.getY() - otherA.getY()) < Line::EPSILON) ) {
                                // First cross product and second vector is zero.
                                retVal = true;
                            } 
                        }
                        else if ( abs(det_b) < Line::EPSILON ) {
                            if ( (abs(thisDX) < Line::EPSILON) && (abs(thisDY) < Line::EPSILON) ) {
                                // Second cross product and first vector is zero.
                                retVal = true;
                            } 
                        }
                    }


/*
                    // Check, if the resulting point is within one of both lines.
                    if (   (  ( ((thisA.getX() - result.getX()) < Line::EPSILON) && ((thisB.getX() - result.getX()) > Line::EPSILON) )  // X within line1.
                           || ( ((thisA.getX() - result.getX()) > Line::EPSILON) && ((thisB.getX() - result.getX()) < Line::EPSILON) ) )
                        &&
                           (  ( ((otherA.getX() - result.getX()) < Line::EPSILON) && ((otherB.getX() - result.getX()) > Line::EPSILON) )  // X within line2.
                           || ( ((otherA.getX() - result.getX()) > Line::EPSILON) && ((otherB.getX() - result.getX()) < Line::EPSILON) ) )
                        &&
                           (  ( ((thisA.getY() - result.getY()) < Line::EPSILON) && ((thisB.getY() - result.getY()) > Line::EPSILON) )  // Y within line1.
                           || ( ((thisA.getY() - result.getY()) > Line::EPSILON) && ((thisB.getY() - result.getY()) < Line::EPSILON) ) )
                        &&
                           (  ( ((otherA.getY() - result.getY()) < Line::EPSILON) && ((otherB.getY() - result.getY()) > Line::EPSILON) )  // Y within line2.
                           || ( ((otherA.getY() - result.getY()) > Line::EPSILON) && ((otherB.getY() - result.getY()) < Line::EPSILON) ) )
                      ) {
                        retVal = true;
                    }
*/
                }
                return retVal;
            }

            const Point3 Line::getPerpendicularPoint(const Point3 &p) const {
                Point3 direction = m_B - m_A;
                direction.normalize();

                Point3 AP = p - m_A;
                const double length = direction * AP;

                Point3 result = m_A + (direction * length);
                return result;
            }

            int32_t Line::ID() {
                return 24;
            }

            int32_t Line::getID() const {
                return 24;
            }

            const string Line::getShortName() const {
                return "Line";
            }

            const string Line::getLongName() const {
                return "hesperia.data.environment.Line";
            }

            const string Line::toString() const {
                stringstream sstr;
                sstr << "A: " << m_A.toString() << ", B: " << m_B.toString();
                return sstr.str();
            }

            ostream& Line::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('a') >::RESULT,
                        m_A);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('b') >::RESULT,
                        m_B);

                return out;
            }

            istream& Line::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('a') >::RESULT,
                       m_A);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('b') >::RESULT,
                       m_B);

                return in;
            }

        }
    }
} // hesperia::data::environment
