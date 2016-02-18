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

#ifndef HESPERIA_SITUATION_SITGRAMMAR_H_
#define HESPERIA_SITUATION_SITGRAMMAR_H_

#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

#include <cassert>
#include <string>

#include "opendavinci/core/opendavinci.h"

#include <boost/spirit/include/classic_ast.hpp>
#include <boost/spirit/include/classic_error_handling.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_core.hpp>

#include "opendlv/core/wrapper/parser/BoostSpiritGrammar.h"
#include "opendlv/core/wrapper/parser/ParserTokenListener.h"
#include "opendlv/core/wrapper/parser/ParserTokenExtendedData.h"
#include "opendlv/core/wrapper/parser/ParserErrorListener.h"
#include "opendlv/core/wrapper/parser/ParserErrorExtendedData.h"

namespace hesperia {
    namespace situation {

        using namespace std;
        using namespace boost::spirit::classic;

        /**
         * This class provides unique identifiers for interpreting the
         * SAX-stylish data processing.
         */
        class SITGrammarTokenIdentifier : public core::wrapper::parser::ParserTokenExtendedData {
            public:
                enum IDENTIFIERS {
                    UNDEFINED = 0,
                    START_ID,
                    SITUATIONHEADER_ID,
                    OBJECT_ID,
                    VERTEX2_ID,
                    VERTEX3_ID,
                    SHAPE_ID,
                    TYPESHAPE_ID,
                    POLYGON_ID,
                    COMPLEXMODEL_ID,
                    RECTANGLE_ID,
                    BEHAVIOR_ID,
                    EXTERNALDRIVER_ID,
                    POINTIDDRIVER_ID,
                    STARTTYPE_ID,
                    TYPESTARTTYPE_ID,
                    IMMEDIATELY_ID,
                    OBJECTID_ID,
                    ONENTERINGPOLYGON_ID,
                    TYPESTOPTYPE_ID,
                    PROFILE_ID,
                    FQID_ID,
                    CONSTANTVELOCITY_ID,
                    CONSTANTACCELERATION_ID,

                    ALPHANUM_ID,
                    NUMBER_ID,
                    NEWLINE_ID,
                    TAB_ID
                };

                /**
                 * Constructor.
                 *
                 * @param id Identifier.
                 */
                SITGrammarTokenIdentifier(const enum IDENTIFIERS &id);

                virtual ~SITGrammarTokenIdentifier();

                /**
                 * This method returns the identifier.
                 *
                 * @return Identifier.
                 */
                enum IDENTIFIERS getIdentifier() const;

            private:
                IDENTIFIERS m_id;
        };

        /**
         * This class implements the grammar for parsing .scn-files:
         *
         * @code
         * ...
         * SITParserTokenListener sitptl;
         * SITParserErrorListener sitpel;
         * SITGrammar g(sitptl, sitpel);
         *
         * string s = "Input to be parsed";
         *
         * g.parseData(s);         * ...
         * @endcode
         */
        class SITGrammar : public core::wrapper::parser::BoostSpiritGrammar, public grammar<SITGrammar> {
            public:
                /**
                 * Constructor.
                 *
                 * @param ptl Listener for successfully parsed tokens.
                 * @param pel Listener for occurring errors.
                 */
                SITGrammar(core::wrapper::parser::ParserTokenListener &ptl, core::wrapper::parser::ParserErrorListener &pel);

                virtual ~SITGrammar();

                virtual core::wrapper::parser::ASTNode* getAST(const string &s);

            private:
                assertion<uint32_t> expect;
                guard<uint32_t> m_guard;

            public:
                template <typename ScannerT>
                struct definition {
                    definition(SITGrammar const &self) :
                            START(),
                            SITUATIONHEADER(),
                            OBJECT(),
                            VERTEX2(),
                            VERTEX3(),
                            SHAPE(),
                            TYPESHAPE(),
                            POLYGON(),
                            COMPLEXMODEL(),
                            RECTANGLE(),
                            BEHAVIOR(),
                            EXTERNALDRIVER(),
                            POINTIDDRIVER(),
                            TYPESTARTTYPE(),
                            IMMEDIATELY(),
                            OBJECTID(),
                            ONENTERINGPOLYGON(),
                            TYPESTOPTYPE(),
                            PROFILE(),
							FQID(),
                            CONSTANTVELOCITY(),
                            CONSTANTACCELERATION(),

