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

#ifndef HESPERIA_CORE_DECORATOR_MODELS_OBJXARCHIVE_H_
#define HESPERIA_CORE_DECORATOR_MODELS_OBJXARCHIVE_H_

#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "hesperia/core/wrapper/Image.h"
#include "opendavinci/core/strings/StringComparator.h"

#include "hesperia/decorator/models/Material.h"
#include "hesperia/decorator/models/TriangleSet.h"

namespace hesperia {
    namespace decorator {
        namespace models {

            using namespace std;

            // Forward declaration to prevent circular dependencies.
            class OBJXArchiveFactory;

            /**
             * This class represents the contents of an SCNX archive.
             */
            class OPENDAVINCI_API OBJXArchive {
                private:
                    friend class OBJXArchiveFactory;

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    OBJXArchive(const OBJXArchive&);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    OBJXArchive& operator=(const OBJXArchive&);

                private:
                    /**
                     * Constructor.
                     */
                    OBJXArchive();

                public:
                    virtual ~OBJXArchive();

                    /**
                     * This method adds a new image for texturing the
                     * model by reading the MTL file.
                     *
                     * @param name Name of the image to be added.
                     * @param image Image to be added.
                     */
                    void addImage(const string &name, core::wrapper::Image *image);

                    /**
                     * This method returns a list of registered images.
                     *
                     * @return List of registered image names.
                     */
                    vector<string> getListOfImages() const;

                    /**
                     * This method sets the content of the obj-file for further
                     * processing.
                     *
                     * @param objContents Contents of the obj-file.
                     */
                    void setContentsOfObjFile(const string &objContents);

                    /**
                     * This method sets the content of the mtl-file for further
                     * processing.
                     *
                     * @param mtlContents Contents of the mtl-file.
                     */
                    void setContentsOfMtlFile(const string &mtlContents);

                    /**
                     * This method returns a reference to the contents of
                     * the obj-file.
                     *
                     * @return Reference to the contents of the obj-file.
                     */
                    const stringstream& getContentsOfObjFile() const;

                    /**
                     * This method returns a reference to the contents of
                     * the mtl-file.
                     *
                     * @return Reference to the contents of the mtl-file.
                     */
                    const stringstream& getContentsOfMtlFile() const;

                    /**
                     * This method returns the list of renderable TriangleSets.
                     *
                     * @return List of renderable triangle sets.
                     */
                    const vector<TriangleSet> getListOfTriangleSets();

                private:
                    map<string, core::wrapper::Image*, core::strings::StringComparator> m_mapOfImages;
                    map<string, Material, core::strings::StringComparator> m_mapOfMaterials;
                    stringstream m_objFile;
                    stringstream m_mtlFile;

                    /**
                     * This method creates the material's map.
                     */
                    void createMapOfMaterials();
            };

        }
    }
} // hesperia::decorator::models

#endif /*HESPERIA_CORE_DECORATOR_MODELS_OBJXARCHIVE_H_*/
