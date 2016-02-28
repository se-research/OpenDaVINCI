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

#ifndef HESPERIA_CORE_WRAPPER_PARSER_BOOSTSPIRITGRAMMAR_H_
#define HESPERIA_CORE_WRAPPER_PARSER_BOOSTSPIRITGRAMMAR_H_

#include <iostream>
#include <string>

#include <boost/algorithm/string/trim.hpp>
#include <boost/spirit/include/classic_ast.hpp>
#include <boost/spirit/include/classic_error_handling.hpp>

#include "opendavinci/odcore/opendavinci.h"
#include "opendlv/core/wrapper/parser/Grammar.h"
#include "opendlv/core/wrapper/parser/ParserError.h"
#include "opendlv/core/wrapper/parser/ParserErrorExtendedData.h"
#include "opendlv/core/wrapper/parser/ParserErrorListener.h"
#include "opendlv/core/wrapper/parser/ParserToken.h"
#include "opendlv/core/wrapper/parser/ParserTokenListener.h"

namespace core {
    namespace wrapper {
        namespace parser {

            /**
             * This class implements a grammar using Boost::Spirit.
             */
class ASTNode;
class ParserTokenExtendedData;

            class OPENDAVINCI_API BoostSpiritGrammar  : public Grammar {
                public:
                    // The following typedef's are necessary to construct the AST.
                    typedef char const* iterator_t;
                    typedef boost::spirit::classic::tree_match<iterator_t> parse_tree_match_t;
                    typedef parse_tree_match_t::tree_iterator iter_t;

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    BoostSpiritGrammar(const BoostSpiritGrammar &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    BoostSpiritGrammar& operator=(const BoostSpiritGrammar &);

                public:
                    /**
                     * Constructor.
                     *
                     * @param gtl Token listener for this grammar.
                     * @param gel Error listener for this grammar.
                     */
                    BoostSpiritGrammar(ParserTokenListener &gtl, ParserErrorListener &gel);

                    virtual ~BoostSpiritGrammar();

                    virtual ASTNode* getAST(const string &s) = 0;

                protected:
                    /**
                     * This method builds actually the AST.
                     *
                     * @param it Iterator for traversing the AST.
                     * @param parent The root node for building the AST.
                     * @param depth Depth describing the descend.
                     */
                    void buildAST(const iter_t &it, ASTNode *parent, const uint32_t &depth = 0) const;

                public:
                    /**
                     * This class is directly called by Boost::Spirit for
                     * delegating parsed token.
                     */
                    class OPENDAVINCI_API ParserTokenHandler {
                        public:
                            /**
                             * Constructor.
                             *
                             * @param g Grammar which has to be used for error handling.
                             * @param data Extended data for the next token.
                             */
                            ParserTokenHandler(const Grammar &g, ParserTokenExtendedData *data = NULL);

                            /**
                             * Copy constructor.
                             *
                             * @param obj Other object.
                             */
                            ParserTokenHandler(const ParserTokenHandler &obj);

                            /**
                             * Assignment operator.
                             *
                             * @param obj Other object.
                             * @return Reference to this object.
                             */
                            ParserTokenHandler& operator=(const ParserTokenHandler &obj);

                            virtual ~ParserTokenHandler();

                            /**
                             * This method is called directly by Boost::Spirit to
                             * retrieve the parsed item.
                             *
                             * @param first Iterator to the beginning of value.
                             * @param second Iterator to the end of the value.
                             */
                            template <typename IteratorT>
                            void operator()(IteratorT first, IteratorT last) const {
                                ParserToken pt(string(first, last), *m_data);
                                m_grammar.getGrammarTokenListener().nextToken(pt);
                            };

                        private:
                            Grammar &m_grammar;
                            ParserTokenExtendedData *m_data;
                    };

                    /**
                     * This class is directly called by Boost::Spirit for
                     * counting new lines.
                     */
                    class OPENDAVINCI_API ParserNewlineHandler {
                        public:
                            /**
                             * Constructor.
                             *
                             * @param g Grammar which has to be used for error handling.
                             */
                            ParserNewlineHandler(const Grammar &g);

                            /**
                             * Copy constructor.
                             *
                             * @param obj Other object.
                             */
                            ParserNewlineHandler(const ParserNewlineHandler &obj);

                            /**
                             * Assignment operator.
                             *
                             * @param obj Other object.
                             * @return Reference to this object.
                             */
                            ParserNewlineHandler& operator=(const ParserNewlineHandler &obj);

                            virtual ~ParserNewlineHandler();

                            /**
                             * This method is called directly by Boost::Spirit to
                             * retrieve the parsed item.
                             *
                             * @param first Iterator to the beginning of value.
                             * @param second Iterator to the end of the value.
                             */
                            template <typename IteratorT>
                            void operator()(IteratorT /*first*/, IteratorT /*last*/) const {
                                m_grammar.incrementLines();
                            };

                        private:
                            Grammar &m_grammar;
                    };

                    /**
                     * This class is directly called by Boost::Spirit for
                     * delegating errors.
                     */
                    class OPENDAVINCI_API ParserErrorHandler {
                        public:
                            /**
                             * Constructor.
                             *
                             * @param g Grammar which has to be used for error handling.
                             */
                            ParserErrorHandler(const Grammar &g, ParserErrorExtendedData *data = NULL);

                            /**
                             * Copy constructor.
                             *
                             * @param obj Other object.
                             */
                            ParserErrorHandler(const ParserErrorHandler &obj);

                            /**
                             * Assignment operator.
                             *
                             * @param obj Other object.
                             * @return Reference to this object.
                             */
                            ParserErrorHandler& operator=(const ParserErrorHandler &obj);

                            virtual ~ParserErrorHandler();

                            template <typename ScannerT, typename ErrorT>
                            boost::spirit::classic::error_status<> operator()(ScannerT const &scan, ErrorT const &/*error*/) const {
                                string context(scan.first, scan.last);
                                boost::algorithm::trim(context);

                                stringstream sstr(context);
                                stringstream sstr2;
                                string tmp;
                                uint32_t newlineCounter = 0;
                                while (getline(sstr, tmp)) {
                                    newlineCounter++;
                                    if (newlineCounter == m_grammar.getCurrentLine()) {
                                        sstr2 << "===Erroneous line===>>> ";
                                    }
                                    sstr2 << tmp << endl;
                                }

                                m_data->setLine(m_grammar.getCurrentLine());
                                ParserError pe(sstr2.str(), *m_data);
                                m_grammar.getGrammarErrorListener().errorToken(pe);
                                return boost::spirit::classic::error_status<>(boost::spirit::classic::error_status<>::fail);
                            }

                        private:
                            Grammar &m_grammar;
                            ParserErrorExtendedData *m_data;
                    };
            };

        }
    }
} // core::wrapper::parser

#endif /*HESPERIA_CORE_WRAPPER_PARSER_BOOSTSPIRITGRAMMAR_H_*/
