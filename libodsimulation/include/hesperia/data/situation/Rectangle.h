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

#ifndef HESPERIA_CORE_DATA_SITUATION_RECTANGLE_H_
#define HESPERIA_CORE_DATA_SITUATION_RECTANGLE_H_

#include <vector>

#include "core/opendavinci.h"
#include "hesperia/data/situation/Shape.h"
#include "hesperia/data/situation/Vertex3.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents a rectangle.
             */
            class OPENDAVINCI_API Rectangle : public Shape {
                public:
                    Rectangle();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Rectangle(const Rectangle &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Rectangle& operator=(const Rectangle &obj);

                    virtual ~Rectangle();

                    virtual void accept(SituationVisitor &visitor);

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
                     * This method returns the rectangle's length.
                     *
                     * @return Rectangle's length.
                     */
                    double getLength() const;

                    /**
                     * This method sets the rectangle's length.
                     *
                     * @param l Rectangle's length.
                     */
                    void setLength(const double l);

                    /**
                     * This method returns the rectangle's width.
                     *
                     * @return Rectangle's width.
                     */
                    double getWidth() const;

                    /**
                     * This method sets the rectangle's width.
                     *
                     * @param w Rectangle's width.
                     */
                    void setWidth(const double w);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    double m_height;
                    Vertex3 m_color;
                    double m_length;
                    double m_width;
            };

        }
    }
} // core::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_RECTANGLE_H_*/
