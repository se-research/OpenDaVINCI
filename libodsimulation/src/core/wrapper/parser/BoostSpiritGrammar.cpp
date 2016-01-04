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

#include <vector>

#include <boost/algorithm/string/trim.hpp>

#include "core/wrapper/parser/ASTNode.h"
#include "core/wrapper/parser/BoostSpiritGrammar.h"
#include "core/wrapper/parser/ParserTokenExtendedData.h"

namespace core {
    namespace wrapper {
        namespace parser {

            BoostSpiritGrammar::BoostSpiritGrammar(ParserTokenListener &ptl, ParserErrorListener &pel) :
                    Grammar(ptl, pel) {}

            BoostSpiritGrammar::~BoostSpiritGrammar() {}

            void BoostSpiritGrammar::buildAST(const iter_t &it, ASTNode *parent, const uint32_t &depth) const {
                ASTNode *child = NULL;
                string key;
                for (uint32_t j = 0; j < it->children.size(); j++) {
                    string data((it->children.begin() + j)->value.begin(), (it->children.begin() + j)->value.end());
                    boost::algorithm::trim(data);
                    if ( (data != "") &&
                            ((it->children.begin() + j)->value.id().to_long() == 0) &&
                            ((it->children.begin() + j)->children.size() == 0)
                       ) {
                        // Keys have no children and an ID of 0 because they are keywords from the grammar.
                        key = data;
                        child = new ASTNode(parent);
                        child->setKey(key);
                        parent->addChild(child);
                    } else if ( (data != "") &&
                                ((it->children.begin() + j)->value.id().to_long() > 0) &&
                                ((it->children.begin() + j)->children.size() == 0) ) {
                        // Values have an ID greater than 0 and no children.
                        // Check if there's already a child with no value set.
                        if ( (child == NULL) || (child->getValue<string>() != "") ) {
                            child = new ASTNode(parent);
                            parent->addChild(child);
                        }
                        child->setKey(key);
                        child->setValue(data);
                    } else if ( ((it->children.begin() + j)->value.id().to_long() > 0) &&
                                ((it->children.begin() + j)->children.size() > 0) ) {
                        // Hierarchically sub-ordered values have also an ID greater than 0 but children as well.
                        ASTNode *multipleChildren = new ASTNode(parent);
                        buildAST(it->children.begin() + j, multipleChildren, depth + 1);
                        multipleChildren->setKey(key);
                        parent->addChild(multipleChildren);
//                        ASTNode *multipleChildren = NULL;
//                        if ( (parent != NULL) && (parent->getLastChild() != NULL) && (parent->getLastChild()->getKey() == key) && (parent->getLastChild()->getValue<string>() == "") ) {
//                            // Re-use last added child if value is empty AND keys are identical.
//                            multipleChildren = parent->getLastChild();
//                        }
//                        else {
//                            multipleChildren = new ASTNode(parent);
//                            parent->addChild(multipleChildren);
//                        }
//                        buildAST(it->children.begin() + j, multipleChildren, depth + 1);
//                        multipleChildren->setKey(key);
                    }
                }
            }

            BoostSpiritGrammar::ParserTokenHandler::ParserTokenHandler(const Grammar &g, ParserTokenExtendedData *data) :
                    m_grammar(const_cast<Grammar&>(g)),
                    m_data(data) {
                // Create default data if no extended data is provided.
                if (m_data == NULL) {
                    m_data = new ParserTokenExtendedData();
                }
                m_grammar.add(data);
            }

            BoostSpiritGrammar::ParserTokenHandler::ParserTokenHandler(const ParserTokenHandler &obj) :
                    m_grammar(obj.m_grammar),
                    m_data(obj.m_data) {}

            BoostSpiritGrammar::ParserTokenHandler& BoostSpiritGrammar::ParserTokenHandler::operator=(const ParserTokenHandler &obj) {
                m_grammar = obj.m_grammar;
                m_data = obj.m_data;
                return (*this);
            }

            BoostSpiritGrammar::ParserTokenHandler::~ParserTokenHandler() {}

            BoostSpiritGrammar::ParserNewlineHandler::ParserNewlineHandler(const Grammar &g) :
                    m_grammar(const_cast<Grammar&>(g)) {}

            BoostSpiritGrammar::ParserNewlineHandler::ParserNewlineHandler(const ParserNewlineHandler &obj) :
                    m_grammar(obj.m_grammar) {}

            BoostSpiritGrammar::ParserNewlineHandler& BoostSpiritGrammar::ParserNewlineHandler::operator=(const ParserNewlineHandler &obj) {
                m_grammar = obj.m_grammar;
                return (*this);
            }

            BoostSpiritGrammar::ParserNewlineHandler::~ParserNewlineHandler() {}

            BoostSpiritGrammar::ParserErrorHandler::ParserErrorHandler(const Grammar &g, ParserErrorExtendedData *data) :
                    m_grammar(const_cast<Grammar&>(g)),
                    m_data(data) {
                // Create default data if no extended data is provided.
                if (m_data == NULL) {
                    m_data = new ParserErrorExtendedData();
                }
                m_grammar.add(data);
            }

            BoostSpiritGrammar::ParserErrorHandler::ParserErrorHandler(const ParserErrorHandler &obj) :
                    m_grammar(obj.m_grammar),
                    m_data(obj.m_data) {}

            BoostSpiritGrammar::ParserErrorHandler& BoostSpiritGrammar::ParserErrorHandler::operator=(const ParserErrorHandler &obj) {
                m_grammar = obj.m_grammar;
                m_data = obj.m_data;
                return (*this);
            }

            BoostSpiritGrammar::ParserErrorHandler::~ParserErrorHandler() {}

        }
    }
} // core::wrapper::parser
