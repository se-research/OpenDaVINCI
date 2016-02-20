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

#ifndef HESPERIA_CORE_DATA_SCENARIO_ZONE_H_
#define HESPERIA_CORE_DATA_SCENARIO_ZONE_H_

#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/Connector.h"
#include "opendlv/data/scenario/Lane.h"
#include "opendlv/data/scenario/Perimeter.h"
#include "opendlv/data/scenario/ScenarioNode.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Spot.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;

            /** Prevent circular dependencies. */
            class Layer;

            /**
             * This class represents a zone.
             */
            class OPENDAVINCI_API Zone : public odcore::data::SerializableData, public ScenarioNode {
                public:
                    Zone();

                    virtual ~Zone();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Zone(const Zone &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Zone& operator=(const Zone &obj);

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the ID.
                     *
                     * @return ID.
                     */
                    uint32_t getIdentifier() const;

                    /**
                     * This method sets the ID.
                     *
                     * @param id ID to be set.
                     */
                    void setIdentifier(const uint32_t &id);

                    /**
                     * This method returns the road's name.
                     *
                     * @return Zone's name.
                     */
                    const string getName() const;

                    /**
                     * This method set the road's name.
                     *
                     * @param name The road's name.
                     */
                    void setName(const string &name);

                    /**
                     * This method returns the list of connectors.
                     *
                     * @return List of connectors.
                     */
                    const vector<Connector>& getListOfConnectors() const;

                    /**
                     * This method adds a connector.
                     *
                     * @param c Connector to be added.
                     */
                    void addConnector(const Connector &c);

                    /**
                     * This method returns the perimeter.
                     *
                     * @return Perimeter.
                     */
                    const Perimeter& getPerimeter() const;

                    /**
                     * This method sets the perimeter.
                     *
                     * @param p Perimeter to be set.
                     */
                    void setPerimeter(const Perimeter &p);

                    /**
                     * This method returns the list of spots.
                     *
                     * @return List of spots.
                     */
                    const vector<Spot>& getListOfSpots() const;

                    /**
                     * This method adds a spot.
                     *
                     * @param s Spot to be added.
                     */
                    void addSpot(const Spot &s);

                    /**
                     * This method sets the layer to which this zone belongs to.
                     *
                     * @param l Layer.
                     */
                    void setLayer(const Layer *l);

                    /**
                     * This method returns the layer to which this zone belongs to.
                     *
                     * @return Layer.
                     */
                    const Layer* getLayer() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    uint32_t m_identifier;
                    string m_name;
                    const Layer *m_layer;
                    vector<Connector> m_listOfConnectors;
                    Perimeter m_perimeter;
                    vector<Spot> m_listOfSpots;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const Zone &obj);
            };

        }
    }
} // opendlv::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_ZONE_H_*/
