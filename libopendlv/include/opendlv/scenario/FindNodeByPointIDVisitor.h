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

#ifndef HESPERIA_SCENARIO_FINDNODEBYPOINTIDVISITOR_H_
#define HESPERIA_SCENARIO_FINDNODEBYPOINTIDVISITOR_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/SerializableData.h"

#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/situation/PointID.h"
#include "opendlv/data/scenario/PointID.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/LaneModel.h"

namespace opendlv {
    namespace scenario {

        using namespace std;

        /**
         * This class finds a node by a given PointID.
         */
        class OPENDAVINCI_API FindNodeByPointIDVisitor : public data::scenario::ScenarioVisitor {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                FindNodeByPointIDVisitor(const FindNodeByPointIDVisitor &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                FindNodeByPointIDVisitor& operator=(const FindNodeByPointIDVisitor &);

            public:
                /**
                 * Constructor.
                 *
                 * @param pID PointID to look for.
                 */
                FindNodeByPointIDVisitor(const data::scenario::PointID &pID);

                /**
                 * Constructor.
                 *
                 * @param pID PointID to look for.
                 */
                FindNodeByPointIDVisitor(const data::situation::PointID &pID);

                virtual ~FindNodeByPointIDVisitor();

                virtual void visit(data::scenario::ScenarioNode &node);

                /**
                 * This method returns the LaneModel, if one could be found.
                 *
                 * @return LaneModel or NULL.
                 */
                const data::scenario::LaneModel* getLaneModel() const;

                /**
                 * This method returns the IDVertex3.
                 *
                 * @return IDVertex3.
                 */
                const data::scenario::IDVertex3 getIDVertex3() const;

            private:
                const data::scenario::PointID m_pointID;
                data::scenario::LaneModel *m_laneModel;
                data::scenario::IDVertex3 m_vertex;
        };

    }
} // opendlv::scenario

#endif /*HESPERIA_SCENARIO_FINDNODEBYPOINTIDVISITOR_H_*/
