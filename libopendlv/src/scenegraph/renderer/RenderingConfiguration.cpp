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

#include "opendlv/scenegraph/renderer/RenderingConfiguration.h"

namespace hesperia {
    namespace scenegraph {
        namespace renderer {

            RenderingConfiguration::RenderingConfiguration() :
                m_sceneNodesRenderingConfiguration() {}

            RenderingConfiguration::RenderingConfiguration(const RenderingConfiguration &obj) :
            	m_sceneNodesRenderingConfiguration(obj.m_sceneNodesRenderingConfiguration) {}

            RenderingConfiguration::~RenderingConfiguration() {}

            RenderingConfiguration& RenderingConfiguration::operator=(const RenderingConfiguration &obj) {
            	m_sceneNodesRenderingConfiguration = obj.m_sceneNodesRenderingConfiguration;

            	return (*this);
            }

            bool RenderingConfiguration::hasSceneNodeDescriptor(const SceneNodeDescriptor &snd) const {
                map<SceneNodeDescriptor, SceneNodeRenderingConfiguration, SceneNodeDescriptorComparator>::const_iterator it = m_sceneNodesRenderingConfiguration.find(snd);
                return (it != m_sceneNodesRenderingConfiguration.end());
            }

            const SceneNodeRenderingConfiguration& RenderingConfiguration::getSceneNodeRenderingConfiguration(const SceneNodeDescriptor &snd) {
                return m_sceneNodesRenderingConfiguration[snd];
            }

            void RenderingConfiguration::setSceneNodeRenderingConfiguration(const SceneNodeDescriptor &snd, const SceneNodeRenderingConfiguration &snrc) {
                m_sceneNodesRenderingConfiguration[snd] = snrc;
            }

        }
    }
} // hesperia::scenegraph::renderer
