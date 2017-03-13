/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <ctime>

#include <iostream>
#include <sstream>
#include <memory>

#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/wrapper/Time.h"
#include "opendavinci/odcore/wrapper/TimeFactory.h"

namespace odcore {
    namespace data {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::serialization;

        TimeStamp::TimeStamp() :
            TimePoint(),
            m_readableYear(0),
            m_readableMonth(0),
            m_readableDayOfMonth(0),
            m_readableHours(0),
            m_readableMinutes(0),
            m_readableSeconds(0) {
            std::shared_ptr<odcore::wrapper::Time> time(odcore::wrapper::TimeFactory::getInstance().now());
            if (time.get()) {
                setSeconds(time->getSeconds());
                setMicroseconds(time->getPartialMicroseconds());
                computeHumanReadableRepresentation();
            }
        }

        TimeStamp::TimeStamp(const int32_t &seconds, const int32_t &microSeconds) :
            TimePoint(seconds, microSeconds),
            m_readableYear(0),
            m_readableMonth(0),
            m_readableDayOfMonth(0),
            m_readableHours(0),
            m_readableMinutes(0),
            m_readableSeconds(0) {
            computeHumanReadableRepresentation();
        }

        TimeStamp::TimeStamp(const string &ddmmyyyyhhmmss) :
            TimePoint(),
            m_readableYear(0),
            m_readableMonth(0),
            m_readableDayOfMonth(0),
            m_readableHours(0),
            m_readableMinutes(0),
            m_readableSeconds(0) {
            if (ddmmyyyyhhmmss.size() == 14) {
                stringstream dataDD;
                dataDD.str(ddmmyyyyhhmmss.substr(0, 2));
                uint32_t dd;
                dataDD >> dd;

                stringstream dataMM;
                dataMM.str(ddmmyyyyhhmmss.substr(2, 2));
                uint32_t mm;
                dataMM >> mm;

                stringstream dataYYYY;
                dataYYYY.str(ddmmyyyyhhmmss.substr(4, 4));
                uint32_t yyyy;
                dataYYYY >> yyyy;

                stringstream dataHour;
                dataHour.str(ddmmyyyyhhmmss.substr(8, 2));
                uint32_t hour;
                dataHour >> hour;

                stringstream dataMin;
                dataMin.str(ddmmyyyyhhmmss.substr(10, 2));
                uint32_t min;
                dataMin >> min;

                stringstream dataSec;
                dataSec.str(ddmmyyyyhhmmss.substr(12, 2));
                uint32_t sec;
                dataSec >> sec;

                const uint32_t yearsSince01011970 = (yyyy - 1970);
                uint32_t additionalLeapDays = 0;
                uint32_t year = 1970;
                for(uint32_t i = 0; i < yearsSince01011970; i++) {
                    if (isLeapYear(year)) {
                        additionalLeapDays++;
                    }
                    year++;
                }

                uint32_t cumulativeDays = 0;
                switch (mm) {
                    case 1:
                        cumulativeDays = 0;
                    break;
                    case 2:
                        cumulativeDays = TimeStamp::January;
                    break;
                    case 3:
                        cumulativeDays = TimeStamp::February;
                    break;
                    case 4:
                        cumulativeDays = TimeStamp::March;
                    break;
                    case 5:
                        cumulativeDays = TimeStamp::April;
                    break;
                    case 6:
                        cumulativeDays = TimeStamp::May;
                    break;
                    case 7:
                        cumulativeDays = TimeStamp::June;
                    break;
                    case 8:
                        cumulativeDays = TimeStamp::July;
                    break;
                    case 9:
                        cumulativeDays = TimeStamp::August;
                    break;
                    case 10:
                        cumulativeDays = TimeStamp::September;
                    break;
                    case 11:
                        cumulativeDays = TimeStamp::October;
                    break;
                    case 12:
                        cumulativeDays = TimeStamp::November;
                    break;
                }

                setSeconds((yearsSince01011970 * 365 + additionalLeapDays + cumulativeDays + dd - 1) * 24 * 60 * 60 + hour*60*60 + min*60 + sec);
                computeHumanReadableRepresentation();
            }
        }

        TimeStamp::TimeStamp(const TimeStamp &obj) :
            TimePoint(obj),
            m_readableYear(obj.m_readableYear),
            m_readableMonth(obj.m_readableMonth),
            m_readableDayOfMonth(obj.m_readableDayOfMonth),
            m_readableHours(obj.m_readableHours),
            m_readableMinutes(obj.m_readableMinutes),
            m_readableSeconds(obj.m_readableSeconds) {}

        TimeStamp::TimeStamp(const TimePoint &obj) :
            TimePoint(obj),
            m_readableYear(0),
            m_readableMonth(0),
            m_readableDayOfMonth(0),
            m_readableHours(0),
            m_readableMinutes(0),
            m_readableSeconds(0) {
            computeHumanReadableRepresentation();
        }

        TimeStamp::~TimeStamp() {}

        TimeStamp& TimeStamp::operator=(const TimeStamp &obj) {
            TimePoint::operator=(obj);
            m_readableYear = obj.m_readableYear;
            m_readableMonth = obj.m_readableMonth;
            m_readableDayOfMonth = obj.m_readableDayOfMonth;
            m_readableHours = obj.m_readableHours;
            m_readableMinutes = obj.m_readableMinutes;
            m_readableSeconds = obj.m_readableSeconds;
            computeHumanReadableRepresentation();
            return (*this);
        }

