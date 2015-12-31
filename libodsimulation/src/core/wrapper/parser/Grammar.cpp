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

#include "core/wrapper/parser/Grammar.h"
#include "core/wrapper/parser/ParserErrorExtendedData.h"
#include "core/wrapper/parser/ParserErrorListener.h"
#include "core/wrapper/parser/ParserTokenExtendedData.h"
#include "core/wrapper/parser/ParserTokenListener.h"

namespace core {
    namespace wrapper {
        namespace parser {

            Grammar::Grammar(ParserTokenListener &ptl, ParserErrorListener &pel) :
                    m_tokenListener(ptl),
                    m_errorListener(pel),
                    m_listOfParserTokenExtendedData(),
                    m_listOfGrammarParserErrorExtendedData(),
                    m_lines(0) {}

            Grammar::Grammar(const Grammar &obj) :
                    m_tokenListener(obj.m_tokenListener),
                    m_errorListener(obj.m_errorListener),
                    m_listOfParserTokenExtendedData(obj.m_listOfParserTokenExtendedData),
                    m_listOfGrammarParserErrorExtendedData(obj.m_listOfGrammarParserErrorExtendedData),
                    m_lines(obj.m_lines) {}

            Grammar& Grammar::operator=(const Grammar &obj) {
                m_tokenListener = obj.m_tokenListener;
                m_errorListener = obj.m_errorListener;
                m_listOfParserTokenExtendedData = obj.m_listOfParserTokenExtendedData;
                m_listOfGrammarParserErrorExtendedData = obj.m_listOfGrammarParserErrorExtendedData;
                m_lines = obj.m_lines;

                return (*this);
            }

            Grammar::~Grammar() {
                vector<ParserTokenExtendedData*>::iterator it = m_listOfParserTokenExtendedData.begin();
                while (it != m_listOfParserTokenExtendedData.end()) {
                    ParserTokenExtendedData *gted = (*it++);
                    delete gted;
                }
                m_listOfParserTokenExtendedData.clear();

                vector<ParserErrorExtendedData*>::iterator jt = m_listOfGrammarParserErrorExtendedData.begin();
                while (jt != m_listOfGrammarParserErrorExtendedData.end()) {
                    ParserErrorExtendedData *gpeed = (*jt++);
                    delete gpeed;
                }
                m_listOfGrammarParserErrorExtendedData.clear();
            }

            ParserTokenListener& Grammar::getGrammarTokenListener() const {
                return m_tokenListener;
            }

            ParserErrorListener& Grammar::getGrammarErrorListener() const {
                return m_errorListener;
            }

            void Grammar::add(ParserTokenExtendedData *gted) {
                m_listOfParserTokenExtendedData.push_back(gted);
            }

            void Grammar::add(ParserErrorExtendedData *gpeed) {
                m_listOfGrammarParserErrorExtendedData.push_back(gpeed);
            }

            void Grammar::incrementLines() {
                m_lines++;
            }

            void Grammar::resetLines() {
                m_lines = 0;
            }

            uint32_t Grammar::getCurrentLine() const {
                return m_lines + 1;
            }

        }
    }
} // core::wrapper::parser
