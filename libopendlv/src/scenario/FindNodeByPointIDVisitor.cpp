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

#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/Arc.h"
#include "opendlv/data/scenario/Clothoid.h"
#include "opendlv/data/scenario/Road.h"
#include "opendlv/data/scenario/Lane.h"
#include "opendlv/data/scenario/Layer.h"
#include "opendlv/data/scenario/PointID.h"
#include "opendlv/data/scenario/PointModel.h"
#include "opendlv/data/scenario/ScenarioNode.h"
#include "opendlv/data/situation/PointID.h"
#include "opendlv/scenario/FindNodeByPointIDVisitor.h"

namespace opendlv { namespace data { namespace scenario { class LaneModel; } } }

namespace opendlv {
    namespace scenario {

        using namespace std;
        using namespace opendlv::data::scenario;
        using namespace opendlv::scenario;

        FindNodeByPointIDVisitor::FindNodeByPointIDVisitor(const PointID &pID) :
            m_pointID(pID),
            m_laneModel(NULL),
			m_vertex() {}

        FindNodeByPointIDVisitor::FindNodeByPointIDVisitor(const opendlv::data::situation::PointID &pID) :
            m_pointID(pID.toString()),
            m_laneModel(NULL),
			m_vertex() {}

        FindNodeByPointIDVisitor::~FindNodeByPointIDVisitor() {}

        void FindNodeByPointIDVisitor::visit(ScenarioNode &node) {
            try {
                Lane &lane = dynamic_cast<Lane&>(node);

                if ( (lane.getLaneModel() != NULL) && (lane.getRoad() != NULL) && (lane.getRoad()->getLayer() != NULL) ) {
                    if (    (lane.getID() == m_pointID.getLaneID())
                         && (lane.getRoad()->getID() == m_pointID.getRoadID())
                         && (lane.getRoad()->getLayer()->getID() == m_pointID.getLayerID()) ) {

                        // Checking for point in LaneModel.
                        try {
                            Arc *arc = dynamic_cast<Arc*>(lane.getLaneModel());
                            if (arc != NULL) {
                            	if (arc->getStart().getID() == m_pointID.getPointID()) {
                                    m_laneModel = arc;
                            		m_vertex = arc->getStart();
                            		return;
                            	}
                                if (arc->getEnd().getID() == m_pointID.getPointID()) {
                                    m_laneModel = arc;
                            		m_vertex = arc->getEnd();
                                    return;
                                }
                            }
                        }
                        catch(...) {}

                        try {
                            Clothoid *clothoid = dynamic_cast<Clothoid*>(lane.getLaneModel());
                            if (clothoid != NULL) {
                            	if (clothoid->getStart().getID() == m_pointID.getPointID()) {
                            		m_laneModel = clothoid;
                            		m_vertex = clothoid->getStart();
                            		return;
                            	}
                                if (clothoid->getEnd().getID() == m_pointID.getPointID()) {
                                    m_laneModel = clothoid;
                                    m_vertex = clothoid->getEnd();
                                    return;
                                }
                            }
                        }
                        catch(...) {}

                        try {
                            StraightLine *sl = dynamic_cast<StraightLine*>(lane.getLaneModel());
                            if (sl != NULL) {
                            	if (sl->getStart().getID() == m_pointID.getPointID()) {
                            		m_laneModel = sl;
                            		m_vertex = sl->getStart();
                            		return;
                            	}
                                if (sl->getEnd().getID() == m_pointID.getPointID()) {
                                    m_laneModel = sl;
                                    m_vertex = sl->getEnd();
                                    return;
                                }
                            }
                        }
                        catch(...) {}

                        try {
                            PointModel *pm = dynamic_cast<PointModel*>(lane.getLaneModel());
                            if (pm != NULL) {
                                const vector<IDVertex3> &listOfVertices = pm->getListOfIdentifiableVertices();
                                vector<IDVertex3>::const_iterator it = listOfVertices.begin();
                                while (it != listOfVertices.end()) {
                                    if ((*it).getID() == m_pointID.getPointID()) {
                                    	m_vertex = (*it);
                                        m_laneModel = pm;
                                        break;
                                    }
                                    it++;
                                }
                                return;
                            }
                        }
                        catch(...) {}
                    }
                }
            }
            catch(...)
            {}
        }

        const IDVertex3 FindNodeByPointIDVisitor::getIDVertex3() const {
        	return m_vertex;
        }

        const LaneModel* FindNodeByPointIDVisitor::getLaneModel() const {
            return m_laneModel;
        }

    }
} // opendlv::scenario
