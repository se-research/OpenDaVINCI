/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
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

#ifndef COCKPIT_PLUGINS_MESSAGETOTUPLEVISITOR_H_
#define COCKPIT_PLUGINS_MESSAGETOTUPLEVISITOR_H_

#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Visitor.h"

namespace odcore { namespace serialization { class Serializable; } }

namespace cockpit {

    namespace plugins {

        namespace livefeed {

            using namespace std;

            /**
             * This class is the container for the livefeed widget.
             */
            class MessageToTupleVisitor : public odcore::base::Visitor {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    MessageToTupleVisitor(const MessageToTupleVisitor &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    MessageToTupleVisitor& operator=(const MessageToTupleVisitor &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param entries Reference to the entries to be displayed.
                     */
                    MessageToTupleVisitor(vector<pair<string, string> > &entries);

                    virtual ~MessageToTupleVisitor();

                public:
                    virtual void beginVisit();
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
                    vector<pair<string, string> > &m_entries;
            };

        }
    }
}

#endif /* COCKPIT_PLUGINS_MESSAGETOTUPLEVISITOR_H_ */
