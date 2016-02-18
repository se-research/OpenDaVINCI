/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#include <vector>

#include "opendavinci/core/base/TreeNode.h"
#include "opendlv/scenegraph/SceneNode.h"
#include "opendlv/scenegraph/renderer/RenderingConfiguration.h"
#include "opendlv/scenegraph/renderer/SceneNodeRenderingConfiguration.h"
#include "opendlv/threeD/Node.h"
#include "opendlv/threeD/NodeRenderingConfiguration.h"
#include "opendlv/threeD/RenderingConfiguration.h"
#include "plugins/birdseyemap/SelectableNodeDescriptor.h"
#include "plugins/birdseyemap/TreeNodeVisitor.h"

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

            using namespace std;
            using namespace core::base;
            using namespace hesperia::scenegraph;
            using namespace hesperia::scenegraph::renderer;

            TreeNodeVisitor::TreeNodeVisitor(RenderingConfiguration &rc, TreeNode<SelectableNodeDescriptor> *root) :
                m_renderingConfiguration(rc),
                m_root(root) {}

            TreeNodeVisitor::~TreeNodeVisitor() {}

            void TreeNodeVisitor::visit(SceneNode *n) {
                if (m_root != NULL) {
                    if (n != NULL) {
                        SceneNodeDescriptor snd = n->getSceneNodeDescriptor();
                        if (snd.getName().size() > 0) {
                            if (!m_renderingConfiguration.hasSceneNodeDescriptor(snd)) {
                                // Enable the node described by this NodeDescriptor for rendering by default.
                                SceneNodeRenderingConfiguration snrc;
                                snrc.setParameter(SceneNodeRenderingConfiguration::ENABLED, true);
                                m_renderingConfiguration.setSceneNodeRenderingConfiguration(snd, snrc);

                                // Add NodeDescriptor to selectable list.
                                TreeNode<SelectableNodeDescriptor> *element = new TreeNode<SelectableNodeDescriptor>();
                                element->setValue(SelectableNodeDescriptor(snd, snrc.hasParameter(SceneNodeRenderingConfiguration::ENABLED)));
                                m_root->addChild(element);
                            }
                        }
                    }
                }
            }
        }
    }
} // plugins::birdseyemap
