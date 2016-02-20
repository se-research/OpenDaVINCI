/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"


#include "test8/generated/testpackage/subpackage/Test8C.h"

namespace testpackage {
	namespace subpackage {
			using namespace std;
			using namespace core::base;
		
		
			Test8C::Test8C() :
			    SerializableData(), Visitable()
				, m_attribute1("")
			{
			}
		
			Test8C::Test8C(
				const std::string &val0
			) :
			    SerializableData(), Visitable()
				, m_attribute1(val0)
			{
			}
		
			Test8C::Test8C(const Test8C &obj) :
			    SerializableData(), Visitable()
				, m_attribute1(obj.m_attribute1)
			{
			}
			
			Test8C::~Test8C() {
			}
		
			Test8C& Test8C::operator=(const Test8C &obj) {
				m_attribute1 = obj.m_attribute1;
				return (*this);
			}
		
			int32_t Test8C::ID() {
				return 10;
			}
		
			const string Test8C::ShortName() {
				return "Test8C";
			}
		
			const string Test8C::LongName() {
				return "testpackage.subpackage.Test8C";
			}
		
			int32_t Test8C::getID() const {
				return Test8C::ID();
			}
		
			const string Test8C::getShortName() const {
				return Test8C::ShortName();
			}
		
			const string Test8C::getLongName() const {
				return Test8C::LongName();
			}
		
			std::string Test8C::getAttribute1() const {
				return m_attribute1;
			}
			
			void Test8C::setAttribute1(const std::string &val) {
				m_attribute1 = val;
			}
		
			void Test8C::accept(core::base::Visitor &v) {
				v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT, 0, "Test8C.attribute1", "attribute1", m_attribute1);
			}
		
			const string Test8C::toString() const {
				stringstream s;
		
		
				s << "Attribute1: " << getAttribute1() << " ";
		
				return s.str();
			}
		
			ostream& Test8C::operator<<(ostream &out) const {
		
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				core::SharedPointer<Serializer> s = sf.getSerializer(out);
		
				s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
						m_attribute1);
				return out;
			}
		
			istream& Test8C::operator>>(istream &in) {
		
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				core::SharedPointer<Deserializer> d = sf.getDeserializer(in);
		
				d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
						m_attribute1);
				return in;
			}
	} // subpackage
} // testpackage
