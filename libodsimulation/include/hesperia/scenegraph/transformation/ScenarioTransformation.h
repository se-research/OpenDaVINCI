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

#ifndef HESPERIA_SCENEGRAPH_TRANSFORMATION_SCENARIOTRANSFORMATION_H_
#define HESPERIA_SCENEGRAPH_TRANSFORMATION_SCENARIOTRANSFORMATION_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"
#include "core/data/SerializableData.h"

#include "hesperia/data/scenario/Lane.h"
#include "hesperia/data/scenario/Layer.h"
#include "hesperia/data/scenario/LaneModel.h"
#include "hesperia/data/scenario/PointModel.h"
#include "hesperia/data/scenario/Road.h"
#include "hesperia/data/scenario/Zone.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/Arc.h"
#include "hesperia/data/scenario/StraightLine.h"
#include "hesperia/data/scenario/Surroundings.h"
#include "hesperia/scenegraph/SceneNode.h"

namespace hesperia {
    namespace scenegraph {
        namespace transformation {

            using namespace std;

            /**
             * This class transforms the Scenario data structure into a renderable scene graph.
             */
            class OPENDAVINCI_API ScenarioTransformation : public data::scenario::ScenarioVisitor {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ScenarioTransformation(const ScenarioTransformation &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ScenarioTransformation& operator=(const ScenarioTransformation &);

                public:
                    ScenarioTransformation();

                    /**
                     * Constructor.
                     *
                     * @param renderLaneConnectors if true, the lane connectors are rendered.
                     */
                    ScenarioTransformation(const bool &renderLaneConnectors);

                    virtual ~ScenarioTransformation();

                    virtual void visit(data::scenario::ScenarioNode &node);

                    /**
                     * @return The renderable root node.
                     */
                    hesperia::scenegraph::SceneNode* getRoot() const;

                private:
                    hesperia::scenegraph::SceneNode *m_root;
                    bool m_renderLaneConnectors;

                    /**
                     * This method transforms a Surroundings into a renderable representation.
                     *
                     * @param surroundings Surroundings.
                     * @param sceneNode to be used.
                     */
                    void transform(data::scenario::Surroundings &surroundings, hesperia::scenegraph::SceneNode *sn);

                    /**
                     * This method transforms a list of traffic controls into a renderable representation.
                     *
                     * @param laneModel LaneModel.
                     * @param layerSceneNode SceneNode for filling with renderable primitives.
                     */
                    void transform(const data::scenario::LaneModel &laneModel, hesperia::scenegraph::SceneNode *layerSceneNode);

                    /**
                     * This method transforms a PointModel into a renderable representation.
                     *
                     * @param pointModel PointModel.
                     * @param road Road.
                     * @param lane Lane.
                     * @param layer Layer containing this PointModel.
                     * @param layerSceneNode SceneNode for filling with renderable primitives.
                     */
                    void transform(const data::scenario::Layer &layer, const data::scenario::Road &road, const data::scenario::Lane &lane, const data::scenario::PointModel &pointModel, hesperia::scenegraph::SceneNode *layerSceneNode);

                    /**
                     * This method transforms a StraightLine into a renderable representation.
                     *
                     * @param sl StraightLine.
                     * @param road Road.
                     * @param lane Lane.
                     * @param layer Layer containing this StraightLine.
                     * @param layerSceneNode SceneNode for filling with renderable primitives.
                     */
                    void transform(const data::scenario::Layer &layer, const data::scenario::Road &road, const data::scenario::Lane &lane, const data::scenario::StraightLine &straightLine, hesperia::scenegraph::SceneNode *layerSceneNode);

                    /**
                     * This method transforms an Arc into a renderable representation.
                     *
                     * @param a Arc.
                     * @param road Road.
                     * @param lane Lane.
                     * @param layer Layer containing this StraightLine.
                     * @param layerSceneNode SceneNode for filling with renderable primitives.
                     */
                    void transform(const data::scenario::Layer &layer, const data::scenario::Road &road, const data::scenario::Lane &lane, const data::scenario::Arc &arc, hesperia::scenegraph::SceneNode *layerSceneNode);

                    /**
                     * This method transforms a Zone into a renderable representation.
                     *
                     * @param z Zone.
                     * @param layer Layer containing this Zone.
                     * @param layerSceneNode SceneNode for filling with renderable primitives.
                     */
                    void transform(const data::scenario::Layer &layer, const data::scenario::Zone &zone, hesperia::scenegraph::SceneNode *layerSceneNode);
            };

        }
    }
} // hesperia::scenegraph::transformation

#endif /*HESPERIA_SCENEGRAPH_TRANSFORMATION_SCENARIOTRANSFORMATION_H_*/
