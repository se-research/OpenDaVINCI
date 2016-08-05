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

#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/reflection/CSVFromVisitableVisitor.h"

namespace odcore {
    namespace reflection {

        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::serialization;

        CSVFromVisitableVisitor::CSVFromVisitableVisitor(ostream &out, const bool &header, const char &delimiter) :
            m_buffer(out),
            m_header(),
            m_entry(),
            m_addHeader(header),
            m_delimiter(delimiter) {}

        CSVFromVisitableVisitor::~CSVFromVisitableVisitor() {}

        void CSVFromVisitableVisitor::beginVisit() {}

        void CSVFromVisitableVisitor::endVisit() {
            if (m_addHeader) {
                m_buffer << m_header.str() << endl;
                m_addHeader = false;
            }
            m_buffer << m_entry.str() << endl;
            m_buffer.flush();

            m_entry.str("");
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, Serializable &/*v*/) {
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, bool &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, char &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, unsigned char &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int8_t &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << (int32_t)v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int16_t &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << (int32_t)v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint16_t &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << (uint32_t)v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int32_t &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint32_t &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int64_t &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint64_t &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, float &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, double &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, string &v) {
            if (m_addHeader) {
                m_header << shortName << m_delimiter;
            }
            m_entry << v << m_delimiter;
        }

        void CSVFromVisitableVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, void */*data*/, const uint32_t &/*size*/) {
        }

    }
} // odcore::reflection

