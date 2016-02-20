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

#ifdef WIN32
#include <windows.h>
#endif

#include <string>
#include <vector>

#include <GL/gl.h>
#include <GL/glut.h>

#include "opendavinci/odcore/opendavinci.h"
#include "automotivedata/generated/cartesian/Constants.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/decorator/models/Material.h"
#include "opendlv/decorator/models/TriangleSet.h"
#include "opendlv/decorator/threeD/Renderer3D.h"
#include "opendlv/threeD/TextureManager.h"

namespace core { namespace wrapper { class Image; } }

namespace opendlv {
    namespace decorator {
        namespace threeD {

            using namespace std;
            using namespace odcore::data;
            using namespace opendlv::data::environment;
            using namespace opendlv::decorator::models;

            Renderer3D::Renderer3D() :
                m_listOfImagesRegisteredAtTextureManager() {}

            Renderer3D::~Renderer3D() {
                opendlv::threeD::TextureManager &textureManager = opendlv::threeD::TextureManager::getInstance();
                vector<string>::iterator it = m_listOfImagesRegisteredAtTextureManager.begin();
                while (it != m_listOfImagesRegisteredAtTextureManager.end()) {
                    textureManager.removeTexture(*it++);
                }
            }

            void Renderer3D::beginPainting() {
                glPushMatrix();
            }

            void Renderer3D::endPainting() {
                glPopMatrix();
            }

            void Renderer3D::setColor(const Point3 &c) {
                glColor3f(static_cast<float>(c.getX()), static_cast<float>(c.getY()), static_cast<float>(c.getZ()));
            }

            void Renderer3D::setPointWidth(const double &width) {
                glPointSize(static_cast<float>(width));
            }

            void Renderer3D::setLineWidth(const double &width) {
                glLineWidth(static_cast<float>(width));
            }

            void Renderer3D::drawText(const Point3 &position, const string &text) {
                glRasterPos3f(static_cast<float>(position.getX()), static_cast<float>(position.getY()), static_cast<float>(position.getZ()));
                for (uint32_t i = 0; i < text.length(); i++) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text.at(i));
                }
            }

            void Renderer3D::drawPoint(const Point3 &p) {
                glBegin(GL_POINTS);
                    glVertex3f(static_cast<float>(p.getX()), static_cast<float>(p.getY()), static_cast<float>(p.getZ()));
                glEnd();
            }

            void Renderer3D::drawLine(const Point3 &A, const Point3 &B) {
                glBegin(GL_LINES);
                    glVertex3f(static_cast<float>(A.getX()), static_cast<float>(A.getY()), static_cast<float>(A.getZ()));
                    glVertex3f(static_cast<float>(B.getX()), static_cast<float>(B.getY()), static_cast<float>(B.getZ()));
                glEnd();
            }

            void Renderer3D::drawPolyLine(const vector<Point3> &listOfPoints) {
                if (listOfPoints.size() > 1) {
                    glBegin(GL_LINES);
                        for(uint32_t i = 0; i < listOfPoints.size() - 1; i++) {
                            glVertex3f(static_cast<float>(listOfPoints[i].getX()), static_cast<float>(listOfPoints[i].getY()), static_cast<float>(listOfPoints[i].getZ()));
                            glVertex3f(static_cast<float>(listOfPoints[i+1].getX()), static_cast<float>(listOfPoints[i+1].getY()), static_cast<float>(listOfPoints[i+1].getZ()));
                        }
                    glEnd();
                }
            }

            void Renderer3D::drawPolyLine(const vector<Point3> &listOfPoints, const double &height) {
                if (listOfPoints.size() > 1) {
                    glBegin(GL_QUADS);
                    for (uint32_t i = 0; i < listOfPoints.size() - 1; i++) {
                        const Point3 &p1 = listOfPoints[i];
                        const Point3 &p2 = listOfPoints[i+1];

                        Point3 P12 = p2 - p1;
                        P12.setZ(0);
                        const Point3 P1H = Point3(p1.getX(), p1.getY(), height);
                        const Point3 P1HxP12 = P1H.cross(P12);

                        glVertex3f(static_cast<float>(p1.getX()), static_cast<float>(p1.getY()), 0);
                        glVertex3f(static_cast<float>(p1.getX()), static_cast<float>(p1.getY()), static_cast<float>(height));
                        glVertex3f(static_cast<float>(p2.getX()), static_cast<float>(p2.getY()), static_cast<float>(height));
                        glVertex3f(static_cast<float>(p2.getX()), static_cast<float>(p2.getY()), 0);
                        glNormal3f(static_cast<float>(P1HxP12.getX()), static_cast<float>(P1HxP12.getY()), static_cast<float>(P1HxP12.getZ()));
                    }
                    glEnd();
                }
            }

            void Renderer3D::drawTriangleSet(const TriangleSet &ts) {
                drawTriangleSet(ts, Point3(), Point3());
            }

            void Renderer3D::drawListOfTriangleSets(const vector<TriangleSet> &listOfTriangleSets) {
                drawListOfTriangleSets(listOfTriangleSets, Point3(), Point3());
            }

