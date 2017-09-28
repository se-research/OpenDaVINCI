/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
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

#include <iomanip>
#include <limits>
#include <sstream>

#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/reflection/CSVFromVisitableVisitor.h"

namespace odcore {
    namespace reflection {

        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::serialization;

        CSVFromVisitableVisitor::CSVFromVisitableVisitor(ostream &out, const bool &header, const char &delimiter, const string &headerPrefix) :
            m_buffer(out),
            m_header(),
            m_headerPrefix(headerPrefix),
            m_entry(),
            m_entryBackup(),
            m_addHeader(header),
            m_delimiter(delimiter) {}

        CSVFromVisitableVisitor::~CSVFromVisitableVisitor() {}

        void CSVFromVisitableVisitor::beginVisit(const int32_t &/*id*/, const string &/*shortName*/, const string &/*longName*/) {}

        void CSVFromVisitableVisitor::endVisit() {
            if (m_addHeader) {
                m_buffer << m_header.str() << endl;
                m_addHeader = false;
            }
            m_buffer << m_entry.str() << endl;
            m_buffer.flush();

            // To enable repeated use, m_entry will be reset.
            // To have access to the last entry, it will be backed up.
            m_entryBackup = m_entry.str();
            m_entry.str("");
        }

        string CSVFromVisitableVisitor::getHeader() const {
            return string(m_header.str());
        }

        string CSVFromVisitableVisitor::getEntry() const {
            return m_entryBackup;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, Serializable &v) {
            try {
                Visitable &visitable = dynamic_cast<Visitable&>(v);

                stringstream buffer;
                CSVFromVisitableVisitor csv(buffer, m_addHeader, m_delimiter, m_headerPrefix + shortName + ".");
                visitable.accept(csv);

                if (m_addHeader) {
                    m_header << csv.getHeader(); // No delimiter as the nested CSVFromVisitableVisitor has added a trailing m_delimiter already.
                }
                m_entry << csv.getEntry(); // No delimiter as the nested CSVFromVisitableVisitor has added a trailing m_delimiter already.
            }
            catch(...) {}
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, bool &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, char &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << static_cast<int32_t>(v) << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, unsigned char &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << static_cast<uint32_t>(v) << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int8_t &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << static_cast<int32_t>(v) << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int16_t &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << static_cast<int32_t>(v) << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint16_t &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << static_cast<uint32_t>(v) << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int32_t &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint32_t &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int64_t &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint64_t &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, float &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            const streamsize oldPrecision = m_entry.precision();
            m_entry.precision(numeric_limits<float>::digits10 + 1);
            m_entry << v << m_delimiter;
            m_entry.precision(oldPrecision);
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, double &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            const streamsize oldPrecision = m_entry.precision();
            m_entry.precision(numeric_limits<double>::digits10 + 1);
            m_entry << v << m_delimiter;
            m_entry.precision(oldPrecision);
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, string &v) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, void */*data*/, const uint32_t &/*size*/) {
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, void *data, const uint32_t &count, const odcore::TYPE_ &t) {
            if (m_addHeader) {
                m_header << (m_headerPrefix + shortName) << m_delimiter;
            }
            m_entry << "(";
            for(uint32_t i = 0; i < count; i++) {
                if (t == odcore::DOUBLE_T) { m_entry << *(static_cast<double*>(data)+i); }
                if (t == odcore::FLOAT_T) { m_entry << *(static_cast<float*>(data)+i); }
                if (t == odcore::UCHAR_T) { m_entry << *(static_cast<unsigned char*>(data)+i); }
                if (t == odcore::CHAR_T) { m_entry << *(static_cast<char*>(data)+i); }
                if (t == odcore::UINT8_T) { m_entry << (uint32_t)*(static_cast<uint8_t*>(data)+i); }
                if (t == odcore::INT8_T) { m_entry << (int32_t)*(static_cast<int8_t*>(data)+i); }
                if (t == odcore::UINT16_T) { m_entry << (uint32_t)*(static_cast<uint16_t*>(data)+i); }
                if (t == odcore::INT16_T) { m_entry << (int32_t)*(static_cast<int16_t*>(data)+i); }
                if (t == odcore::UINT32_T) { m_entry << *(static_cast<uint32_t*>(data)+i); }
                if (t == odcore::INT32_T) { m_entry << *(static_cast<int32_t*>(data)+i); }
                if (t == odcore::UINT64_T) { m_entry << *(static_cast<uint64_t*>(data)+i); }
                if (t == odcore::INT64_T) { m_entry << *(static_cast<int64_t*>(data)+i); }
                m_entry << (i+1<count ? "," : "");
            }
            m_entry << ")" << m_delimiter;
        }

    }
} // odcore::reflection

