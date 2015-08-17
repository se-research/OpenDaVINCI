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

#ifndef HESPERIA_CORE_THREED_NODERENDERINGCONFIGURATION_H_
#define HESPERIA_CORE_THREED_NODERENDERINGCONFIGURATION_H_

#include <stdint.h>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

namespace hesperia {
    namespace threeD {

        using namespace std;

        /**
         * This class configures several options for the rendering method.
         */
        class OPENDAVINCI_API NodeRenderingConfiguration {
            public:
                // Rendering parameters (must be power of two numbers since it's set using |'s).
                enum RENDERING_PARAMETERS {
                    ENABLED = 1,
                    //NEXT_PARAMETER = 2,
                    //FURTHER_PARAMETERS = 4, ...
                };

            public:
                NodeRenderingConfiguration();

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                NodeRenderingConfiguration(const NodeRenderingConfiguration &obj);

                virtual ~NodeRenderingConfiguration();

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                NodeRenderingConfiguration& operator=(const NodeRenderingConfiguration &obj);

                /**
                 * This method returns true if the selected parameter is set.
                 *
                 * @param p Parameter to check.
                 * @return True if the selected parameter is s.
                 */
                bool hasParameter(const enum RENDERING_PARAMETERS &p) const;

                /**
                 * This method sets a rendering parameter.
                 *
                 * @param p Parameter to set.
                 * @param enabled True if p is set.
                 */
                void setParameter(const enum RENDERING_PARAMETERS &p, const bool &enabled);

            private:
                uint32_t m_parameters;
        };

    }
} // hesperia::threeD

#endif /*HESPERIA_CORE_THREED_NODERENDERINGCONFIGURATION_H_*/
