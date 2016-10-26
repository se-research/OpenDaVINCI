/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

#include <iostream>
#include <test3/GeneratedHeaders_Test3.h>
#include <test3/GeneratedHeaders_Test3_Helper.h>
#include <opendavinci/odcore/base/Visitable.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
extern "C" {
    odcore::reflection::Helper *newHelper() {
        return new GeneratedHeaders_Test3_Helper;
    }
    void deleteHelper(odcore::reflection::Helper *h) {
        delete h;
    }
}
GeneratedHeaders_Test3_Helper::~GeneratedHeaders_Test3_Helper() {}
void GeneratedHeaders_Test3_Helper::delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    GeneratedHeaders_Test3_Helper::__delegateVistor(c, v, successfullyDelegated);
}
odcore::reflection::Message GeneratedHeaders_Test3_Helper::map(odcore::data::Container &c, bool &successfullyMapped) {
    return GeneratedHeaders_Test3_Helper::__map(c, successfullyMapped);
}
void GeneratedHeaders_Test3_Helper::__delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    successfullyDelegated = false;
    if (c.getDataType() == Test3::ID()) {
        Test3 payload = c.getData<Test3>();
        payload.accept(v);
        successfullyDelegated = true;
    }
}
odcore::reflection::Message GeneratedHeaders_Test3_Helper::__map(odcore::data::Container &c, bool &successfullyMapped) {
    successfullyMapped = false;
    odcore::reflection::Message msg;
    odcore::reflection::MessageFromVisitableVisitor mfvv;
    __delegateVistor(c, mfvv, successfullyMapped);
    if (successfullyMapped) {
        msg = mfvv.getMessage();
    }
    return msg;
}
