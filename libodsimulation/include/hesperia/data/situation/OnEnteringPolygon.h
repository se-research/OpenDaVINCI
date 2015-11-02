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

#ifndef HESPERIA_CORE_DATA_SITUATION_ONENTERINGPOLYGON_H_
#define HESPERIA_CORE_DATA_SITUATION_ONENTERINGPOLYGON_H_

#include <vector>

#include "hesperia/data/situation/StartType.h"
#include "hesperia/data/situation/Vertex3.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents the start type ONENTERINGPOLYGON.
             */
            class OPENDAVINCI_API OnEnteringPolygon : public StartType {
                public:
                    OnEnteringPolygon();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    OnEnteringPolygon(const OnEnteringPolygon &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    OnEnteringPolygon& operator=(const OnEnteringPolygon &obj);

                    virtual ~OnEnteringPolygon();

                    virtual void accept(SituationVisitor &visitor);

                    /**
                     * This method returns the object's ID.
                     *
                     * @return Object's ID.
                     */
                    uint32_t getIdentifier() const;

                    /**
                     * This method sets the object's ID.
                     *
                     * @param id Object's ID.
                     */
                    void setIdentifier(const uint32_t &id);

                    /**
                     * This method returns the list of vertices.
                     *
                     * @return List of vertices.
                     */
                    const vector<Vertex3>& getListOfVertices() const;

                    /**
                     * This method add a new vertex to the polygon.
                     *
                     * @param v Vertex to be added.
                     */
                    void add(const Vertex3 &v);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    uint32_t m_identifier;
                    vector<Vertex3> m_listOfVertices;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object to be copy.
                     */
                    void deepCopy(const OnEnteringPolygon &obj);
            };

        }
    }
} // core::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_ONENTERINGPOLYGON_H_*/
