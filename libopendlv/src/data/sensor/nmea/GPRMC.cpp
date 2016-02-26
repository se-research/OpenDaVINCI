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

#include <iostream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendlv/data/environment/WGS84Coordinate.h"
#include "opendlv/data/sensor/nmea/GPRMC.h"

namespace opendlv {
    namespace data {
        namespace sensor {
            namespace nmea {

                using namespace std;
                using namespace odcore::base;
                using namespace odcore::data;
                using namespace opendlv::data::environment;

                GPRMC::GPRMC() :
                        SerializableData(),
                        m_message(),
                        m_timeStamp(),
                        m_coordinate() {
                    // Update message.
                    encode();
                }

                GPRMC::GPRMC(const GPRMC &obj) :
                        m_message(obj.getMessage()),
                        m_timeStamp(obj.getTimeStamp()),
                        m_coordinate(obj.getCoordinate()) {
                    // Update message.
                    encode();
                }

                GPRMC::~GPRMC() {}

                GPRMC& GPRMC::operator=(const GPRMC &obj) {
                    setMessage(obj.getMessage());
                    setTimeStamp(obj.getTimeStamp());
                    setCoordinate(obj.getCoordinate());

                    // Update message.
                    encode();

                    return (*this);
                }

                const string GPRMC::getMessage() const {
                    return m_message;
                }

                void GPRMC::setMessage(const string &msg) {
                    m_message = msg;

                    // Decode message.
                    decode();
                }

                const WGS84Coordinate GPRMC::getCoordinate() const {
                    return m_coordinate;
                }

                void GPRMC::setCoordinate(const WGS84Coordinate &coordinate) {
                    m_coordinate = coordinate;

                    // Update message.
                    encode();
                }

                const TimeStamp GPRMC::getTimeStamp() const {
                    return m_timeStamp;
                }

                void GPRMC::setTimeStamp(const odcore::data::TimeStamp &timeStamp) {
                    m_timeStamp = timeStamp;

                    // Update message.
                    encode();
                }

                void GPRMC::decode() {
                    //$GPRMC,162748,A,5214.0456,N,01103.4540,E,0.0,0.0,250309,0.0,E,A*17CRLF
                    if (m_message.size() > 65) {
                        uint32_t pos = 0;
                        string strGPRMC = m_message.substr(pos, 6);

                        if (strGPRMC != "$GPRMC") {
                            clog << "No $GPRMC message." << endl;
                            return;
                        }

                        ////////////////////////////////////////////////////////

                        pos = pos + 6 + 1; // Consume value + ","
                        stringstream timeStr(m_message.substr(pos, 6));
                        uint32_t time;
                        timeStr >> time;

                        pos = pos + 6 + 1; // Consume value + ","
                        char type = m_message.at(pos);
                        if (type != 'A') {
                            clog << "No data message." << endl;
                            return;
                        }

                        ////////////////////////////////////////////////////////

                        pos = pos + 1 + 1; // Consume value + ","
                        stringstream latitudeStr(m_message.substr(pos, 2));

                        pos = pos + 2; // Consume value

                        stringstream latitudeArcMinuteStr(m_message.substr(pos, 7));

                        double temp;
                        double latitude = 0;
                        latitudeStr >> temp;
                        latitude = temp;
                        latitudeArcMinuteStr >> temp;
                        latitude += (temp / 60);

                        pos = pos + 7 + 1; // Consume value + ","
                        char LAT = m_message.at(pos);

                        m_coordinate.setLatitude(latitude);
                        m_coordinate.setLATITUDE((LAT == 'N') ? WGS84Coordinate::NORTH : WGS84Coordinate::SOUTH);

                        ////////////////////////////////////////////////////////

                        pos = pos + 1 + 1; // Consume value + ","

                        stringstream longitudeStr(m_message.substr(pos, 3));

                        pos = pos + 3; // Consume value

                        stringstream longitudeArcMinuteStr(m_message.substr(pos, 7));

                        double longitude = 0;
                        longitudeStr >> temp;
                        longitude = temp;
                        longitudeArcMinuteStr >> temp;
                        longitude += (temp / 60);

                        pos = pos + 7 + 1; // Consume value + ","
                        char LON = m_message.at(pos);

                        m_coordinate.setLongitude(longitude);
                        m_coordinate.setLONGITUDE((LON == 'W') ? WGS84Coordinate::WEST: WGS84Coordinate::EAST);

                        ////////////////////////////////////////////////////////

                        pos = pos + 1 + 1; // Consume value + ","

                        stringstream velocityStr;
                        char c = m_message.at(pos);
                        while (c != ',') {
                            velocityStr << c;
                            pos++;
                            c = m_message.at(pos);
                        }

                        pos = pos + 1; // Consume ","

                        stringstream directionStr;
                        c = m_message.at(pos);
                        while (c != ',') {
                            directionStr << c;
                            pos++;
                            c = m_message.at(pos);
                        }

                        pos = pos + 1; // Consume ","

                        stringstream ddmmStr(m_message.substr(pos, 4));

                        pos = pos + 4; // Consume value

                        stringstream yyStr(m_message.substr(pos, 2));
                        uint32_t yy;
                        yyStr >> yy;

                        stringstream dateTimeStr;
                        dateTimeStr << ddmmStr.str() << GPRMC::BASE_YEAR + yy << timeStr.str();
                        m_timeStamp = TimeStamp(dateTimeStr.str());

                        pos = pos + 2 + 1; // Consume value + ","

                        stringstream magneticDeviationStr;
                        c = m_message.at(pos);
                        while (c != ',') {
                            magneticDeviationStr << c;
                            pos++;
                            c = m_message.at(pos);
                        }

                        pos = pos + 1; // Consume ","

                        LON = m_message.at(pos);

                        pos = pos + 1 + 1; // Consume value + ","
                        type = m_message.at(pos);

                        pos = pos + 1 + 1; // Consume value + "*"
                        const uint32_t messageEnd = pos;

                        stringstream checksumStr(m_message.substr(pos));
                        uint32_t checksum;
                        checksumStr >> hex >> checksum;

                        uint32_t XOR = 0;
                        for(uint32_t i = 0; i < messageEnd; i++) {
                            XOR ^= m_message.at(i);
                        }

                        if (XOR != checksum) {
                            clog << "GPRMC corrupt!" << endl;
                        }
                    }
                }

