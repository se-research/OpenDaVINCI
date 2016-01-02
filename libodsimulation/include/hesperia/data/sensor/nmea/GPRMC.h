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

#ifndef HESPERIA_DATA_SENSOR_NMEA_GPRMC_H_
#define HESPERIA_DATA_SENSOR_NMEA_GPRMC_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"

#include "core/data/SerializableData.h"
#include "core/data/TimeStamp.h"
#include "hesperia/data/environment/WGS84Coordinate.h"

namespace hesperia {
    namespace data {
        namespace sensor {
            namespace nmea {

                using namespace std;

                /**
                 * This class encapsulated a GPRMC (GPS recommended) message.
                 */
                class OPENDAVINCI_API GPRMC : public core::data::SerializableData {
                    private:
                        enum {
                            BASE_YEAR = 2000
                        };
                    public:
                        GPRMC();

                        /**
                         * Copy constructor.
                         *
                         * @param obj Reference to an object of this class.
                         */
                        GPRMC(const GPRMC &obj);

                        virtual ~GPRMC();

                        /**
                         * Assignment operator.
                         *
                         * @param obj Reference to an object of this class.
                         * @return Reference to this instance.
                         */
                        GPRMC& operator=(const GPRMC &obj);

                        /**
                         * This method returns the raw GPRMC message.
                         *
                         * @return GPRMC message.
                         */
                        const string getMessage() const;

                        /**
                         * This method sets the GPRMC message.
                         *
                         * @param msg Message to be set.
                         */
                        void setMessage(const string &msg);

                        /**
                         * This method returns the time stamp for this
                         * GPRMC message.
                         *
                         * @return timestamp.
                         */
                        const core::data::TimeStamp getTimeStamp() const;

                        /**
                         * This method sets the time stamp for this
                         * GPRMC message.
                         *
                         * @param timeStamp Timestamp.
                         */
                        void setTimeStamp(const core::data::TimeStamp &timeStamp);

                        /**
                         * This methods returns the WGS84 coordinate.
                         *
                         * @return WGS84Coordinate.
                         */
                        const hesperia::data::environment::WGS84Coordinate getCoordinate() const;

                        /**
                         * This methods sets the WGS84 coordinate.
                         *
                         * @param coordinate WGS84Coordinate.
                         */
                        void setCoordinate(const hesperia::data::environment::WGS84Coordinate &coordinate);

                        virtual ostream& operator<<(ostream &out) const;
                        virtual istream& operator>>(istream &in);

                        virtual const string toString() const;

                    private:
                        string m_message;
                        core::data::TimeStamp m_timeStamp;
                        hesperia::data::environment::WGS84Coordinate m_coordinate;

                        /**
                         * This method decodes a given GPRMC string.
                         */
                        void decode();

                        /**
                         * This method encodes a GPRMC string based on the data of this instance.
                         */
                        void encode();
                };

            }
        }
    }
} // hesperia::data::sensor::nmea

#endif /*HESPERIA_DATA_SENSOR_NMEA_GPRMC_H_*/
