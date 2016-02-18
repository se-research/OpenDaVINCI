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

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/opendavinci.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/scenario/ComplexModel.h"
#include "opendlv/data/scenario/Vertex3.h"
#include "opendlv/scenario/GroundBasedComplexModelLoader.h"
#include "opendlv/scenario/SCNXArchive.h"
#include "opendlv/threeD/NodeDescriptor.h"
#include "opendlv/threeD/TransformGroup.h"
#include "opendlv/threeD/loaders/OBJXArchive.h"
#include "opendlv/threeD/loaders/OBJXArchiveFactory.h"

namespace hesperia { namespace threeD { class Node; } }

namespace hesperia {
    namespace scenario {

        using namespace std;
        using namespace core;
        using namespace hesperia::data::environment;
        using namespace data::scenario;
        using namespace scenario;
        using namespace threeD;
        using namespace threeD::loaders;

        GroundBasedComplexModelLoader::GroundBasedComplexModelLoader() {}

        GroundBasedComplexModelLoader::~GroundBasedComplexModelLoader() {}

        TransformGroup* GroundBasedComplexModelLoader::getGroundBasedComplexModels(const SCNXArchive &scnxArchive) const {
            TransformGroup *complexModels = new TransformGroup();

            // Get list of all ground based complex models.
            vector<ComplexModel*> listOfComplexModels = scnxArchive.getListOfGroundBasedComplexModels();

            // Iterate over all ground based complex models and try to build a transform group.
            vector<ComplexModel*>::iterator jt = listOfComplexModels.begin();
            while (jt != listOfComplexModels.end()) {
                ComplexModel *cm = (*jt++);
                SharedPointer<istream> in = scnxArchive.getModelData(cm->getModelFile());
                if (in.isValid()) {
                    Node *model = NULL;

                    // Check model.
                    OBJXArchive *objxArchive = NULL;
                    if (cm->getModelFile().find(".objx") != string::npos) {
                        objxArchive = OBJXArchiveFactory::getInstance().getOBJXArchive(*in);
                    } else if (cm->getModelFile().find(".obj") != string::npos) {
                        objxArchive = OBJXArchiveFactory::getInstance().getOBJXArchiveFromPlainOBJFile(*in);
                    }

                    if (objxArchive != NULL) {
                        model = objxArchive->createTransformGroup(NodeDescriptor(cm->getName()));

                        if (model != NULL) {
                            clog << "OBJ model successfully opened." << endl;
                            clog << "  Translation: " << cm->getPosition().toString() << endl;
                            clog << "  Rotation: " << cm->getRotation().toString() << endl;

                            TransformGroup *complexModel = new TransformGroup();

                            // Translation.
                            Point3 translation(cm->getPosition());
                            complexModel->setTranslation(translation);

                            // TODO: Achsenprüfung!!
                            Point3 rotation(cm->getRotation().getX(), cm->getRotation().getZ(), cm->getRotation().getY());
                            complexModel->setRotation(rotation);

                            complexModel->addChild(model);

                            complexModels->addChild(complexModel);

                        } else {
                            clog << "OBJ model could not be opened." << endl;
                        }

                        OPENDAVINCI_CORE_DELETE_POINTER(objxArchive);
                    }
                }
            }

            return complexModels;
        }

    }
} // hesperia::scenario
