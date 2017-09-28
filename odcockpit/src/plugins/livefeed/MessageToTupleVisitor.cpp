/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#include <iomanip>
#include <ostream>

#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "plugins/livefeed/MessageToTupleVisitor.h"

namespace cockpit {

    namespace plugins {

        namespace livefeed {

            using namespace std;
            using namespace odcore::base;

            MessageToTupleVisitor::MessageToTupleVisitor(vector<pair<string, string> > &entries, const string &prefixForFieldName) :
                m_prefixForFieldName(prefixForFieldName),
                m_entries(entries) {}

            MessageToTupleVisitor::~MessageToTupleVisitor() {}

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, odcore::serialization::Serializable &v) {
                try {
                    Visitable &visitable = dynamic_cast<Visitable&>(v);

                    MessageToTupleVisitor visitor(m_entries, shortName + ".");
                    visitable.accept(visitor);
                }
                catch(...) {}
            }

            void MessageToTupleVisitor::beginVisit(const int32_t &/*id*/, const string &/*shortName*/, const string &/*longName*/) {}
            void MessageToTupleVisitor::endVisit() {}

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, bool &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, char &v) {
                stringstream sstr;
                sstr << static_cast<int32_t>(v);
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, unsigned char &v) {
                stringstream sstr;
                sstr << static_cast<uint32_t>(v);
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int8_t &v) {
                stringstream sstr;
                sstr << static_cast<int32_t>(v);
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int16_t &v) {
                stringstream sstr;
                sstr << static_cast<int32_t>(v);
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint16_t &v) {
                stringstream sstr;
                sstr << static_cast<uint32_t>(v);
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int32_t &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint32_t &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int64_t &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint64_t &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, float &v) {
                stringstream sstr;
                sstr << setprecision(10) << v << setprecision(6);
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, double &v) {
                stringstream sstr;
                sstr << setprecision(10) << v << setprecision(6);
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, string &v) {
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, v));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, void */*data*/, const uint32_t &/*size*/) {
               m_entries.push_back(make_pair(m_prefixForFieldName + shortName, "Could not display data."));
             }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, void *data, const uint32_t &count, const odcore::TYPE_ &t) {
                stringstream entry;
                entry << "(";
                for(uint32_t i = 0; i < count; i++) {
                    if (t == odcore::DOUBLE_T) { entry << *(static_cast<double*>(data)+i); }
                    if (t == odcore::FLOAT_T) { entry << *(static_cast<float*>(data)+i); }
                    if (t == odcore::UCHAR_T) { entry << *(static_cast<unsigned char*>(data)+i); }
                    if (t == odcore::CHAR_T) { entry << *(static_cast<char*>(data)+i); }
                    if (t == odcore::UINT8_T) { entry << (uint32_t)*(static_cast<uint8_t*>(data)+i); }
                    if (t == odcore::INT8_T) { entry << (int32_t)*(static_cast<int8_t*>(data)+i); }
                    if (t == odcore::UINT16_T) { entry << (uint32_t)*(static_cast<uint16_t*>(data)+i); }
                    if (t == odcore::INT16_T) { entry << (int32_t)*(static_cast<int16_t*>(data)+i); }
                    if (t == odcore::UINT32_T) { entry << *(static_cast<uint32_t*>(data)+i); }
                    if (t == odcore::INT32_T) { entry << *(static_cast<int32_t*>(data)+i); }
                    if (t == odcore::UINT64_T) { entry << *(static_cast<uint64_t*>(data)+i); }
                    if (t == odcore::INT64_T) { entry << *(static_cast<int64_t*>(data)+i); }
                    entry << (i+1<count ? ", " : "");
                }
                entry << ")";
                const string s = entry.str();
                m_entries.push_back(make_pair(m_prefixForFieldName + shortName, s));
            }

        }
    }
}

