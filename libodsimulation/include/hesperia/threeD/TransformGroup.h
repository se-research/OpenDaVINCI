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

#ifndef HESPERIA_CORE_THREED_TRANSFORMGROUP_H_
#define HESPERIA_CORE_THREED_TRANSFORMGROUP_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include <vector>

#include "core/base/Mutex.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/TransformGroupVisitor.h"

namespace hesperia {
    namespace threeD {

        using namespace std;

        /**
         * This class creates a scene graph.
         */
        class OPENDAVINCI_API TransformGroup : public Node {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                TransformGroup(const TransformGroup &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                TransformGroup& operator=(const TransformGroup &);

            public:
                /**
                 * Default constructor.
                 */
                TransformGroup();

                /**
                 * Constructor.
                 *
                 * @param nodeDescriptor Description for this transform group.
                 */
                TransformGroup(const NodeDescriptor &nodeDescriptor);

                virtual ~TransformGroup();

                virtual void render(RenderingConfiguration &renderingConfiguration);

                /**
                 * This method sets the translation.
                 *
                 * @param t Translation.
                 */
                void setTranslation(const hesperia::data::environment::Point3 &t);

                /**
                 * This method returns the translation.
                 *
                 * @return Translation.
                 */
                hesperia::data::environment::Point3 getTranslation() const;

                /**
                 * This method sets the rotation.
                 *
                 * @param r Rotation.
                 */
                void setRotation(const hesperia::data::environment::Point3 &r);

                /**
                 * This method returns the rotation.
                 *
                 * @return Rotation.
                 */
                hesperia::data::environment::Point3 getRotation() const;

                /**
                 * This method sets the scaling.
                 *
                 * @param s Scaling.
                 */
                void setScaling(const hesperia::data::environment::Point3 &s);

                /**
                 * This method returns the scaling.
                 *
                 * @return Scaling.
                 */
                hesperia::data::environment::Point3 getScaling() const;

                /**
                 * This method adds a child.
                 *
                 * @param c Child to be added.
                 */
                void addChild(Node *c);

                /**
                 * This method removes a child.
                 *
                 * @param c Child to be removed.
                 */
                void removeChild(Node *c);

                /**
                 * This method deletes all registered children.
                 */
                void deleteAllChildren();

                /**
                 * This method accepts a visitor.
                 *
                 * @param visitor Visitor to accept.
                 */
                void accept(TransformGroupVisitor &visitor);

            private:
                hesperia::data::environment::Point3 m_translation;
                hesperia::data::environment::Point3 m_rotation;
                hesperia::data::environment::Point3 m_scaling;

                mutable core::base::Mutex m_listOfChildrenMutex;
                vector<Node*> m_listOfChildren;
        };

    }
} // hesperia::threeD

#endif /*HESPERIA_CORE_THREED_TRANSFORMGROUP_H_*/
