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

#ifndef HESPERIA_DATA_ENVIRONMENT_LINE_H_
#define HESPERIA_DATA_ENVIRONMENT_LINE_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/environment/Point3.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;

            using namespace opendlv::data::environment;

            /**
             * This class can be used for line operations.
             */
            class OPENDAVINCI_API Line : public odcore::data::SerializableData {
                private:
                    const static double EPSILON;

                public:
                    Line();

                    /**
                     * Constructor.
                     *
                     * @param A
                     * @param B
                     */
                    Line(const Point3 &A, const Point3 &B);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Line(const Line &obj);

                    virtual ~Line();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Line& operator=(const Line &obj);

                    /**
                     * This method returns point A.
                     *
                     * @return Point A.
                     */
                    Point3 getA() const;

                    /**
                     * This method sets point A.
                     *
                     * @param A Point A.
                     */
                    void setA(const Point3 &A);

                    /**
                     * This method returns point B.
                     *
                     * @return Point B.
                     */
                    Point3 getB() const;

                    /**
                     * This method sets point B.
                     *
                     * @param B Point B.
                     */
                    void setB(const Point3 &B);

                    /**
                     * This method computes the intersection point
                     * ignoring the Z coordinate.
                     *
                     * @param l Line to intersect.
                     * @param result Result of intersection.
                     * @return true, if an intersection point could be found.
                     */
                    bool intersectIgnoreZ(const Line &l, Point3 &result) const;

                    /**
                     * This method computes the perpendicular point
                     * for the given p.
                     *
                     * @param p Point to be used for perpendicular computation.
                     * @return Perpendicular point.
                     */
                    const Point3 getPerpendicularPoint(const Point3 &p) const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    static int32_t ID();
                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    Point3 m_A;
                    Point3 m_B;

                    double det(const double &a, const double &b, const double &c, const double &d) const;
            };

        }
    }
} // opendlv::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_LINE_H_*/