        TimeStamp TimeStamp::operator+(const TimeStamp & t) const {
            int32_t sumSeconds = getSeconds() + t.getSeconds();
            int32_t sumMicroseconds = getFractionalMicroseconds() + t.getFractionalMicroseconds();

            while (sumMicroseconds > 1000000L) {
                sumSeconds++;
                sumMicroseconds -= 1000000L;
            }

            return TimeStamp(sumSeconds, sumMicroseconds);
        }

        TimeStamp TimeStamp::operator-(const TimeStamp & t) const {
            int32_t deltaSeconds = getSeconds() - t.getSeconds();
            int32_t deltaMicroseconds = getFractionalMicroseconds() - t.getFractionalMicroseconds();

            while (deltaMicroseconds < 0) {
                deltaSeconds--;
                deltaMicroseconds += 1000000L;
            }

            return TimeStamp(deltaSeconds, deltaMicroseconds);
        }

        bool TimeStamp::operator==(const TimeStamp& t) const {
            return toMicroseconds() == t.toMicroseconds();
        }

        bool TimeStamp::operator!=(const TimeStamp& t) const {
            return toMicroseconds() != t.toMicroseconds();
        }

        bool TimeStamp::operator<(const TimeStamp& t) const
        {
            return toMicroseconds() < t.toMicroseconds();
        }

        bool TimeStamp::operator>(const TimeStamp& t) const
        {
            return toMicroseconds() > t.toMicroseconds();
        }

        bool TimeStamp::operator<=(const TimeStamp& t) const
        {
            return toMicroseconds() <= t.toMicroseconds();
        }

        bool TimeStamp::operator>=(const TimeStamp& t) const
        {
            return toMicroseconds() >= t.toMicroseconds();
        }

        int64_t TimeStamp::toMicroseconds() const {
            return getSeconds() * 1000000L + getFractionalMicroseconds();
        }

        int32_t TimeStamp::getFractionalMicroseconds() const {
            return getMicroseconds();
        }

        void TimeStamp::computeHumanReadableRepresentation() {
            const long int seconds = getSeconds();
            struct tm *tm = localtime(&seconds);

            m_readableYear = (1900 + tm->tm_year);
            m_readableMonth = (1 + tm->tm_mon);
            m_readableDayOfMonth = tm->tm_mday;
            m_readableHours = tm->tm_hour;
            m_readableMinutes = tm->tm_min;
            m_readableSeconds = tm->tm_sec;
        }

        uint32_t TimeStamp::getHour() const {
            return m_readableHours;
        }

        uint32_t TimeStamp::getMinute() const {
            return m_readableMinutes;
        }

        uint32_t TimeStamp::getSecond() const {
            return m_readableSeconds;
        }

        uint32_t TimeStamp::getDay() const {
            return m_readableDayOfMonth;
        }

        uint32_t TimeStamp::getMonth() const {
            return m_readableMonth;

        }

        uint32_t TimeStamp::getYear() const {
            return m_readableYear;
        }

        bool TimeStamp::isLeapYear(const uint32_t &year) const {
            bool retVal = false;
            if ( (year % 4) == 0 ) {
                if ( (year % 100) == 0) {
                    // Don't add leap day.
                    if ( (year % 400) == 0) {
                        // Add leap day.
                        retVal = true;
                    }
                }
                else {
                    // Add leap day.
                    retVal = true;
                }
            }
            return retVal;
        }

        const string TimeStamp::getYYYYMMDD_HHMMSS() const {
            const uint32_t MONTH = getMonth();
            const uint32_t DAY = getDay();
            const uint32_t HOUR = getHour();
            const uint32_t MINUTE = getMinute();
            const uint32_t SECOND = getSecond();

            stringstream s;
            s << getYear() << "-" << ( (MONTH < 10) ? "0" : "" ) << MONTH << "-" << ( (DAY < 10) ? "0" : "" ) << DAY
                           << " " << ( (HOUR < 10) ? "0" : "" ) << HOUR
                           << ":" << ( (MINUTE < 10) ? "0" : "" ) << MINUTE
                           << ":" << ( (SECOND < 10) ? "0" : "" ) << SECOND;
            return s.str();
        }

        const string TimeStamp::getYYYYMMDD_HHMMSS_noBlank() const {
            const uint32_t MONTH = getMonth();
            const uint32_t DAY = getDay();
            const uint32_t HOUR = getHour();
            const uint32_t MINUTE = getMinute();
            const uint32_t SECOND = getSecond();

            stringstream s;
            s << getYear() << "-" << ( (MONTH < 10) ? "0" : "" ) << MONTH << "-" << ( (DAY < 10) ? "0" : "" ) << DAY
                           << "_" << ( (HOUR < 10) ? "0" : "" ) << HOUR
                           << ":" << ( (MINUTE < 10) ? "0" : "" ) << MINUTE
                           << ":" << ( (SECOND < 10) ? "0" : "" ) << SECOND;
            return s.str();
        }

        const string TimeStamp::getYYYYMMDD_HHMMSSms() const {
            stringstream s;
            s << getYYYYMMDD_HHMMSS() << "." << getMicroseconds();
            return s.str();
        }

    }
} // odcore::data
