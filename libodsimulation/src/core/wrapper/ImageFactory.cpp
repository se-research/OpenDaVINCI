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

#include <cstdio>

#include "core/wrapper/DisposalService.h"
#include "hesperia/core/wrapper/HesperiaLibraries.h"
#include "hesperia/core/wrapper/ImageFactory.h"
#include "core/wrapper/Mutex.h"
#include "core/wrapper/MutexFactory.h"
#include "hesperia/core/wrapper/OpenCV/OpenCVImageFactory.h"

namespace core {
    namespace wrapper {

        // Initialization of the singleton instance.
        Mutex* ImageFactory::m_singletonMutex = MutexFactory::createMutex();
        ImageFactory* ImageFactory::m_singleton = NULL;

        ImageFactory::ImageFactory() {}

        ImageFactory::~ImageFactory() {
            ImageFactory::m_singleton = NULL;
        }

        ImageFactory& ImageFactory::getInstance() {
            ImageFactory::m_singletonMutex->lock();
            {
                if (ImageFactory::m_singleton == NULL) {
                    switch (USEIMAGINGLIBRARY) {
                    case OPENCV_LIBRARIES:
                        ImageFactory::m_singleton = new OpenCV::OpenCVImageFactory();
                        break;
                    }

                    // Add to disposal service.
                    DisposalService::getInstance().addDisposableForFinalRemoval((Disposable**)&ImageFactory::m_singleton);
                }
            }
            ImageFactory::m_singletonMutex->unlock();

            return *m_singleton;
        }

    }
} // core::wrapper
