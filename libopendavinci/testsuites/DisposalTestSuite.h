/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CORE_DISPOSALTESTSUITE_H_
#define CORE_DISPOSALTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include "core/base/Thread.h"
#include "core/wrapper/Disposable.h"
#include "core/wrapper/DisposalService.h"

using namespace std;

class DisposalTestTrash : public core::wrapper::Disposable {
    public:
        DisposalTestTrash() :
            data(42) {};

        int32_t data;
};

class DisposalTest : public CxxTest::TestSuite {
    public:
        void testDisposal() {
            DisposalTestTrash *trash1regular = new DisposalTestTrash();
            trash1regular->data = 13;
            DisposalTestTrash *trash2final = new DisposalTestTrash();
            trash2final->data = 14;

            TS_ASSERT(trash1regular != NULL);
            TS_ASSERT(trash1regular->data == 13);
            TS_ASSERT(trash2final != NULL);
            TS_ASSERT(trash2final->data == 14);
            TS_ASSERT(trash1regular != trash2final);

            {
                core::wrapper::DisposalService::getInstance().addDisposableForRegularRemoval((core::wrapper::Disposable**)&trash1regular);
                core::wrapper::DisposalService::getInstance().addDisposableForFinalRemoval((core::wrapper::Disposable**)&trash2final);
                core::base::Thread::usleepFor(2 * 1000 * 1000);

                core::wrapper::DisposalService &ds1 = core::wrapper::DisposalService::getInstance();
                core::wrapper::DisposalService *ds2 = &ds1;
                delete ds2;
            }

            // Allow for some thread yielding so that the DisposalService can release the memory.
            core::base::Thread::usleepFor(2 * 1000 * 1000);

            // DisposableService must contain a list of pointer to pointers!
            TS_ASSERT(trash1regular == NULL);
            TS_ASSERT(trash2final == NULL);
        }
};

#endif /*CORE_DISPOSALTESTSUITE_H_*/
