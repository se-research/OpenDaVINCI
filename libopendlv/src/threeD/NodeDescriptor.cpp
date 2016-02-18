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

#include "opendlv/threeD/NodeDescriptor.h"

namespace hesperia {
    namespace threeD {

        using namespace std;

        NodeDescriptor::NodeDescriptor() :
                m_name() {}

        NodeDescriptor::NodeDescriptor(const string &name) :
                m_name(name) {}

        NodeDescriptor::~NodeDescriptor() {}

        NodeDescriptor::NodeDescriptor(const NodeDescriptor &obj) :
                m_name(obj.m_name) {}

        NodeDescriptor& NodeDescriptor::operator=(const NodeDescriptor &obj) {
            m_name = obj.m_name;

            return (*this);
        }

        const string NodeDescriptor::getName() const {
            return m_name;
        }
    }
} // hesperia::threeD
