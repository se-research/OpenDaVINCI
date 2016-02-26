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

#ifndef HESPERIA_CORE_DATA_SITUATION_EXTERNALDRIVER_H_
#define HESPERIA_CORE_DATA_SITUATION_EXTERNALDRIVER_H_

#include "opendlv/data/situation/Behavior.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents an external driver.
             */
            class OPENDAVINCI_API ExternalDriver : public Behavior {
                public:
                    ExternalDriver();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ExternalDriver(const ExternalDriver &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ExternalDriver& operator=(const ExternalDriver &obj);

                    virtual ~ExternalDriver();

                    virtual void accept(SituationVisitor &visitor);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
            };

        }
    }
} // core::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_EXTERNALDRIVER_H_*/