                            ALPHANUM(),
                            NUMBER(),
                            NEWLINE(),
                            TAB() {

                        START = self.m_guard(self.expect(
                                                 *NEWLINE
                                                 >> SITUATIONHEADER      // File header.
                                                 >> NEWLINE
                                                 >> + ( OBJECT >> NEWLINE)
                                                 >> str_p("ENDSITUATION")// End of scenario.
                                                 >> !NEWLINE
                                             ))[BoostSpiritGrammar::ParserErrorHandler(self, NULL)];

                        SITUATIONHEADER =
                            str_p("SITUATION")
                            >> TAB
                            >> ALPHANUM             // Scenario's name.
                            >> NEWLINE
                            >> str_p("VERSION")
                            >> TAB
                            >> ALPHANUM             // Version of the scenario grammar.
                            >> NEWLINE
                            >> str_p("DATE")
                            >> TAB
                            >> ALPHANUM             // Creation date of the file.
                            >> NEWLINE
                            >> str_p("SCENARIO")
                            >> TAB
                            >> ALPHANUM;             // Referred scenario.

                        OBJECT =
                            str_p("OBJECT")
                            >> TAB
                            >> ALPHANUM             // Object's name.
                            >> NEWLINE
                            >> str_p("OBJECTID")
                            >> TAB
                            >> ALPHANUM             // ID for this object.
                            >> NEWLINE
                            >> SHAPE                // Object's shape.
                            >> str_p("ROTZ")
                            >> TAB
                            >> ALPHANUM             // Rotation for this object.
                            >> NEWLINE
                            >> BEHAVIOR
                            >> str_p("ENDOBJECT");  // End of object.

                        VERTEX2 =
                            str_p("VERTEX2")
                            >> NEWLINE
                            >> ch_p('X')
                            >> TAB
                            >> NUMBER
                            >> NEWLINE
                            >> ch_p('Y')
                            >> TAB
                            >> NUMBER;

                        VERTEX3 =
                            str_p("VERTEX3")
                            >> NEWLINE
                            >> ch_p('X')
                            >> TAB
                            >> NUMBER
                            >> NEWLINE
                            >> ch_p('Y')
                            >> TAB
                            >> NUMBER
                            >> NEWLINE
                            >> ch_p('Z')
                            >> TAB
                            >> NUMBER;

                        SHAPE =
                            str_p("SHAPENAME")
                            >> TAB
                            >> ALPHANUM
                            >> NEWLINE
                            >> (RECTANGLE | POLYGON | COMPLEXMODEL) // Type of the shape.
                            >> NEWLINE;

                        TYPESHAPE =
                            ( leaf_node_d[str_p("POLYGON")] |   // Either polygon (i.e. rectangular boxes, complex polygons)...
                              leaf_node_d[str_p("RECTANGLE")] |  // ...or cylinders...
                              leaf_node_d[str_p("COMPLEXMODEL")] );  // ...or complex model to be loaded from file.

                        POLYGON =
                            TYPESHAPE
                            >> NEWLINE
                            >> str_p("HEIGHT")
                            >> TAB
                            >> NUMBER                   // Height of the polygon > 0.
                            >> NEWLINE
                            >> str_p("COLOR")
                            >> NEWLINE
                            >> VERTEX3                  // RGB color.
                            >> NEWLINE
                            >> VERTEX2                  // Front.
                            >> NEWLINE
                            >> VERTEX2                  // A minimum of two vertices is necessary.
                            >> + (NEWLINE >> VERTEX2);

                        COMPLEXMODEL =
                            TYPESHAPE
                            >> NEWLINE
                            >> str_p("MODELFILE")
                            >> TAB
                            >> ALPHANUM                 // File name of the model.
                            >> NEWLINE
                            >> VERTEX2                  // Front.
                            >> NEWLINE
                            >> str_p("POSITION")
                            >> NEWLINE
                            >> VERTEX3                  // Position of the complex model (center of mass).
                            >> NEWLINE
                            >> str_p("ROTATION")
                            >> NEWLINE
                            >> VERTEX3                  // Counterclockwise rotation of the complex model in RAD (3am is 0).
                            >> NEWLINE
                            >> str_p("BOUNDINGBOX")     // The bounding box defines a rectangular outline around the complex model.
                            >> NEWLINE
                            >> VERTEX2                  // First: upper/left.
                            >> NEWLINE
                            >> VERTEX2                  // Second: upper/right.
                            >> NEWLINE
                            >> VERTEX2                  // Third: lower/right.
                            >> NEWLINE
                            >> VERTEX2;                 // Fourth: lower/left.

                        RECTANGLE =
                            TYPESHAPE
                            >> NEWLINE
                            >> str_p("HEIGHT")
                            >> TAB
                            >> NUMBER                   // Height of the polygon > 0.
                            >> NEWLINE
                            >> str_p("COLOR")
                            >> NEWLINE
                            >> VERTEX3                  // RGB color.
                            >> NEWLINE
                            >> VERTEX2                  // Front.
                            >> NEWLINE
                            >> str_p("LENGTH")
                            >> TAB
                            >> NUMBER                   // Length.
                            >> NEWLINE
                            >> str_p("WIDTH")
                            >> TAB
                            >> NUMBER;                  // Width.
                        // The construction of a rectangle is defined as:
                        //
                        // ---------Length------------
                        // |                         |
                        // W                         |
                        // i                         |      \
                        // d                         X-------+
                        // t                         |      /
                        // h                         |
                        // |                         |
                        // ---------Length------------
                        //
                        // X = Front, + = ROTZ.

                        BEHAVIOR =
                            str_p("BEHAVIOR")
                            >> NEWLINE
                            >> (EXTERNALDRIVER | POINTIDDRIVER);

                        EXTERNALDRIVER =
                            str_p("EXTERNALDRIVER")
                            >> NEWLINE;

                        POINTIDDRIVER =
                            str_p("POINTIDDRIVER")
                            >> NEWLINE
                            >> TYPESTARTTYPE
                            >> NEWLINE
                            >> !OBJECTID
                            >> !ONENTERINGPOLYGON
                            >> TYPESTOPTYPE
                            >> NEWLINE
                            >> PROFILE
                            >> + (NEWLINE >> FQID)
							>> NEWLINE;

                        TYPESTARTTYPE =
                            str_p("STARTTYPE")
                            >> NEWLINE
                            >> ( leaf_node_d[str_p("IMMEDIATELY")] |        // Start immediately.
                                 leaf_node_d[str_p("ONMOVING")] |              // Start when object ID starts moving.
                                 leaf_node_d[str_p("ONENTERINGPOLYGON")] );    // Start when object ID enters the polygon defined by at least four vertices.

                        IMMEDIATELY =
                            NEWLINE;

                        OBJECTID =
                            str_p("OBJECTID")
                            >> TAB
                            >> NUMBER                                       // Number of object to react on.
                            >> NEWLINE;

                        ONENTERINGPOLYGON =
                            VERTEX2
                            >> NEWLINE
                            >> VERTEX2
                            >> NEWLINE
                            >> VERTEX2
                            >> + (NEWLINE >> VERTEX2)                       // Polygon to be entered by object ID.
                            >> NEWLINE;

                        TYPESTOPTYPE =
                            str_p("STOPTYPE")
                            >> NEWLINE
                            >> ( leaf_node_d[str_p("STOP")] |               // Stop immediately.
                                 leaf_node_d[str_p("RETURNTOSTART")] |         // Find a route to the start point and return.
                                 leaf_node_d[str_p("WARPTOSTART")] );          // "Warp" to the start point.

                        PROFILE = (CONSTANTACCELERATION | CONSTANTVELOCITY);

                        CONSTANTACCELERATION =
                            str_p("CONSTANTACCELERATION")
                            >> NEWLINE
                            >> str_p("A")
                            >> TAB
                            >> NUMBER;                                      // Constant acceleration.

                        CONSTANTVELOCITY =
                            str_p("CONSTANTVELOCITY")
                            >> NEWLINE
                            >> str_p("V")
                            >> TAB
                            >> NUMBER;                                      // Constant velocity.



                        // Terminals of the grammar.

                        ALPHANUM = leaf_node_d[+ print_p];

                        NUMBER = leaf_node_d[!ch_p('-') >> ((range_p('1', '9') >> *range_p('0', '9')) | (range_p('0', '9'))) >> !(ch_p('.') >>  + range_p('0', '9'))];

                        FQID = leaf_node_d[ch_p('(') >> range_p('1', '9') >> *range_p('0', '9') >> ch_p('.')
                                           >> range_p('1', '9') >> *range_p('0', '9') >> ch_p('.')
                                           >> ( (range_p('1', '9') >> *range_p('0', '9') >> ch_p('.')) | (ch_p('0')) )
                                           >> range_p('1', '9') >> *range_p('0', '9') >> ch_p(')')
                                          ];

                        TAB = + blank_p;

                        NEWLINE = *TAB >> + eol_p[BoostSpiritGrammar::ParserNewlineHandler(self)]; // Count new lines.
                    }

