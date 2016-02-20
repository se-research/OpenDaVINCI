/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"


#include "test8/generated/testpackage/Test8B.h"

namespace testpackage {
		using namespace std;
		using namespace core::base;
	
	
		Test8B::Test8B() :
		    SerializableData(), Visitable()
			, m_attribute1(true) // TODO: Validation if the default value is of the desired type.
		{
		}
	
		Test8B::Test8B(
			const bool &val0
		) :
		    SerializableData(), Visitable()
			, m_attribute1(val0)
		{
		}
	
		Test8B::Test8B(const Test8B &obj) :
		    SerializableData(), Visitable()
			, m_attribute1(obj.m_attribute1)
		{
		}
		
		Test8B::~Test8B() {
		}
	
		Test8B& Test8B::operator=(const Test8B &obj) {
			m_attribute1 = obj.m_attribute1;
			return (*this);
		}
	
		int32_t Test8B::ID() {
			return 9;
		}
	
		const string Test8B::ShortName() {
			return "Test8B";
		}
	
		const string Test8B::LongName() {
			return "testpackage.Test8B";
		}
	
		int32_t Test8B::getID() const {
			return Test8B::ID();
		}
	
		const string Test8B::getShortName() const {
			return Test8B::ShortName();
		}
	
		const string Test8B::getLongName() const {
			return Test8B::LongName();
		}
	
		bool Test8B::getAttribute1() const {
			return m_attribute1;
		}
		
		void Test8B::setAttribute1(const bool &val) {
			m_attribute1 = val;
		}
	
		void Test8B::accept(core::base::Visitor &v) {
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT, 0, "Test8B.attribute1", "attribute1", m_attribute1);
		}
	
		const string Test8B::toString() const {
			stringstream s;
	
	
			s << "Attribute1: " << getAttribute1() << " ";
	
			return s.str();
		}
	
		ostream& Test8B::operator<<(ostream &out) const {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			core::SharedPointer<Serializer> s = sf.getSerializer(out);
	
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
					m_attribute1);
			return out;
		}
	
		istream& Test8B::operator>>(istream &in) {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			core::SharedPointer<Deserializer> d = sf.getDeserializer(in);
	
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
					m_attribute1);
			return in;
		}
} // testpackage
