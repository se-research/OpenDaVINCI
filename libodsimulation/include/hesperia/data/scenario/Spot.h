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

#ifndef HESPERIA_CORE_DATA_SCENARIO_SPOT_H_
#define HESPERIA_CORE_DATA_SCENARIO_SPOT_H_

#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/data/SerializableData.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/Vertex3.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a polygon.
             */
            class OPENDAVINCI_API Spot : public core::data::SerializableData, public ScenarioNode {
                public:
                    Spot();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Spot(const Spot &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Spot& operator=(const Spot &obj);

                    virtual ~Spot();

                    virtual void accept(ScenarioVisitor &visitor);

                    /**
                     * This method returns the ID of this spot.
                     *
                     * @return ID of this spot.
                     */
                    uint32_t getID() const;

                    /**
                     * This method sets the ID of this spot.
                     *
                     * @param id ID of this spot.
                     */
                    void setID(const uint32_t &id);

                    /**
                     * This method returns the first vertex
                     *
                     * @return First vertex.
                     */
                    const Vertex3& getFirstVertex() const;

                    /**
                     * This method sets the first vertex.
                     *
                     * @param v Vertex.
                     */
                    void setFirstVertex(const Vertex3 &v);

                    /**
                     * This method returns the second vertex
                     *
                     * @return Second vertex.
                     */
                    const Vertex3& getSecondVertex() const;

                    /**
                     * This method sets the second vertex.
                     *
                     * @param v Vertex.
                     */
                    void setSecondVertex(const Vertex3 &v);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    uint32_t m_id;
                    Vertex3 m_firstVertex;
                    Vertex3 m_secondVertex;
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_SPOT_H_*/
