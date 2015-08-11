/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CORE_TREENODETESTSUITE_H_
#define CORE_TREENODETESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <string>

#include "core/base/TreeNode.h"

using namespace std;
using namespace core::base;

class TreeNodeTest : public CxxTest::TestSuite {
    public:
        string printNodes(TreeNode<string> *ptr, string current) {
            string retVal;
            if (ptr != NULL) {
                vector<TreeNode<string>* > listOfChildren = ptr->getChildren();

                if (listOfChildren.size() > 0) {
                    vector<TreeNode<string>* >::iterator it = listOfChildren.begin();
                    while (it != listOfChildren.end()) {
                        retVal = retVal + printNodes((*it++), current);
                    }
                }

                retVal += ptr->getValue();
            }
            return retVal;
        }

        void testSimpleTree() {
            TreeNode<string> *root = new TreeNode<string>();

            TreeNode<string> *child1 = new TreeNode<string>();
            root->addChild(child1);
            child1->setValue("Hello ");

            TreeNode<string> *child2 = new TreeNode<string>();
            root->addChild(child2);
            child2->setValue("World!");

            string retVal = printNodes(root, "");

            TS_ASSERT(retVal == "Hello World!");

            delete root;
        }
};

#endif /*CORE_TREENODETESTSUITE_H_*/
