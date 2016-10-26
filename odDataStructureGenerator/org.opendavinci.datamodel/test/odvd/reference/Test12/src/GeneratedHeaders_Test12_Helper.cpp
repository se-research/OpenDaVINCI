/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

#include <iostream>
#include <test12/GeneratedHeaders_Test12.h>
#include <test12/GeneratedHeaders_Test12_Helper.h>
#include <opendavinci/odcore/base/Visitable.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
extern "C" {
    odcore::reflection::Helper *newHelper() {
        return new GeneratedHeaders_Test12_Helper;
    }
    void deleteHelper(odcore::reflection::Helper *h) {
        delete h;
    }
}
GeneratedHeaders_Test12_Helper::~GeneratedHeaders_Test12_Helper() {}
void GeneratedHeaders_Test12_Helper::delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    GeneratedHeaders_Test12_Helper::__delegateVistor(c, v, successfullyDelegated);
}
odcore::reflection::Message GeneratedHeaders_Test12_Helper::map(odcore::data::Container &c, bool &successfullyMapped) {
    return GeneratedHeaders_Test12_Helper::__map(c, successfullyMapped);
}
void GeneratedHeaders_Test12_Helper::__delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    successfullyDelegated = false;
    if (c.getDataType() == Test12Simple::ID()) {
        Test12Simple payload = c.getData<Test12Simple>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test12Complex::ID()) {
        Test12Complex payload = c.getData<Test12Complex>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test12Lists::ID()) {
        Test12Lists payload = c.getData<Test12Lists>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test12MapBool::ID()) {
        Test12MapBool payload = c.getData<Test12MapBool>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test12MapChar::ID()) {
        Test12MapChar payload = c.getData<Test12MapChar>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test12MapInt32::ID()) {
        Test12MapInt32 payload = c.getData<Test12MapInt32>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test12MapUint32::ID()) {
        Test12MapUint32 payload = c.getData<Test12MapUint32>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test12MapFloat::ID()) {
        Test12MapFloat payload = c.getData<Test12MapFloat>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test12MapDouble::ID()) {
        Test12MapDouble payload = c.getData<Test12MapDouble>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == Test12MapString::ID()) {
        Test12MapString payload = c.getData<Test12MapString>();
        payload.accept(v);
        successfullyDelegated = true;
    }
}
odcore::reflection::Message GeneratedHeaders_Test12_Helper::__map(odcore::data::Container &c, bool &successfullyMapped) {
    successfullyMapped = false;
    odcore::reflection::Message msg;
    odcore::reflection::MessageFromVisitableVisitor mfvv;
    __delegateVistor(c, mfvv, successfullyMapped);
    if (successfullyMapped) {
        msg = mfvv.getMessage();
    }
    return msg;
}
