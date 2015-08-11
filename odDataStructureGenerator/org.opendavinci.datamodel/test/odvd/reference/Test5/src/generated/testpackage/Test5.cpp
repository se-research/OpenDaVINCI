/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"


#include "generated/testpackage/Test5.h"

namespace testpackage {
		using namespace std;
		using namespace core::base;
	
	
		Test5::Test5() :
		    SerializableData(), Visitable()
			, m_attribute1(true) // TODO: Validation if the default value is of the desired type.
			, m_attribute2('c') // TODO: Validation if the default value is of the desired type.
			, m_attribute3(-12) // TODO: Validation if the default value is of the desired type.
			, m_attribute4(+45) // TODO: Validation if the default value is of the desired type.
			, m_attribute5(-0.12) // TODO: Validation if the default value is of the desired type.
			, m_attribute6(+0.45678) // TODO: Validation if the default value is of the desired type.
			, m_attribute7("Hello World.") // TODO: Validation if the default value is of the desired type.
		{
		}
	
		Test5::Test5(
			const bool &val0, 
			const char &val1, 
			const int32_t &val2, 
			const uint32_t &val3, 
			const float &val4, 
			const double &val5, 
			const std::string &val6
		) :
		    SerializableData(), Visitable()
			, m_attribute1(val0)
			, m_attribute2(val1)
			, m_attribute3(val2)
			, m_attribute4(val3)
			, m_attribute5(val4)
			, m_attribute6(val5)
			, m_attribute7(val6)
		{
		}
	
		Test5::Test5(const Test5 &obj) :
		    SerializableData(), Visitable()
			, m_attribute1(obj.m_attribute1)
			, m_attribute2(obj.m_attribute2)
			, m_attribute3(obj.m_attribute3)
			, m_attribute4(obj.m_attribute4)
			, m_attribute5(obj.m_attribute5)
			, m_attribute6(obj.m_attribute6)
			, m_attribute7(obj.m_attribute7)
		{
		}
		
		Test5::~Test5() {
		}
	
		Test5& Test5::operator=(const Test5 &obj) {
			m_attribute1 = obj.m_attribute1;
			m_attribute2 = obj.m_attribute2;
			m_attribute3 = obj.m_attribute3;
			m_attribute4 = obj.m_attribute4;
			m_attribute5 = obj.m_attribute5;
			m_attribute6 = obj.m_attribute6;
			m_attribute7 = obj.m_attribute7;
			return (*this);
		}
	
		int32_t Test5::ID() {
			return 5;
		}
	
		const string Test5::ShortName() {
			return "Test5";
		}
	
		const string Test5::LongName() {
			return "testpackage.Test5";
		}
	
		bool Test5::getAttribute1() const {
			return m_attribute1;
		}
		
		void Test5::setAttribute1(const bool &val) {
			m_attribute1 = val;
		}
		char Test5::getAttribute2() const {
			return m_attribute2;
		}
		
		void Test5::setAttribute2(const char &val) {
			m_attribute2 = val;
		}
		int32_t Test5::getAttribute3() const {
			return m_attribute3;
		}
		
		void Test5::setAttribute3(const int32_t &val) {
			m_attribute3 = val;
		}
		uint32_t Test5::getAttribute4() const {
			return m_attribute4;
		}
		
		void Test5::setAttribute4(const uint32_t &val) {
			m_attribute4 = val;
		}
		float Test5::getAttribute5() const {
			return m_attribute5;
		}
		
		void Test5::setAttribute5(const float &val) {
			m_attribute5 = val;
		}
		double Test5::getAttribute6() const {
			return m_attribute6;
		}
		
		void Test5::setAttribute6(const double &val) {
			m_attribute6 = val;
		}
		std::string Test5::getAttribute7() const {
			return m_attribute7;
		}
		
		void Test5::setAttribute7(const std::string &val) {
			m_attribute7 = val;
		}
	
		void Test5::accept(core::base::Visitor &v) {
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT, 0, "Test5.attribute1", "attribute1", m_attribute1);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT, 0, "Test5.attribute2", "attribute2", m_attribute2);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT, 0, "Test5.attribute3", "attribute3", m_attribute3);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'4', NullType> > > > > > > > > >  >::RESULT, 0, "Test5.attribute4", "attribute4", m_attribute4);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'5', NullType> > > > > > > > > >  >::RESULT, 0, "Test5.attribute5", "attribute5", m_attribute5);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'6', NullType> > > > > > > > > >  >::RESULT, 0, "Test5.attribute6", "attribute6", m_attribute6);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'7', NullType> > > > > > > > > >  >::RESULT, 0, "Test5.attribute7", "attribute7", m_attribute7);
		}
	
		const string Test5::toString() const {
			stringstream s;
	
	
			s << "Attribute1: " << getAttribute1() << " ";
			s << "Attribute2: " << getAttribute2() << " ";
			s << "Attribute3: " << getAttribute3() << " ";
			s << "Attribute4: " << getAttribute4() << " ";
			s << "Attribute5: " << getAttribute5() << " ";
			s << "Attribute6: " << getAttribute6() << " ";
			s << "Attribute7: " << getAttribute7() << " ";
	
			return s.str();
		}
	
		ostream& Test5::operator<<(ostream &out) const {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			core::SharedPointer<Serializer> s = sf.getSerializer(out);
	
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
					m_attribute1);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT,
					m_attribute2);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT,
					m_attribute3);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'4', NullType> > > > > > > > > >  >::RESULT,
					m_attribute4);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'5', NullType> > > > > > > > > >  >::RESULT,
					m_attribute5);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'6', NullType> > > > > > > > > >  >::RESULT,
					m_attribute6);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'7', NullType> > > > > > > > > >  >::RESULT,
					m_attribute7);
			return out;
		}
	
		istream& Test5::operator>>(istream &in) {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			core::SharedPointer<Deserializer> d = sf.getDeserializer(in);
	
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
					m_attribute1);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT,
					m_attribute2);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT,
					m_attribute3);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'4', NullType> > > > > > > > > >  >::RESULT,
					m_attribute4);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'5', NullType> > > > > > > > > >  >::RESULT,
					m_attribute5);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'6', NullType> > > > > > > > > >  >::RESULT,
					m_attribute6);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'7', NullType> > > > > > > > > >  >::RESULT,
					m_attribute7);
			return in;
		}
} // testpackage
