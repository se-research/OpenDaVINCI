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

#include "plugins/environmentviewer/SelectableNodeDescriptor.h"

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            using namespace opendlv::threeD;

            SelectableNodeDescriptor::SelectableNodeDescriptor() :
                m_nodeDescriptor(),
                m_selected(false) {}

            SelectableNodeDescriptor::SelectableNodeDescriptor(const NodeDescriptor &nd, const bool &selected) :
                m_nodeDescriptor(nd),
                m_selected(selected) {}

            SelectableNodeDescriptor::SelectableNodeDescriptor(const SelectableNodeDescriptor &obj) :
                m_nodeDescriptor(obj.getNodeDescriptor()),
                m_selected(obj.isSelected()) {}

            SelectableNodeDescriptor::~SelectableNodeDescriptor() {}

            SelectableNodeDescriptor& SelectableNodeDescriptor::operator=(const SelectableNodeDescriptor &obj) {
                m_nodeDescriptor = obj.getNodeDescriptor();
                m_selected = obj.isSelected();

                return (*this);
            }

            const NodeDescriptor SelectableNodeDescriptor::getNodeDescriptor() const {
                return m_nodeDescriptor;
            }

            void SelectableNodeDescriptor::setNodeDescriptor(const NodeDescriptor &nd) {
                m_nodeDescriptor = nd;
            }

            bool SelectableNodeDescriptor::isSelected() const {
                return m_selected;
            }

            void SelectableNodeDescriptor::setSelected(const bool &selected) {
                m_selected = selected;
            }
        }
    }
} // plugins::environmentviewer
