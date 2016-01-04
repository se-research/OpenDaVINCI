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

#include "core/base/Lock.h"
#include "core/base/Mutex.h"
#include "core/exceptions/Exceptions.h"
#include "core/opendavinci.h"
#include "core/wrapper/parser/ASTNode.h"
#include "core/wrapper/parser/ParserError.h"
#include "core/wrapper/parser/ParserErrorExtendedData.h"
#include "core/wrapper/parser/ParserToken.h"
#include "core/wrapper/parser/ParserTokenExtendedData.h"
#include "hesperia/data/situation/Situation.h"
#include "hesperia/situation/SITGrammar.h"
#include "hesperia/situation/SituationFactory.h"
#include "hesperia/situation/SITSituationVisitor.h"

namespace hesperia {
    namespace situation {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace core::exceptions;
        using namespace core::wrapper::parser;
        using namespace data::situation;

        // Initialize singleton instance.
        Mutex SituationFactory::m_singletonMutex;
        SituationFactory* SituationFactory::m_singleton = NULL;

        SituationFactory::SituationFactory() {}

        SituationFactory::~SituationFactory() {}

        SituationFactory& SituationFactory::getInstance() {
            {
                Lock l(SituationFactory::m_singletonMutex);
                if (SituationFactory::m_singleton == NULL) {
                    SituationFactory::m_singleton = new SituationFactory();
                }
            }

            return (*SituationFactory::m_singleton);
        }

        Situation SituationFactory::getSituation(const string &s) throw (InvalidArgumentException) {
            Situation situation;

            SITGrammarTokenListener sittl(situation);
            SITGrammarErrorListener sitel;

            SITGrammar sitGrammar(sittl, sitel);
            ASTNode *root = sitGrammar.getAST(s.c_str());
            if (root == NULL) {
                errno = 0;
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, sitel.getLastError());
            } else {
//                ASTPrettyPrinter pp;
//                pp.visit(root);

                // Visit AST with situation visitor to create Situation data structure.
                SITSituationVisitor situationVisitor(situation);
                root->accept(situationVisitor);

                // Clean up AST since all data is now in an instance of Situation.
                delete root;
            }

            return situation;
        }

        SituationFactory::SITGrammarTokenListener::SITGrammarTokenListener(data::situation::Situation &s) :
                m_situation(s) {}

        SituationFactory::SITGrammarTokenListener::~SITGrammarTokenListener() {}

        void SituationFactory::SITGrammarTokenListener::nextToken(const core::wrapper::parser::ParserToken &token) {
            try {
                const SITGrammarTokenIdentifier &tid = dynamic_cast<const SITGrammarTokenIdentifier&>(token.getExtendedData());
                clog << "SITGrammarTokenListener: " << tid.getIdentifier() << ", value: " << token.getValue() << " was not processed." << endl;
            } catch (...) {
                // Ignore std::bad_cast because this factory cannot use irregular data to construct a scenario.
            }
        }

        SituationFactory::SITGrammarErrorListener::SITGrammarErrorListener() :
                m_lastError() {}

        SituationFactory::SITGrammarErrorListener::~SITGrammarErrorListener() {}

        void SituationFactory::SITGrammarErrorListener::errorToken(core::wrapper::parser::ParserError &error) {
            stringstream s;
            s << "SITGrammarErrorListener caught an unknown parser error at line: " << error.getExtendedData().getLine() << " in context '" << error.getContext() << "'.";
            m_lastError = s.str();
        }

        const string SituationFactory::SITGrammarErrorListener::getLastError() const {
            return m_lastError;
        }

    }
} // hesperia::situation
