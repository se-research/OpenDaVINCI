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

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendlv/data/environment/EgoState.h"
#include "opendlv/data/environment/Obstacle.h"
#include "opendlv/data/environment/OtherVehicleState.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/Polygon.h"
#include "opendlv/data/planning/Route.h"
#include "opendlv/data/sensor/ContouredObject.h"
#include "opendlv/data/sensor/ContouredObjects.h"
#include "opendlv/data/situation/ComplexModel.h"
#include "opendlv/data/situation/Object.h"
#include "opendlv/data/situation/Shape.h"
#include "opendlv/data/situation/Situation.h"
#include "opendlv/data/situation/Vertex3.h"
#include "opendlv/decorator/DataRenderer.h"
#include "opendlv/decorator/Renderer.h"
#include "opendlv/decorator/models/OBJXArchive.h"
#include "opendlv/decorator/models/OBJXArchiveFactory.h"
#include "opendlv/decorator/models/TriangleSet.h"
#include "opendlv/scenario/SCNXArchive.h"

namespace opendlv {
    namespace decorator {

        using namespace std;
        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace opendlv::data::environment;
        using namespace opendlv::data::environment;
        using namespace opendlv::data::planning;
        using namespace opendlv::data::sensor;
        using namespace opendlv::decorator::models;

        DataRenderer::DataRenderer() :
            m_dataRendererMutex(),
            m_renderer(NULL),
            m_scnxArchive(NULL),
            m_egoStateModel(),
            m_listOfLoadedOBJXArchives(),
            m_mapOfModels() {}

        DataRenderer::~DataRenderer() {
            Lock l(m_dataRendererMutex);

            vector<OBJXArchive*>::iterator it = m_listOfLoadedOBJXArchives.begin();
            while (it != m_listOfLoadedOBJXArchives.end()) {
                OBJXArchive *objxArchive = (*it++);

                OPENDAVINCI_CORE_DELETE_POINTER(objxArchive);
            }
        }

        void DataRenderer::draw(Container &c) {
            if (c.getDataType() == opendlv::data::environment::EgoState::ID()){
                draw(c.getData<EgoState>());
            }

            if (c.getDataType() == opendlv::data::sensor::ContouredObjects::ID()){
                draw(c.getData<ContouredObjects>());
            }

            if (c.getDataType() == opendlv::data::environment::Obstacle::ID()){
                draw(c.getData<Obstacle>());
            }

            if (c.getDataType() == opendlv::data::environment::OtherVehicleState::ID()){
                draw(c.getData<OtherVehicleState>());
            }

            if (c.getDataType() == opendlv::data::planning::Route::ID()){
                draw(c.getData<Route>());
            }
        }

        void DataRenderer::draw(const OtherVehicleState &o) {
            Lock l(m_dataRendererMutex);
            if (m_renderer != NULL) {
                // Look up model.
                map<uint32_t, vector<TriangleSet> >::iterator res = m_mapOfModels.find(o.getIdentifier());
                if (res != m_mapOfModels.end()) {
                    m_renderer->beginPainting();
                        // TODO: Rotation for OpenGL is given in Eulerian angles for X-axis, for Y-axis, and for Z-axis SEPERATELY!
                        Point3 dir(0, 0, o.getRotation().getAngleXY());
                        m_renderer->drawListOfTriangleSets(m_mapOfModels[o.getIdentifier()], o.getPosition(), dir);
                    m_renderer->endPainting();
                }
            }
        }

