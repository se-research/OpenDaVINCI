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

#ifndef HESPERIA_SCENARIO_SCNGRAMMAR_H_
#define HESPERIA_SCENARIO_SCNGRAMMAR_H_

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

#include "hesperia/core/wrapper/parser/BoostSpiritGrammar.h"
#include "hesperia/core/wrapper/parser/ParserTokenListener.h"
#include "hesperia/core/wrapper/parser/ParserTokenExtendedData.h"
#include "hesperia/core/wrapper/parser/ParserErrorListener.h"
#include "hesperia/core/wrapper/parser/ParserErrorExtendedData.h"

namespace hesperia {
    namespace scenario {

        using namespace std;
        using namespace boost::spirit::classic;

        /**
         * This class provides unique identifiers for interpreting the
         * SAX-stylish data processing.
         */
        class SCNGrammarTokenIdentifier : public core::wrapper::parser::ParserTokenExtendedData {
            public:
                enum IDENTIFIERS {
                    UNDEFINED = 0,
                    START_ID,
                    SCENARIOHEADER_ID,
                    COORDINATESYSTEM_ID,
                    WGS84COORDINATESYSTEM_ID,
                    TYPECOORDINATESYSTEM_ID,
                    VERTEX2_ID,
                    VERTEX3_ID,
                    GROUND_ID,
                    LAYER_ID,
                    AERIALIMAGE_ID,
                    HEIGHTIMAGE_ID,
                    IMAGE_ID,
                    IMAGEFILE_ID,
                    SURROUNDING_ID,
                    SHAPE_ID,
                    TYPESHAPE_ID,
                    POLYGON_ID,
                    CYLINDER_ID,
                    COMPLEXMODEL_ID,
                    ROAD_ID,
                    LANE_ID,
                    LANEMODEL_ID,
                    POINTMODEL_ID,
                    FUNCTIONMODEL_ID,
                    TYPEFUNCTIONMODEL_ID,
                    IDVERTEX2_ID,
                    STRAIGHTLINE_ID,
                    CLOTHOID_ID,
                    ARC_ID,
                    LANEATTRIBUTE_ID,
                    BOUNDARYSTYLE_ID,
                    TRAFFICCONTROL_ID,
                    TRAFFICCONTROLTRAFFICLIGHTTYPE_ID,
                    TRAFFICCONTROLTRAFFICSIGNTYPE_ID,
                    TRAFFICLIGHT_ID,
                    TRAFFICSIGN_ID,
                    TRAFFICSIGNTYPE_ID,
                    CONNECTOR_ID,
                    FQID_ID,
                    ZONE_ID,
                    PERIMETER_ID,
                    SPOT_ID,

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
                SCNGrammarTokenIdentifier(const enum IDENTIFIERS &id);

                virtual ~SCNGrammarTokenIdentifier();

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
         * SCNParserTokenListener scnptl;
         * SCNParserErrorListener scnpel;
         * SCNGrammar g(scnptl, scnpel);
         *
         * string s = "Input to be parsed";
         *
         * g.parseData(s);
         * ...
         * @endcode
         */
        class SCNGrammar : public core::wrapper::parser::BoostSpiritGrammar, public grammar<SCNGrammar> {
            public:
                /**
                 * Constructor.
                 *
                 * @param ptl Listener for successfully parsed tokens.
                 * @param pel Listener for occurring errors.
                 */
                SCNGrammar(core::wrapper::parser::ParserTokenListener &ptl, core::wrapper::parser::ParserErrorListener &pel);

                virtual ~SCNGrammar();

                virtual core::wrapper::parser::ASTNode* getAST(const string &s);

            private:
                assertion<uint32_t> expect;
                guard<uint32_t> m_guard;

            public:
                template <typename ScannerT>
                struct definition {
                    definition(SCNGrammar const &self) :
                            START(),
                            SCENARIOHEADER(),
                            COORDINATESYSTEM(),
                            WGS84COORDINATESYSTEM(),
                            TYPECOORDINATESYSTEM(),
                            VERTEX2(),
                            VERTEX3(),
                            GROUND(),
                            LAYER(),
                            AERIALIMAGE(),
                            HEIGHTIMAGE(),
                            IMAGE(),
                            IMAGEFILE(),
                            SURROUNDING(),
                            SHAPE(),
                            TYPESHAPE(),
                            POLYGON(),
                            CYLINDER(),
                            COMPLEXMODEL(),
                            ROAD(),
                            LANE(),
                            LANEMODEL(),
                            POINTMODEL(),
                            FUNCTIONMODEL(),
                            TYPEFUNCTIONMODEL(),
                            IDVERTEX2(),
                            STRAIGHTLINE(),
                            CLOTHOID(),
                            ARC(),
                            LANEATTRIBUTE(),
                            BOUNDARYSTYLE(),
                            TRAFFICCONTROL(),
                            TRAFFICCONTROLTRAFFICLIGHTTYPE(),
                            TRAFFICCONTROLTRAFFICSIGNTYPE(),
                            TRAFFICLIGHT(),
                            TRAFFICSIGN(),
                            TRAFFICSIGNTYPE(),
                            CONNECTOR(),
                            FQID(),
                            ZONE(),
                            PERIMETER(),
                            SPOT(),

