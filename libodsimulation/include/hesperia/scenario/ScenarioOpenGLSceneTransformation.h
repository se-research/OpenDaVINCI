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

#ifndef HESPERIA_SCENARIO_SCENARIOOPENGLSCENETRANSFORMATION_H_
#define HESPERIA_SCENARIO_SCENARIOOPENGLSCENETRANSFORMATION_H_

#include "core/opendavinci.h"
#include "core/data/SerializableData.h"

#include "hesperia/data/scenario/Lane.h"
#include "hesperia/data/scenario/Layer.h"
#include "hesperia/data/scenario/LaneModel.h"
#include "hesperia/data/scenario/PointModel.h"
#include "hesperia/data/scenario/Road.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/Arc.h"
#include "hesperia/data/scenario/StraightLine.h"
#include "hesperia/data/scenario/Surroundings.h"
#include "hesperia/data/scenario/Zone.h"
#include "hesperia/threeD/TransformGroup.h"

namespace hesperia {
    namespace scenario {

        using namespace std;

        /**
         * This class transforms the Scenario data structure into an OpenGL
         * based scene graph for visualization.
         */
        class OPENDAVINCI_API ScenarioOpenGLSceneTransformation : public data::scenario::ScenarioVisitor {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ScenarioOpenGLSceneTransformation(const ScenarioOpenGLSceneTransformation &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ScenarioOpenGLSceneTransformation& operator=(const ScenarioOpenGLSceneTransformation &);

            public:
                ScenarioOpenGLSceneTransformation();

                /**
                 * Constructor.
                 *
                 * @param renderLaneConnectors if true, the lane connectors are rendered.
                 */
                ScenarioOpenGLSceneTransformation(const bool &renderLaneConnectors);

                virtual ~ScenarioOpenGLSceneTransformation();

                virtual void visit(data::scenario::ScenarioNode &node);

                /**
                 * This method returns the root node.
                 *
                 * @return Root node of the
                 */
                threeD::TransformGroup* getRoot() const;

            private:
                threeD::TransformGroup *m_root;
                bool m_renderLaneConnectors;

                /**
                 * This method transforms a Surroundings into an OpenGL representation.
                 *
                 * @param surroundings Surroundings.
                 * @param TransformGroup to be used.
                 */
                void transform(data::scenario::Surroundings &surroundings, threeD::TransformGroup &root);

                /**
                 * This method transforms a list of traffic controls into an OpenGL representation.
                 *
                 * @param laneModel LaneModel.
                 * @param layerTG TransformGroup for filling with 3D primitives.
                 */
                void transform(const data::scenario::LaneModel &laneModel, threeD::TransformGroup &layerTG);

                /**
                 * This method transforms a PointModel into an OpenGL representation.
                 *
                 * @param pointModel PointModel.
                 * @param road Road.
                 * @param lane Lane.
                 * @param layer Layer containing this PointModel.
                 * @param layerTG TransformGroup for filling with 3D primitives.
                 */
                void transform(const data::scenario::Layer &layer, const data::scenario::Road &road, const data::scenario::Lane &lane, const data::scenario::PointModel &pointModel, threeD::TransformGroup &layerTG);

                /**
                 * This method transforms a StraightLine into an OpenGL representation.
                 *
                 * @param sl StraightLine.
                 * @param road Road.
                 * @param lane Lane.
                 * @param layer Layer containing this StraightLine.
                 * @param layerTG TransformGroup for filling with 3D primitives.
                 */
                void transform(const data::scenario::Layer &layer, const data::scenario::Road &road, const data::scenario::Lane &lane, const data::scenario::StraightLine &straightLine, threeD::TransformGroup &layerTG);

                /**
                 * This method transforms an Arc into an OpenGL representation.
                 *
                 * @param a Arc.
                 * @param road Road.
                 * @param lane Lane.
                 * @param layer Layer containing this StraightLine.
                 * @param layerTG TransformGroup for filling with 3D primitives.
                 */
                void transform(const data::scenario::Layer &layer, const data::scenario::Road &road, const data::scenario::Lane &lane, const data::scenario::Arc &arc, threeD::TransformGroup &layerTG);

                /**
                 * This method transforms a Zone into an OpenGL representation.
                 *
                 * @param z Zone.
                 * @param layer Layer containing this Zone.
                 * @param layerTG TransformGroup for filling with 3D primitives.
                 */
                void transform(const data::scenario::Layer &layer, const data::scenario::Zone &z, threeD::TransformGroup &layerTG);

        };

    }
} // hesperia::scenario

#endif /*HESPERIA_SCENARIO_SCENARIOOPENGLSCENETRANSFORMATION_H_*/
