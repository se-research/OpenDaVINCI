/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */
// Source file for: WheelSpeed

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

