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

#ifndef PLUGINS_BIRDSEYEMAP_SELECTABLENODEDESCRIPTORTREELISTENER_H_
#define PLUGINS_BIRDSEYEMAP_SELECTABLENODEDESCRIPTORTREELISTENER_H_

#include <vector>

#include "core/base/TreeNode.h"

#include "plugins/birdseyemap/SelectableNodeDescriptor.h"

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

            /**
             * This interface encapsulates the access to the tree of SelectableNodeDescriptors.
             */
            class SelectableNodeDescriptorTreeListener {
                public:
                    virtual ~SelectableNodeDescriptorTreeListener();

                    /**
                     * This method is called by to update the SelectableNodeDescriptor.
                     *
                     * @param node Node of the tree to update.
                     */
                    virtual void update(core::base::TreeNode<SelectableNodeDescriptor> *node) = 0;
            };
        }
    }
} // plugins::birdseyemap

#endif /*PLUGINS_BIRDSEYEMAP_SELECTABLENODEDESCRIPTORTREELISTENER_H_*/
