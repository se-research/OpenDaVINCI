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

#ifndef HESPERIA_CORE_DATA_SCENARIO_SURROUNDINGS_H_
#define HESPERIA_CORE_DATA_SCENARIO_SURROUNDINGS_H_

#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"

#include "opendavinci/core/data/SerializableData.h"
#include "opendlv/data/scenario/ScenarioNode.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Shape.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents the surroundings.
             */
            class OPENDAVINCI_API Surroundings : public core::data::SerializableData, public ScenarioNode {
                public:
                    Surroundings();

                    virtual ~Surroundings();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Surroundings(const Surroundings &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Surroundings& operator=(const Surroundings &obj);

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the list of shapes.
                     *
                     * @return List of shapes.
                     */
                    const vector<Shape*>& getListOfShapes() const;

                    /**
                     * This method adds a shape.
                     *
                     * @param s Shape to be added.
                     */
                    void addShape(Shape *s);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    vector<Shape*> m_listOfShapes;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const Surroundings &obj);

                    /**
                     * This method clean's up the data.
                     */
                    void cleanUp();
            };

        }
    }
} // opendlv::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_SURROUNDINGS_H_*/
