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

#ifndef HESPERIA_DATA_SENSOR_LMS291MESSAGE_H_
#define HESPERIA_DATA_SENSOR_LMS291MESSAGE_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/data/SerializableData.h"

namespace opendlv {
    namespace data {
        namespace sensor {

            using namespace std;

            /**
             * This class encapsulated an LMS291 message.
             */
            class OPENDAVINCI_API LMS291Message : public odcore::data::SerializableData {
                public:
                    LMS291Message();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    LMS291Message(const LMS291Message &obj);

                    virtual ~LMS291Message();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    LMS291Message& operator=(const LMS291Message &obj);

                    /**
                     * This method returns the ID of the LMS291.
                     *
                     * @return LMS291's ID.
                     */
                    const string getID() const;

                    /**
                     * This method sets the LMS291 ID.
                     *
                     * @param id ID to be set.
                     */
                    void setID(const string &id);

                    /**
                     * This method returns the raw LMS291 message.
                     *
                     * @return LMS291 message.
                     */
                    const string getMessage() const;

                    /**
                     * This method sets the LMS291 message.
                     *
                     * @param msg Message to be set.
                     */
                    void setMessage(const string &msg);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    string m_id;
                    string m_message;
            };

        }
    }
} // opendlv::data::sensor

#endif /*HESPERIA_DATA_SENSOR_LMS291MESSAGE_H_*/