        void DataRenderer::draw(const ContouredObjects &cos) {
            Lock l(m_dataRendererMutex);
            if (m_renderer != NULL) {
                vector<ContouredObject> listOfContouredObjects = cos.getContouredObjects();
                vector<ContouredObject>::iterator it = listOfContouredObjects.begin();
                while (it != listOfContouredObjects.end()) {
                    m_renderer->beginPainting();
                        switch (cos.getColor()) {
                            case ContouredObjects::BLUE:
                                m_renderer->setColor(Point3(0, 0, 1));
                            break;
                            case ContouredObjects::GREEN:
                                m_renderer->setColor(Point3(0, 1, 0));
                            break;
                            case ContouredObjects::RED:
                                m_renderer->setColor(Point3(1, 0, 0));
                            break;
                            case ContouredObjects::YELLOW:
                                m_renderer->setColor(Point3(1, 1, 0));
                            break;
                        }

                        m_renderer->setPointWidth(1.0);
                        vector<Point3> contour = (*it).getContour();
                        vector<Point3>::iterator jt = contour.begin();
                        while (jt != contour.end()) {
                            m_renderer->drawPoint(*jt++);
                        }
                    m_renderer->endPainting();
                    it++;
                }
            }
        }

        void DataRenderer::draw(const EgoState &es) {
            Lock l(m_dataRendererMutex);
            if (m_renderer != NULL) {
                if (m_egoStateModel.size() > 0) {
                    // Use model of triangle sets for drawing.
                    m_renderer->beginPainting();
                        // TODO: Rotation for OpenGL is given in Eulerian angles for X-axis, for Y-axis, and for Z-axis SEPERATELY!
                        Point3 dir(0, 0, es.getRotation().getAngleXY());
                        m_renderer->drawListOfTriangleSets(m_egoStateModel, es.getPosition(), dir);
                    m_renderer->endPainting();
                }
                else {
                    // Use box.
                    Point3 p1(2, 1, 0);
                    Point3 p2(2, -1, 0);
                    Point3 p3(-2, -1, 0);
                    Point3 p4(-2, 1, 0);

                    p1.rotateZ(es.getRotation().getAngleXY());
                    p1 += es.getPosition();

                    p2.rotateZ(es.getRotation().getAngleXY());
                    p2 += es.getPosition();

                    p3.rotateZ(es.getRotation().getAngleXY());
                    p3 += es.getPosition();

                    p4.rotateZ(es.getRotation().getAngleXY());
                    p4 += es.getPosition();

                    vector<Point3> listOfPoints;
                    listOfPoints.push_back(p1);
                    listOfPoints.push_back(p2);
                    listOfPoints.push_back(p3);
                    listOfPoints.push_back(p4);
                    listOfPoints.push_back(p1);

                    m_renderer->beginPainting();
                        m_renderer->setColor(Point3(0.7, 0.7, 0.7));
                        m_renderer->setLineWidth(2.0);
                        m_renderer->drawPolyLine(listOfPoints, 1.0);
                    m_renderer->endPainting();
                }
            }
        }

        void DataRenderer::draw(const Obstacle &o) {
            Lock l(m_dataRendererMutex);
            if (m_renderer != NULL) {
                // Ignore other states.
                if (o.getState() == Obstacle::UPDATE) {
                    // Update obstacle.
                    m_renderer->beginPainting();
                        m_renderer->setColor(Point3(0, 1, 0));
                        m_renderer->setLineWidth(2.0);

                        // Add additional height to lift the obstacle from the ground.
                        vector<Point3> points;
                        vector<Point3> originalPoints = o.getPolygon().getVertices();
                        vector<Point3>::iterator it = originalPoints.begin();
                        while (it != originalPoints.end()) {
                            Point3 p = (*it++);
                            p.setZ(0.5);
                            points.push_back(p);
                        }
                        m_renderer->drawPolyLine(points);
                    m_renderer->endPainting();
                }
            }
        }

        void DataRenderer::draw(const Route &r) {
            Lock l(m_dataRendererMutex);
            if (m_renderer != NULL) {
                m_renderer->beginPainting();
                    m_renderer->setColor(Point3(0, 1, 1));
                    m_renderer->setLineWidth(2.0);

                    // Add additional height to lift the route from the ground.
                    vector<Point3> points;
                    vector<Point3> originalPoints = r.getListOfPoints();
                    vector<Point3>::iterator it = originalPoints.begin();
                    while (it != originalPoints.end()) {
                        Point3 p = (*it++);
                        p.setZ(0.05);
                        points.push_back(p);
                    }
                    m_renderer->drawPolyLine(points);
                m_renderer->endPainting();
            }
        }