                            ALPHANUM(),
                            NUMBER(),
                            NEWLINE(),
                            TAB() {

                        START = self.m_guard(self.expect(
                                                 *NEWLINE
                                                 >> SCENARIOHEADER      // File header.
                                                 >> NEWLINE
                                                 >> GROUND              // Ground layer.
                                                 >> NEWLINE
                                                 >> + LAYER             // Data layers containing roads and other stuff.
                                                 >> NEWLINE
                                                 >> str_p("ENDSCENARIO")// End of scenario.
                                                 >> !NEWLINE
                                             ))[BoostSpiritGrammar::ParserErrorHandler(self, NULL)];

                        SCENARIOHEADER =
                            str_p("SCENARIO")
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
                            >> str_p("ORIGINCOORDINATESYSTEM")
                            >> NEWLINE
                            >> COORDINATESYSTEM;

                        COORDINATESYSTEM =
                            WGS84COORDINATESYSTEM   // At the moment, only WGS84 is supported.
                            >> NEWLINE
                            >> str_p("ROTATION")
                            >> TAB
                            >> NUMBER;              // The scenario's rotation around the coordinate's origin in RAD (3am is 0).

                        WGS84COORDINATESYSTEM =
                            TYPECOORDINATESYSTEM
                            >> NEWLINE
                            >> str_p("ORIGIN")
                            >> NEWLINE
                            >> VERTEX2;             // Logical (0, 0) lies at (ORIGINX, ORIGINY) in the chosen coordinates.

                        TYPECOORDINATESYSTEM =
                            leaf_node_d[str_p("WGS84")]; // Currently, only WGS84 is supported.

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

                        GROUND =
                            str_p("GROUND")
                            >> TAB
                            >> ALPHANUM                 // Begin of the ground layer.
                            >> NEWLINE
                            >> !AERIALIMAGE             // Aerial image for the ground.
                            >> !HEIGHTIMAGE             // Image for the height data.
                            >> !SURROUNDING             // Surroundings like houses or trees.
                            >> str_p("ENDGROUND");

                        AERIALIMAGE =
                            str_p("AERIALIMAGE")
                            >> NEWLINE
                            >> IMAGE                    // Data for the aerial image.
                            >> NEWLINE;

                        HEIGHTIMAGE =
                            str_p("HEIGHTIMAGE")
                            >> NEWLINE
                            >> IMAGE                    // Data for the height image.
                            >> NEWLINE
                            >> str_p("GROUNDHEIGHT")
                            >> TAB
                            >> NUMBER                   // Which color is used for ground level (0 m)?
                            >> NEWLINE
                            >> str_p("MINHEIGHT")
                            >> TAB
                            >> NUMBER                   // Which height level in m is meant by color 0?
                            >> NEWLINE
                            >> str_p("MAXHEIGHT")
                            >> TAB
                            >> NUMBER                   // Which height level in m is meant by color 255?
                            >> NEWLINE;

                        IMAGE =
                            str_p("IMAGE")
                            >> TAB
                            >> IMAGEFILE                // File name of the image.
                            >> NEWLINE
                            >> str_p("ORIGINX")
                            >> TAB
                            >> NUMBER                   // Origin of X in image coordinates (relative to upper/left corner).
                            >> NEWLINE
                            >> str_p("ORIGINY")
                            >> TAB
                            >> NUMBER                   // Origin of Y in image coordinates (relative to upper/left corner).
                            >> NEWLINE
                            >> str_p("MPPX")
                            >> TAB
                            >> NUMBER                   // Image's resolution per m in X direction.
                            >> NEWLINE
                            >> str_p("MPPY")
                            >> TAB
                            >> NUMBER                   // Image's resolution per m in Y direction.
                            >> NEWLINE
                            >> str_p("ROTZ")
                            >> TAB
                            >> NUMBER;                  // Counterclockwise rotation around Z-axis in RAD (3am is 0).

                        IMAGEFILE = ALPHANUM;

                        SURROUNDING =
                            str_p("SURROUNDING")        // Begin of surroundings.
                            >> NEWLINE
                            >> + SHAPE;                // List of shapes.

                        SHAPE =
                            str_p("SHAPENAME")
                            >> TAB
                            >> ALPHANUM
                            >> NEWLINE
                            >> (POLYGON | CYLINDER | COMPLEXMODEL) // Type of the shape.
                            >> NEWLINE;

                        TYPESHAPE =
                            ( leaf_node_d[str_p("POLYGON")] |   // Either polygon (i.e. rectangular boxes, complex polygons)...
                              leaf_node_d[str_p("CYLINDER")] |  // ...or cylinders...
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
                            >> VERTEX2                  // A minimum of two vertices is necessary.
                            >> + (NEWLINE >> VERTEX2);

                        CYLINDER =
                            TYPESHAPE
                            >> NEWLINE
                            >> VERTEX2                  // Center of the cylinder.
                            >> NEWLINE
                            >> str_p("RADIUS")
                            >> TAB
                            >> NUMBER                   // Radius of the cylinder > 0.
                            >> NEWLINE
                            >> str_p("HEIGHT")
                            >> TAB
                            >> NUMBER                   // Height of the polygon > 0.
                            >> NEWLINE
                            >> str_p("COLOR")
                            >> NEWLINE
                            >> VERTEX3;                 // RGB color.

                        COMPLEXMODEL =
                            TYPESHAPE
                            >> NEWLINE
                            >> str_p("MODELFILE")
                            >> TAB
                            >> ALPHANUM                 // File name of the model.
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

                        LAYER =
                            str_p("LAYER")
                            >> TAB
                            >> ALPHANUM                 // Begin of layer "LAYER_NAME". Layers contain roads and are stacked to allow bridges.
                            >> NEWLINE
                            >> str_p("LAYERID")
                            >> TAB
                            >> NUMBER                   // Integer identifier of this layer greater than 0.
                            >> NEWLINE
                            >> str_p("HEIGHT")
                            >> TAB
                            >> NUMBER                   // Height of this layer.
                            >> NEWLINE
                            >> + ( ROAD >> NEWLINE)
                            >> *( ZONE >> NEWLINE)
                            >> str_p("ENDLAYER");

                        ROAD =
                            str_p("ROAD")               // Begin of a road.
                            >> NEWLINE
                            >> str_p("ROADID")          // Integer identifier of this road greater than 0.
                            >> TAB
                            >> NUMBER
                            >> NEWLINE
                            >> !(str_p("ROADNAME") >> TAB >> ALPHANUM >> NEWLINE) // Name of the road.
                            >> + (LANE >> NEWLINE)     // Each road contains at least one lane.
                            >> str_p("ENDROAD");

                        LANE =
                            str_p("LANE")
                            >> NEWLINE
                            >> str_p("LANEID")
                            >> TAB
                            >> NUMBER                   // Integer identifier of this lane greater than 0.
                            >> NEWLINE
                            >> LANEMODEL                // Which lane model to be used.
                            >> NEWLINE
                            >> str_p("ENDLANE");

                        LANEMODEL =
                            LANEATTRIBUTE               // Lane's width as well as lane markings.
                            >> *(CONNECTOR)             // Connectors describe how lanes are interconnected.
                            >> *(TRAFFICCONTROL)        // Traffic lights, traffic signs...
                            >> (POINTMODEL | FUNCTIONMODEL); // Either point- or function-model.

                        CONNECTOR =                     // Layer-ID . Road-ID . Lane-ID . {Point|Function}-ID.
                            FQID
                            >> TAB
                            >> str_p("->")
                            >> TAB
                            >> FQID
                            >> NEWLINE;

                        LANEATTRIBUTE =
                            !(str_p("LANEWIDTH") >> TAB >> NUMBER >> NEWLINE) // Lane's width.
                            >> !(str_p("LEFTLANEMARKING") >> TAB >> BOUNDARYSTYLE >> NEWLINE) // Lane's left boundary style.
                            >> !(str_p("RIGHTLANEMARKING") >> TAB >> BOUNDARYSTYLE >> NEWLINE); // Lane's right boundary style.

                        BOUNDARYSTYLE =
                            ( leaf_node_d[str_p("double_yellow")] |
                              leaf_node_d[str_p("solid_yellow")] |
                              leaf_node_d[str_p("solid_white")] |
                              leaf_node_d[str_p("broken_white")] |
                              leaf_node_d[str_p("crosswalk")] );

                        TRAFFICCONTROL =
                            (TRAFFICLIGHT | TRAFFICSIGN)
                            >> NEWLINE
                            >> str_p("NAME")
                            >> TAB
                            >> ALPHANUM                 // Name of the traffic control.
                            >> NEWLINE
                            >> IDVERTEX2                // Identifier and position inside the layer.
                            >> NEWLINE
                            >> SHAPE;                   // Shape of the traffic control.

                        TRAFFICCONTROLTRAFFICLIGHTTYPE =
                            leaf_node_d[str_p("TRAFFICLIGHT")]; // Either traffic light...

                        TRAFFICCONTROLTRAFFICSIGNTYPE =
                            leaf_node_d[str_p("TRAFFICSIGN")]; // Either traffic light...

                        TRAFFICLIGHT =
                            TRAFFICCONTROLTRAFFICLIGHTTYPE;

                        TRAFFICSIGN =
                            TRAFFICCONTROLTRAFFICSIGNTYPE
                            >> NEWLINE
                            >> str_p("VALUE")
                            >> TAB
                            >> TRAFFICSIGNTYPE;         // Different types of traffic signs.

                        TRAFFICSIGNTYPE =
                            ( leaf_node_d[str_p("stopline")] ); // Only stoplines at the moment.

                        POINTMODEL =
                            str_p("POINTMODEL")
                            >> NEWLINE
                            >> + (IDVERTEX2 >> NEWLINE) // Identifiable points.
                            >> str_p("ENDPOINTMODEL");

                        IDVERTEX2 =
                            str_p("ID")
                            >> TAB
                            >> NUMBER                   // Integer number greater than 0.
                            >> NEWLINE
                            >> VERTEX2;                 // Ordinary vertex2.

                        FUNCTIONMODEL =
                            str_p("FUNCTIONMODEL")
                            >> NEWLINE
                            >> (STRAIGHTLINE | CLOTHOID | ARC) // Either straight line, clothoid or arc.
                            >> NEWLINE
                            >> str_p("ENDFUNCTIONMODEL");

                        TYPEFUNCTIONMODEL =
                            ( leaf_node_d[str_p("STRAIGHTLINE")] |  // A straight line.
                              leaf_node_d[str_p("CLOTHOID")] |      // A clothoid.
                              leaf_node_d[str_p("ARC")] );          // An arc in polar coordinates using r and phi (= x).

                        STRAIGHTLINE =
                            TYPEFUNCTIONMODEL
                            >> NEWLINE
                            >> str_p("START")
                            >> NEWLINE
                            >> IDVERTEX2                // The start point.
                            >> NEWLINE
                            >> str_p("END")
                            >> NEWLINE
                            >> IDVERTEX2;               // The end point.

                        CLOTHOID =
                            TYPEFUNCTIONMODEL
                            >> NEWLINE
                            >> str_p("DK")
                            >> TAB
                            >> NUMBER                   // Curvature change.
                            >> NEWLINE
                            >> str_p("K")
                            >> TAB
                            >> NUMBER                   // Curvature.
                            >> NEWLINE
                            >> str_p("START")
                            >> NEWLINE
                            >> IDVERTEX2                // The start point.
                            >> NEWLINE
                            >> str_p("END")
                            >> NEWLINE
                            >> IDVERTEX2                // The end point.
                            >> NEWLINE
                            >> str_p("ROTZ")
                            >> TAB
                            >> NUMBER;                  // Rotation around Z axis.

                        ARC =
                            TYPEFUNCTIONMODEL
                            >> NEWLINE
                            >> str_p("RADIUS")
                            >> TAB
                            >> NUMBER                   // Radius.
                            >> NEWLINE
                            >> ch_p('[')                // The definition interval.
                            >> TAB
                            >> NUMBER
                            >> TAB
                            >> NUMBER
                            >> TAB
                            >> ch_p(']')
                            >> NEWLINE
                            >> str_p("START")
                            >> NEWLINE
                            >> IDVERTEX2                // The start point.
                            >> NEWLINE
                            >> str_p("END")
                            >> NEWLINE
                            >> IDVERTEX2                // The end point.
                            >> NEWLINE
                            >> str_p("ROTZ")
                            >> TAB
                            >> NUMBER;                  // Rotation around Z axis.

                        ZONE =
                            str_p("ZONE")               // Begin of a zone.
                            >> NEWLINE
                            >> str_p("ZONEID")
                            >> TAB
                            >> NUMBER                   // Integer identifier of this zone greater than 0.
                            >> NEWLINE
                            >> !(str_p("ZONENAME") >> TAB >> ALPHANUM >> NEWLINE) // Name of the zone.
                            >> *(CONNECTOR)             // Connectors describe how lanes and zones are interconnected.
                            // Exit points of zones are denoted by LANEID . ZONEID . 0 . POINTID.
                            >> PERIMETER                // Description of the bounding polygon.
                            >> NEWLINE
                            >> *(SPOT >> NEWLINE)       // List of special spots in this zone.
                            >> str_p("ENDZONE");

                        PERIMETER =
                            str_p("PERIMETER")
                            >> NEWLINE
                            >> IDVERTEX2
                            >> NEWLINE
                            >> IDVERTEX2
                            >> NEWLINE
                            >> + (IDVERTEX2 >> NEWLINE) // At least three vertices describe a perimeter.
                            >> str_p("ENDPERIMETER");

                        SPOT =
                            str_p("SPOT")
                            >> NEWLINE
                            >> str_p("SPOTID")
                            >> TAB
                            >> NUMBER                   // Integer identifier of this zone greater than 0.
                            >> NEWLINE
                            >> VERTEX2
                            >> NEWLINE
                            >> VERTEX2                  // Two vertices determine orientation.
                            >> NEWLINE
                            >> str_p("ENDSPOT");


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
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::START_ID> > START;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::SCENARIOHEADER_ID> > SCENARIOHEADER;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::COORDINATESYSTEM_ID> > COORDINATESYSTEM;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::WGS84COORDINATESYSTEM_ID> > WGS84COORDINATESYSTEM;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TYPECOORDINATESYSTEM_ID> > TYPECOORDINATESYSTEM;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::VERTEX2_ID> > VERTEX2;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::VERTEX3_ID> > VERTEX3;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::GROUND_ID> > GROUND;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::LAYER_ID> > LAYER;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::AERIALIMAGE_ID> > AERIALIMAGE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::HEIGHTIMAGE_ID> > HEIGHTIMAGE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::IMAGE_ID> > IMAGE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::IMAGEFILE_ID> > IMAGEFILE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::SURROUNDING_ID> > SURROUNDING;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::SHAPE_ID> > SHAPE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TYPESHAPE_ID> > TYPESHAPE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::POLYGON_ID> > POLYGON;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::CYLINDER_ID> > CYLINDER;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::COMPLEXMODEL_ID> > COMPLEXMODEL;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::ROAD_ID> > ROAD;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::LANE_ID> > LANE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::LANEMODEL_ID> > LANEMODEL;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::POINTMODEL_ID> > POINTMODEL;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::FUNCTIONMODEL_ID> > FUNCTIONMODEL;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TYPEFUNCTIONMODEL_ID> > TYPEFUNCTIONMODEL;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::IDVERTEX2_ID> > IDVERTEX2;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::STRAIGHTLINE_ID> > STRAIGHTLINE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::CLOTHOID_ID> > CLOTHOID;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::ARC_ID> > ARC;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::LANEATTRIBUTE_ID> > LANEATTRIBUTE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::BOUNDARYSTYLE_ID> > BOUNDARYSTYLE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TRAFFICCONTROL_ID> > TRAFFICCONTROL;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TRAFFICCONTROLTRAFFICLIGHTTYPE_ID> > TRAFFICCONTROLTRAFFICLIGHTTYPE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TRAFFICCONTROLTRAFFICSIGNTYPE_ID> > TRAFFICCONTROLTRAFFICSIGNTYPE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TRAFFICLIGHT_ID> > TRAFFICLIGHT;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TRAFFICSIGN_ID> > TRAFFICSIGN;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TRAFFICSIGNTYPE_ID> > TRAFFICSIGNTYPE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::CONNECTOR_ID> > CONNECTOR;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::FQID_ID> > FQID;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::ZONE_ID> > ZONE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::PERIMETER_ID> > PERIMETER;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::SPOT_ID> > SPOT;

                    // Identifier for the terminals of the grammar.
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::ALPHANUM_ID> > ALPHANUM;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::NUMBER_ID> > NUMBER;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::NEWLINE_ID> > NEWLINE;
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::TAB_ID> > TAB;

                    // Start production rule.
                    rule<ScannerT, parser_context<>, parser_tag<SCNGrammarTokenIdentifier::START_ID> > const& start() const {
                        return START;
                    }
                };
        };

    }
} // hesperia::scenario

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#endif /*HESPERIA_SCENARIO_SCNGRAMMAR_H_*/
