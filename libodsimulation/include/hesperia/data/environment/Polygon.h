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

#ifndef HESPERIA_DATA_ENVIRONMENT_POLYGON_H_
#define HESPERIA_DATA_ENVIRONMENT_POLYGON_H_

#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"

#include "core/data/SerializableData.h"
#include "hesperia/data/environment/Point3.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;

            using namespace hesperia::data::environment;

            /**
             * This class represents a polygon.
             */
            class OPENDAVINCI_API Polygon : public core::data::SerializableData {
                private:
                    const static double EPSILON;

                public:
                    Polygon();

                    /**
                     * Constructor.
                     *
                     * @param List of vertices.
                     */
                    Polygon(const vector<Point3> &vertices);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Polygon(const Polygon &obj);

                    virtual ~Polygon();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Polygon& operator=(const Polygon &obj);

                    /**
                     * This method adds a point to a polygon.
                     *
                     * @param p Point to be added.
                     */
                    void add(const Point3 &p);

                    /**
                     * This method returns all vertices.
                     *
                     * @return Vertices from this polygon.
                     */
                    vector<Point3> getVertices() const;

                    /**
                     * This method returns this polygon's size.
                     *
                     * @return Number of vertices.
                     */
                    uint32_t getSize() const;

                    /**
                     * This method checks if the given point
                     * is within this polygon ignoring Z coordinate.
                     *
                     * @param p Point to be tested.
                     * @return true, if p is within this polygon.
                     */
                    bool containsIgnoreZ(const Point3 &p) const;

                    /**
                     * This method intersects this polygon with
                     * the other return the resulting contour
                     * ignoring the Z coordinate.
                     *
                     * @param other Polygon to be intersect with this one.
                     * @return Polygon built from intersection points.
                     */
                    Polygon intersectIgnoreZ(const Polygon &other) const;

                    /**
                     * This method returns only the visible vertices
                     * for a given point ignoring the Z coordinate.
                     *
                     * @param point Point for visibility computation.
                     * @return Polygon containing only directly visible vertices.
                     */
                    Polygon getVisiblePolygonIgnoreZ(const Point3 &point) const;

                    /**
                     * This method computes the center of the polygon.
                     *
                     * @return Center of the polyon.
                     */
                    Point3 getCenter() const;

                    /**
                     * This method sorts all contained vertices to
                     * avoid crossing lines.
                     */
                    void sort();

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    vector<Point3> m_listOfVertices;
            };

        }
    }
} // hesperia::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_POINT3_H_*/
