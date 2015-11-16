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

#ifndef CORE_MODULESTATISTICSTESTSUITE_H_
#define CORE_MODULESTATISTICSTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <iostream>
#include <sstream>
#include <string>

#include "core/data/Container.h"
#include "GeneratedHeaders_CoreData.h"

using namespace std;
using namespace core::data;
using namespace coredata::dmcp;

class ModuleStatisticsTest : public CxxTest::TestSuite {
    public:
        void testSerializeDeserialize() {
            ModuleStatistic mod1;
            {
                ModuleDescriptor md;
                    md.setName("Module A");
                    md.setIdentifier("1");
                    md.setVersion("5");
                    md.setFrequency(2);

                RuntimeStatistic rs;
                    rs.setSliceConsumption(0.57);

                mod1.setModule(md);
                mod1.setRuntimeStatistic(rs);
            }

            ModuleStatistic mod2;
            {
                ModuleDescriptor md;
                    md.setName("Module B");
                    md.setIdentifier("2");
                    md.setVersion("7");
                    md.setFrequency(4);

                RuntimeStatistic rs;
                    rs.setSliceConsumption(0.34);

                mod2.setModule(md);
                mod2.setRuntimeStatistic(rs);
            }

            stringstream sstr;

            ModuleStatistics ms;
            ms.putTo_MapOfModuleStatistics("Module 1", mod1);
            ms.putTo_MapOfModuleStatistics("Module 2", mod2);

            Container c(ms);
            sstr << c;

            Container c2;
            sstr >> c2;

            TS_ASSERT(c2.getDataType() == ModuleStatistics::ID());

            // Unpack data:
            ModuleStatistics ms2 = c2.getData<ModuleStatistics>();

            TS_ASSERT(ms2.getValueForKey_MapOfModuleStatistics("Module 1").getModule().getName() == "Module A");
            TS_ASSERT(ms2.getValueForKey_MapOfModuleStatistics("Module 1").getModule().getIdentifier() == "1");
            TS_ASSERT(ms2.getValueForKey_MapOfModuleStatistics("Module 1").getModule().getVersion() == "5");
            TS_ASSERT_DELTA(ms2.getValueForKey_MapOfModuleStatistics("Module 1").getModule().getFrequency(), 2, 1e-2);
            TS_ASSERT_DELTA(ms2.getValueForKey_MapOfModuleStatistics("Module 1").getRuntimeStatistic().getSliceConsumption(), 0.57, 1e-2);

            TS_ASSERT(ms2.getValueForKey_MapOfModuleStatistics("Module 2").getModule().getName() == "Module B");
            TS_ASSERT(ms2.getValueForKey_MapOfModuleStatistics("Module 2").getModule().getIdentifier() == "2");
            TS_ASSERT(ms2.getValueForKey_MapOfModuleStatistics("Module 2").getModule().getVersion() == "7");
            TS_ASSERT_DELTA(ms2.getValueForKey_MapOfModuleStatistics("Module 2").getModule().getFrequency(), 4, 1e-2);
            TS_ASSERT_DELTA(ms2.getValueForKey_MapOfModuleStatistics("Module 2").getRuntimeStatistic().getSliceConsumption(), 0.34, 1e-2);
        }
};

#endif /*CORE_MODULESTATISTICSTESTSUITE_H_*/
