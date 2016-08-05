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

#include <iostream>
#include <sstream>
#include <memory>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/wrapper/Time.h"
#include "opendavinci/odcore/wrapper/TimeFactory.h"

namespace odcore {
    namespace data {

        using namespace std;
        using namespace base;

        TimeStamp::TimeStamp() :
            m_seconds(0),
            m_microseconds(0) {
            std::shared_ptr<odcore::wrapper::Time> time(odcore::wrapper::TimeFactory::getInstance().now());
            if (time.get()) {
                m_seconds = time->getSeconds();
                m_microseconds = time->getPartialMicroseconds();
            }
        }

        TimeStamp::TimeStamp(const int32_t &seconds, const int32_t &microSeconds) :
            m_seconds(seconds),
            m_microseconds(microSeconds) {}

        TimeStamp::TimeStamp(const string &ddmmyyyyhhmmss) :
            m_seconds(0),
            m_microseconds(0) {
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

                m_seconds = (yearsSince01011970 * 365 + additionalLeapDays + cumulativeDays + dd - 1) * 24 * 60 * 60 + hour*60*60 + min*60 + sec;
            }
        }

        TimeStamp::TimeStamp(const TimeStamp &obj) :
            SerializableData(),
            m_seconds(obj.m_seconds),
            m_microseconds(obj.m_microseconds) {}

        TimeStamp::~TimeStamp() {}

        TimeStamp& TimeStamp::operator=(const TimeStamp &obj) {
            m_seconds = obj.m_seconds;
            m_microseconds = obj.m_microseconds;
            return (*this);
        }

        TimeStamp TimeStamp::operator+(const TimeStamp & t) const {
            int32_t sumSeconds = m_seconds + t.getSeconds();
            int32_t sumMicroseconds = m_microseconds + t.getFractionalMicroseconds();

            while (sumMicroseconds > 1000000L) {
                sumSeconds++;
                sumMicroseconds -= 1000000L;
            }

            return TimeStamp(sumSeconds, sumMicroseconds);
        }

