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
#include "core/wrapper/HesperiaLibraries.h"
#include "core/wrapper/MatrixFactory.h"
#include "core/wrapper/Mutex.h"
#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/OpenCV/OpenCVMatrixFactory.h"

namespace core {
    namespace wrapper {

        // Initialization of the singleton instance.
        Mutex* MatrixFactory::m_singletonMutex = MutexFactory::createMutex();
        MatrixFactory* MatrixFactory::m_singleton = NULL;

        MatrixFactory::MatrixFactory() {}

        MatrixFactory::~MatrixFactory() {
            MatrixFactory::m_singleton = NULL;
        }

        MatrixFactory& MatrixFactory::getInstance() {
            MatrixFactory::m_singletonMutex->lock();
            {
                if (MatrixFactory::m_singleton == NULL) {
                    switch (USEMATRIXLIBRARY) {
                    case MATRIX_OPENCV_LIBRARIES:
                        MatrixFactory::m_singleton = new OpenCV::OpenCVMatrixFactory();
                        break;
                    }

                    // Add to disposal service.
                    DisposalService::getInstance().addDisposableForFinalRemoval((Disposable**)&MatrixFactory::m_singleton);
                }
            }
            MatrixFactory::m_singletonMutex->unlock();

            return *m_singleton;
        }

    }
} // core::wrapper
