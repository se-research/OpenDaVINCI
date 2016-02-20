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

#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Serializable.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"
#include "hesperia/data/environment/Line.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/environment/Polygon.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace core::base;
            using namespace hesperia::data::environment;

            const double Polygon::EPSILON = 1e-10;

            Polygon::Polygon() :
                m_listOfVertices() {}

            Polygon::Polygon(const vector<Point3> &vertices) :
                m_listOfVertices(vertices) {
                sort();            
            }

            Polygon::Polygon(const Polygon &obj) :
                m_listOfVertices(obj.m_listOfVertices) {
                sort();            
            }

            Polygon::~Polygon() {}

            Polygon& Polygon::operator=(const Polygon &obj) {
                m_listOfVertices = obj.m_listOfVertices;
                sort();

                return (*this);
            }

            void Polygon::add(const Point3 &p) {
                m_listOfVertices.push_back(p);
            }

            uint32_t Polygon::getSize() const {
                return m_listOfVertices.size();
            }

            vector<Point3> Polygon::getVertices() const {
                return m_listOfVertices;
            }

            bool Polygon::containsIgnoreZ(const Point3 &p) const {
                // http://rw7.de/ralf/inffaq/polygon.html
                bool retVal = false;

                if (getSize() > 0) {
                    Point3 oldPoint = m_listOfVertices.back();
                    Point3 currentPoint;

                    int32_t alpha = 0;
                    int32_t quadrant = 0;
                    int32_t currentQuadrant = 0;

                    if ( (oldPoint.getY() < p.getY()) || (oldPoint.getY() - p.getY() < Polygon::EPSILON) ) {
                        if ( (oldPoint.getX() < p.getX()) || (oldPoint.getX() - p.getX() < Polygon::EPSILON) ) {
                            quadrant = 0;
                        }
                        else {
                            quadrant = 1;
                        }
                    }
                    else if ( (oldPoint.getX() <= p.getX()) || (oldPoint.getX() - p.getX() < Polygon::EPSILON) ) {
                        quadrant = 3;
                    }
                    else {
                        quadrant = 2;
                    }

                    for(uint32_t i = 0; i < getSize(); i++) {
                        currentPoint = m_listOfVertices.at(i);

                        if ( (currentPoint.getY() < p.getY()) || (currentPoint.getY() - p.getY() < Polygon::EPSILON) ) {
                            if ( (currentPoint.getX() < p.getX()) || (currentPoint.getX() - p.getX() < Polygon::EPSILON) ) {
                                currentQuadrant = 0;
                            }
                            else {
                                currentQuadrant = 1;
                            }
                        }
                        else if ( (currentPoint.getX() < p.getX()) || (currentPoint.getX() - p.getX() < Polygon::EPSILON) ) {
                            currentQuadrant = 3;
                        }
                        else {
                            currentQuadrant = 2;
                        }

                        switch ((currentQuadrant - quadrant) & 3) {
                            case 0:
                            break;
                            case 1:
                                alpha++;
                            break;
                            case 3:
                                alpha--;
                            break;
                            default: {
                                const double nominator = (currentPoint.getX() - oldPoint.getX()) * (p.getY() - oldPoint.getY());
                                const double denominator = (currentPoint.getY() - oldPoint.getY());
                                if (fabs(denominator) > Polygon::EPSILON) {
                                    const double value = nominator / denominator + oldPoint.getX();

                                    if (fabs(p.getX() - value) < Polygon::EPSILON) {
                                        return false;
                                    }

                                    if ( (p.getX() > value) == (currentPoint.getY() > oldPoint.getY()) ) {
                                        alpha -= 2;
                                    }
                                    else {
                                        alpha += 2;
                                    }
                                }
                            }
                        }

                        oldPoint = currentPoint;
                        quadrant = currentQuadrant;
                    }

                    retVal = ((alpha == 4) || (alpha == -4));
                }

                return retVal;
            }

            Polygon Polygon::intersectIgnoreZ(const Polygon &other) const {
                // Algorithm:
                // For every pair<Vertex, Vertex> from other determine the intersection point P with every pair<Vertex, Vertex> from this.
                // For every Vertex from other check if the Vertex is inside this.
                // For all resulting Vertices in the overlapping polygon sort vertices to remove all crossings.

                Polygon resultingPolygon;

                vector<Point3> thisPolygon = getVertices();
                vector<Point3> otherPolygon = other.getVertices();

                if ( (thisPolygon.size() > 0) && (otherPolygon.size() > 0) ) {
                    // Modify vertices by adding the first vertex at the end of both lists for closing the polygon.
                    thisPolygon.push_back((*thisPolygon.begin()));
                    otherPolygon.push_back((*otherPolygon.begin()));

                    for(uint32_t i = 0; i < thisPolygon.size() - 1; i++) {
                        Point3 thisA = thisPolygon.at(i);
                        Point3 thisB = thisPolygon.at(i+1);
                        Line thisLine(thisA, thisB);

                        for(uint32_t j = 0; j < otherPolygon.size() - 1; j++) {
                            Point3 otherA = otherPolygon.at(j);
                            Point3 otherB = otherPolygon.at(j+1);
                            Line otherLine(otherA, otherB);

                            Point3 result;
                            if (thisLine.intersectIgnoreZ(otherLine, result)) {
                                // Intersection point found.
                                resultingPolygon.add(result);
                            }
                        }
                    }

                    // Now, check if one vertex from other is within this polygon.
                    for(uint32_t j = 0; j < otherPolygon.size()-1; j++) {
                        Point3 otherVertex = otherPolygon.at(j);

                        if (containsIgnoreZ(otherVertex)) {
                            resultingPolygon.add(otherVertex);
                        }
                    }

                    // Remove crossing lines.
                    resultingPolygon.sort();
                }

                return resultingPolygon;
            }

            /**
             * This class can be used to sort lines by angle.
             */
            class AngleXYComparator {
                public:
                    /**
                     * Constructor.
                     *
                     * @param point Point to be used for sorting.
                     */
                    AngleXYComparator(const Point3 &point) :
                        m_point(point) {}

                    bool operator()(const Point3 &p1, const Point3 &p2) {
                        return ((p1-m_point).getAngleXY() < (p2-m_point).getAngleXY());
                    }

                private:
                    Point3 m_point;
            };

            void Polygon::sort() {
                AngleXYComparator angleXYComparator(getCenter());
                std::sort(m_listOfVertices.begin(), m_listOfVertices.end(), angleXYComparator);
            }

            Polygon Polygon::getVisiblePolygonIgnoreZ(const Point3 &point) const {
                // Algorithm:
                // For using as contour: Determine all visible vertices:
                //  For every vertex v from resulting polygon:
                //    Determine intersection point from pair<v, point>
                //    minus epsilon with all pair<Vertex, Vertex> from Polygon p.
                //    If no such point exists, the vertex is directly visible.
                Polygon contour;

                vector<Point3> thisPolygon = getVertices();

                if (thisPolygon.size() > 0) {
                    vector<Point3> resultingVertices;

                    // Add the first vertex to the end to close the polygon.
                    vector<Point3> thisPolygonCyclic = getVertices();
                    thisPolygonCyclic.push_back((*thisPolygonCyclic.begin()));

                    for(uint32_t i = 0; i < thisPolygon.size(); i++) {
                        Point3 thisA = thisPolygon.at(i);
                        Line viewingPositionLine(point, thisA);

                        // ALL sides of the other polygon must be tested.
                        bool thisACanBeSeenDirectly = true;
                        for(uint32_t j = 0; j < thisPolygonCyclic.size() - 1; j++) {
                            // Skip the vertex to be checked itself.
                            if ((i == j) || (i == j+1)) {
                                continue;
                            }

                            Point3 thisPolygonA = thisPolygonCyclic.at(j);
                            Point3 thisPolygonB = thisPolygonCyclic.at(j+1);
                            Line thisPolygonLine(thisPolygonA, thisPolygonB);

                            Point3 result;
                            if (viewingPositionLine.intersectIgnoreZ(thisPolygonLine, result)) {
                                // Found one side of the polygon that is intersect by viewingPositionLine.
                                thisACanBeSeenDirectly = false;
                            }
                        }

                        // This vertex is not hidden.
                        if (thisACanBeSeenDirectly) {
                            resultingVertices.push_back(thisA);
                        }
                    }

                    // Remove crossing from viewing position.
                    AngleXYComparator angleXYComparator(point);
                    std::sort(resultingVertices.begin(), resultingVertices.end(), angleXYComparator);
                    contour = Polygon(resultingVertices);
                }

                return contour;
            }

            Point3 Polygon::getCenter() const {
                Point3 center;

                if (getSize() > 0) {
                    Point3 smallest = (*m_listOfVertices.begin());
                    Point3 greatest = (*m_listOfVertices.begin());

                    for(uint32_t i = 0; i < getSize(); i++) {
                        Point3 point = m_listOfVertices.at(i);

                        // Compute smallest coordinates.
                        if (point.getX() < smallest.getX()) {
                            smallest.setX(point.getX());
                        }
                        if (point.getY() < smallest.getY()) {
                            smallest.setY(point.getY());
                        }
                        if (point.getZ() < smallest.getZ()) {
                            smallest.setZ(point.getZ());
                        }

                        // Compute greatest coordinates.
                        if (point.getX() > greatest.getX()) {
                            greatest.setX(point.getX());
                        }
                        if (point.getY() > greatest.getY()) {
                            greatest.setY(point.getY());
                        }
                        if (point.getZ() > greatest.getZ()) {
                            greatest.setZ(point.getZ());
                        }
                    }

                    center = (smallest + greatest) * 0.5;
                }
                return center;
            }

            int32_t Polygon::getID() const {
                return 25;
            }

            const string Polygon::getShortName() const {
                return "Polygon";
            }

            const string Polygon::getLongName() const {
                return "hesperia.data.environment.Polygon";
            }

            const string Polygon::toString() const {
                stringstream s;
                s << "Polygon contains " << m_listOfVertices.size() << " vertices: " << endl;
                vector<Point3>::const_iterator it = m_listOfVertices.begin();
                while (it != m_listOfVertices.end()) {
                    s << (*it).toString();

                    if ((it+1) != m_listOfVertices.end()) {
                        s << ", ";
                    }

                    it++;
                }
                return s.str();
            }

            ostream& Polygon::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                // Write number of vertices.
                uint32_t numberOfVertices = static_cast<uint32_t>(m_listOfVertices.size());
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'v', 'e', 'r', 't', 's') >::RESULT,
                        numberOfVertices);

                // Write actual vertices to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfVertices; i++) {
                    sstr << m_listOfVertices.at(i);
                }

                // Write string of vertices.
                if (numberOfVertices > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('v', 'e', 'r', 't', 'i', 'c', 'e', 's') >::RESULT,
                            sstr.str());
                }

                return out;
            }

            istream& Polygon::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                // Clean up.
                m_listOfVertices.clear();

                // Read number of vertices.
                uint32_t numberOfVertices = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'v', 'e', 'r', 't', 's') >::RESULT,
                       numberOfVertices);

                if (numberOfVertices > 0) {
                    // Read string of vertices.
                    string vertices;
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('v', 'e', 'r', 't', 'i', 'c', 'e', 's') >::RESULT,
                           vertices);

                    stringstream sstr(vertices);

                    // Read actual vertices from stringstream.
                    for (uint32_t i = 0; i < numberOfVertices; i++) {
                        Point3 p;
                        sstr >> p;
                        add(p);
                    }
                }

                return in;
            }

        }
    }
} // hesperia::data::environment
