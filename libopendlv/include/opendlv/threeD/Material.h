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

#ifndef HESPERIA_CORE_THREED_MATERIAL_H_
#define HESPERIA_CORE_THREED_MATERIAL_H_

#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendlv/data/environment/Point3.h"

namespace hesperia {
    namespace threeD {

        using namespace std;

        /**
         * This class represents a material description.
         */
        class Material {
            public:
                Material();

                /**
                 * Constructor.
                 *
                 * @param name Name of this material description.
                 */
                Material(const string &name);

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                Material(const Material &obj);

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                Material& operator=(const Material &obj);

                virtual ~Material();

                /**
                 * This method returns the name of this material description.
                 *
                 * @return Material's name.
                 */
                const string getName() const;

                /**
                 * This method sets the name of the texture for this material description.
                 *
                 * @param textureName Name of the texture for this material.
                 */
                void setTextureName(const string &textureName);

                /**
                 * This method returns the teture's name of this material.
                 *
                 * @return Texture's name.
                 */
                const string getTextureName() const;

                /**
                 * This method sets the shininess factor.
                 *
                 * @param s Shininess.
                 */
                void setShininess(const double &s);

                /**
                 * This method returns the shininess factor.
                 *
                 * @return Shininess.
                 */
                double getShininess() const;

                /**
                 * This method sets the value for ambient.
                 *
                 * @param a Value for ambient.
                 */
                void setAmbient(const hesperia::data::environment::Point3 &a);

                /**
                 * This method returns the value for ambient.
                 *
                 * @return Value for ambient.
                 */
                const hesperia::data::environment::Point3 getAmbient() const;

                /**
                 * This method sets the value for diffuse.
                 *
                 * @param d Value for diffuse.
                 */
                void setDiffuse(const hesperia::data::environment::Point3 &d);

                /**
                 * This method returns the value for diffuse.
                 *
                 * @return Value for diffuse.
                 */
                const hesperia::data::environment::Point3 getDiffuse() const;

                /**
                 * This method sets the value for specular.
                 *
                 * @param s Value for specular.
                 */
                void setSpecular(const hesperia::data::environment::Point3 &s);

                /**
                 * This method returns the value for specular.
                 *
                 * @return Value for specular.
                 */
                const hesperia::data::environment::Point3 getSpecular() const;

                /**
                 * This method sets the texture handle.
                 *
                 * @param textureHandle Texture handle;
                 */
                void setTextureHandle(const int32_t &textureHandle);

                /**
                 * This method returns the texture handle to be used.
                 * If the handle is -1, no texture is found.
                 *
                 * @return Texture handle.
                 */
                int32_t getTextureHandle() const;

            private:
                string m_name;
                string m_textureName;
                int32_t m_textureHandle;
                double m_shininess;

                hesperia::data::environment::Point3 m_ambient;
                hesperia::data::environment::Point3 m_diffuse;
                hesperia::data::environment::Point3 m_specular;
        };

    }
} // hesperia::threeD

#endif /*HESPERIA_CORE_THREED_MATERIAL_H_*/
