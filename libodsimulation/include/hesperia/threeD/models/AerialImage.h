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

#ifndef HESPERIA_CORE_THREED_MODELS_AERIALIMAGE_H_
#define HESPERIA_CORE_THREED_MODELS_AERIALIMAGE_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"
#include "core/wrapper/Image.h"

#include "hesperia/data/environment/Point3.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/TransformGroup.h"

namespace hesperia {
    namespace threeD {
        namespace models {

            using namespace std;

            /**
             * This class represents the actual renderer.
             */
            class OPENDAVINCI_API AerialImageRenderer : public Node {
                public:
                    /**
                     * Constructor.
                     *
                    * @param nodeDesciptor Description for this node.
                     * @param textureHandle Handle for the image's data inside an OpenGL texture.
                     */
                    AerialImageRenderer(const NodeDescriptor &nodeDescriptor, const uint32_t &textureHandle);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    AerialImageRenderer(const AerialImageRenderer &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    AerialImageRenderer& operator=(const AerialImageRenderer &obj);

                    virtual ~AerialImageRenderer();

                    virtual void render(RenderingConfiguration &renderingConfiguration);

                private:
                    uint32_t m_textureHandle;
            };

            /**
             * This class an aerial image.
             */
            class OPENDAVINCI_API AerialImage : public Node {
                public:
                    /**
                     * Constructor.
                     *
                    * @param nodeDesciptor Description for this node.
                     * @param image Image to be used as aerial image.
                     * @param originPixelXY Origin pixel inside the image.
                     * @param scalingPixelXY Scaling for the pixels.
                     * @param rotationZ Rotation of the image around the Z-axis.
                     */
                    AerialImage(const NodeDescriptor &nodeDescriptor,
                                const core::wrapper::Image *image,
                                const hesperia::data::environment::Point3 &originPixelXY,
                                const hesperia::data::environment::Point3 &scalingPixelXY,
                                const float &rotationZ);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    AerialImage(const AerialImage &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    AerialImage& operator=(const AerialImage &obj);

                    virtual ~AerialImage();

                    virtual void render(RenderingConfiguration &renderingConfiguration);

                private:
                    const core::wrapper::Image *m_image;
                    hesperia::data::environment::Point3 m_originPixelXY;
                    hesperia::data::environment::Point3 m_scalingPixelXY;
                    float m_rotationZ;

                    uint32_t m_textureHandle;
                    TransformGroup *m_aerialImageNode;
                    AerialImageRenderer *m_aerialImageRenderer;
                    TransformGroup *m_translateToTheCenterOfTheImage;
                    TransformGroup *m_flipImageAroundXAxis;
                    TransformGroup *m_translateBack;

                    /**
                     * This method initializes the aerial image.
                     */
                    void init();
            };

        }
    }
} // hesperia::threeD::models

#endif /*HESPERIA_CORE_THREED_MODELS_AERIALIMAGE_H_*/
