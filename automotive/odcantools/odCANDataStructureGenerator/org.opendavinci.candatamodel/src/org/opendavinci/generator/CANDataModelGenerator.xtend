/**
 * CANDataStructureGenerator - IDL tool to describe the mapping from
 *                             CAN data to high-level messages.
 * Copyright (C) 2015 Christian Berger
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

package org.opendavinci.generator

import org.eclipse.emf.ecore.resource.Resource
import org.eclipse.xtext.generator.IGenerator
import org.eclipse.xtext.generator.IFileSystemAccess
import org.opendavinci.canDataModel.CANSignalMapping

class CANDataModelGenerator implements IGenerator {
	
    /* This method is our interface to an outside caller. */
	override void doGenerate(Resource resource, IFileSystemAccess fsa) {
		val generatedHeadersFile = resource.URI.toString().substring(resource.URI.toString().lastIndexOf("/") + 1).replaceAll(".odvd", "")
		for (e : resource.allContents.toIterable.filter(typeof(CANSignalMapping))) {
			fsa.generateFile("include/GeneratedHeaders_" + generatedHeadersFile + ".h", generateSuperHeaderFileContent(generatedHeadersFile, e))
			fsa.generateFile("src/GeneratedHeaders_" + generatedHeadersFile + ".cpp", generateSuperImplementationFileContent(generatedHeadersFile, e))
			fsa.generateFile("include/generated/" + e.message.toString().replaceAll("\\.", "/") + ".h", generateHeaderFileContent(generatedHeadersFile, e))
			fsa.generateFile("src/generated/" + e.message.toString().replaceAll("\\.", "/") + ".cpp", generateImplementationFileContent(e, "generated"))
			fsa.generateFile("testsuites/" + e.message.toString().replaceAll("\\.", "_") + "TestSuite.h", generateTestSuiteContent(generatedHeadersFile, e))
			fsa.generateFile("uppaal/generated/" + e.message.toString().replaceAll("\\.", "/"), generateUPPAALFileContent(e))
		}
	}

    /* This method generates the header file content. */
	def generateSuperHeaderFileContent(String generatedHeadersFile, CANSignalMapping mapping) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Header file for: «mapping.message.toString»

#ifndef GENERATEDHEADERS_«generatedHeadersFile.toUpperCase()»_H_
#define GENERATEDHEADERS_«generatedHeadersFile.toUpperCase()»_H_

#include <vector>

#include "generated/WheelSpeed.h"

#include <core/data/Container.h>

#include "GeneratedHeaders_AutomotiveData.h"

namespace simple {

    using namespace std;

    class Simple {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Simple(const Simple &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Simple& operator=(const Simple &/*obj*/);

        public:
            Simple();

            virtual ~Simple();

            /**
             * This method adds the given GenericCANMessage to the internal
             * CAN message decoder. If this message could be decoded (or
             * including the previous sequence, this method returns a valid
             * Container (ie. Container::UNDEFINEDDATA).
             *
             * @param gcm Next GenericCANMessage.
             * @return Container, where the type needs to be checked to determine invalidity (i.e. !Container::UNDEFINEDDATA).
             */
            vector<core::data::Container> mapNext(const automotive::GenericCANMessage &gcm);

        private:
            WheelSpeed m_wheelSpeed;
    };

} // simple

#endif /*GENERATEDHEADERS_«generatedHeadersFile.toUpperCase()»_H_*/
'''

    /* This method generates the header file content. */
	def generateSuperImplementationFileContent(String generatedHeadersFile, CANSignalMapping mapping) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Header file for: «mapping.message.toString»

#include "generated/WheelSpeed.h"

#include "GeneratedHeaders_Simple.h"

namespace simple {

    Simple::Simple() :
        m_wheelSpeed() {}

    Simple::~Simple() {}

    vector<core::data::Container> Simple::mapNext(const automotive::GenericCANMessage &gcm) {
        vector<core::data::Container> listOfContainers;

        // Traverse all defined mappings and check whether a new high-level message could be fully decoded.
        {
            core::data::Container container = m_wheelSpeed.decode(gcm);
            if (container.getDataType() != core::data::Container::UNDEFINEDDATA) {
                listOfContainers.push_back(container);
            }
        }

        // Add the next mapping like:
//        {
//            core::data::Container container = m_message2.decode(gcm);
//            if (container.getDataType() != core::data::Container::UNDEFINEDDATA) {
//                listOfContainers.push_back(container);
//            }
//        }

        return listOfContainers;
    }

} // simple
'''