        void DataRenderer::setEgoStateModel(const string &fn)  {
            Lock l(m_dataRendererMutex);

            cout << "Trying to load file stream to car model " << fn << endl;
            fstream fin(fn.c_str(), ios::in | ios::binary);

            OBJXArchive *objxArchive = OBJXArchiveFactory::getInstance().getOBJXArchive(fin);
            if (objxArchive != NULL) {
                m_egoStateModel = objxArchive->getListOfTriangleSets();

                if (m_egoStateModel.size() > 0) {
                    clog << "OBJ model successfully opened (containing " << m_egoStateModel.size() << " sets of triangles)." << endl;
                }
                else {
                    clog << "OBJ model could not be opened." << endl;
                }

                m_listOfLoadedOBJXArchives.push_back(objxArchive);
            }
        }

        void DataRenderer::setSCNXArchive(opendlv::scenario::SCNXArchive *scnxArchive) {
            Lock l(m_dataRendererMutex);
            m_scnxArchive = scnxArchive;

            if (m_scnxArchive != NULL) {
                // Remove any existing models.
                m_mapOfModels.clear();

            	// Load models from scenario by looping trough the (FIRST!) available situation.
                vector<opendlv::data::situation::Situation> listOfSituations = m_scnxArchive->getListOfSituations();
                if (listOfSituations.size() > 0) {
                	opendlv::data::situation::Situation situation = listOfSituations.front();

                	map<uint32_t, opendlv::data::situation::Object> mapOfObjects;
                	vector<opendlv::data::situation::Object> listOfObjects = situation.getListOfObjects();
                	vector<opendlv::data::situation::Object>::iterator it = listOfObjects.begin();
                	while (it != listOfObjects.end()) {
                		opendlv::data::situation::Object o = (*it++);

                		opendlv::data::situation::ComplexModel *cm = dynamic_cast<opendlv::data::situation::ComplexModel*>(o.getShape());
                		if (cm != NULL) {
                			// Load complexmodel from SCNXArchive.
                			loadComplexModel(o.getIdentifier(), *cm);
                		}
                	}
                }
            }
        }

        void DataRenderer::loadComplexModel(const uint32_t &id, opendlv::data::situation::ComplexModel &cm) {
            std::shared_ptr<istream> in = m_scnxArchive->getModelData(cm.getModelFile());
            if (in.get()) {
                // Load model.
                OBJXArchive *objxArchive = NULL;
                if (cm.getModelFile().find(".objx") != string::npos) {
                    objxArchive = OBJXArchiveFactory::getInstance().getOBJXArchive(*in);
                }
                else if (cm.getModelFile().find(".obj") != string::npos) {
                    objxArchive = OBJXArchiveFactory::getInstance().getOBJXArchiveFromPlainOBJFile(*in);
                }

                if (objxArchive != NULL) {
                    m_listOfLoadedOBJXArchives.push_back(objxArchive);

                    vector<TriangleSet> listOfTriangleSets = objxArchive->getListOfTriangleSets();

                    if (listOfTriangleSets.size() > 0) {
                        clog << "OBJ model successfully opened (containing " << listOfTriangleSets.size() << " sets of triangles)." << endl;
                        clog << "  Translation: " << cm.getPosition().toString() << endl;
                        clog << "  Rotation: " << cm.getRotation().toString() << endl;

                        m_mapOfModels[id] = listOfTriangleSets;
                    }
                    else {
                        clog << "OBJ model could not be opened." << endl;
                    }
                }
            }
        }

        void DataRenderer::setRenderer(Renderer *renderer) {
            Lock l(m_dataRendererMutex);
            m_renderer = renderer;
        }

    }
} // opendlv::decorator
