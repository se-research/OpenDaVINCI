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

#include <algorithm>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendlv/scenegraph/SceneNode.h"
#include "opendlv/scenegraph/SceneNodeDescriptor.h"
#include "opendlv/scenegraph/SceneNodeVisitor.h"

namespace opendlv {
    namespace scenegraph {

        using namespace odcore::base;

        SceneNode::SceneNode() :
            m_sceneNodeDescriptor(),
            m_childrenMutex(),
            m_children() {}

        SceneNode::SceneNode(const SceneNodeDescriptor &sceneNodeDescriptor) :
            m_sceneNodeDescriptor(sceneNodeDescriptor),
            m_childrenMutex(),
            m_children() {}

        SceneNode::~SceneNode() {
            deleteAllChildren();
        }

        const SceneNodeDescriptor SceneNode::getSceneNodeDescriptor() const {
            return m_sceneNodeDescriptor;
        }

        void SceneNode::setSceneNodeDescriptor(const SceneNodeDescriptor &sceneNodeDescriptor) {
            m_sceneNodeDescriptor = sceneNodeDescriptor;
        }

        void SceneNode::addChild(SceneNode *sceneNode) {
            if (sceneNode != NULL) {
                Lock l(m_childrenMutex);
                m_children.push_back(sceneNode);
            }
        }

        void SceneNode::removeChild(SceneNode *c) {
            Lock l(m_childrenMutex);

            if (c != NULL) {
                vector<SceneNode*>::iterator result = find(m_children.begin(), m_children.end(), c);
                if (result != m_children.end()) {
                    SceneNode *sn = *result;
                    sn->deleteAllChildren();

                    OPENDAVINCI_CORE_DELETE_POINTER(sn);

                    m_children.erase(result);
                }
            }
        }

        void SceneNode::deleteAllChildren() {
            Lock l(m_childrenMutex);

            vector<SceneNode*>::iterator it = m_children.begin();
            while (it != m_children.end()) {
                SceneNode *sn = (*it++);

                sn->deleteAllChildren();

                OPENDAVINCI_CORE_DELETE_POINTER(sn);
            }
            m_children.clear();
        }

        uint32_t SceneNode::getNumberOfChildren() {
            Lock l(m_childrenMutex);
            return m_children.size();
        }

        void SceneNode::accept(SceneNodeVisitor &sceneNodeVisitor) {
            Lock l(m_childrenMutex);

            sceneNodeVisitor.visit(this);

            vector<SceneNode*>::iterator it = m_children.begin();
            while (it != m_children.end()) {
                SceneNode *sn = (*it++);
                sn->accept(sceneNodeVisitor);
            }
        }

    }
} // opendlv::scenegraph
