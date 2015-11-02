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

#ifndef HESPERIA_CORE_DATA_SCENARIO_SHAPE_H_
#define HESPERIA_CORE_DATA_SCENARIO_SHAPE_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/data/SerializableData.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a shape (i.e. a polygon, cylinder or complex model).
             */
            class OPENDAVINCI_API Shape : public core::data::SerializableData, public ScenarioNode {
                public:
                    enum SHAPETYPE {
                        UNDEFINED,
                        COMPLEXMODEL,
                        CYLINDER,
                        POLYGON
                    };

                protected:
                    Shape();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Shape(const Shape &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Shape& operator=(const Shape &obj);

                public:
                    virtual ~Shape();

                    virtual void accept(ScenarioVisitor &visitor) = 0;

                    /**
                     * This method returns the shape's name.
                     *
                     * @return Shape's name.
                     */
                    const string getName() const;

                    /**
                     * This method sets the shape's name.
                     *
                     * @param name Shape's name.
                     */
                    void setName(const string &name);

                    /**
                     * This method returns the type of the shape.
                     *
                     * @return Type of shape.
                     */
                    enum SHAPETYPE getType() const;

                    /**
                     * This method sets the shape's type.
                     *
                     * @param type Type of the shape.
                     */
                    void setType(const enum Shape::SHAPETYPE &type);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    string m_name;
                    enum SHAPETYPE m_type;
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_SHAPE_H_*/
