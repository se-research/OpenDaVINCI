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

// The following include is necessary on Win32 platforms to set up necessary macro definitions.
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

#include <algorithm>
#include <vector>

#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/opendavinci.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/TransformGroup.h"
#include "hesperia/threeD/RenderingConfiguration.h"

namespace hesperia { namespace threeD { class TransformGroupVisitor; } }

namespace hesperia {
    namespace threeD {

        using namespace core::base;
        using namespace hesperia::data::environment;

        TransformGroup::TransformGroup() :
                Node(NodeDescriptor()),
                m_translation(),
                m_rotation(),
                m_scaling(Point3(1, 1, 1)),
                m_listOfChildrenMutex(),
                m_listOfChildren() {}

        TransformGroup::TransformGroup(const NodeDescriptor &nodeDescriptor) :
                Node(nodeDescriptor),
                m_translation(),
                m_rotation(),
                m_scaling(Point3(1, 1, 1)),
                m_listOfChildrenMutex(),
                m_listOfChildren() {}

        TransformGroup::~TransformGroup() {
            deleteAllChildren();
        }

        void TransformGroup::render(RenderingConfiguration &renderingConfiguration) {
            Lock l(m_listOfChildrenMutex);

            // Render if unnamed or not disabled.
            if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                glPushMatrix();
                {
                    // Translate the model.
                    glTranslated(m_translation.getX(), m_translation.getY(), m_translation.getZ());

                    // Rotate the model using DEG (m_rotation is in RAD!).
                    glRotated(m_rotation.getX()*180.0 / cartesian::Constants::PI, 1, 0, 0);
                    glRotated(m_rotation.getY()*180.0 / cartesian::Constants::PI, 0, 1, 0);
                    glRotated(m_rotation.getZ()*180.0 / cartesian::Constants::PI, 0, 0, 1);

                    // Scale the model.
                    glScaled(m_scaling.getX(), m_scaling.getY(), m_scaling.getZ());

                    // Draw all existing children.
                    vector<Node*>::const_iterator it = m_listOfChildren.begin();
                    while (it != m_listOfChildren.end()) {
                        Node *n = (*it++);
                        if (n != NULL) {
                            n->render(renderingConfiguration);
                        }
                    }
                }
                glPopMatrix();
            }
        }

        void TransformGroup::setTranslation(const Point3 &t) {
            m_translation = t;
        }

        Point3 TransformGroup::getTranslation() const {
            return m_translation;
        }

        void TransformGroup::setRotation(const Point3 &r) {
            m_rotation = r;
        }

        Point3 TransformGroup::getRotation() const {
            return m_rotation;
        }

        void TransformGroup::setScaling(const Point3 &s) {
            m_scaling = s;
        }

        Point3 TransformGroup::getScaling() const {
            return m_scaling;
        }

        void TransformGroup::accept(TransformGroupVisitor &visitor) {
            visitor.visit(this);

            // Traverse all children.
            vector<Node*>::iterator it = m_listOfChildren.begin();
            while (it != m_listOfChildren.end()) {
                Node *n = (*it++);
                TransformGroup *tg = dynamic_cast<TransformGroup*>(n);
                if (tg != NULL) {
                    tg->accept(visitor);
                }
                else {
                    // Child is not a TransformGroup.
                    visitor.visit(n);
                }
            }
        }

        void TransformGroup::addChild(Node *c) {
            Lock l(m_listOfChildrenMutex);

            m_listOfChildren.push_back(c);
        }

        void TransformGroup::removeChild(Node *c) {
            Lock l(m_listOfChildrenMutex);

            if (c != NULL) {
                vector<Node*>::iterator result = find(m_listOfChildren.begin(), m_listOfChildren.end(), c);
                if (result != m_listOfChildren.end()) {
//                    core::wrapper::DisposalService::getInstance().addDisposableForRegularRemoval((Disposable**)&(*result));
                    OPENDAVINCI_CORE_DELETE_POINTER(*result);
                    m_listOfChildren.erase(result);
                }
            }
        }

        void TransformGroup::deleteAllChildren() {
            Lock lc(m_listOfChildrenMutex);

            vector<Node*>::iterator it = m_listOfChildren.begin();
            while (it != m_listOfChildren.end()) {
                Node *n = (*it++);

                TransformGroup *tg = dynamic_cast<TransformGroup*>(n);
                if (tg != NULL) {
                    tg->deleteAllChildren();
                }
                else {
                    // Child is not a TransformGroup.
                    OPENDAVINCI_CORE_DELETE_POINTER(n);

                    // Use disposal service for cleaning up.
//                    core::wrapper::DisposalService::getInstance().addDisposableForRegularRemoval((Disposable**)&n);
                }
            }

            // Clear regular node list.
            m_listOfChildren.clear();
        }

    }
} // hesperia::threeD
