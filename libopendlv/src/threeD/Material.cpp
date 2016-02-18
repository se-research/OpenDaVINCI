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

#include "opendlv/threeD/Material.h"

namespace hesperia {
    namespace threeD {

        using namespace hesperia::data::environment;

        Material::Material() :
                m_name("Undefined"),
                m_textureName(),
                m_textureHandle(-1),
                m_shininess(0),
                m_ambient(),
                m_diffuse(1, 1, 1),
                m_specular() {}

        Material::Material(const string &name) :
                m_name(name),
                m_textureName(),
                m_textureHandle(-1),
                m_shininess(0),
                m_ambient(),
                m_diffuse(1, 1, 1),
                m_specular() {}

        Material::Material(const Material &obj) :
                m_name(obj.m_name),
                m_textureName(obj.m_textureName),
                m_textureHandle(obj.m_textureHandle),
                m_shininess(obj.m_shininess),
                m_ambient(obj.m_ambient),
                m_diffuse(obj.m_diffuse),
                m_specular(obj.m_specular) {}

        Material::~Material() {}

        Material& Material::operator=(const Material &obj) {
            m_name = obj.m_name;
            m_textureName = obj.m_textureName;
            m_textureHandle = obj.m_textureHandle;
            m_shininess = obj.m_shininess;
            m_ambient = obj.m_ambient;
            m_diffuse = obj.m_diffuse;
            m_specular = obj.m_specular;

            return (*this);
        }

        const string Material::getName() const {
            return m_name;
        }

        void Material::setTextureName(const string &textureName) {
            m_textureName = textureName;
        }

        const string Material::getTextureName() const {
            return m_textureName;
        }

        void Material::setShininess(const double &s) {
            m_shininess = s;
        }

        double Material::getShininess() const {
            return m_shininess;
        }

        void Material::setAmbient(const Point3 &a) {
            m_ambient = a;
        }

        const Point3 Material::getAmbient() const {
            return m_ambient;
        }

        void Material::setDiffuse(const Point3 &d) {
            m_diffuse = d;
        }

        const Point3 Material::getDiffuse() const {
            return m_diffuse;
        }

        void Material::setSpecular(const Point3 &s) {
            m_specular = s;
        }

        const Point3 Material::getSpecular() const {
            return m_specular;
        }

        void Material::setTextureHandle(const int32_t &textureHandle) {
            m_textureHandle = textureHandle;
        }

        int32_t Material::getTextureHandle() const {
            return m_textureHandle;
        }

    }
} // hesperia::threeD
