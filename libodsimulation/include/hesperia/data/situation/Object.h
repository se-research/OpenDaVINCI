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

#ifndef HESPERIA_CORE_DATA_SITUATION_OBJECT_H_
#define HESPERIA_CORE_DATA_SITUATION_OBJECT_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"
#include "core/data/SerializableData.h"
#include "hesperia/data/situation/Behavior.h"
#include "hesperia/data/situation/Shape.h"
#include "hesperia/data/situation/SituationNode.h"
#include "hesperia/data/situation/SituationVisitor.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents the header of a scenario.
             */
            class OPENDAVINCI_API Object : public core::data::SerializableData, public SituationNode {
                public:
                    Object();

                    virtual ~Object();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Object(const Object &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Object& operator=(const Object &obj);

                    virtual void accept(situation::SituationVisitor &visitor);

                    /**
                     * This method returns the object's name.
                     *
                     * @return Object's name.
                     */
                    const string getName() const;

                    /**
                     * This method sets the object's name.
                     *
                     * @param name Object's name.
                     */
                    void setName(const string &name);

                    /**
                     * This method returns the object's ID.
                     *
                     * @return Object's ID.
                     */
                    uint32_t getID() const;

                    /**
                     * This method sets the object's ID.
                     *
                     * @param id Object's ID.
                     */
                    void setID(const uint32_t &id);

                    /**
                     * This method returns the shape of this object.
                     *
                     * @return Shape of this object.
                     */
                    Shape* getShape() const;

                    /**
                     * This method sets the object's shape.
                     *
                     * @param s Shape of this object.
                     */
                    void setShape(Shape *s);

                    /**
                     * This method returns the object's rotation around Z-axis.
                     *
                     * @return Object's rotation around Z-axis.
                     */
                    double getRotationZ() const;

                    /**
                     * This method sets the object's rotation around Z-axis.
                     *
                     * @param rotationZ Object's rotation around Z-axis.
                     */
                    void setRotationZ(const double &rotationZ);

                    /**
                     * This method returns the behavior of this object.
                     *
                     * @return Behavior of this object.
                     */
                    Behavior* getBehavior() const;

                    /**
                     * This method sets the object's behavior.
                     *
                     * @param b Behavior of this object.
                     */
                    void setBehavior(Behavior *b);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    string m_name;
                    uint32_t m_id;
                    Shape *m_shape;
                    double m_rotationZ;
                    Behavior *m_behavior;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const Object &obj);

                    /**
                     * This method clean's up the data.
                     */
                    void cleanUp();
            };

        }
    }
} // core::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_OBJECT_H_*/
