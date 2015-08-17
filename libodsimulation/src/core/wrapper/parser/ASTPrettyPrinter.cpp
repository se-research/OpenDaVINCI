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

#include <iostream>

#include "core/wrapper/parser/ASTNode.h"
#include "core/wrapper/parser/ASTPrettyPrinter.h"

namespace core {
    namespace wrapper {
        namespace parser {

            using namespace std;

            ASTPrettyPrinter::ASTPrettyPrinter() :
                    m_depth(0) {}

            ASTPrettyPrinter::~ASTPrettyPrinter() {}

            void ASTPrettyPrinter::visit(ASTNode *node) {
                if (node != NULL) {
                    if (node->getValue<string>() != "") {
                        for (uint32_t k = 0; k < m_depth; k++) {
                            clog << " ";
                        }
                        clog << "'" << node->getValue<string>() << "'" << endl;
                    } else {
                        vector<ASTNode*> list = node->getChildren();
                        vector<ASTNode*>::iterator it = list.begin();
                        while (it != list.end()) {
                            ASTNode *n = (*it++);
                            string key = n->getKey();
                            string value = n->getValue<string>();
                            for (uint32_t k = 0; k < m_depth; k++) {
                                clog << " ";
                            }
                            clog << "Depth: " << m_depth << ", Key: " << "'" << key << "'" << ", Value: " << "'" << value << "'" << endl;
                            m_depth++;
                            n->accept(*this);
                            m_depth--;
                        }
                    }
                }
            }

        }
    }
} // core::wrapper::parser
