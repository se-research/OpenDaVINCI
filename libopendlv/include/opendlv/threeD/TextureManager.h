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

#ifndef HESPERIA_CORE_THREED_TEXTUREMANAGER_H_
#define HESPERIA_CORE_THREED_TEXTUREMANAGER_H_

#include <map>
#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/base/Mutex.h"
#include "opendlv/core/wrapper/Image.h"
#include "opendavinci/core/strings/StringComparator.h"

namespace opendlv {
    namespace threeD {

        using namespace std;

        /**
         * This class manages all textures for an OpenGL scene.
         */
        class OPENDAVINCI_API TextureManager {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                TextureManager(const TextureManager &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                TextureManager& operator=(const TextureManager &);

            private:
                TextureManager();

            public:
                virtual ~TextureManager();

                /**
                 * This method returns a static instance for this factory.
                 *
                 * @return Instance of this factory.
                 */
                static TextureManager& getInstance();

                /**
                 * This method adds a new image to be used as a texture.
                 * Furthermore, mipmaps are generated automatically.
                 *
                 * @param name Unique name for this image to be added.
                 * @param image Image to be added.
                 * @return true, if the image could be added.
                 */
                bool addImage(const string &name, const core::wrapper::Image *image);

                /**
                 * This method returns the texture handle for the given
                 * name or -1 if the no texture is registered for this name.
                 *
                 * @param name Name of the texture to be found.
                 * @return Texture handle if found or -1.
                 */
                int32_t getTexture(const string &name) const;

                /**
                 * This method checks if the TextureManager has loaded
                 * the texture named "name".
                 *
                 * @param name Name of the texture.
                 * @return true, if the TextureManager has loaded the texture.
                 */
                bool hasTexture(const string &name) const;

                /**
                 * This method removes the texture "name".
                 *
                 * @param name Name of the texture to be removed.
                 */
                void removeTexture(const string &name);

            private:
                static core::base::Mutex m_singletonMutex;
                static TextureManager* m_singleton;
                map<string, uint32_t, core::strings::StringComparator> m_mapOfTextureHandles;
        };

    }
} // opendlv::threeD

#endif /*HESPERIA_CORE_THREED_TEXTUREMANAGER_H_*/
