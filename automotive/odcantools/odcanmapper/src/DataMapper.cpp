/**
 * DataMapper - Tool for mapping GenericCANMessages to
 *              high-level C++ data structures and vice-versa
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

#include <iostream>

#include <core/SharedPointer.h>
#include <core/reflection/Message.h>
#include <core/reflection/MessageToVisitableVisitor.h>
#include <core/reflection/MessagePrettyPrinterVisitor.h>

#include "GeneratedHeaders_AutomotiveData.h"

#include "DataMapper.h"

namespace automotive {

    using namespace std;
    using namespace core;
    using namespace core::base;
    using namespace core::data;
    using namespace core::reflection;
    using namespace coredata::reflection;

    DataMapper::DataMapper() {}

    DataMapper::~DataMapper() {}

    void DataMapper::printPayload(uint64_t payload) const {
        const uint16_t LENGTH = 8;
        uint8_t val[LENGTH];
        for (uint8_t i = 0; i < LENGTH; i++) {
            val[i] = (payload & 0xFF);
            payload = payload >> 8;
        }
        cout << "Payload: " << hex << (int)val[0] << " "
                            << hex << (int)val[1] << " "
                            << hex << (int)val[2] << " "
                            << hex << (int)val[3] << " "
                            << hex << (int)val[4] << " "
                            << hex << (int)val[5] << " "
                            << hex << (int)val[6] << " "
                            << hex << (int)val[7] << endl;
    }

    // This methods would have to be auto-generated!
    core::data::Container DataMapper::decodeWheelSpeed(const GenericCANMessage &gcm) {
        Container c;

        // 2. If the identifier is matching, get the raw payload.
        uint64_t data = gcm.getData();

        // Optionally: print payload for debug purposes.
        // printPayload(data);

        // 3. Map uin64_t value to 8 byte char array.
        string value((char*)(&data), 8);
        stringstream sstr(value);

        // 4. Create a generic message.
        Message message;

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
                Field<float> *f = new Field<float>(v);
                f->setLongIdentifier(1); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setShortIdentifier(1); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setLongName("WheelSpeed.frontLeft");
                f->setShortName("frontLeft");
                f->setFieldDataType(coredata::reflection::AbstractField::FLOAT_T);
                f->setSize(sizeof(v));

                // 5.5 Add created field to generic message.
                message.addField(SharedPointer<AbstractField>(f));
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
                Field<float> *f = new Field<float>(v);
                f->setLongIdentifier(2); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setShortIdentifier(2); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setLongName("WheelSpeed.frontRight");
                f->setShortName("frontRight");
                f->setFieldDataType(coredata::reflection::AbstractField::FLOAT_T);
                f->setSize(sizeof(v));

                // 5.5 Add created field to generic message.
                message.addField(SharedPointer<AbstractField>(f));
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
                Field<float> *f = new Field<float>(v);
                f->setLongIdentifier(3); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setShortIdentifier(3); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setLongName("WheelSpeed.rearLeft");
                f->setShortName("rearLeft");
                f->setFieldDataType(coredata::reflection::AbstractField::FLOAT_T);
                f->setSize(sizeof(v));

                // 5.5 Add created field to generic message.
                message.addField(SharedPointer<AbstractField>(f));
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
                Field<float> *f = new Field<float>(v);
                f->setLongIdentifier(4); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setShortIdentifier(4); // The identifiers specified here must match with the ones defined in the .odvd file!
                f->setLongName("WheelSpeed.rearRight");
                f->setShortName("rearRight");
                f->setFieldDataType(coredata::reflection::AbstractField::FLOAT_T);
                f->setSize(sizeof(v));

                // 5.5 Add created field to generic message.
                message.addField(SharedPointer<AbstractField>(f));
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
            MessageToVisitableVisitor mtvv(message);

            // 8. Create an instance of the named high-level message.
            automotive::vehicle::WheelSpeed wheelSpeed;

            // 9. Letting the high-level message accept the visitor to enter the values.
            wheelSpeed.accept(mtvv);

            {
                // Optional: Showing how to use the MessagePrettyPrinterVisitor to print the content of the unnamed message.
                MessagePrettyPrinterVisitor mppv;
                message.accept(mppv);
                mppv.getOutput(cout);

                // Optional: Just print the content for convenience purposes.
                cout << wheelSpeed.toString() << endl;
            }

            // 10. Create the resulting container carrying a valid payload.
            c = Container(Container::WHEELSPEED, wheelSpeed);
        }

        return c;
    }

    Container DataMapper::mapNext(const GenericCANMessage &gcm) {
        Container c;

        // Here, we are invoked after receiving the CAN message.
        cout << "Received GenericCANMessage" <<
                                  " sent at " << c.getSentTimeStamp().getYYYYMMDD_HHMMSSms() <<
                              " received at " << c.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms() <<
                ", " << gcm.toString() << endl;

        // Next, we need a state machine to
        // a) sort/allocate the received CAN message to a (sub-)state machine to compose a high-level C++ message (defined in .odvd).
        // b) run the (sub-)state machine a compose an "unnamed" Message, which will be traversed into the "named" high-level C++ message.
        // If the high-level C++ message is not available (yet), this method returns an uninitialized Container (i.e. Container::UNDEFINEDDATA).

        // Example for decoding a low-level CAN message into a high-level automotive::vehicle::WheelSpeed instance:
        // Do the (pre-)sorting based on the low-level CAN message identifier. This should be generated based on a DSL!
        if (gcm.getIdentifier() == 0x123) {
            c = decodeWheelSpeed(gcm);
        }

        // Return the created Container (which can be either Container::UNDEFINED_DATA or a valid one).
        return c;
    }

} // automotive
