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

#ifndef HESPERIA_SCENEGRAPH_RENDERER_RENDERINGCONFIGURATION_H_
#define HESPERIA_SCENEGRAPH_RENDERER_RENDERINGCONFIGURATION_H_

#include <map>

#include "opendavinci/core/opendavinci.h"
#include "hesperia/scenegraph/SceneNodeDescriptor.h"
#include "hesperia/scenegraph/SceneNodeDescriptorComparator.h"
#include "hesperia/scenegraph/renderer/SceneNodeRenderingConfiguration.h"

namespace hesperia {
    namespace scenegraph {
        namespace renderer {

            /**
             * This class configures several options for the rendering method.
             */
            class OPENDAVINCI_API RenderingConfiguration {
                public:
                    RenderingConfiguration();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Other object.
                     */
                    RenderingConfiguration(const RenderingConfiguration &obj);

                    virtual ~RenderingConfiguration();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Other obj.
                     * @return This instance.
                     */
                    RenderingConfiguration& operator=(const RenderingConfiguration &obj);

                    /**
                     * @param snd SceneNodeDescriptor.
                     * @return true iff snd is already in the map.
                     */
                    bool hasSceneNodeDescriptor(const SceneNodeDescriptor &snd) const;

                    /**
                     * This method returns a SceneNodeRenderingConfiguration
                     * for the given SceneNodeDescriptor.
                     *
                     * @param snd SceneNodeDescriptor.
                     * @return SceneNodeRenderingConfiguration.
                     */
                    const SceneNodeRenderingConfiguration& getSceneNodeRenderingConfiguration(const SceneNodeDescriptor &snd);

                    /**
                     * This method sets a SceneNodeRenderingConfiguration
                     * for the given SceneNodeDescriptor.
                     *
                     * @param snd SceneNodeDescriptor.
                     * @param snrc SceneNodeRenderingConfiguration to be set.
                     */
                    void setSceneNodeRenderingConfiguration(const SceneNodeDescriptor &snd, const SceneNodeRenderingConfiguration &snrc);

                private:
                    map<SceneNodeDescriptor, SceneNodeRenderingConfiguration, SceneNodeDescriptorComparator> m_sceneNodesRenderingConfiguration;
            };

        }
    }
} // hesperia::scenegraph::renderer

#endif /*HESPERIA_SCENEGRAPH_RENDERER_RENDERINGCONFIGURATION_H_*/
