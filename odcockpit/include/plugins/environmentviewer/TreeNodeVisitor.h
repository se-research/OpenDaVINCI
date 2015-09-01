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

#ifndef PLUGINS_ENVIRONMENTVIEWER_TREENODEVISITOR_H_
#define PLUGINS_ENVIRONMENTVIEWER_TREENODEVISITOR_H_

#include "core/base/TreeNode.h"

#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/TransformGroupVisitor.h"

#include "plugins/environmentviewer/SelectableNodeDescriptor.h"

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            using namespace std;

            /**
             * This class represents NodeDescriptor combined with a state
             * indicating whether this element was selected by the user.
             */
            class TreeNodeVisitor : public hesperia::threeD::TransformGroupVisitor {
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
                     * @param rc RenderingConfiguration.
                     * @param root TreeNode for adding NodeDescriptors.
                     */
                    TreeNodeVisitor(hesperia::threeD::RenderingConfiguration &rc, core::base::TreeNode<SelectableNodeDescriptor> *root);

                    virtual ~TreeNodeVisitor();

                    virtual void visit(hesperia::threeD::Node *nd);

                private:
                    hesperia::threeD::RenderingConfiguration &m_renderingConfiguration;
                    core::base::TreeNode<SelectableNodeDescriptor> *m_root;
            };
        }
    }
} // plugins::environmentviewer

#endif /*PLUGINS_ENVIRONMENTVIEWER_TREENODEVISITOR_H_*/
