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
#include <string>

#include "opendavinci/core/opendavinci.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/NodeRenderingConfiguration.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/TextureManager.h"
#include "hesperia/threeD/models/AerialImage.h"

namespace core { namespace wrapper { class Image; } }

namespace hesperia {
    namespace threeD {
        namespace models {

            using namespace hesperia::data::environment;
            using namespace core::wrapper;

            AerialImageRenderer::AerialImageRenderer(const NodeDescriptor &nodeDescriptor, const uint32_t &textureHandle) :
                    Node(nodeDescriptor),
                    m_textureHandle(textureHandle) {}

            AerialImageRenderer::AerialImageRenderer(const AerialImageRenderer &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_textureHandle(obj.m_textureHandle) {}

            AerialImageRenderer& AerialImageRenderer::operator=(const AerialImageRenderer &obj) {
                setNodeDescriptor(obj.getNodeDescriptor());
                m_textureHandle = obj.m_textureHandle;
                return (*this);
            }

            AerialImageRenderer::~AerialImageRenderer() {}

            void AerialImageRenderer::render(RenderingConfiguration &renderingConfiguration) {
                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                    glPushMatrix();
                    {
                        if (renderingConfiguration.hasDrawTextures()) {
                            glEnable(GL_TEXTURE_2D);
                            glBindTexture(GL_TEXTURE_2D, m_textureHandle);
                            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                        }

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

                        if (renderingConfiguration.hasDrawTextures()) {
                            glDisable(GL_TEXTURE_2D);
                        }
                    }
                    glPopMatrix();
                }
            }

            ////////////////////////////////////////////////////////////////////

            AerialImage::AerialImage(const NodeDescriptor &nodeDescriptor, const Image *image, const Point3 &originPixelXY, const Point3 &scalingPixelXY, const float &rotationZ) :
                    Node(nodeDescriptor),
                    m_image(image),
                    m_originPixelXY(originPixelXY),
                    m_scalingPixelXY(scalingPixelXY),
                    m_rotationZ(rotationZ),
                    m_textureHandle(0),
                    m_aerialImageNode(NULL),
                    m_aerialImageRenderer(NULL),
                    m_translateToTheCenterOfTheImage(NULL),
                    m_flipImageAroundXAxis(NULL),
                    m_translateBack(NULL) {
                // Setup aerial image renderer.
                init();
            }

            AerialImage::AerialImage(const AerialImage &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_image(obj.m_image),
                    m_originPixelXY(obj.m_originPixelXY),
                    m_scalingPixelXY(obj.m_scalingPixelXY),
                    m_rotationZ(obj.m_rotationZ),
                    m_textureHandle(obj.m_textureHandle),
                    m_aerialImageNode(NULL),
                    m_aerialImageRenderer(NULL),
                    m_translateToTheCenterOfTheImage(NULL),
                    m_flipImageAroundXAxis(NULL),
                    m_translateBack(NULL) {
                // Setup aerial image renderer.
                init();
            }

            AerialImage& AerialImage::operator=(const AerialImage &obj) {
                setNodeDescriptor(obj.getNodeDescriptor()),
                m_image = obj.m_image;
                m_originPixelXY = obj.m_originPixelXY;
                m_scalingPixelXY = obj.m_scalingPixelXY;
                m_rotationZ = obj.m_rotationZ;
                m_textureHandle = obj.m_textureHandle;

                // Setup aerial image renderer.
                init();

                return (*this);
            }

            AerialImage::~AerialImage() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_aerialImageRenderer);
                TextureManager& tm = TextureManager::getInstance();
                tm.removeTexture("SCNX.AerialImage");
          }

            void AerialImage::init() {
                if (m_image != NULL) {
                    // Compute the translation point considering the image coordinate system.
                    Point3 translate;
                    translate.setX(-1 * m_originPixelXY.getX() * m_scalingPixelXY.getX());
                    translate.setY(-1 * (m_image->getHeight() - m_originPixelXY.getY()) * m_scalingPixelXY.getY());

                    // Compute the scaling factor.
                    Point3 scale;
                    scale.setX(m_image->getWidth() * m_scalingPixelXY.getX());
                    scale.setY(m_image->getHeight() * m_scalingPixelXY.getY());

                    // Create texture.
                    TextureManager& tm = TextureManager::getInstance();
                    tm.addImage("SCNX.AerialImage", m_image);
                    int32_t textureHandle = tm.getTexture("SCNX.AerialImage");
                    if (textureHandle > 0) {
                        m_textureHandle = static_cast<uint32_t>(textureHandle);
                        // Set up aerialImageRenderer.
                        m_aerialImageRenderer = new AerialImageRenderer(getNodeDescriptor(), m_textureHandle);
                    }

                    // Create transformation group for modifying the aerial image.
                    // The image is flipped by PI around the X-axis. Therefore,
                    // the image needs to be translated to the half of its size,
                    // rotated around the X-axis and translated back to its
                    // original position by the half of its size.
                    m_translateToTheCenterOfTheImage = new TransformGroup();
                    m_translateToTheCenterOfTheImage->addChild(m_aerialImageRenderer);
                    m_translateToTheCenterOfTheImage->setTranslation(Point3(-0.5, -0.5, 0));

                    // Flip the actual image around the X-axis and rotate the aerial image.
                    m_flipImageAroundXAxis = new TransformGroup();
                    m_flipImageAroundXAxis->addChild(m_translateToTheCenterOfTheImage);
                    m_flipImageAroundXAxis->setRotation(Point3(cartesian::Constants::PI, 0, m_rotationZ));

                    m_translateBack = new TransformGroup();
                    m_translateBack->addChild(m_flipImageAroundXAxis);
                    m_translateBack->setTranslation(Point3(0.5, 0.5, 0));

                    // Collate all transformations into the real TransformGroup.
                    m_aerialImageNode = new TransformGroup();
                    m_aerialImageNode->addChild(m_translateBack);

                    // Translate the aerial image.
                    m_aerialImageNode->setTranslation(Point3(translate.getX(), translate.getY(), 0));

                    // Scale the aerial image.
                    m_aerialImageNode->setScaling(Point3(scale.getX(), scale.getY(), 0));
                }
            }

            void AerialImage::render(RenderingConfiguration &renderingConfiguration) {
                // Delegate rendering.
                if (m_image != NULL) {
                    m_aerialImageNode->render(renderingConfiguration);
                }
            }

        }
    }
} // hesperia::threeD::models