        TimeStamp TimeStamp::operator-(const TimeStamp & t) const {
            int32_t deltaSeconds = m_seconds - t.getSeconds();
            int32_t deltaMicroseconds = m_microseconds - t.getFractionalMicroseconds();

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

        long TimeStamp::toMicroseconds() const {
            return getSeconds() * 1000000L + getFractionalMicroseconds();
        }

        int32_t TimeStamp::getFractionalMicroseconds() const {
            return m_microseconds;
        }

        int32_t TimeStamp::getSeconds() const {
            return m_seconds;
        }

        uint32_t TimeStamp::getHour() const {
            const int32_t seconds = getSeconds();
            const int32_t daysSince01011970 = seconds / (60*60*24);
            const int32_t secondsSinceMidnight = seconds - daysSince01011970 * 60*60*24;
            const int32_t hour = secondsSinceMidnight / (60*60);
            return hour;
        }

        uint32_t TimeStamp::getMinute() const {
            const int32_t seconds = getSeconds();
            const int32_t daysSince01011970 = seconds / (60*60*24);
            const int32_t secondsSinceMidnight = seconds - daysSince01011970 * (60*60*24);
            const int32_t hour = secondsSinceMidnight / (60*60);
            const int32_t minute = static_cast<int32_t>((static_cast<double>(secondsSinceMidnight) / (60.0*60.0) - hour) * 60);
            return minute;
        }

        uint32_t TimeStamp::getSecond() const {
            const int32_t seconds = getSeconds();
            const int32_t daysSince01011970 = seconds / (60*60*24);
            const int32_t secondsSinceMidnight = seconds - daysSince01011970 * 60*60*24;
            const int32_t hour = secondsSinceMidnight / (60*60);
            const int32_t minute = static_cast<int32_t>((static_cast<double>(secondsSinceMidnight) / (60.0*60.0) - hour) * 60);
            return secondsSinceMidnight - hour*60*60 - minute*60;
        }

        uint32_t TimeStamp::getDay() const {
            const int32_t seconds = getSeconds();
            const int32_t daysSince01011970 = seconds / (60*60*24);
            const int32_t yearsSince01011970 = daysSince01011970 / 365;

            uint32_t additionalLeapDays = 0;
            uint32_t year = 1970;
            for(int32_t i = 0; i < yearsSince01011970; i++) {
                if (isLeapYear(year)) {
                    additionalLeapDays++;
                }
                year++;
            }

            const int32_t days = daysSince01011970 - yearsSince01011970*365 - additionalLeapDays + 1; // 01.01.1970 is the 0. day.
            uint32_t day = days;
            if (days > TimeStamp::January) {
                day = days - TimeStamp::January;
            }
            if (days > TimeStamp::February) {
                day = days - TimeStamp::February;
            }
            if (days > TimeStamp::March) {
                day = days - TimeStamp::March;
            }
            if (days > TimeStamp::April) {
                day = days - TimeStamp::April;
            }
            if (days > TimeStamp::May) {
                day = days - TimeStamp::May;
            }
            if (days > TimeStamp::June) {
                day = days - TimeStamp::June;
            }
            if (days > TimeStamp::July) {
                day = days - TimeStamp::July;
            }
            if (days > TimeStamp::August) {
                day = days - TimeStamp::August;
            }
            if (days > TimeStamp::September) {
                day = days - TimeStamp::September;
            }
            if (days > TimeStamp::October) {
                day = days - TimeStamp::October;
            }
            if (days > TimeStamp::November) {
                day = days - TimeStamp::November;
            }

            return day;
        }

        uint32_t TimeStamp::getMonth() const {
            const int32_t seconds = getSeconds();
            const int32_t daysSince01011970 = seconds / (60*60*24);
            const int32_t yearsSince01011970 = daysSince01011970 / 365;

            uint32_t additionalLeapDays = 0;
            uint32_t year = 1970;
            for(int32_t i = 0; i < yearsSince01011970; i++) {
                if (isLeapYear(year)) {
                    additionalLeapDays++;
                }
                year++;
            }

            const int32_t days = daysSince01011970 - yearsSince01011970*365 - additionalLeapDays;
            uint32_t month = 1;
            if (days < TimeStamp::December) {
                month = 12;
            }
            if (days < TimeStamp::November) {
                month = 11;
            }
            if (days < TimeStamp::October) {
                month = 10;
            }
            if (days < TimeStamp::September) {
                month = 9;
            }
            if (days < TimeStamp::August) {
                month = 8;
            }
            if (days < TimeStamp::July) {
                month = 7;
            }
            if (days < TimeStamp::June) {
                month = 6;
            }
            if (days < TimeStamp::May) {
                month = 5;
            }
            if (days < TimeStamp::April) {
                month = 4;
            }
            if (days < TimeStamp::March) {
                month = 3;
            }
            if (days < TimeStamp::February) {
                month = 2;
            }
            if (days < TimeStamp::January) {
                month = 1;
            }

            return month;
        }

        uint32_t TimeStamp::getYear() const {
            const int32_t seconds = getSeconds();
            const int32_t daysSince01011970 = seconds / (60*60*24);
            const int32_t yearsSince01011970 = static_cast<int>(daysSince01011970 / 365.24);
            return 1970 + yearsSince01011970;
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

        const string TimeStamp::getYYYYMMDD_HHMMSSms() const {
            stringstream s;
            s << getYYYYMMDD_HHMMSS() << "." << m_microseconds;
            return s.str();
        }

        int32_t TimeStamp::getID() const {
            return 12;
        }

        const string TimeStamp::getShortName() const {
            return "TimeStamp";
        }

        const string TimeStamp::getLongName() const {
            return "core.data.TimeStamp";
        }

        int32_t TimeStamp::ID() {
            return 12;
        }

        const string TimeStamp::ShortName() {
            return "TimeStamp";
        }

        const string TimeStamp::LongName() {
            return "core.data.TimeStamp";
        }

        const string TimeStamp::toString() const {
            stringstream s;
            s << m_seconds << "s/" << m_microseconds << "us.";
            return s.str();
        }

        void TimeStamp::accept(Visitor &v) {
            v.beginVisit();
            v.visit(1, "TimeStamp.seconds", "seconds", m_seconds);
            v.visit(2, "TimeStamp.microseconds", "microseconds", m_microseconds);
            v.endVisit();
        }

        ostream& TimeStamp::operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();;

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(1, m_seconds);

            s->write(2, m_microseconds);

            return out;
        }

        istream& TimeStamp::operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();;

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(1, m_seconds);

            d->read(2, m_microseconds);

            return in;
        }

    }
} // odcore::data