                    // Identifier for the non-terminals of the grammar.
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::START_ID> > START;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::SITUATIONHEADER_ID> > SITUATIONHEADER;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::OBJECT_ID> > OBJECT;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::VERTEX2_ID> > VERTEX2;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::VERTEX3_ID> > VERTEX3;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::SHAPE_ID> > SHAPE;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::TYPESHAPE_ID> > TYPESHAPE;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::POLYGON_ID> > POLYGON;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::COMPLEXMODEL_ID> > COMPLEXMODEL;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::RECTANGLE_ID> > RECTANGLE;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::BEHAVIOR_ID> > BEHAVIOR;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::EXTERNALDRIVER_ID> > EXTERNALDRIVER;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::POINTIDDRIVER_ID> > POINTIDDRIVER;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::TYPESTARTTYPE_ID> > TYPESTARTTYPE;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::IMMEDIATELY_ID> > IMMEDIATELY;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::OBJECTID_ID> > OBJECTID;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::ONENTERINGPOLYGON_ID> > ONENTERINGPOLYGON;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::TYPESTOPTYPE_ID> > TYPESTOPTYPE;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::PROFILE_ID> > PROFILE;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::FQID_ID> > FQID;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::CONSTANTVELOCITY_ID> > CONSTANTVELOCITY;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::CONSTANTACCELERATION_ID> > CONSTANTACCELERATION;

                    // Identifier for the terminals of the grammar.
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::ALPHANUM_ID> > ALPHANUM;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::NUMBER_ID> > NUMBER;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::NEWLINE_ID> > NEWLINE;
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::TAB_ID> > TAB;

                    // Start production rule.
                    rule<ScannerT, parser_context<>, parser_tag<SITGrammarTokenIdentifier::START_ID> > const& start() const {
                        return START;
                    }
                };
        };

    }
} // hesperia::situation

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#endif /*HESPERIA_SITUATION_SITGRAMMAR_H_*/
