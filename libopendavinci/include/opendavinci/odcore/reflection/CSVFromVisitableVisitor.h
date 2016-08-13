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

#ifndef OPENDAVINCI_CORE_REFLECTION_CSVFROMVISITABLEVISITOR_H_
#define OPENDAVINCI_CORE_REFLECTION_CSVFROMVISITABLEVISITOR_H_

#include <ostream>
#include <sstream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Visitor.h"

namespace odcore { namespace serialization { class Serializable; } }

namespace odcore {
    namespace reflection {

        using namespace std;

        /**
         * This class transforms a Visitable into a character separated output.
         */
        class CSVFromVisitableVisitor : public odcore::base::Visitor {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                CSVFromVisitableVisitor(const CSVFromVisitableVisitor &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                CSVFromVisitableVisitor& operator=(const CSVFromVisitableVisitor &);

            public:
                CSVFromVisitableVisitor();

                /**
                 * Constructor.
                 *
                 * @param out Buffer for the output.
                 * @param header Add human-readable header.
                 * @param delimiter Indent level.
                 */
                CSVFromVisitableVisitor(ostream &out, const bool &header = true, const char &delimiter = ',');

                virtual ~CSVFromVisitableVisitor();

            public:
                virtual void beginVisit(const int32_t &id, const string &shortName, const string &longName);
                virtual void endVisit();

                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, odcore::serialization::Serializable &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, bool &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, char &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, unsigned char &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int8_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int16_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, uint16_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int32_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, uint32_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int64_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, uint64_t &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, float &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, double &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, string &v);
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, void *data, const uint32_t &size);

            private:
                ostream &m_buffer;
                stringstream m_header;
                stringstream m_entry;
                bool m_addHeader;
                char m_delimiter;
        };

    }
} // odcore::reflection

#endif /*OPENDAVINCI_CORE_REFLECTION_CSVFROMVISITABLEVISITOR_H_*/
