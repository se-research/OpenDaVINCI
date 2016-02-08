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

#ifndef HESPERIA_THREED_NODE_H_
#define HESPERIA_THREED_NODE_H_

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/wrapper/Disposable.h"
#include "hesperia/threeD/NodeDescriptor.h"

namespace hesperia {
    namespace threeD {

        /**
         * This interface must be implemented by any subclass
         * to be drawn in an OpenGL scene.
         */
class RenderingConfiguration;

        class OPENDAVINCI_API Node : public core::wrapper::Disposable {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                Node(const Node &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                Node& operator=(const Node &);

            protected:
                Node();

            public:
                /**
                 * Constructor.
                 *
                 * @param nodeDescriptor Description of this node.
                 */
                Node(const NodeDescriptor &nodeDescriptor);

                virtual ~Node();

                /**
                 * This method is called whenever this node should to draw its
                 * content using plain OpenGL statements.
                 *
                 * @param renderingConfiguration Configuration for the rendering process.
                 */
                virtual void render(RenderingConfiguration &renderingConfiguration) = 0;

                /**
                 * This method returns this node's description.
                 *
                 * @return This node's descriptor.
                 */
                const NodeDescriptor getNodeDescriptor() const;

                /**
                 * This method sets the node descriptor.
                 *
                 * @param nodeDescriptor Node description to be set.
                 */
                void setNodeDescriptor(const NodeDescriptor &nodeDescriptor);

            private:
                NodeDescriptor m_nodeDescriptor;
        };

    }
} // hesperia::threeD

#endif /*HESPERIA_THREED_NODE_H_*/
