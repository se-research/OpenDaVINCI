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

#ifndef HESPERIA_CORE_DATA_SCENARIO_POLYGON_H_
#define HESPERIA_CORE_DATA_SCENARIO_POLYGON_H_

#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/scenario/Shape.h"
#include "hesperia/data/scenario/Vertex3.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a polygon.
             */
            class OPENDAVINCI_API Polygon : public Shape {
                public:
                    Polygon();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Polygon(const Polygon &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Polygon& operator=(const Polygon &obj);

                    virtual ~Polygon();

                    virtual void accept(ScenarioVisitor &visitor);

                    /**
                     * This method returns the height of this cylinder.
                     *
                     * @return Height.
                     */
                    double getHeight() const;

                    /**
                     * This method sets the height of this cylinder.
                     *
                     * @param h Height.
                     */
                    void setHeight(const double &h);

                    /**
                     * This method returns the color (R, G, B) of this cylinder.
                     *
                     * @return Color.
                     */
                    const Vertex3& getColor() const;

                    /**
                     * This method sets the color of this cylinder.
                     *
                     * @param c Color.
                     */
                    void setColor(const Vertex3 &c);

                    /**
                     * This method returns the list of vertices.
                     *
                     * @return List of vertices.
                     */
                    const vector<Vertex3>& getListOfVertices() const;

                    /**
                     * This method returns a list of Point3 vertices.
                     *
                     * @return List of Point3 vertices.
                     */
                    const vector<hesperia::data::environment::Point3> getListOfVerticesAsPoint3() const;

                    /**
                     * This method add a new vertex to the polygon.
                     *
                     * @param v Vertex to be added.
                     */
                    void add(const Vertex3 &v);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    double m_height;
                    Vertex3 m_color;
                    vector<Vertex3> m_listOfVertices;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object to be copy.
                     */
                    void deepCopy(const Polygon &obj);
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_POLYGON_H_*/
