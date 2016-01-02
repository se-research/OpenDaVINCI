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

#ifndef HESPERIA_WRAPPER_PARSER_ASTVISITOR_H_
#define HESPERIA_WRAPPER_PARSER_ASTVISITOR_H_

#include "core/opendavinci.h"

namespace core {
    namespace wrapper {
        namespace parser {

            // Forward declaration to prevent circular dependencies.
            class ASTNode;

            /**
             * This class is the interface for any AST visitor.
             */
            class OPENDAVINCI_API ASTVisitor {
                public:
                    virtual ~ASTVisitor();

                    /**
                     * This method is called to visit the given node by
                     * this visitor.
                     *
                     * @param node Node to be visited.
                     */
                    virtual void visit(ASTNode *node) = 0;
            };

        }
    }
} // core::wrapper::parser

#endif /*HESPERIA_WRAPPER_PARSER_ASTVISITOR_H_*/
