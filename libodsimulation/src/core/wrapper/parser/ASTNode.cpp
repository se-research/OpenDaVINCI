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

#include <algorithm>
#include <functional>
#include <iostream>

#include "opendavinci/core/opendavinci.h"
#include "hesperia/core/wrapper/parser/ASTNode.h"
#include "hesperia/core/wrapper/parser/ASTVisitor.h"

namespace core {
    namespace wrapper {
        namespace parser {

            using namespace std;

            ASTNode::ASTNode() :
                    m_parent(NULL),
                    m_key(""),
                    m_value(""),
                    m_children() {}

            ASTNode::ASTNode(ASTNode *parent) :
                    m_parent(parent),
                    m_key(""),
                    m_value(""),
                    m_children() {}

            ASTNode::~ASTNode() {
                vector<ASTNode*>::iterator it = m_children.begin();
                while (it != m_children.end()) {
                    ASTNode *n = (*it++);
                    delete n;
                }
                m_children.clear();
            }

            void ASTNode::accept(ASTVisitor &visitor) {
                visitor.visit(this);
            }

            ASTNode* ASTNode::getParent() {
                return m_parent;
            }

            const string ASTNode::getKey() const {
                return m_key;
            }

            void ASTNode::setKey(const string &key) {
                m_key = key;
            }

            void ASTNode::setValue(const string &value) {
                m_value = value;
            }

            void ASTNode::addChild(ASTNode *c) {
                if (c != NULL) {
                    m_children.push_back(c);
                }
            }

            ASTNode* ASTNode::getFirstChild() {
                ASTNode *n = NULL;

                if (m_children.size() > 0) {
                    n = m_children.at(0);
                }

                return n;
            }

            ASTNode* ASTNode::getLastChild() {
                ASTNode *n = NULL;

                if (m_children.size() > 0) {
                    n = *(m_children.end() - 1);
                }

                return n;
            }

            vector<ASTNode*> ASTNode::getChildren() {
                return m_children;
            }

            vector<ASTNode*> ASTNode::getChildren(const string &key) {
                vector<ASTNode*> subset;

                if (m_children.size() > 0) {
                    string keyLC = key;

                    // Transform key name to lower case for case insensitive lookups.
                    transform(keyLC.begin(), keyLC.end(), keyLC.begin(), ptr_fun(::tolower));

                    vector<ASTNode*>::iterator it = m_children.begin();
                    while (it != m_children.end()) {
                        ASTNode *n = (*it++);
                        string nodeKey = n->getKey();

                        // Transform key name to lower case for case insensitive lookups.
                        transform(nodeKey.begin(), nodeKey.end(), nodeKey.begin(), ptr_fun(::tolower));

                        // Try to match the key.
                        if (keyLC == nodeKey) {
                            subset.push_back(n);
                        }
                    }
                }

                return subset;
            }

            ASTNode* ASTNode::getNodeFromFirstMatchingChildFor(const string &key) {
                ASTNode *node = NULL;

                vector<ASTNode*> subset = getChildren(key);
                if (subset.size() > 0) {
                    node = subset.at(0);
                }

                return node;
            }

            void ASTNode::printKeys() const {
                vector<ASTNode*>::const_iterator it = m_children.begin();
                while (it != m_children.end()) {
                    ASTNode *n = (*it++);
                    clog << "Key: " << n->getKey() << endl;
                }
            }

        }
    }
} // core::wrapper::parser
