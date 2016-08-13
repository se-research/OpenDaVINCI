/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

#include <iostream>
#include <test7/GeneratedHeaders_Test7.h>
#include <test7/GeneratedHeaders_Test7_Helper.h>
#include <opendavinci/odcore/base/Visitable.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
void GeneratedHeaders_Test7_Helper::delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    successfullyDelegated = false;
    if (c.getDataType() == testpackage::Test7A::ID()) {
        testpackage::Test7A payload = c.getData<testpackage::Test7A>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == testpackage::Test7B::ID()) {
        testpackage::Test7B payload = c.getData<testpackage::Test7B>();
        payload.accept(v);
        successfullyDelegated = true;
    }
}
odcore::reflection::Message GeneratedHeaders_Test7_Helper::map(odcore::data::Container &c, bool &successfullyMapped) {
    successfullyMapped = false;
    odcore::reflection::Message msg;
    odcore::reflection::MessageFromVisitableVisitor mfvv;
    delegateVistor(c, mfvv, successfullyMapped);
    if (successfullyMapped) {
        msg = mfvv.getMessage();
    }
    return msg;
}
