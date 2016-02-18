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

#include <iostream>

#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/base/Mutex.h"
#include "opendlv/data/scenario/Scenario.h"
#include "opendlv/scenario/GroundBasedComplexModelLoader.h"
#include "opendlv/scenario/SCNXArchive.h"
#include "opendlv/scenario/ScenarioOpenGLSceneTransformation.h"
#include "opendlv/threeD/models/AerialImage.h"
#include "opendlv/threeD/NodeDescriptor.h"
#include "opendlv/threeD/TransformGroup.h"
#include "opendlv/threeD/decorator/DecoratorFactory.h"

namespace opendlv { namespace threeD { class Node; } }
namespace opendlv { namespace threeD { namespace loaders { class OBJXArchive; } } }

namespace opendlv {
    namespace threeD {
        namespace decorator {

            using namespace std;
            using namespace core::base;
            using namespace opendlv::data::environment;
            using namespace data::scenario;
            using namespace scenario;
            using namespace threeD::loaders;
            using namespace threeD::models;

            // Initialize singleton instance.
            Mutex DecoratorFactory::m_singletonMutex;
            DecoratorFactory* DecoratorFactory::m_singleton = NULL;

            DecoratorFactory::DecoratorFactory() {}

            DecoratorFactory::~DecoratorFactory() {
                DecoratorFactory::m_singleton = NULL;
            }

            DecoratorFactory& DecoratorFactory::getInstance() {
                {
                    Lock l(DecoratorFactory::m_singletonMutex);
                    if (DecoratorFactory::m_singleton == NULL) {
                        DecoratorFactory::m_singleton = new DecoratorFactory();
                    }
                }

                return (*DecoratorFactory::m_singleton);
            }

            Node* DecoratorFactory::decorate(scenario::SCNXArchive &scnxArchive) {
                return decorate(scnxArchive, true);
            }

            Node* DecoratorFactory::decorate(scenario::SCNXArchive &scnxArchive, const bool &showLaneConnectors) {
                TransformGroup *tg = new TransformGroup();

                Scenario &scenario = scnxArchive.getScenario();
                if (scnxArchive.getAerialImage() != NULL) {
                    clog << "AerialImage loaded." << endl;

                    Point3 origin(scenario.getGround().getAerialImage().getOriginX(), scenario.getGround().getAerialImage().getOriginY(), 0);
                    Point3 scaling(scenario.getGround().getAerialImage().getMeterPerPixelX(), scenario.getGround().getAerialImage().getMeterPerPixelY(), 0);

                    AerialImage *ai = new AerialImage(
                        NodeDescriptor("AerialImage"),
                        scnxArchive.getAerialImage(),
                        origin,
                        scaling,
                        static_cast<float> (scenario.getGround().getAerialImage().getRotationZ()));

                    tg->addChild(ai);
                }
                if (scnxArchive.getHeightImage() != NULL) {
                    clog << "HeightImage available but will be skipped." << endl;
/*
                    Point3 origin(scenario.getGround().getHeightImage().getOriginX(), scenario.getGround().getHeightImage().getOriginY(), 0);
                    Point3 scaling(scenario.getGround().getHeightImage().getMeterPerPixelX(), scenario.getGround().getHeightImage().getMeterPerPixelY(), 0);

                    HeightGrid *hg = new HeightGrid(NodeDescriptor("HeightGrid"), scnxArchive.getHeightImage(), origin, scaling, static_cast<float>(scenario.getGround().getHeightImage().getRotationZ()), static_cast<float>(scenario.getGround().getHeightImage().getGroundHeight()), static_cast<float>(scenario.getGround().getHeightImage().getMinimumHeight()), static_cast<float>(scenario.getGround().getHeightImage().getMaximumHeight()));
                    tg->addChild(hg);
*/
                }

                ScenarioOpenGLSceneTransformation scnOpenGL(showLaneConnectors);
                scenario.accept(scnOpenGL);

                tg->addChild(scnOpenGL.getRoot());

                // Load complex models.
                GroundBasedComplexModelLoader gbcml;
                TransformGroup *complexModels = gbcml.getGroundBasedComplexModels(scnxArchive);
                if (complexModels != NULL) {
                    tg->addChild(complexModels);
                }

                return tg;
            }

            Node* DecoratorFactory::decorate(loaders::OBJXArchive &objxArchive, const NodeDescriptor &nd) {
                return objxArchive.createTransformGroup(nd);
            }
        }
    }
} // opendlv::threeD::decorator
