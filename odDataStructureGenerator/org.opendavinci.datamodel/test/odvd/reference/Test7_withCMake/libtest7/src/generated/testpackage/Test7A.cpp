/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"


#include "generated/testpackage/Test7A.h"

namespace testpackage {
		using namespace std;
		using namespace core::base;
	
	
		Test7A::Test7A() :
		    SerializableData(), Visitable()
			, m_attribute1(false)
			, m_attribute2('\0')
			, m_attribute3(0)
		{
		}
	
		Test7A::Test7A(
			const bool &val0, 
			const char &val1, 
			const int32_t &val2
		) :
		    SerializableData(), Visitable()
			, m_attribute1(val0)
			, m_attribute2(val1)
			, m_attribute3(val2)
		{
		}
	
		Test7A::Test7A(const Test7A &obj) :
		    SerializableData(), Visitable()
			, m_attribute1(obj.m_attribute1)
			, m_attribute2(obj.m_attribute2)
			, m_attribute3(obj.m_attribute3)
		{
		}
		
		Test7A::~Test7A() {
		}
	
		Test7A& Test7A::operator=(const Test7A &obj) {
			m_attribute1 = obj.m_attribute1;
			m_attribute2 = obj.m_attribute2;
			m_attribute3 = obj.m_attribute3;
			return (*this);
		}
	
		int32_t Test7A::ID() {
			return 7;
		}
	
		const string Test7A::ShortName() {
			return "Test7A";
		}
	
		const string Test7A::LongName() {
			return "testpackage.Test7A";
		}
	
		int32_t Test7A::getID() const {
			return Test7A::ID();
		}
	
		const string Test7A::getShortName() const {
			return Test7A::ShortName();
		}
	
		const string Test7A::getLongName() const {
			return Test7A::LongName();
		}
	
		bool Test7A::getAttribute1() const {
			return m_attribute1;
		}
		
		void Test7A::setAttribute1(const bool &val) {
			m_attribute1 = val;
		}
		char Test7A::getAttribute2() const {
			return m_attribute2;
		}
		
		void Test7A::setAttribute2(const char &val) {
			m_attribute2 = val;
		}
		int32_t Test7A::getAttribute3() const {
			return m_attribute3;
		}
		
		void Test7A::setAttribute3(const int32_t &val) {
			m_attribute3 = val;
		}
	
		void Test7A::accept(core::base::Visitor &v) {
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT, 0, "Test7A.attribute1", "attribute1", m_attribute1);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT, 0, "Test7A.attribute2", "attribute2", m_attribute2);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT, 0, "Test7A.attribute3", "attribute3", m_attribute3);
		}
	
		const string Test7A::toString() const {
			stringstream s;
	
	
			s << "Attribute1: " << getAttribute1() << " ";
			s << "Attribute2: " << getAttribute2() << " ";
			s << "Attribute3: " << getAttribute3() << " ";
	
			return s.str();
		}
	
		ostream& Test7A::operator<<(ostream &out) const {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			core::SharedPointer<Serializer> s = sf.getSerializer(out);
	
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
					m_attribute1);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT,
					m_attribute2);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT,
					m_attribute3);
			return out;
		}
	
		istream& Test7A::operator>>(istream &in) {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			core::SharedPointer<Deserializer> d = sf.getDeserializer(in);
	
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
					m_attribute1);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT,
					m_attribute2);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT,
					m_attribute3);
			return in;
		}
} // testpackage
