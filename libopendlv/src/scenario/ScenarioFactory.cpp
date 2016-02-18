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

#include <cerrno>
#include <iostream>
#include <string>

#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/base/Mutex.h"
#include "opendavinci/core/exceptions/Exceptions.h"
#include "opendavinci/core/opendavinci.h"
#include "opendlv/core/wrapper/parser/ASTNode.h"
#include "opendlv/core/wrapper/parser/ParserError.h"
#include "opendlv/core/wrapper/parser/ParserErrorExtendedData.h"
#include "opendlv/core/wrapper/parser/ParserToken.h"
#include "opendlv/core/wrapper/parser/ParserTokenExtendedData.h"
#include "opendlv/data/scenario/Scenario.h"
#include "opendlv/scenario/SCNGrammar.h"
#include "opendlv/scenario/ScenarioFactory.h"
#include "opendlv/scenario/SCNScenarioVisitor.h"

namespace hesperia {
    namespace scenario {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace core::exceptions;
        using namespace core::wrapper::parser;
        using namespace data::scenario;

        // Initialize singleton instance.
        Mutex ScenarioFactory::m_singletonMutex;
        ScenarioFactory* ScenarioFactory::m_singleton = NULL;

        ScenarioFactory::ScenarioFactory() {}

        ScenarioFactory::~ScenarioFactory() {}

        ScenarioFactory& ScenarioFactory::getInstance() {
            {
                Lock l(ScenarioFactory::m_singletonMutex);
                if (ScenarioFactory::m_singleton == NULL) {
                    ScenarioFactory::m_singleton = new ScenarioFactory();
                }
            }

            return (*ScenarioFactory::m_singleton);
        }

        Scenario ScenarioFactory::getScenario(const string &s) throw (InvalidArgumentException) {
            Scenario scenario;

            SCNGrammarTokenListener scntl(scenario);
            SCNGrammarErrorListener scnel;

            SCNGrammar scnGrammar(scntl, scnel);
            ASTNode *root = scnGrammar.getAST(s.c_str());
            if (root == NULL) {
                errno = 0;
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, scnel.getLastError());
            } else {
//                ASTPrettyPrinter pp;
//                pp.visit(root);

                // Visit AST with scenario visitor to create Scenario data structure.
                SCNScenarioVisitor scenarioVisitor(scenario);
                root->accept(scenarioVisitor);

                // Clean up AST since all data is now in an instance of Scenario.
                delete root;
            }

            return scenario;
        }

        ScenarioFactory::SCNGrammarTokenListener::SCNGrammarTokenListener(data::scenario::Scenario &s) :
                m_scenario(s) {}

        ScenarioFactory::SCNGrammarTokenListener::~SCNGrammarTokenListener() {}

        void ScenarioFactory::SCNGrammarTokenListener::nextToken(const core::wrapper::parser::ParserToken &token) {
            try {
                const SCNGrammarTokenIdentifier &tid = dynamic_cast<const SCNGrammarTokenIdentifier&>(token.getExtendedData());
                clog << "SCNGrammarTokenListener: " << tid.getIdentifier() << ", value: " << token.getValue() << " was not processed." << endl;
            } catch (...) {
                // Ignore std::bad_cast because this factory cannot use irregular data to construct a scenario.
            }
        }

        ScenarioFactory::SCNGrammarErrorListener::SCNGrammarErrorListener() :
                m_lastError() {}

        ScenarioFactory::SCNGrammarErrorListener::~SCNGrammarErrorListener() {}

        void ScenarioFactory::SCNGrammarErrorListener::errorToken(core::wrapper::parser::ParserError &error) {
            stringstream s;
            s << "SCNGrammarErrorListener caught an unknown parser error at line: " << error.getExtendedData().getLine() << " in context '" << error.getContext() << "'.";
            m_lastError = s.str();
        }

        const string ScenarioFactory::SCNGrammarErrorListener::getLastError() const {
            return m_lastError;
        }

    }
} // hesperia::scenario
