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

#ifndef HESPERIA_WRAPPER_PARSER_ASTPRETTYPRINTER_H_
#define HESPERIA_WRAPPER_PARSER_ASTPRETTYPRINTER_H_

#include "core/opendavinci.h"
#include "core/wrapper/parser/ASTVisitor.h"

namespace core {
    namespace wrapper {
        namespace parser {

class ASTNode;

            using namespace std;

            /**
             * This class prints the parsed AST.
             */
            class ASTPrettyPrinter : public ASTVisitor {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ASTPrettyPrinter(const ASTPrettyPrinter &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ASTPrettyPrinter& operator=(const ASTPrettyPrinter &);

                public:
                    ASTPrettyPrinter();

                    virtual ~ASTPrettyPrinter();

                    virtual void visit(ASTNode *node);

                private:
                    uint32_t m_depth;
            };

        }
    }
} // core::wrapper::parser

#endif /*HESPERIA_WRAPPER_PARSER_ASTPRETTYPRINTER_H_*/