    /* This method generates the header file content. */
	def generateHeaderFileContent(String generatedHeadersFile, CANSignalMapping mapping) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Header file for: «mapping.message.toString»
#ifndef WHEELSPEED_H_
#define WHEELSPEED_H_

#include "generated/WheelSpeed.h"

#include <core/data/Container.h>

#include "GeneratedHeaders_AutomotiveData.h"

namespace simple {

    using namespace std;

    class WheelSpeed {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            WheelSpeed(const WheelSpeed &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            WheelSpeed& operator=(const WheelSpeed &/*obj*/);

        public:
            WheelSpeed();

            virtual ~WheelSpeed();

            core::data::Container decode(const automotive::GenericCANMessage &gcm);
    };

} // simple

#endif /*WHEELSPEED_H_*/
'''

	/* This method generates the implementation (.cpp). */
	def generateImplementationFileContent(CANSignalMapping mapping, String includeDirectoryPrefix) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Source file for: «mapping.message.toString»

#include "generated/WheelSpeed.h"

#include <core/SharedPointer.h>
#include <core/reflection/Message.h>
#include <core/reflection/MessageToVisitableVisitor.h>
#include <core/reflection/MessagePrettyPrinterVisitor.h>

#include "GeneratedHeaders_AutomotiveData.h"

namespace simple {

    using namespace std;

    WheelSpeed::WheelSpeed() {}

    WheelSpeed::~WheelSpeed() {}

    core::data::Container WheelSpeed::decode(const automotive::GenericCANMessage &gcm) {
        core::data::Container c;

        // TODO: Check the CAN ID and perform the CAN signal mapping before to process the rest of this method.
        if (gcm.getIdentifier() != 0x123) {
            return c;
        }

        // 2. If the identifier is matching, get the raw payload.
        uint64_t data = gcm.getData();

        // Optionally: print payload for debug purposes.
        // printPayload(data);

        // 3. Map uin64_t value to 8 byte char array.
        string value((char*)(&data), 8);
        stringstream sstr(value);

        // 4. Create a generic message.
        core::reflection::Message message;

        // 5. Decode all contained attributes as defined in this CAN message specification.
        {
            {
                // 5.1 Get raw value from 1st attribute.
                uint16_t _wheel1 = 0;
                sstr.read((char*)&_wheel1, sizeof(uint16_t));

                // 5.2 Optional: Fix endianness depending on CAN message specification.
                _wheel1 = ntohs(_wheel1);

                // 5.3 Apply value transformation (i.e. formula) to map raw value to (physically) meaningful value according to CAN message specification.
                const float SCALE = 0.01;
                float v = _wheel1 * SCALE;

                // 5.4 Create a field for a generic message.
                core::reflection::Field<float> *f = new core::reflection::Field<float>(v);
                f->setLongIdentifier(1); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setShortIdentifier(1); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setLongName("WheelSpeed.frontLeft");
                f->setShortName("frontLeft");
                f->setFieldDataType(coredata::reflection::AbstractField::FLOAT_T);
                f->setSize(sizeof(v));

                // 5.5 Add created field to generic message.
                message.addField(core::SharedPointer<coredata::reflection::AbstractField>(f));
            }

            // Continue decoding values depending on CAN message specification.
            {
                // 5.1 Get raw value from 2nd attribute.
                uint16_t _wheel2 = 0;
                sstr.read((char*)&_wheel2, sizeof(uint16_t));

                // 5.2 Optional: Fix endianness depending on CAN message specification.
                _wheel2 = ntohs(_wheel2);

                // 5.3 Apply value transformation (i.e. formula) to map raw value to (physically) meaningful value according to CAN message specification.
                const float SCALE = 0.01;
                float v = _wheel2 * SCALE;

                // 5.4 Create a field for a generic message.
                core::reflection::Field<float> *f = new core::reflection::Field<float>(v);
                f->setLongIdentifier(2); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setShortIdentifier(2); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setLongName("WheelSpeed.frontRight");
                f->setShortName("frontRight");
                f->setFieldDataType(coredata::reflection::AbstractField::FLOAT_T);
                f->setSize(sizeof(v));

                // 5.5 Add created field to generic message.
                message.addField(core::SharedPointer<coredata::reflection::AbstractField>(f));
            }

            // Continue decoding values depending on CAN message specification.
            {
                // 5.1 Get raw value from 3rd attribute.
                uint16_t _wheel3 = 0;
                sstr.read((char*)&_wheel3, sizeof(uint16_t));

                // 5.2 Optional: Fix endianness depending on CAN message specification.
                _wheel3 = ntohs(_wheel3);

                // 5.3 Apply value transformation (i.e. formula) to map raw value to (physically) meaningful value according to CAN message specification.
                const float SCALE = 0.01;
                float v = _wheel3 * SCALE;

                // 5.4 Create a field for a generic message.
                core::reflection::Field<float> *f = new core::reflection::Field<float>(v);
                f->setLongIdentifier(3); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setShortIdentifier(3); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setLongName("WheelSpeed.rearLeft");
                f->setShortName("rearLeft");
                f->setFieldDataType(coredata::reflection::AbstractField::FLOAT_T);
                f->setSize(sizeof(v));

                // 5.5 Add created field to generic message.
                message.addField(core::SharedPointer<coredata::reflection::AbstractField>(f));
            }

            // Continue decoding values depending on CAN message specification.
            {
                // 5.1 Get raw value from 4th attribute.
                uint16_t _wheel4 = 0;
                sstr.read((char*)&_wheel4, sizeof(uint16_t));

                // 5.2 Optional: Fix endianness depending on CAN message specification.
                _wheel4 = ntohs(_wheel4);

                // 5.3 Apply value transformation (i.e. formula) to map raw value to (physically) meaningful value according to CAN message specification.
                const float SCALE = 0.01;
                float v = _wheel4 * SCALE;

                // 5.4 Create a field for a generic message.
                core::reflection::Field<float> *f = new core::reflection::Field<float>(v);
                f->setLongIdentifier(4); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setShortIdentifier(4); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setLongName("WheelSpeed.rearRight");
                f->setShortName("rearRight");
                f->setFieldDataType(coredata::reflection::AbstractField::FLOAT_T);
                f->setSize(sizeof(v));

                // 5.5 Add created field to generic message.
                message.addField(core::SharedPointer<coredata::reflection::AbstractField>(f));
            }
        }

        // 6. Depending on the CAN message specification, we are either ready here
        // (i.e. mapping one CAN message to one high-level C++ message), or we have
        // to wait for more low-level CAN messages to complete this high-level C++ message.
        // Thus, our state machine would have to store this (incomplete) "message"
        // variable internally to continue decoding later.

        {
            // 7. As we are ready here for the given example, we create a visitor to
            // traverse the unnamed message and create a named message (i.e. an instance
            // of a high-level C++ message) to be distributed as a Container.
            core::reflection::MessageToVisitableVisitor mtvv(message);

            // 8. Create an instance of the named high-level message.
            automotive::vehicle::WheelSpeed wheelSpeed;

            // 9. Letting the high-level message accept the visitor to enter the values.
            wheelSpeed.accept(mtvv);

            {
                // Optional: Showing how to use the MessagePrettyPrinterVisitor to print the content of the unnamed message.
                core::reflection::MessagePrettyPrinterVisitor mppv;
                message.accept(mppv);
                mppv.getOutput(cout);

                // Optional: Just print the content for convenience purposes.
                cout << wheelSpeed.toString() << endl;
            }

            // 10. Create the resulting container carrying a valid payload.
            c = core::data::Container(core::data::Container::WHEELSPEED, wheelSpeed);
        }

        return c;
    }

} // simple
'''

	// Generate the test suite content (.h).	
	def generateTestSuiteContent(String generatedHeadersFile, CANSignalMapping mapping) '''
/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Test suite file for: «mapping.message.toString»
'''

    /* This method generates the UPPAAL file content. */
	def generateUPPAALFileContent(CANSignalMapping mapping) '''
<!--
This software is open source. Please see COPYING and AUTHORS for further information.

This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
-->
<!-- UPPAAL file for: «mapping.message.toString» -->
'''
}
