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

#ifndef HESPERIA_CORE_DATA_SITUATION_ONMOVING_H_
#define HESPERIA_CORE_DATA_SITUATION_ONMOVING_H_

#include "opendlv/data/situation/StartType.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents the start type ONMOVING.
             */
            class OPENDAVINCI_API OnMoving : public StartType {
                public:
                    OnMoving();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    OnMoving(const OnMoving &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    OnMoving& operator=(const OnMoving &obj);

                    virtual ~OnMoving();

                    virtual void accept(SituationVisitor &visitor);

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

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    uint32_t m_id;
            };

        }
    }
} // core::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_ONMOVING_H_*/
