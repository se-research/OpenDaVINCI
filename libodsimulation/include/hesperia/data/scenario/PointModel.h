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

#ifndef HESPERIA_CORE_DATA_SCENARIO_POINTMODEL_H_
#define HESPERIA_CORE_DATA_SCENARIO_POINTMODEL_H_

#include <string>
#include <vector>

#include "core/opendavinci.h"

#include "core/data/SerializableData.h"
#include "core/exceptions/Exceptions.h"
#include "hesperia/data/scenario/IDVertex3.h"
#include "hesperia/data/scenario/LaneModel.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a point model.
             */
            class OPENDAVINCI_API PointModel : public LaneModel {
                public:
                    PointModel();

                    virtual ~PointModel();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    PointModel(const PointModel &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    PointModel& operator=(const PointModel &obj);

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the list of identifiable vertices.
                     *
                     * @return List of identifiable vertices.
                     */
                    const vector<IDVertex3>& getListOfIdentifiableVertices() const;

                    /**
                     * This method returns IDVertex3 for the given ID.
                     *
                     * @param id ID to look up.
                     * @return IDVertex3 for the given ID.
                     * @throws InvalidArgumentException if the ID could not be found.
                     */
                    const IDVertex3 getIDVertex3(const uint32_t &id) const throw (core::exceptions::InvalidArgumentException);

                    /**
                     * This method adds an identifiable vertex.
                     *
                     * @param idV Identifiable vertex to be added.
                     */
                    void addIdentifiableVertex(const IDVertex3 &idV);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    vector<IDVertex3> m_listOfIdentifiableVertices;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const PointModel &obj);
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_POINTMODEL_H_*/
