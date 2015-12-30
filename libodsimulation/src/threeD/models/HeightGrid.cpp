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

// The following include is necessary on Win32 platforms to set up necessary macro definitions.
#ifdef WIN32
    #include <windows.h>
#endif

#include <GL/gl.h>

#include <iostream>
#include <string>

#include "core/platform.h"
#include "core/wrapper/Image.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/NodeRenderingConfiguration.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/models/HeightGrid.h"

namespace hesperia {
    namespace threeD {
        namespace models {

            using namespace core;
            using namespace hesperia::data::environment;

            HeightGridRenderer::HeightGridRenderer(const NodeDescriptor &nodeDescriptor, const uint32_t &callList) :
                    Node(nodeDescriptor),
                    m_callList(callList) {}

            HeightGridRenderer::HeightGridRenderer(const HeightGridRenderer &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_callList(obj.m_callList) {}

            HeightGridRenderer& HeightGridRenderer::operator=(const HeightGridRenderer &obj) {
                setNodeDescriptor(obj.getNodeDescriptor());
                m_callList = obj.m_callList;
                return (*this);
            }

            HeightGridRenderer::~HeightGridRenderer() {}

            void HeightGridRenderer::render(RenderingConfiguration &renderingConfiguration) {
                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                    glPushMatrix();
                    {
                        glCallList(m_callList);
                    }
                    glPopMatrix();
                }
            }

            ////////////////////////////////////////////////////////////////////

            HeightGrid::HeightGrid(const NodeDescriptor &nodeDescriptor, const wrapper::Image *heightImage, const Point3 &originPixelXY, const Point3 &scalingPixelXY, const float &rotationZ, const float &ground, const float &min, const float &max) :
                    Node(nodeDescriptor),
                    m_heightImage(heightImage),
                    m_originPixelXY(originPixelXY),
                    m_scalingPixelXY(scalingPixelXY),
                    m_rotationZ(rotationZ),
                    m_ground(ground),
                    m_min(min),
                    m_max(max),
                    m_callList(0),
                    m_heightImageNode(NULL),
                    m_heightImageRenderer(NULL) {
                // Setup height grid renderer.
                init();
            }

