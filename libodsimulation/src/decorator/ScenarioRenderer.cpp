/**
 * hesperia - Simulation environment
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

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/opendavinci.h"
#include "hesperia/data/scenario/ComplexModel.h"
#include "hesperia/data/scenario/HeightImage.h"
#include "hesperia/data/scenario/Image.h"
#include "hesperia/data/scenario/PointModel.h"
#include "hesperia/data/scenario/Polygon.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/Surroundings.h"
#include "hesperia/decorator/ScenarioRenderer.h"
#include "hesperia/decorator/models/OBJXArchiveFactory.h"
#include "hesperia/decorator/models/TriangleSet.h"

namespace hesperia { namespace scenario { class SCNXArchive; } }

namespace hesperia {
    namespace decorator {

class Renderer;
namespace models { class OBJXArchive; }

        using namespace std;
        using namespace core;
        using namespace core::base;
        using namespace core::data;
        using namespace hesperia::data::environment;
        using namespace hesperia::data::scenario;
        using namespace hesperia::decorator::models;

        ScenarioRenderer::ScenarioRenderer() :
            m_scenarioRendererMutex(),
            m_scnxArchive(NULL),
            m_renderer(NULL),
            m_mapOfGroundBasedComplexModels(),
            m_listOfLoadedOBJXArchives() {}

        ScenarioRenderer::~ScenarioRenderer() {
            Lock l(m_scenarioRendererMutex);

            m_mapOfGroundBasedComplexModels.clear();

            vector<OBJXArchive*>::iterator it = m_listOfLoadedOBJXArchives.begin();
            while (it != m_listOfLoadedOBJXArchives.end()) {
                OBJXArchive *objxArchive = (*it++);

                OPENDAVINCI_CORE_DELETE_POINTER(objxArchive);
            }
        }

        void ScenarioRenderer::setRenderer(Renderer *renderer) {
            Lock l(m_scenarioRendererMutex);
            m_renderer = renderer;
        }

        void ScenarioRenderer::setSCNXArchive(hesperia::scenario::SCNXArchive *scnxArchive) {
            Lock l(m_scenarioRendererMutex);
            m_scnxArchive = scnxArchive;
        }

        void ScenarioRenderer::visit(ScenarioNode &node) {
            try {
                Polygon &p = dynamic_cast<Polygon&>(node);
                visitPolygon(p);
            }
            catch(...) {}

            try {
                PointModel &p = dynamic_cast<PointModel&>(node);
                visitPointModel(p);
            }
            catch(...) {}

            try {
                Image &image = dynamic_cast<Image&>(node);
                visitImage(image);
            }
            catch(...) {}

            try {
                Surroundings &s = dynamic_cast<Surroundings&>(node);
                visitSurroundings(s);
            }
            catch(...) {}
        }

        void ScenarioRenderer::visitSurroundings(Surroundings &s) {
            Lock l(m_scenarioRendererMutex);
            if ( (m_scnxArchive != NULL) && (m_renderer != NULL) ) {
                const vector<Shape*> &listOfShapes = s.getListOfShapes();

                vector<Shape*>::const_iterator it = listOfShapes.begin();
                while (it != listOfShapes.end()) {
                    Shape *shape = (*it++);
                    if (shape != NULL) {
                        ComplexModel *cm = dynamic_cast<data::scenario::ComplexModel*>(shape);
                        if (cm != NULL) {
                            vector<TriangleSet> listOfTriangleSets = m_mapOfGroundBasedComplexModels[cm->toString()];

                            // Check if the complex model must be loaded first.
                            if (listOfTriangleSets.size() == 0) {
                                loadGroundBasedComplexModel(*cm);
                            }

                            // Draw list of triangle sets.
                            m_renderer->beginPainting();
                                m_renderer->drawListOfTriangleSets(listOfTriangleSets, cm->getPosition(), cm->getRotation());
                            m_renderer->endPainting();
                        }
                    }
                }
            }
        }

        void ScenarioRenderer::loadGroundBasedComplexModel(ComplexModel &cm) {
            SharedPointer<istream> in = m_scnxArchive->getModelData(cm.getModelFile());
            if (in.isValid()) {
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

                        m_mapOfGroundBasedComplexModels[cm.toString()] = listOfTriangleSets;
                    }
                    else {
                        clog << "OBJ model could not be opened." << endl;
                    }
                }
            }
        }

        void ScenarioRenderer::visitImage(Image &image) {
            try {
                HeightImage &hi = dynamic_cast<HeightImage&>(image);
                visitHeightImage(hi);
            }
            catch(...) {
                Lock l(m_scenarioRendererMutex);
                if ( (m_scnxArchive != NULL) && (m_scnxArchive->getAerialImage() != NULL) && (m_renderer != NULL) ) {
                    m_renderer->beginPainting();
                        m_renderer->drawImage(m_scnxArchive->getAerialImage(), Point3(image.getOriginX(), image.getOriginY(), 0), Point3(image.getMeterPerPixelX(), image.getMeterPerPixelY(), 0), image.getRotationZ());
                    m_renderer->endPainting();
                }
            }
        }

        void ScenarioRenderer::visitHeightImage(HeightImage &/*hi*/) {
            Lock l(m_scenarioRendererMutex);
            if ( (m_scnxArchive != NULL) && (m_scnxArchive->getHeightImage() != NULL) && (m_renderer != NULL) ) {

            }
        }

        void ScenarioRenderer::visitPolygon(Polygon &p) {
            Lock l(m_scenarioRendererMutex);
            if (m_renderer != NULL) {
                if (p.getListOfVertices().size() > 0) {
                    m_renderer->beginPainting();
                        m_renderer->setColor(p.getColor());
                        vector<Point3> listOfVertices = p.getListOfVerticesAsPoint3();
                        listOfVertices.push_back(*listOfVertices.begin()); // Close polygon by adding first vertex.
                        m_renderer->drawPolyLine(listOfVertices, p.getHeight());
                    m_renderer->endPainting();
                }
            }
        }

        void ScenarioRenderer::visitPointModel(PointModel &pointModel) {
            Lock l(m_scenarioRendererMutex);
            if (m_renderer != NULL) {
                if ( (pointModel.getLane() != NULL) && (pointModel.getLane()->getRoad() != NULL) && (pointModel.getLane()->getRoad()->getLayer() != NULL) ) {
                    const vector<IDVertex3> &listOfVertices = pointModel.getListOfIdentifiableVertices();
                    const uint32_t SIZE = listOfVertices.size();
                    if (SIZE > 1) {
                        m_renderer->beginPainting();
                        for (uint32_t i = 0; i < (SIZE-1); i++) {
                            // Get to adjacent vertices, determine direction, construct orthogonal direction
                            Point3 ptA = listOfVertices.at(i);
                            ptA.setZ(pointModel.getLane()->getRoad()->getLayer()->getHeight());

                            Point3 ptB = listOfVertices.at(i+1);
                            ptB.setZ(pointModel.getLane()->getRoad()->getLayer()->getHeight());

                            // Label Waypoints.
                            stringstream namePtA;
                            namePtA << pointModel.getLane()->getRoad()->getLayer()->getIdentifier() << "." << pointModel.getLane()->getRoad()->getIdentifier() << "." << pointModel.getLane()->getIdentifier() << "." << listOfVertices.at(i).getIdentifier();
                            m_renderer->setColor(Point3(0.7, 0.7, 0.7));
                            m_renderer->drawText(ptA, namePtA.str());

                            stringstream namePtB;
                            namePtB << pointModel.getLane()->getRoad()->getLayer()->getIdentifier() << "." << pointModel.getLane()->getRoad()->getIdentifier() << "." << pointModel.getLane()->getIdentifier() << "." << listOfVertices.at(i+1).getIdentifier();
                            m_renderer->setColor(Point3(0.7, 0.7, 0.7));
                            m_renderer->drawText(ptB, namePtB.str());

                            m_renderer->setColor(Point3(1, 0, 0));
                            m_renderer->setPointWidth(5);
                            m_renderer->drawPoint(ptA);
                            m_renderer->drawPoint(ptB);

                            Point3 colorSkeleton(0.2, 0.2, 0.2);
                            m_renderer->setColor(colorSkeleton);
                            m_renderer->setLineWidth(1);
                            m_renderer->drawLine(ptA, ptB);

                            const double halfWidth = pointModel.getLaneAttribute().getWidth() / 2.0;
                            if (halfWidth > 1) {
                                Point3 orthonormalDirection = (ptB - ptA);
                                orthonormalDirection.normalizeXY();
                                orthonormalDirection.setZ(0);
                                orthonormalDirection.rotateZ(cartesian::Constants::PI/2.0);

                                Point3 colorLeftMarking;
                                switch (pointModel.getLaneAttribute().getLeftLaneMarking()) {
                                    case LaneAttribute::SOLID_YELLOW:
                                    case LaneAttribute::DOUBLE_YELLOW:
                                        colorLeftMarking = Point3(1, 1, 0);
                                    break;

                                    case LaneAttribute::BROKEN_WHITE:
                                    case LaneAttribute::SOLID_WHITE:
                                        colorLeftMarking = Point3(1, 1, 1);
                                    break;

                                    case LaneAttribute::UNDEFINED:
                                    case LaneAttribute::CROSSWALK:
                                        colorLeftMarking = Point3(0.3, 0.3, 0.3);
                                    break;
                                }
                                Point3 leftLanePtA = ptA + (orthonormalDirection * halfWidth);
                                Point3 leftLanePtB = ptB + (orthonormalDirection * halfWidth);

                                m_renderer->setColor(colorLeftMarking);
                                m_renderer->setLineWidth(5);
                                m_renderer->drawLine(leftLanePtA, leftLanePtB);

                                // Draw right lane marking.
                                Point3 colorRightMarking;
                                switch (pointModel.getLaneAttribute().getRightLaneMarking()) {
                                    case LaneAttribute::SOLID_YELLOW:
                                    case LaneAttribute::DOUBLE_YELLOW:
                                        colorRightMarking = Point3(1, 1, 0);
                                    break;

                                    case LaneAttribute::BROKEN_WHITE:
                                    case LaneAttribute::SOLID_WHITE:
                                        colorRightMarking = Point3(1, 1, 1);
                                    break;

                                    case LaneAttribute::UNDEFINED:
                                    case LaneAttribute::CROSSWALK:
                                        colorRightMarking = Point3(0.3, 0.3, 0.3);
                                    break;
                                }
                                Point3 rightLanePtA = ptA - (orthonormalDirection * halfWidth);
                                Point3 rightLanePtB = ptB - (orthonormalDirection * halfWidth);

                                m_renderer->setColor(colorRightMarking);
                                m_renderer->setLineWidth(5);
                                m_renderer->drawLine(rightLanePtA, rightLanePtB);
                            }
                        }
                        m_renderer->endPainting();
                    }
                }
            }
        }

    }
} // hesperia::decorator
