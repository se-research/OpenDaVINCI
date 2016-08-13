/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

#include <iostream>
#include <test11/GeneratedHeaders_Test11.h>
#include <test11/GeneratedHeaders_Test11_Helper.h>
#include <opendavinci/odcore/base/Visitable.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
extern "C" {
    odcore::reflection::Helper *newHelper() {
        return new GeneratedHeaders_Test11_Helper;
    }
    void deleteHelper(odcore::reflection::Helper *h) {
        delete h;
    }
}
GeneratedHeaders_Test11_Helper::~GeneratedHeaders_Test11_Helper() {}
void GeneratedHeaders_Test11_Helper::delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    GeneratedHeaders_Test11_Helper::__delegateVistor(c, v, successfullyDelegated);
}
odcore::reflection::Message GeneratedHeaders_Test11_Helper::map(odcore::data::Container &c, bool &successfullyMapped) {
    return GeneratedHeaders_Test11_Helper::__map(c, successfullyMapped);
}
void GeneratedHeaders_Test11_Helper::__delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    successfullyDelegated = false;
    if (c.getDataType() == Test11Simple::ID()) {
        Test11Simple payload = c.getData<Test11Simple>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test11Lists::ID()) {
        Test11Lists payload = c.getData<Test11Lists>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test11MapBool::ID()) {
        Test11MapBool payload = c.getData<Test11MapBool>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test11MapChar::ID()) {
        Test11MapChar payload = c.getData<Test11MapChar>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test11MapInt32::ID()) {
        Test11MapInt32 payload = c.getData<Test11MapInt32>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test11MapUint32::ID()) {
        Test11MapUint32 payload = c.getData<Test11MapUint32>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test11MapFloat::ID()) {
        Test11MapFloat payload = c.getData<Test11MapFloat>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test11MapDouble::ID()) {
        Test11MapDouble payload = c.getData<Test11MapDouble>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test11MapString::ID()) {
        Test11MapString payload = c.getData<Test11MapString>();
        payload.accept(v);
        successfullyDelegated = true;
    }
}
odcore::reflection::Message GeneratedHeaders_Test11_Helper::__map(odcore::data::Container &c, bool &successfullyMapped) {
    successfullyMapped = false;
    odcore::reflection::Message msg;
    odcore::reflection::MessageFromVisitableVisitor mfvv;
    __delegateVistor(c, mfvv, successfullyMapped);
    if (successfullyMapped) {
        msg = mfvv.getMessage();
    }
    return msg;
}
