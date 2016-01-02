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

#ifndef HESPERIA_CORE_DATA_SCENARIO_TRAFFICCONTROL_H_
#define HESPERIA_CORE_DATA_SCENARIO_TRAFFICCONTROL_H_

#include <string>

#include "core/opendavinci.h"

#include "core/data/SerializableData.h"
#include "hesperia/data/scenario/IDVertex3.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/Shape.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a traffic control (sign/light).
             */
            class OPENDAVINCI_API TrafficControl : public core::data::SerializableData, public ScenarioNode {
                public:
                    enum TRAFFICCONTROLTYPE {
                        TRAFFICLIGHT,
                        TRAFFICSIGN
                    };

                protected:
                    TrafficControl();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    TrafficControl(const TrafficControl &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    TrafficControl& operator=(const TrafficControl &obj);

                public:
                    virtual ~TrafficControl();

                    virtual void accept(ScenarioVisitor &visitor) = 0;

                    /**
                     * This method returns the shape's name.
                     *
                     * @return TrafficControl's name.
                     */
                    const string getName() const;

                    /**
                     * This method sets the shape's name.
                     *
                     * @param name TrafficControl's name.
                     */
                    void setName(const string &name);

                    /**
                     * This method returns the type of the shape.
                     *
                     * @return Type of shape.
                     */
                    enum TRAFFICCONTROLTYPE getType() const;

                    /**
                     * This method sets the shape's type.
                     *
                     * @param type Type of the shape.
                     */
                    void setType(const enum TrafficControl::TRAFFICCONTROLTYPE &type);

                    /**
                     * This method returns the position of the traffic control.
                     *
                     * @return Position of the traffic control.
                     */
                    const IDVertex3& getPosition() const;

                    /**
                     * This method sets the position of the traffic control.
                     *
                     * @param p Position of the traffic control.
                     */
                    void setPosition(const IDVertex3 &p);

                    /**
                     * This method returns the shape of the traffic control.
                     *
                     * @return Shape of the traffic control.
                     */
                    Shape* getShape() const;

                    /**
                     * This method sets the shape of the traffic control.
                     *
                     * @param s Shape.
                     */
                    void setShape(Shape *s);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    string m_name;
                    enum TRAFFICCONTROLTYPE m_type;
                    IDVertex3 m_position;
                    Shape *m_shape;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const TrafficControl &obj);
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_TRAFFICCONTROL_H_*/
