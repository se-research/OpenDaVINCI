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

#ifndef HESPERIA_DATA_ENVIRONMENT_POINT3_H_
#define HESPERIA_DATA_ENVIRONMENT_POINT3_H_

#include "core/opendavinci.h"

#include "core/data/SerializableData.h"

#include "GeneratedHeaders_AutomotiveData.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;

            /**
             * This class is the main class for all cartesian computations.
             */
            class OPENDAVINCI_API Point3 : public core::data::SerializableData {
                private:
                    const static double EPSILON;

                public:
                    Point3();

                    /**
                     * Constructor.
                     *
                     * @param x
                     * @param y
                     * @param z
                     */
                    Point3(const double &x, const double &y, const double &z);

                    /**
                     * Constructor.
                     *
                     * @param s String containing the data "(x; y; z)".
                     */
                    Point3(const string &s);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Point3(const Point3 &obj);

                    virtual ~Point3();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Point3& operator=(const Point3 &obj);

                    /**
                     * This method returns the x coordinate.
                     *
                     * @return x-coordinate.
                     */
                    double getX() const;

                    /**
                     * This method sets the x coordinate.
                     *
                     * @param x.
                     */
                    void setX(const double &x);

                    /**
                     * This method returns the y coordinate.
                     *
                     * @return y-coordinate.
                     */
                    double getY() const;

                    /**
                     * This method sets the y coordinate.
                     *
                     * @param y.
                     */
                    void setY(const double &y);

                    /**
                     * This method returns the z coordinate.
                     *
                     * @return z-coordinate.
                     */
                    double getZ() const;

                    /**
                     * This method sets the z coordinate.
                     *
                     * @param z.
                     */
                    void setZ(const double &z);

                    /**
                     * This operator adds the other cartesian coordinate
                     * with this instance to a new object of this class.
                     *
                     * @param other Other coordinate.
                     * @return New object.
                     */
                    Point3 operator+(const Point3 &other) const;

                    /**
                     * This operator adds the other cartesian coordinate
                     * to this instance.
                     *
                     * @param other Other coordinate.
                     * @return Modified instance.
                     */
                    Point3& operator+=(const Point3 &other);

                    /**
                     * This operator subtracts the other cartesian coordinate
                     * with this instance to a new object of this class.
                     *
                     * @param other Other coordinate.
                     * @return New object.
                     */
                    Point3 operator-(const Point3 &other) const;

                    /**
                     * This operator subtracts the other cartesian coordinate
                     * to this instance.
                     *
                     * @param other Other coordinate.
                     * @return Modified instance.
                     */
                    Point3& operator-=(const Point3 &other);

                    /**
                     * This operator scales this coordinate and returns
                     * a new instance.
                     *
                     * @param a Scaling factor.
                     * @return New object.
                     */
                    Point3 operator*(const double &a) const;

                    /**
                     * This operator scales this coordinate and returns
                     * a the modified instance.
                     *
                     * @param a Scaling factor.
                     * @return Modified instance.
                     */
                    Point3& operator*=(const double &a);

                    /**
                     * This operator multiplies this vector by the given matrix.
                     *
                     * @param m Matrix.
                     * @return New object.
                     */
                    Point3 operator*(const cartesian::Matrix3x3 &m) const;

                    /**
                     * This operator multiplies this vector by the given matrix
                     * and returns a the modified instance.
                     *
                     * @param m Matrix.
                     * @return Modified instance.
                     */
                    Point3& operator*=(const cartesian::Matrix3x3 &m);

                    /**
                     * This operator computes the scalar product.
                     *
                     * @param other Other coordinate.
                     * @return Scalar product.
                     */
                    double operator*(const Point3 &other) const;

                    /**
                     * This operator compares the other coordinate with
                     * this instance and returns true iff both are identical,
                     * i.e. delta < 1e-10;
                     *
                     * @return true iff delta for every attribute is smaller than 1e-10
                     */
                    bool operator==(const Point3 &other) const;

                    /**
                     * This operator is the counterpart of operator==.
                     *
                     * @return false iff delta for every attribute is smaller than 1e-10
                     */
                    bool operator!=(const Point3 &other) const;

                    /**
                     * This method computes the length of the cartesian coordinate.
                     *
                     * @return Length.
                     */
                    double length() const;

                    /**
                     * This method computes the length of the cartesian coordinate
                     * in the X-Y-layer.
                     *
                     * @return Length in the X-Y-layer.
                     */
                    double lengthXY() const;

                    /**
                     * This method normalizes the coordinate.
                     */
                    void normalize();

                    /**
                     * This method normalizes the coordinate in the X-Y-layer.
                     */
                    void normalizeXY();

                    /**
                     * This method rotates this coordinate around the X-axis.
                     * Positive angles means rotation clockwise.
                     *
                     * @param angle Angle in RAD.
                     * @return Reference to this instance.
                     */
                    Point3& rotateX(const double &angle);

                    /**
                     * This method rotates this coordinate around the Y-axis.
                     * Positive angles means rotation clockwise.
                     *
                     * @param angle Angle in RAD.
                     * @return Reference to this instance.
                     */
                    Point3& rotateY(const double &angle);

                    /**
                     * This method rotates this coordinate around the Z-axis.
                     * Positive angles means rotation clockwise.
                     *
                     * @param angle Angle in RAD.
                     * @return Reference to this instance.
                     */
                    Point3& rotateZ(const double &angle);

                    /**
                     * This method rotates this coordinate around an
                     * arbitrary axis.
                     * Positive angles means rotation clockwise.
                     *
                     * @param dir Normalized vector to rotate around.
                     * @param angle Angle in RAD.
                     * @return Reference to this instance.
                     */
                    Point3& rotate(const Point3 direction, const double &angle);

                    /**
                     * This method computes the cross product.
                     *
                     * @param other Other coordinate.
                     * @return The cross product.
                     */
                    Point3 cross(const Point3 &other) const;

                    /**
                     * This method computes the angle between the X-axis
                     * with respect to the quadrant (atan2) in the X-Y-layer.
                     *
                     * @return angle between X-axis and vector in RAD.
                     */
                    double getAngleXY() const;

                    /**
                     * This method computes the squared distance to an other coordinate.
                     *
                     * @param other Other coordinate.
                     * @return Squared distance to the other coordinate.
                     */
                    double getSquaredDistanceTo(const Point3 &other) const;

                    /**
                     * This method computes the squared distance to an other coordinate
                     * in the X-Y-layer.
                     *
                     * @param other Other coordinate.
                     * @return Squared distance to the other coordinate in the X-Y-layer
                     */
                    double getSquaredXYDistanceTo(const Point3 &other) const;

                    /**
                     * This method computes the distance to an other coordinate.
                     *
                     * @param other Other coordinate.
                     * @return Distance to the other coordinate.
                     */
                    double getDistanceTo(const Point3 &other) const;

                    /**
                     * This method computes the distance to an other coordinate
                     * in the X-Y-layer.
                     *
                     * @param other Other coordinate.
                     * @return Distance to the other coordinate in the X-Y-layer
                     */
                    double getXYDistanceTo(const Point3 &other) const;

                    /**
                     * This method checks if this point is in front of the
                     * other point regarding the given angle.
                     *
                     * @param p other Point.
                     * @param angleXY Viewing direction.
                     * @return true, if p is in front of this point.
                     */
                    bool isInFront(const Point3 &p, const double &angleXY) const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    double m_x;
                    double m_y;
                    double m_z;
            };

        }
    }
} // hesperia::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_POINT3_H_*/
