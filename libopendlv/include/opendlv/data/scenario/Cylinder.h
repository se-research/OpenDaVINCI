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

#ifndef HESPERIA_CORE_DATA_SCENARIO_CYLINDER_H_
#define HESPERIA_CORE_DATA_SCENARIO_CYLINDER_H_

#include "opendavinci/core/opendavinci.h"

#include "opendlv/data/scenario/Shape.h"
#include "opendlv/data/scenario/Vertex3.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a cylinder.
             */
            class OPENDAVINCI_API Cylinder : public Shape {
                public:
                    Cylinder();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Cylinder(const Cylinder &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Cylinder& operator=(const Cylinder &obj);

                    virtual ~Cylinder();

                    virtual void accept(ScenarioVisitor &visitor);

                    /**
                     * This method returns the center of this cylinder.
                     *
                     * @return Center.
                     */
                    const Vertex3& getCenter() const;

                    /**
                     * This method sets the center of this cylinder.
                     *
                     * @param c Center.
                     */
                    void setCenter(const Vertex3 &c);

                    /**
                     * This method returns the radius of this cylinder.
                     *
                     * @return Radius.
                     */
                    double getRadius() const;

                    /**
                     * This method sets the radius of this cylinder.
                     * Radius must be greater than 0.
                     *
                     * @param r Radius.
                     */
                    void setRadius(const double &r);

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

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    Vertex3 m_center;
                    double m_radius;
                    double m_height;
                    Vertex3 m_color;
            };

        }
    }
} // core::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_CYLINDER_H_*/
