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
#include "opendavinci/odcore/data/SerializableData.h"
#include "plugins/livefeed/MessageToTupleVisitor.h"

namespace cockpit {

    namespace plugins {

        namespace livefeed {

            using namespace std;
            using namespace odcore::base;

            MessageToTupleVisitor::MessageToTupleVisitor(vector<pair<string, string> > &entries) :
                m_entries(entries) {}

            MessageToTupleVisitor::~MessageToTupleVisitor() {}

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, odcore::serialization::Serializable &v) {
                try {
                    odcore::data::SerializableData& tmp = dynamic_cast<odcore::data::SerializableData&>(v);
                    m_entries.push_back(make_pair(shortName, tmp.toString()));
                }
                catch(...) {
                    m_entries.push_back(make_pair(shortName, "Could not display Serializable."));
                }
            }

            void MessageToTupleVisitor::beginVisit(const int32_t &/*id*/, const string &/*shortName*/, const string &/*longName*/) {}
            void MessageToTupleVisitor::endVisit() {}

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, bool &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, char &v) {
                stringstream sstr;
                sstr << static_cast<int32_t>(v);
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, unsigned char &v) {
                stringstream sstr;
                sstr << static_cast<uint32_t>(v);
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int8_t &v) {
                stringstream sstr;
                sstr << static_cast<int32_t>(v);
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int16_t &v) {
                stringstream sstr;
                sstr << static_cast<int32_t>(v);
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint16_t &v) {
                stringstream sstr;
                sstr << static_cast<uint32_t>(v);
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int32_t &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint32_t &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, int64_t &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, uint64_t &v) {
                stringstream sstr;
                sstr << v;
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, float &v) {
                stringstream sstr;
                sstr << setprecision(10) << v << setprecision(6);
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, double &v) {
                stringstream sstr;
                sstr << setprecision(10) << v << setprecision(6);
                m_entries.push_back(make_pair(shortName, sstr.str()));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, string &v) {
                m_entries.push_back(make_pair(shortName, v));
            }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &shortName, void */*data*/, const uint32_t &/*size*/) {
               m_entries.push_back(make_pair(shortName, "Could not display data."));
             }

            void MessageToTupleVisitor::visit(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, void */*data*/, const uint32_t &/*count*/, const odcore::TYPE_ &/*t*/) {
                std::cerr << "cockpit::plugins::livefeed::MessageToTupleVisitor::visit not implemented." << std::endl;
            }

        }
    }
}