            HeightGrid::HeightGrid(const HeightGrid &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_heightImage(obj.m_heightImage),
                    m_originPixelXY(obj.m_originPixelXY),
                    m_scalingPixelXY(obj.m_scalingPixelXY),
                    m_rotationZ(obj.m_rotationZ),
                    m_ground(obj.m_ground),
                    m_min(obj.m_min),
                    m_max(obj.m_max),
                    m_callList(obj.m_callList),
                    m_heightImageNode(NULL),
                    m_heightImageRenderer(NULL) {
                // Setup height grid renderer.
                init();
            }

            HeightGrid& HeightGrid::operator=(const HeightGrid &obj) {
                setNodeDescriptor(obj.getNodeDescriptor());
                m_heightImage = obj.m_heightImage;
                m_originPixelXY = obj.m_originPixelXY;
                m_scalingPixelXY = obj.m_scalingPixelXY;
                m_rotationZ = obj.m_rotationZ;
                m_ground = obj.m_ground;
                m_min = obj.m_min;
                m_max = obj.m_max;

                // Setup height grid renderer.
                init();

                return (*this);
            }

            HeightGrid::~HeightGrid() {}

            template <class T>
            class MyImage {
                private:
                    const wrapper::Image *m_image;
                    T m_t;

                    MyImage(const MyImage &obj);
                    MyImage& operator=(const MyImage &obj);

                public:
                    MyImage(const wrapper::Image *image) :
                            m_image(image),
                            m_t() {}

                    ~MyImage() {
                        m_image = NULL;
                    }

                    inline T* getPixel(const uint32_t &col, const uint32_t &row) {
                        const uint32_t bytesPerPixel = m_image->getWidthStep() / m_image->getWidth();
                        if ( (   (m_image->getRawData() + row * m_image->getWidth() * bytesPerPixel + col * bytesPerPixel)
                                 > (m_image->getRawData() + m_image->getHeight() * m_image->getWidth() * bytesPerPixel + m_image->getWidth() * bytesPerPixel )
                                 ||
                                 (   (m_image->getRawData() + row * m_image->getWidth() * bytesPerPixel + col * bytesPerPixel)
                                     < (m_image->getRawData()) ) ) ) {
                            return &m_t;
                        }

                        // TODO: Why the heck do I have sometime to add 1?
//                        return (T*)(m_image->getRawData() + (bytesPerPixel * (row * (m_image->getWidth()+1) + col)));
                        return (T*)(m_image->getRawData() + (bytesPerPixel * (row * (m_image->getWidth()) + col)));
                    }
            };
            typedef class BGRPixel_T {
                public:
                    unsigned char b;
                    unsigned char g;
                    unsigned char r;
                    BGRPixel_T() :
                            b(0),
                            g(0),
                            r(0) {}

            } BGRPixel;

            void HeightGrid::init() {
                if (m_heightImage != NULL) {
                    clog << "Generate terrain data: " << m_heightImage->getWidth() << ", " << m_heightImage->getHeight() << ", Format: " << m_heightImage->getFormat() << ", width step: " << m_heightImage->getWidthStep() << endl;

                    MyImage<BGRPixel> img(m_heightImage);

                    // TODO: Compute normals.

                    float scaleZ = m_max - m_min;
                    if (scaleZ < 0) {
                        scaleZ = 1.0f;
                    }
                    if ( (m_ground < 0) || (m_ground > 1) ) {
                        m_ground = 0.5;
                    }
                    clog << "Ground height: " << m_ground << ", scaling Z : " << scaleZ << ", translation for z-direction: " << (-1 * scaleZ * m_ground) << endl;

                    m_callList = glGenLists(1);
                    glNewList(m_callList, GL_COMPILE);
                    for (uint32_t y = 0; y < m_heightImage->getHeight() - 2; y++) {
                        glBegin(GL_TRIANGLE_STRIP);
                        for (uint32_t x = 0; x < m_heightImage->getWidth(); x++) {
                            glColor3f(static_cast<int>(img.getPixel(x, m_heightImage->getHeight() - 1 - y)->r) / 255.0f, static_cast<int>(img.getPixel(x, m_heightImage->getHeight() - 1 - y)->r) / 255.0f, static_cast<int>(img.getPixel(x, m_heightImage->getHeight() - 1 - y)->r) / 255.0f);

                            glVertex3f(static_cast<float>(x), static_cast<float>(y), (static_cast<int>(img.getPixel(x, m_heightImage->getHeight() - 1 - y)->r) / 255.0f - m_ground) * scaleZ);
                            glVertex3f(static_cast<float>(x), static_cast<float>(y + 1), (static_cast<int>(img.getPixel(x, m_heightImage->getHeight() - 1 - (y + 1))->r) / 255.0f - m_ground) * scaleZ);
                        }
                        glEnd();
                    }
                    glEndList();

                    // Compute translation.
                    Point3 translate;
                    translate.setX(-1 * m_originPixelXY.getX() * m_scalingPixelXY.getX());
                    translate.setY(-1 * (m_heightImage->getHeight() - m_originPixelXY.getY()) * m_scalingPixelXY.getY());

                    Point3 scale(m_scalingPixelXY);
                    // m_scalingPixelXY sets z to 0, thus elevation is disable. Therefore, scale z to 1.0, i.e. keep computed elevation.
                    scale.setZ(1.0);

                    // Set up the actual renderer.
                    m_heightImageRenderer = new HeightGridRenderer(getNodeDescriptor(), m_callList);

                    // Set up transform group.
                    m_heightImageNode = new TransformGroup();
                    m_heightImageNode->addChild(m_heightImageRenderer);

                    // Translate the height image.
                    m_heightImageNode->setTranslation(Point3(translate.getX(), translate.getY(), 0));

                    // Scale the height image.
                    m_heightImageNode->setScaling(scale);
                }
            }

            void HeightGrid::render(RenderingConfiguration &renderingConfiguration) {
                // Delegate rendering.
                if (m_heightImage != NULL) {
                    m_heightImageNode->render(renderingConfiguration);
                }
            }
        }
    }
} // hesperia::threeD::models