                void GPRMC::encode() {
                    /*
                    $ – Start
                    GP – GPS-Data
                    RMC – recommended minimum sentence C
                    HHMMSS(.ss)? – UTC-Time of position
                    {A|V} – Data or warning
                    BBbb.bbbb – Latitude
                    {N|S} – norther or southern latitude
                    LLLll.llll – Longitude
                    {W|E} – western or eastern longitude
                    vv.v – Velocity in bend (Knoten)
                    dd.d – Direction in DEG
                    DDMMYY – Date
                    m.m {W|E} – magnetic deviation western or eastern
                    {A|D|E|N|S}? – Mode: autonomous, differential, estimated, invalid, simulated
                    *
                    ps – hex XOR check sum of the string between $ and *
                    */

                    //$GPRMC,162748,A,5214.0456,N,01103.4540,E,0.0,0.0,250309,0.0,E,A*17CRLF
                    stringstream sstr;
                    sstr << "$";
                    sstr << "GP";
                    sstr << "RMC" << ",";
                    sstr << m_timeStamp.getHour() << m_timeStamp.getMinute() << m_timeStamp.getSecond() << ",";

                    sstr << "A" << ",";

                    double latitude = m_coordinate.getLatitude();
                    uint32_t lat = static_cast<uint32_t>(latitude);
                    latitude -= lat;

                    stringstream latStr;
                    latStr.fill('0');
                    latStr.width(2);
                    latStr << lat;

                    stringstream latArcMinuteStr;
                    latArcMinuteStr.fill('0');
                    latArcMinuteStr.width(7);
                    latArcMinuteStr.precision(6);
                    latArcMinuteStr << latitude * 60;

                    sstr << latStr.str() << latArcMinuteStr.str() << ",";
                    sstr << ((m_coordinate.getLATITUDE() == WGS84Coordinate::NORTH) ? "N" : "S") << ",";

                    double longitude = m_coordinate.getLongitude();
                    uint32_t lon = static_cast<uint32_t>(longitude);
                    longitude -= lon;

                    stringstream lonStr;
                    lonStr.fill('0');
                    lonStr.width(3);
                    lonStr << lon;

                    stringstream lonArcMinuteStr;
                    lonArcMinuteStr.fill('0');
                    lonArcMinuteStr.width(7);
                    lonArcMinuteStr.precision(6);
                    lonArcMinuteStr << longitude * 60;

                    sstr << lonStr.str() << lonArcMinuteStr.str() << ",";
                    sstr << ((m_coordinate.getLONGITUDE() == WGS84Coordinate::WEST) ? "W" : "E") << ",";

                    sstr << "0.0" << ",";
                    sstr << "0.0" << ",";

                    stringstream day;
                    day.fill('0');
                    day.width(2);
                    day << m_timeStamp.getDay();

                    stringstream month;
                    month.fill('0');
                    month.width(2);
                    month << m_timeStamp.getMonth();

                    stringstream year;
                    year.fill('0');
                    year.width(2);
                    year << (m_timeStamp.getYear() - GPRMC::BASE_YEAR);

                    sstr << day.str() << month.str() << year.str() << ",";
                    sstr << "0.0" << ",";
                    sstr << ((m_coordinate.getLONGITUDE() == WGS84Coordinate::WEST) ? "W" : "E") << ",";
                    sstr << "S" << "*";

                    // Compute check sum.
                    string str = sstr.str();
                    unsigned char c = 0;
                    uint32_t XOR = 0;
                    for(uint32_t i = 0; i < str.size(); i++) {
                        c = str.at(i);
                        XOR ^= static_cast<uint32_t>(c);
                    }

                    // Write checksum.
                    sstr << hex << XOR;

                    // Write final CRLF.
                    sstr << endl;

                    m_message = sstr.str();
                }

                int32_t GPRMC::getID() const {
                    return 18;
                }

                const string GPRMC::getShortName() const {
                    return "GPRMC";
                }

                const string GPRMC::getLongName() const {
                    return "hesperia.data.sensor.nmea.GPRMC";
                }

                const string GPRMC::toString() const {
                    return m_message;
                }

                ostream& GPRMC::operator<<(ostream &out) const {
                    // Serialize this class.
                    SerializationFactory& sf=SerializationFactory::getInstance();

                    odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('m', 'e', 's', 's', 'a', 'g', 'e') >::RESULT,
                            m_message);

                    return out;
                }

                istream& GPRMC::operator>>(istream &in) {
                    // Deserialize this class.
                    SerializationFactory& sf=SerializationFactory::getInstance();

                    odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('m', 'e', 's', 's', 'a', 'g', 'e') >::RESULT,
                           m_message);

                    // Decode message.
                    decode();

                    return in;
                }

            }
        }
    }
} // opendlv::data::sensor::nmea
