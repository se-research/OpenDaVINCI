/**
 * odplayer - Tool for playing back recorded data
 * Copyright (C) 2017 Christian Berger
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

#ifndef PLAYER2TESTSUITE_H_
#define PLAYER2TESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <fstream>
#include <iostream>

#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/data/TimeStamp.h>
#include <opendavinci/odcore/io/URL.h>
#include <opendavinci/odtools/player/Player2.h>

using namespace std;
using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::io;
using namespace odtools::player;

class PlayerModule2Test : public CxxTest::TestSuite {
    public:
        void testCorrectMonotonicTemporalOrder() {
            // Prepare record file.
            fstream fout("PlayerModule2Test.rec", ios::out | ios::binary | ios::trunc);

            // Write data with non-monotonic order.
            TimeStamp ts1(4, 5);
            TimeStamp ts2(2, 3);
            TimeStamp ts3(0, 1);
            TimeStamp ts4(1, 2);
            TimeStamp ts5(3, 4);

            Container c1(ts1);
            c1.setSampleTimeStamp(ts1);
            fout << c1;

            Container c2(ts2);
            c2.setSampleTimeStamp(ts2);
            fout << c2;

            Container c3(ts3);
            c3.setSampleTimeStamp(ts3);
            fout << c3;

            Container c4(ts4);
            c4.setSampleTimeStamp(ts4);
            fout << c4;

            Container c5(ts5);
            c5.setSampleTimeStamp(ts5);
            fout << c5;

            fout.flush();
            fout.close();

            const URL u("file://PlayerModule2Test.rec");

            // Create Player2 instance.
            Player2 p2(u);

            // Check whether Player stores the entries in correct time order.
            int64_t counter = 0;
            while (p2.hasMoreData()) {
                Container c = p2.getNextContainerToBeSent();
                TS_ASSERT((counter * 1000 * 1000 + (counter + 1)) == c.getSampleTimeStamp().toMicroseconds());
                counter++;
            }

            UNLINK("PlayerModuleTest2.rec");
        }

};

#endif /*PLAYER2TESTSUITE_H_*/
