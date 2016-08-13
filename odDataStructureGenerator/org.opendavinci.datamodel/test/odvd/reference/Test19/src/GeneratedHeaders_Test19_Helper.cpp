/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

#include <iostream>
#include <test19/GeneratedHeaders_Test19.h>
#include <test19/GeneratedHeaders_Test19_Helper.h>
#include <opendavinci/odcore/base/Visitable.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
extern "C" {
    odcore::reflection::Helper *newHelper() {
        return new GeneratedHeaders_Test19_Helper;
    }
    void deleteHelper(odcore::reflection::Helper *h) {
        delete h;
    }
}
GeneratedHeaders_Test19_Helper::~GeneratedHeaders_Test19_Helper() {}
void GeneratedHeaders_Test19_Helper::delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    GeneratedHeaders_Test19_Helper::__delegateVistor(c, v, successfullyDelegated);
}
odcore::reflection::Message GeneratedHeaders_Test19_Helper::map(odcore::data::Container &c, bool &successfullyMapped) {
    return GeneratedHeaders_Test19_Helper::__map(c, successfullyMapped);
}
void GeneratedHeaders_Test19_Helper::__delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    successfullyDelegated = false;
    if (c.getDataType() == Test19a::ID()) {
        Test19a payload = c.getData<Test19a>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test19b::ID()) {
        Test19b payload = c.getData<Test19b>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test19c::ID()) {
        Test19c payload = c.getData<Test19c>();
        payload.accept(v);
        successfullyDelegated = true;
    }
}
odcore::reflection::Message GeneratedHeaders_Test19_Helper::__map(odcore::data::Container &c, bool &successfullyMapped) {
    successfullyMapped = false;
    odcore::reflection::Message msg;
    odcore::reflection::MessageFromVisitableVisitor mfvv;
    __delegateVistor(c, mfvv, successfullyMapped);
    if (successfullyMapped) {
        msg = mfvv.getMessage();
    }
    return msg;
}