            void Renderer3D::drawTriangleSet(const TriangleSet &ts, const Point3 &position, const Point3 &rotation) {
                glTranslatef(static_cast<float>(position.getX()), static_cast<float>(position.getY()), static_cast<float>(position.getZ()));

                glRotatef(static_cast<float>(rotation.getX()*180.0 / cartesian::Constants::PI), 1, 0, 0);
                glRotatef(static_cast<float>(rotation.getY()*180.0 / cartesian::Constants::PI), 0, 1, 0);
                glRotatef(static_cast<float>(rotation.getZ()*180.0 / cartesian::Constants::PI), 0, 0, 1);

                glPushMatrix();
                {
                    uint32_t normalIndexCounter = 0;
                    glBegin(GL_TRIANGLES);
                    for (uint32_t i = 0; i < ts.m_vertices.size(); i++) {
                        if (i < ts.m_textureCoordinates.size()) {
                            glTexCoord2f(static_cast<float>(ts.m_textureCoordinates[i].getX()),
                                         static_cast<float>(ts.m_textureCoordinates[i].getY()));
                        }
                        if ((i % 3) == 0) {
                            if (normalIndexCounter < ts.m_normals.size()) {
                                glNormal3f(static_cast<float>(ts.m_normals[normalIndexCounter].getX()),
                                           static_cast<float>(ts.m_normals[normalIndexCounter].getY()),
                                           static_cast<float>(ts.m_normals[normalIndexCounter].getZ()));
                            }
                            normalIndexCounter++;
                        }
                        glVertex3f(static_cast<float>(ts.m_vertices[i].getX()),
                                   static_cast<float>(ts.m_vertices[i].getY()),
                                   static_cast<float>(ts.m_vertices[i].getZ()));
                    }
                    glEnd();
                }
                glPopMatrix();
            }

