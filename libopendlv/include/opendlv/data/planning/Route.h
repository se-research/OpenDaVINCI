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

#ifndef HESPERIA_DATA_PLANNING_ROUTE_H_
#define HESPERIA_DATA_PLANNING_ROUTE_H_

#include <vector>

#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/environment/Point3.h"

namespace opendlv {
    namespace data {
        namespace planning {

            using namespace std;

            /**
             * This class represents a route consisting of several points.
             */
            class OPENDAVINCI_API Route : public odcore::data::SerializableData {
                public:
                    Route();

                    /**
                     * Constructor.
                     *
                     * @param List of vertices.
                     */
                    Route(const vector<opendlv::data::environment::Point3> &vertices);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Route(const Route &obj);

                    virtual ~Route();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Route& operator=(const Route &obj);

                    /**
                     * This method adds a point to a polygon.
                     *
                     * @param p Point to be added.
                     */
                    void add(const opendlv::data::environment::Point3 &p);

                    /**
                     * This method returns all vertices.
                     *
                     * @return Vertices from this polygon.
                     */
                    vector<opendlv::data::environment::Point3> getListOfPoints() const;

                    /**
                     * This method returns this route size.
                     *
                     * @return Number of vertices.
                     */
                    uint32_t getSize() const;

                    /**
                     * This method computes the length of the route.
                     *
                     * @return Length of the route.
                     */
                    double getLength() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    vector<opendlv::data::environment::Point3> m_listOfVertices;
            };

        }
    }
} // opendlv::data::planning

#endif /*HESPERIA_DATA_PLANNING_ROUTE_H_*/
