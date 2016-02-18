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

#ifndef HESPERIA_CORE_DATA_SITUATION_SITUATION_H_
#define HESPERIA_CORE_DATA_SITUATION_SITUATION_H_

#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/data/SerializableData.h"

#include "opendlv/data/situation/Header.h"
#include "opendlv/data/situation/Object.h"
#include "opendlv/data/situation/SituationNode.h"
#include "opendlv/data/situation/SituationVisitor.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents a situation.
             */
            class OPENDAVINCI_API Situation : public core::data::SerializableData, public SituationNode {
                public:
                    Situation();

                    virtual ~Situation();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Situation(const Situation &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Situation& operator=(const Situation &obj);

                    virtual void accept(situation::SituationVisitor &visitor);

                    /**
                     * This method returns the situation's header.
                     *
                     * @return Situation's header.
                     */
                    const Header& getHeader() const;

                    /**
                     * This method sets the situation's header.
                     *
                     * @param h Situation's header.
                     */
                    void setHeader(const Header &h);

                    /**
                     * This method returns the list of objects.
                     *
                     * @return List of objects.
                     */
                    const vector<Object>& getListOfObjects() const;

                    /**
                     * This method adds a object.
                     *
                     * @param o Object to be added.
                     */
                    void addObject(const Object &o);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    Header m_header;
                    vector<Object> m_listOfObjects;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const Situation &obj);
            };

        }
    }
} // opendlv::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_SITUATION_H_*/
