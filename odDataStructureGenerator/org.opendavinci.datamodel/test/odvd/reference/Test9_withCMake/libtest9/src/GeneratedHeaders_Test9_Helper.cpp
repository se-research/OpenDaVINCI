/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

#include <iostream>
#include <test9/GeneratedHeaders_Test9.h>
#include <test9/GeneratedHeaders_Test9_Helper.h>
#include <opendavinci/odcore/base/Visitable.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
extern "C" {
    odcore::reflection::Helper *newHelper() {
        return new GeneratedHeaders_Test9_Helper;
    }
    void deleteHelper(odcore::reflection::Helper *h) {
        delete h;
    }
}
GeneratedHeaders_Test9_Helper::~GeneratedHeaders_Test9_Helper() {}
void GeneratedHeaders_Test9_Helper::delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    GeneratedHeaders_Test9_Helper::__delegateVistor(c, v, successfullyDelegated);
}
odcore::reflection::Message GeneratedHeaders_Test9_Helper::map(odcore::data::Container &c, bool &successfullyMapped) {
    return GeneratedHeaders_Test9_Helper::__map(c, successfullyMapped);
}
void GeneratedHeaders_Test9_Helper::__delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    successfullyDelegated = false;
    if (c.getDataType() == Test9A::ID()) {
        Test9A payload = c.getData<Test9A>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test9B::ID()) {
        Test9B payload = c.getData<Test9B>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == subpackage::Test9C::ID()) {
        subpackage::Test9C payload = c.getData<subpackage::Test9C>();
        payload.accept(v);
        successfullyDelegated = true;
    }
}
odcore::reflection::Message GeneratedHeaders_Test9_Helper::__map(odcore::data::Container &c, bool &successfullyMapped) {
    successfullyMapped = false;
    odcore::reflection::Message msg;
    odcore::reflection::MessageFromVisitableVisitor mfvv;
    __delegateVistor(c, mfvv, successfullyMapped);
    if (successfullyMapped) {
        msg = mfvv.getMessage();
    }
    return msg;
}