            void Renderer3D::drawListOfTriangleSets(const vector<opendlv::decorator::models::TriangleSet> &listOfTriangleSets, const opendlv::data::environment::Point3 &position, const opendlv::data::environment::Point3 &rotation) {
                glTranslatef(static_cast<float>(position.getX()), static_cast<float>(position.getY()), static_cast<float>(position.getZ()));

                glRotatef(static_cast<float>(rotation.getX()*180.0 / cartesian::Constants::PI), 1, 0, 0);
                glRotatef(static_cast<float>(rotation.getY()*180.0 / cartesian::Constants::PI), 0, 1, 0);
                glRotatef(static_cast<float>(rotation.getZ()*180.0 / cartesian::Constants::PI), 0, 0, 1);

                glPushMatrix();
                {
                    // Fix inside OBJ-Wavefront-Models (OBJXArchive).
                    // Rotate the model using DEG (rotation is in RAD!).
                    Point3 rotateAroundXAxis(cartesian::Constants::PI/2.0, 0, 0);

                    glRotatef(static_cast<float>(rotateAroundXAxis.getX()*180.0 / cartesian::Constants::PI), 1, 0, 0);
                    glRotatef(static_cast<float>(rotateAroundXAxis.getY()*180.0 / cartesian::Constants::PI), 0, 1, 0);
                    glRotatef(static_cast<float>(rotateAroundXAxis.getZ()*180.0 / cartesian::Constants::PI), 0, 0, 1);

                    glPushMatrix();
                    {
                        vector<TriangleSet>::const_iterator it = listOfTriangleSets.begin();
                        while (it != listOfTriangleSets.end()) {
                            if ((*it).m_vertices.size() > 0) {
                                int32_t textureHandle = -1;
                                if ((*it).m_material.getImage() != NULL) {
                                    opendlv::threeD::TextureManager &textureManager = opendlv::threeD::TextureManager::getInstance();

                                    // Check if the texture has to be loaded first.
                                    stringstream sstrImage;
                                    sstrImage << "Image-" << (*it).m_material.getImage();
                                    if (!textureManager.hasTexture(sstrImage.str())) {
                                        textureManager.addImage(sstrImage.str(), (*it).m_material.getImage());
                                        m_listOfImagesRegisteredAtTextureManager.push_back(sstrImage.str());
                                    }

                                    // Get texture handle.
                                    textureHandle = textureManager.getTexture(sstrImage.str());
                                    glEnable(GL_TEXTURE_2D);
                                    glBindTexture(GL_TEXTURE_2D, static_cast<uint32_t>(textureHandle));
                                    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                                }

                                // Apply material.
                                glEnable(GL_COLOR_MATERIAL);
                                glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                                float ambient[] = { static_cast<float>((*it).m_material.getAmbient().getX()),
                                                    static_cast<float>((*it).m_material.getAmbient().getY()),
                                                    static_cast<float>((*it).m_material.getAmbient().getZ()) };

                                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

                                float diffuse[] = { static_cast<float>((*it).m_material.getDiffuse().getX()),
                                                    static_cast<float>((*it).m_material.getDiffuse().getY()),
                                                    static_cast<float>((*it).m_material.getDiffuse().getZ())
                                                  };

                                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

                                float specular[] = { static_cast<float>((*it).m_material.getSpecular().getX()),
                                                    static_cast<float>((*it).m_material.getSpecular().getY()),
                                                    static_cast<float>((*it).m_material.getSpecular().getZ()) };

                                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

                                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, static_cast<float>((*it).m_material.getShininess()));

                                glColor3f(static_cast<float>((*it).m_material.getDiffuse().getX()),
                                          static_cast<float>((*it).m_material.getDiffuse().getY()),
                                          static_cast<float>((*it).m_material.getDiffuse().getZ()));

                                // Draw triangle set.
                                drawTriangleSet(*it);

                                if (textureHandle > -1) {
                                    glDisable(GL_TEXTURE_2D);
                                }
                            }
                            it++;
                        }
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }

            void Renderer3D::drawImage(const core::wrapper::Image *image, const Point3 &originPixelXY, const Point3 &scalingPixelXY, const float &rotationZ) {
                if (image != NULL) {
                    // Get texture manager.
                    opendlv::threeD::TextureManager &textureManager = opendlv::threeD::TextureManager::getInstance();

                    // Use current image's memory address as identifier.
                    stringstream sstrAddressOfImage;
                    sstrAddressOfImage << "Image-" << image;

                    // Try to retrieve a previously loaded image from the texture manager.
                    uint32_t textureHandle = 0;
                    int32_t retVal = textureManager.getTexture(sstrAddressOfImage.str());
                    if (retVal > 0) {
                        // Image was already loaded.
                        textureHandle = static_cast<uint32_t>(retVal);
                    }
                    else {
                        // Initially load the image.
                        textureManager.addImage(sstrAddressOfImage.str(), image);
                        m_listOfImagesRegisteredAtTextureManager.push_back(sstrAddressOfImage.str());

                        textureHandle = static_cast<uint32_t>(textureManager.getTexture(sstrAddressOfImage.str()));
                    }

                    // Compute the translation point considering the image coordinate system.
                    Point3 translate;
                    translate.setX(-1 * originPixelXY.getX() * scalingPixelXY.getX());
                    translate.setY(-1 * (image->getHeight() - originPixelXY.getY()) * scalingPixelXY.getY());

                    // Compute the scaling factor.
                    Point3 scale;
                    scale.setX(image->getWidth() * scalingPixelXY.getX());
                    scale.setY(image->getHeight() * scalingPixelXY.getY());

                    // Now, scale the image.
                    Point3 translateToTheCenterOfTheImage(-0.5, -0.5, 0);
                    Point3 translateBack = translateToTheCenterOfTheImage * (-1);
                    Point3 flipAroundXAxis(cartesian::Constants::PI, 0, rotationZ);

                    // Draw the image.
                    glPushMatrix();
                    {
                        glTranslatef(static_cast<float>(translate.getX()),
                                     static_cast<float>(translate.getY()),
                                     static_cast<float>(translate.getZ()));

                        // Scale the aerial image.
                        glScalef(static_cast<float>(scale.getX()),
                                 static_cast<float>(scale.getY()),
                                 static_cast<float>(scale.getZ()));

                        glPushMatrix();
                        {
                            glTranslatef(static_cast<float>(translateBack.getX()),
                                         static_cast<float>(translateBack.getY()),
                                         static_cast<float>(translateBack.getZ()));

                            glPushMatrix();
                            {
                                // Rotate the model using DEG (rotation is in RAD!).
                                glRotatef(static_cast<float>(flipAroundXAxis.getX()*180.0 / cartesian::Constants::PI), 1, 0, 0);
                                glRotatef(static_cast<float>(flipAroundXAxis.getY()*180.0 / cartesian::Constants::PI), 0, 1, 0);
                                glRotatef(static_cast<float>(flipAroundXAxis.getZ()*180.0 / cartesian::Constants::PI), 0, 0, 1);

                                glPushMatrix();
                                {
                                    glTranslatef(static_cast<float>(translateToTheCenterOfTheImage.getX()),
                                                 static_cast<float>(translateToTheCenterOfTheImage.getY()),
                                                 static_cast<float>(translateToTheCenterOfTheImage.getZ()));

                                    glPushMatrix();
                                    {
                                        // Actually draw the image.
                                        glEnable(GL_TEXTURE_2D);
                                        glBindTexture(GL_TEXTURE_2D, textureHandle);
                                        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

                                        glBegin(GL_QUADS);
                                        glTexCoord2f(0, 0);
                                        glVertex3f(0, 0, 0);

                                        glTexCoord2f(0, 1);
                                        glVertex3f(0, 1, 0);

                                        glTexCoord2f(1, 1);
                                        glVertex3f(1, 1, 0);

                                        glTexCoord2f(1, 0);
                                        glVertex3f(1, 0, 0);
                                        glEnd();

                                        glDisable(GL_TEXTURE_2D);
                                    }
                                    glPopMatrix();
                                }
                                glPopMatrix();
                            }
                            glPopMatrix();
                        }
                        glPopMatrix();
                    }
                    glPopMatrix();
                }
            }
        }
    }
} // opendlv::decorator::threeD
