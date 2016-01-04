/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
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

#include "core/base/TreeNode.h"
#include "hesperia/scenegraph/SceneNode.h"
#include "hesperia/scenegraph/renderer/RenderingConfiguration.h"
#include "hesperia/scenegraph/renderer/SceneNodeRenderingConfiguration.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeRenderingConfiguration.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "plugins/environmentviewer/SelectableNodeDescriptor.h"
#include "plugins/environmentviewer/TreeNodeVisitor.h"

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            using namespace std;
            using namespace core::base;
            using namespace hesperia::threeD;

            TreeNodeVisitor::TreeNodeVisitor(RenderingConfiguration &rc, TreeNode<SelectableNodeDescriptor> *root) :
                m_renderingConfiguration(rc),
                m_root(root) {}

            TreeNodeVisitor::~TreeNodeVisitor() {}

            void TreeNodeVisitor::visit(Node *n) {
                if (m_root != NULL) {
                    if (n != NULL) {
                        NodeDescriptor nd = n->getNodeDescriptor();
                        if (nd.getName().size() > 0) {
                            // Enable the node described by this NodeDescriptor for rendering by default.
                            NodeRenderingConfiguration nrc;
                            nrc.setParameter(NodeRenderingConfiguration::ENABLED, true);
                            m_renderingConfiguration.setNodeRenderingConfiguration(nd, nrc);

                            // Add NodeDescriptor to selectable list.
                            TreeNode<SelectableNodeDescriptor> *element = new TreeNode<SelectableNodeDescriptor>();
                            element->setValue(SelectableNodeDescriptor(nd, nrc.hasParameter(NodeRenderingConfiguration::ENABLED)));
                            m_root->addChild(element);
                        }
                    }
                }
            }
        }
    }
} // plugins::environmentviewer
