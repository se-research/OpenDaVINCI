/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

#include <iostream>
#include <test18/GeneratedHeaders_Test18.h>
#include <test18/GeneratedHeaders_Test18_Helper.h>
#include <opendavinci/odcore/base/Visitable.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
extern "C" {
    odcore::reflection::Helper *newHelper() {
        return new GeneratedHeaders_Test18_Helper;
    }
    void deleteHelper(odcore::reflection::Helper *h) {
        delete h;
    }
}
GeneratedHeaders_Test18_Helper::~GeneratedHeaders_Test18_Helper() {}
void GeneratedHeaders_Test18_Helper::delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    GeneratedHeaders_Test18_Helper::__delegateVistor(c, v, successfullyDelegated);
}
odcore::reflection::Message GeneratedHeaders_Test18_Helper::map(odcore::data::Container &c, bool &successfullyMapped) {
    return GeneratedHeaders_Test18_Helper::__map(c, successfullyMapped);
}
void GeneratedHeaders_Test18_Helper::__delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    successfullyDelegated = false;
    if (c.getDataType() == Test18::ID()) {
        Test18 payload = c.getData<Test18>();
        payload.accept(v);
        successfullyDelegated = true;
    }
}
odcore::reflection::Message GeneratedHeaders_Test18_Helper::__map(odcore::data::Container &c, bool &successfullyMapped) {
    successfullyMapped = false;
    odcore::reflection::Message msg;
    odcore::reflection::MessageFromVisitableVisitor mfvv;
    __delegateVistor(c, mfvv, successfullyMapped);
    if (successfullyMapped) {
        msg = mfvv.getMessage();
    }
    return msg;
}
