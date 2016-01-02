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

#ifndef HESPERIA_CORE_THREED_RENDERINGCONFIGURATION_H_
#define HESPERIA_CORE_THREED_RENDERINGCONFIGURATION_H_

#include <map>

#include "core/opendavinci.h"

#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/NodeDescriptorComparator.h"
#include "hesperia/threeD/NodeRenderingConfiguration.h"

namespace hesperia {
    namespace threeD {

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
                 * This method returns the actual drawing configuration
                 * for texture.
                 *
                 * @return true if textures should be drawn.
                 */
                bool hasDrawTextures() const;

                /**
                 * This method enables or disables the drawing of textures
                 * where supported.
                 *
                 * @param drawTextures true if textures should be drawn.
                 */
                void setDrawTextures(const bool &drawTextures);

                /**
                 * This method returns a NodeRenderingConfiguration
                 * for the given NodeDescriptor.
                 *
                 * @param nd NodeDescriptor.
                 * @return NodeRenderingConfiguration.
                 */
                const NodeRenderingConfiguration& getNodeRenderingConfiguration(const NodeDescriptor &nd);

                /**
                 * This method sets a NodeRenderingConfiguration
                 * for the given NodeDescriptor.
                 *
                 * @param nd NodeDescriptor.
                 * @param nrc NodeRenderingConfiguration to be set.
                 */
                void setNodeRenderingConfiguration(const NodeDescriptor &nd, const NodeRenderingConfiguration &nrc);

            private:
                bool m_drawTextures;
                map<NodeDescriptor, NodeRenderingConfiguration, NodeDescriptorComparator> m_nodesRenderingConfiguration;
        };

    }
} // hesperia::threeD

#endif /*HESPERIA_CORE_THREED_RENDERINGCONFIGURATION_H_*/
