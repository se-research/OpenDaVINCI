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

#ifndef PLUGINS_BIRDSEYEMAP_TREENODEVISITOR_H_
#define PLUGINS_BIRDSEYEMAP_TREENODEVISITOR_H_

#include "opendlv/scenegraph/SceneNodeVisitor.h"

namespace odcore { namespace base { template <typename T> class TreeNode; } }
namespace opendlv { namespace scenegraph { class SceneNode; } }
namespace opendlv { namespace scenegraph { namespace renderer { class RenderingConfiguration; } } }

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

class SelectableNodeDescriptor;

            using namespace std;

            /**
             * This class represents SceneNodeDescriptor combined with a state
             * indicating whether this element was selected by the user.
             */
            class TreeNodeVisitor : public opendlv::scenegraph::SceneNodeVisitor {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    TreeNodeVisitor(const TreeNodeVisitor &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    TreeNodeVisitor& operator=(const TreeNodeVisitor &);

                public:
                    /**
                     * Constructor.
                     *
                     * @param root TreeNode for adding SceneNodeDescriptors.
                     */
                    TreeNodeVisitor(opendlv::scenegraph::renderer::RenderingConfiguration &rc, odcore::base::TreeNode<SelectableNodeDescriptor> *root);

                    virtual ~TreeNodeVisitor();

                    virtual void visit(opendlv::scenegraph::SceneNode *snd);

                private:
                    opendlv::scenegraph::renderer::RenderingConfiguration &m_renderingConfiguration;
                    odcore::base::TreeNode<SelectableNodeDescriptor> *m_root;
            };
        }
    }
} // plugins::birdseyemap

#endif /*PLUGINS_BIRDSEYEMAP_TREENODEVISITOR_H_*/
