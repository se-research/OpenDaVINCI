/**
 * OpenDLV - Simulation environment
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

#include "opendlv/threeD/NodeRenderingConfiguration.h"

namespace opendlv {
    namespace threeD {

        NodeRenderingConfiguration::NodeRenderingConfiguration() :
                m_parameters(NodeRenderingConfiguration::ENABLED) {}

        NodeRenderingConfiguration::~NodeRenderingConfiguration() {}

        NodeRenderingConfiguration::NodeRenderingConfiguration(const NodeRenderingConfiguration &obj) :
            m_parameters(obj.m_parameters) {}

        NodeRenderingConfiguration& NodeRenderingConfiguration::operator=(const NodeRenderingConfiguration &obj) {
            m_parameters = obj.m_parameters;

            return (*this);
        }

        bool NodeRenderingConfiguration::hasParameter(const enum RENDERING_PARAMETERS &p) const {
            return ( (m_parameters & static_cast<uint32_t>(p)) == static_cast<uint32_t>(p));
        }

        void NodeRenderingConfiguration::setParameter(const enum RENDERING_PARAMETERS &p, const bool &enabled) {
            if (enabled) {
                m_parameters |= p;
            }
            else {
                m_parameters &= ~p;
            }
        }

    }
} // opendlv::threeD
