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

#ifndef HESPERIA_SCENARIO_SCENARIOFACTORY_H_
#define HESPERIA_SCENARIO_SCENARIOFACTORY_H_

#include <string>

#include "opendavinci/core/opendavinci.h"

#include "opendavinci/core/base/Mutex.h"
#include "opendavinci/core/exceptions/Exceptions.h"
#include "opendlv/core/wrapper/parser/ParserErrorListener.h"
#include "opendlv/core/wrapper/parser/ParserTokenListener.h"

#include "opendlv/data/scenario/Scenario.h"

namespace opendlv {
    namespace scenario {

        using namespace std;

        /**
         * This class produces the complex core::data::Scenario data structure.
         */
        class OPENDAVINCI_API ScenarioFactory {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ScenarioFactory(const ScenarioFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ScenarioFactory& operator=(const ScenarioFactory &);

            private:
                ScenarioFactory();

            public:
                virtual ~ScenarioFactory();

                /**
                 * This method returns a static instance for this factory.
                 *
                 * @return Instance of this factory.
                 */
                static ScenarioFactory& getInstance();

                /**
                 * This method returns the complex data structure for a scenario.
                 *
                 * @param s String to be parsed.
                 * @return Scenario data structure.
                 * @throws InvalidArgumentException if the input could be parsed.
                 */
                data::scenario::Scenario getScenario(const string &s) throw (core::exceptions::InvalidArgumentException);

            private:
                static core::base::Mutex m_singletonMutex;
                static ScenarioFactory* m_singleton;

                /**
                 * This class is responsible for creating the data structure.
                 */
                class SCNGrammarTokenListener : public core::wrapper::parser::ParserTokenListener {
                    private:
                        /**
                         * "Forbidden" copy constructor. Goal: The compiler should warn
                         * already at compile time for unwanted bugs caused by any misuse
                         * of the copy constructor.
                         */
                        SCNGrammarTokenListener(const SCNGrammarTokenListener &);

                        /**
                         * "Forbidden" assignment operator. Goal: The compiler should warn
                         * already at compile time for unwanted bugs caused by any misuse
                         * of the assignment operator.
                         */
                        SCNGrammarTokenListener& operator=(const SCNGrammarTokenListener &);

                    public:
                        /**
                         * Constructor.
                         *
                         * @param s Scenario to construct using the incoming tokens.
                         */
                        SCNGrammarTokenListener(data::scenario::Scenario &s);

                        virtual ~SCNGrammarTokenListener();

                        virtual void nextToken(const core::wrapper::parser::ParserToken &token);

                    private:
                        data::scenario::Scenario &m_scenario;
                };

                /**
                 * This class is called whenever an error occurs during parsing.
                 */
                class SCNGrammarErrorListener : public core::wrapper::parser::ParserErrorListener {
                    private:
                        /**
                         * "Forbidden" copy constructor. Goal: The compiler should warn
                         * already at compile time for unwanted bugs caused by any misuse
                         * of the copy constructor.
                         */
                        SCNGrammarErrorListener(const SCNGrammarErrorListener &);

                        /**
                         * "Forbidden" assignment operator. Goal: The compiler should warn
                         * already at compile time for unwanted bugs caused by any misuse
                         * of the assignment operator.
                         */
                        SCNGrammarErrorListener& operator=(const SCNGrammarErrorListener &);

                    public:
                        SCNGrammarErrorListener();

                        virtual ~SCNGrammarErrorListener();

                        void errorToken(core::wrapper::parser::ParserError &error);

                        /**
                         * This method returns the occurred error.
                         *
                         * @return Occurred error.
                         */
                        const string getLastError() const;

                    private:
                        string m_lastError;
                };
        };

    }
} // opendlv::scenario

#endif /*HESPERIA_SCENARIO_SCENARIOFACTORY_H_*/
