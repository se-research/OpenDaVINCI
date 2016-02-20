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

#ifndef HESPERIA_CORE_DATA_SCENARIO_IDVERTEX3_H_
#define HESPERIA_CORE_DATA_SCENARIO_IDVERTEX3_H_

#include "opendavinci/odcore/opendavinci.h"

#include "opendlv/data/scenario/Vertex3.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents an identifiable two dimensional coordinate.
             */
            class OPENDAVINCI_API IDVertex3 : public Vertex3 {
                public:
                    IDVertex3();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    IDVertex3(const IDVertex3 &obj);

                    virtual ~IDVertex3();

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    IDVertex3& operator=(const IDVertex3 &obj);

                    /**
                     * This method returns the ID.
                     *
                     * @return ID.
                     */
                    uint32_t getIdentifier() const;

                    /**
                     * This method sets the ID.
                     *
                     * @param ID.
                     */
                    void setIdentifier(const uint32_t &ID);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    uint32_t m_identifier;
            };

        }
    }
} // opendlv::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_IDVERTEX3_H_*/
