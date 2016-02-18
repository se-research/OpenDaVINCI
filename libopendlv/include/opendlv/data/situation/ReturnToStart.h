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

#ifndef HESPERIA_CORE_DATA_SITUATION_RETURNTOSTART_H_
#define HESPERIA_CORE_DATA_SITUATION_RETURNTOSTART_H_

#include "opendlv/data/situation/StopType.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents the start type STOP.
             */
            class OPENDAVINCI_API ReturnToStart : public StopType {
                public:
                    ReturnToStart();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ReturnToStart(const ReturnToStart &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ReturnToStart& operator=(const ReturnToStart &obj);

                    virtual ~ReturnToStart();

                    virtual void accept(SituationVisitor &visitor);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
            };

        }
    }
} // core::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_RETURNTOSTART_H_*/
