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

#include "core/macros.h"
#include "generated/cartesian/Constants.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/scenegraph/SceneNode.h"
#include "hesperia/scenegraph/SceneNodeDescriptor.h"
#include "hesperia/scenegraph/models/SimpleCar.h"
#include "hesperia/scenegraph/primitives/Line.h"

namespace hesperia {
    namespace scenegraph {
        namespace models {

            using namespace std;
            using namespace core::data;
            using namespace hesperia::data::environment;
            using namespace hesperia::scenegraph::primitives;

            /**
             * This class represents a simple car:
             *
             * ---------Length------------
             * |                         |
             * |                         W
             * |                         i      \
             * |           X-------------d-------+
             * |                         t      /
             * |                         h
             * |                         |
             * ---------Length------------
             *
             * X = Position, + = ROTZ.
             */

            SimpleCar::SimpleCar(const SceneNodeDescriptor &sceneNodeDescriptor, const double &length, const double &width, const hesperia::data::environment::Point3 &position, const double &rotZ, const hesperia::data::environment::Point3 &color, const float &height) :
                SceneNode(sceneNodeDescriptor),
                m_length(length),
                m_width(width),
                m_color(color),
                m_height(height),
                m_rearLeft(NULL),
                m_rearRight(NULL),
                m_sideLeft(NULL),
                m_sideRight(NULL),
                m_front(NULL),
                m_arrowLeft(NULL),
                m_arrowRight(NULL),
                m_arrowRear(NULL) {

                m_rearLeft = new Line(sceneNodeDescriptor, Point3(), Point3(), color, 1);
                m_rearRight = new Line(sceneNodeDescriptor, Point3(), Point3(), color, 1);
                m_sideLeft = new Line(sceneNodeDescriptor, Point3(), Point3(), color, 1);
                m_sideRight = new Line(sceneNodeDescriptor, Point3(), Point3(), color, 1);
                m_front = new Line(sceneNodeDescriptor, Point3(), Point3(), color, 1);
                m_arrowLeft = new Line(sceneNodeDescriptor, Point3(), Point3(), color, 1);
                m_arrowRight = new Line(sceneNodeDescriptor, Point3(), Point3(), color, 1);
                m_arrowRear = new Line(sceneNodeDescriptor, Point3(), Point3(), color, 1);

                addChild(m_rearLeft);
                addChild(m_rearRight);
                addChild(m_sideLeft);
                addChild(m_sideRight);
                addChild(m_front);
                addChild(m_arrowLeft);
                addChild(m_arrowRight);
                addChild(m_arrowRear);

                setPosition(position, rotZ);
            }

            SimpleCar::SimpleCar(const SimpleCar &obj) :
                SceneNode(obj.getSceneNodeDescriptor()),
                m_length(obj.m_length),
                m_width(obj.m_width),
                m_color(obj.m_color),
                m_height(obj.m_height),
                m_rearLeft(NULL),
                m_rearRight(NULL),
                m_sideLeft(NULL),
                m_sideRight(NULL),
                m_front(NULL),
                m_arrowLeft(NULL),
                m_arrowRight(NULL),
                m_arrowRear(NULL) {

                m_rearLeft = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_rearRight = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_sideLeft = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_sideRight = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_front = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_arrowLeft = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_arrowRight = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_arrowRear = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);

                addChild(m_rearLeft);
                addChild(m_rearRight);
                addChild(m_sideLeft);
                addChild(m_sideRight);
                addChild(m_front);
                addChild(m_arrowLeft);
                addChild(m_arrowRight);
                addChild(m_arrowRear);

                setPosition(Point3(), 0);
            }

            SimpleCar& SimpleCar::operator=(const SimpleCar &obj) {
                setSceneNodeDescriptor(obj.getSceneNodeDescriptor());
                m_length = obj.m_length;
                m_width = obj.m_width;
                m_color = obj.m_color;
                m_height = obj.m_height;

                OPENDAVINCI_CORE_DELETE_POINTER(m_rearLeft);
                OPENDAVINCI_CORE_DELETE_POINTER(m_rearRight);
                OPENDAVINCI_CORE_DELETE_POINTER(m_sideLeft);
                OPENDAVINCI_CORE_DELETE_POINTER(m_sideRight);
                OPENDAVINCI_CORE_DELETE_POINTER(m_front);
                OPENDAVINCI_CORE_DELETE_POINTER(m_arrowLeft);
                OPENDAVINCI_CORE_DELETE_POINTER(m_arrowRight);
                OPENDAVINCI_CORE_DELETE_POINTER(m_arrowRear);

                m_rearLeft = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_rearRight = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_sideLeft = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_sideRight = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_front = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_arrowLeft = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_arrowRight = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);
                m_arrowRear = new Line(obj.getSceneNodeDescriptor(), Point3(), Point3(), obj.m_color, 1);

                addChild(m_rearLeft);
                addChild(m_rearRight);
                addChild(m_sideLeft);
                addChild(m_sideRight);
                addChild(m_front);
                addChild(m_arrowLeft);
                addChild(m_arrowRight);
                addChild(m_arrowRear);

                setPosition(Point3(), 0);

                return *this;
            }

            SimpleCar::~SimpleCar() {}

            void SimpleCar::setPosition(const hesperia::data::environment::Point3 &positionCenter, const double &rotZ) {
                Point3 positionCenterRearAxle(-m_length/2.0, 0, 0);
                positionCenterRearAxle.rotateZ(rotZ);
                positionCenterRearAxle += positionCenter;

                Point3 rearLeft(m_width/2.0, 0, 0);
                rearLeft.rotateZ(rotZ + 90*cartesian::Constants::DEG2RAD);

                Point3 rearRight(m_width/2.0, 0, 0);
                rearRight.rotateZ(rotZ - 90*cartesian::Constants::DEG2RAD);

                Point3 top(m_length, 0, 0);
                top.rotateZ(rotZ);

                Point3 topLeft(m_length, 0, 0);
                topLeft.rotateZ(rotZ);
                topLeft += rearLeft;

                Point3 topRight(m_length, 0, 0);
                topRight.rotateZ(rotZ);
                topRight += rearRight;

                Point3 arrowLeft(m_length * 0.75, 0, 0);
                arrowLeft.rotateZ(rotZ);
                arrowLeft += rearLeft;

                Point3 arrowRight(m_length * 0.75, 0, 0);
                arrowRight.rotateZ(rotZ);
                arrowRight += rearRight;

                // Translate points wrt. to position.
                rearLeft += positionCenterRearAxle;
                rearRight += positionCenterRearAxle;
                topLeft += positionCenterRearAxle;
                topRight += positionCenterRearAxle;
                top += positionCenterRearAxle;
                arrowLeft += positionCenterRearAxle;
                arrowRight += positionCenterRearAxle;

                m_rearLeft->setA(positionCenterRearAxle);
                m_rearLeft->setB(rearLeft);

                m_rearRight->setA(positionCenterRearAxle);
                m_rearRight->setB(rearRight);

                m_sideLeft->setA(rearLeft);
                m_sideLeft->setB(topLeft);

                m_sideRight->setA(rearRight);
                m_sideRight->setB(topRight);

                m_front->setA(topLeft);
                m_front->setB(topRight);

                m_arrowLeft->setA(top);
                m_arrowLeft->setB(arrowLeft);

                m_arrowRight->setA(top);
                m_arrowRight->setB(arrowRight);

                m_arrowRear->setA(arrowLeft);
                m_arrowRear->setB(arrowRight);
            }

        }
    }
}  // hesperia::scenegraph::models

