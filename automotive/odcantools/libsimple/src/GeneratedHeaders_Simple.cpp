/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

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

