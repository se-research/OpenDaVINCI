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

#ifndef HESPERIA_WRAPPER_PARSER_ASTNODE_H_
#define HESPERIA_WRAPPER_PARSER_ASTNODE_H_

#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"

namespace core {
    namespace wrapper {
        namespace parser {

class ASTVisitor;

            using namespace std;

            /**
             * This class represents the tree-like representation of the grammar's instance.
             */
            class OPENDAVINCI_API ASTNode {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ASTNode(const ASTNode &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ASTNode& operator=(const ASTNode &);

                public:
                    ASTNode();

                    /**
                     * Constructor.
                     *
                     * @param parent Parental node.
                     */
                    ASTNode(ASTNode *parent);

                    virtual ~ASTNode();

                    /**
                     * This method accepts a visitor for traversing the AST.
                     *
                     * @param visitor Visitor to be accepted.
                     */
                    void accept(ASTVisitor &visitor);

                    /**
                     * This method returns a pointer to the parent or NULL
                     * if this node is the root node.
                     *
                     * @return Pointer to the parental node.
                     */
                    ASTNode* getParent();

                    /**
                     * This method returns the key of this node.
                     *
                     * @return key.
                     */
                    const string getKey() const;

                    /**
                     * This method sets the key of this node.
                     *
                     * @param key Key.
                     */
                    void setKey(const string &key);

                    /**
                     * This method returns the value as desired type.
                     *
                     * @code
                     * ASTNode n;
                     * ...
                     * T t = n.getValue<T>();
                     * @endcode
                     *
                     * @return Value.
                     */
                    template<class T>
                    inline T getValue() const  {
                        stringstream s(m_value);
                        T value;
                        s >> value;
                        return value;
                    };

                    /**
                     * This method sets the value of this node.
                     *
                     * @param value Value.
                     */
                    void setValue(const string &value);

                    /**
                     * This method add a new child.
                     *
                     * @param c Child to be added if not NULL.
                     */
                    void addChild(ASTNode *c);

                    /**
                     * This method returns the first child or NULL.
                     *
                     * @return First child or NULL.
                     */
                    ASTNode* getFirstChild();

                    /**
                     * This method returns the last child or NULL.
                     *
                     * @return Last child or NULL.
                     */
                    ASTNode* getLastChild();

                    /**
                     * This method returns a shallow copy
                     * of all children.
                     *
                     * @return Shallow copy of all children.
                     */
                    vector<ASTNode*> getChildren();

                    /**
                     * This method returns a shallow copy
                     * of all children matching incasesensitively the
                     * given key.
                     *
                     * @param key Key to be used for matching.
                     * @return Shallow copy of all children matching the given key.
                     */
                    vector<ASTNode*> getChildren(const string &key);

                    /**
                     * This method tries to get the node for the
                     * given key from the list of children by looking
                     * for the first child matching incasesensitively the key.
                     * Otherwise, NULL is returned.
                     *
                     * @param key Key to be used for matching.
                     * @return Node from the first matching child or NULL.
                     */
                    ASTNode* getNodeFromFirstMatchingChildFor(const string &key);

                    /**
                     * This method prints all keys (for debugging purposes only).
                     */
                    void printKeys() const;

                private:
                    ASTNode *m_parent;
                    string m_key;
                    string m_value;
                    vector<ASTNode*> m_children;
            };

        }
    }
} // core::wrapper::parser

#endif /*HESPERIA_WRAPPER_PARSER_ASTNODE_H_*/
