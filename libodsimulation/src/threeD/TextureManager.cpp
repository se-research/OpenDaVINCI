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
#include <GL/glu.h>

// Under Win32, GL_BGR is missing.
#ifdef WIN32
#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif
#endif

#include <iostream>
#include <map>
#include <string>

#include "core/opendavinci.h"
#include "core/base/Lock.h"
#include "core/base/Mutex.h"
#include "core/strings/StringComparator.h"
#include "hesperia/threeD/TextureManager.h"

namespace core { namespace wrapper { class Image; } }

namespace hesperia {
    namespace threeD {

        using namespace std;
        using namespace core::base;

        // Initialize singleton instance.
        Mutex TextureManager::m_singletonMutex;
        TextureManager* TextureManager::m_singleton = NULL;

        TextureManager::TextureManager() :
                m_mapOfTextureHandles() {}

        TextureManager::~TextureManager() {}

        TextureManager& TextureManager::getInstance() {
            {
                Lock l(TextureManager::m_singletonMutex);
                if (TextureManager::m_singleton == NULL) {
                    TextureManager::m_singleton = new TextureManager();
                }
            }

            return (*TextureManager::m_singleton);
        }

        void TextureManager::removeTexture(const string &name) {
            map<string, uint32_t, core::strings::StringComparator>::iterator it = m_mapOfTextureHandles.find(name);
            if (it != m_mapOfTextureHandles.end()) {
                // TODO: glDeleteTextures(1, it->second); fails...
                m_mapOfTextureHandles.erase(it);
                clog << "Removed texture " << name << "." << endl;
            }
        }

        int32_t TextureManager::getTexture(const string &name) const {
            int32_t textureHandle = -1;

            map<string, uint32_t, core::strings::StringComparator>::const_iterator it = m_mapOfTextureHandles.find(name);
            if (it != m_mapOfTextureHandles.end()) {
                textureHandle = static_cast<int>(it->second);
            }

            return textureHandle;
        }

        bool TextureManager::hasTexture(const string &name) const {
            bool retVal = false;

            map<string, uint32_t, core::strings::StringComparator>::const_iterator it = m_mapOfTextureHandles.find(name);
            retVal = (it != m_mapOfTextureHandles.end());

            return retVal;
        }

        bool TextureManager::addImage(const string &name, const core::wrapper::Image *image) {
            bool retVal = false;

            if ( (name.length() != 0) && ( (image != NULL) && (image->getHeight() > 0) && (image->getWidth() > 0) && (image->getWidthStep() > 0) ) ) {
                // Check if a texture was previously registered for this name.
                if (m_mapOfTextureHandles.find(name) == m_mapOfTextureHandles.end()) {
                    // No texture registered, thus register the give image.
                    uint32_t identifier = 0;

                    glGenTextures(1, &identifier);
                    glBindTexture(GL_TEXTURE_2D, identifier);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

                    // Set up byte order.
                    GLenum format = GL_RGB;
                    uint32_t numberOfColorComponents = 0;
                    switch (image->getFormat()) {
                    case core::wrapper::Image::BGR_24BIT:
                        format = GL_BGR;
                        numberOfColorComponents = 3;
                        break;
                    case core::wrapper::Image::RGB_24BIT:
                        format = GL_RGB;
                        numberOfColorComponents = 3;
                        break;
                    case core::wrapper::Image::INVALID:
                        format = 0;
                    }

                    if (format != 0) {

                        // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
                        // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
                        glTexImage2D(GL_TEXTURE_2D, 0, numberOfColorComponents, image->getWidth(), image->getHeight(), 0, format, GL_UNSIGNED_BYTE, image->getRawData());
                        gluBuild2DMipmaps(GL_TEXTURE_2D, numberOfColorComponents, image->getWidth(), image->getHeight(), format, GL_UNSIGNED_BYTE, image->getRawData());

                        // Register texture using the given name.
                        m_mapOfTextureHandles[name] = identifier;

                        retVal = true;
                    } else {
                        retVal = false;
                    }
                }
            }

            return retVal;
        }

    }
} // hesperia::threeD
