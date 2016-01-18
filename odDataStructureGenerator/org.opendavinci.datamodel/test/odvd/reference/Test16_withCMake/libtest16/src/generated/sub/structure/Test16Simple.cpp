/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"


#include "test16/generated/sub/structure/Test16Simple.h"

namespace sub {
	namespace structure {
			using namespace std;
			using namespace core::base;
		
		
			Test16Simple::Test16Simple() :
			    SerializableData(), Visitable()
				, m_myData(4.6) // TODO: Validation if the default value is of the desired type.
				, m_myValue(1) // TODO: Validation if the default value is of the desired type.
			{
			}
		
			Test16Simple::Test16Simple(
				const double &val0, 
				const int32_t &val1
			) :
			    SerializableData(), Visitable()
				, m_myData(val0)
				, m_myValue(val1)
			{
			}
		
			Test16Simple::Test16Simple(const Test16Simple &obj) :
			    SerializableData(), Visitable()
				, m_myData(obj.m_myData)
				, m_myValue(obj.m_myValue)
			{
			}
			
			Test16Simple::~Test16Simple() {
			}
		
			Test16Simple& Test16Simple::operator=(const Test16Simple &obj) {
				m_myData = obj.m_myData;
				m_myValue = obj.m_myValue;
				return (*this);
			}
		
			int32_t Test16Simple::ID() {
				return 16;
			}
		
			const string Test16Simple::ShortName() {
				return "Test16Simple";
			}
		
			const string Test16Simple::LongName() {
				return "sub.structure.Test16Simple";
			}
		
			double Test16Simple::getMyData() const {
				return m_myData;
			}
			
			void Test16Simple::setMyData(const double &val) {
				m_myData = val;
			}
			int32_t Test16Simple::getMyValue() const {
				return m_myValue;
			}
			
			void Test16Simple::setMyValue(const int32_t &val) {
				m_myValue = val;
			}
		
			void Test16Simple::accept(core::base::Visitor &v) {
				v.visit(CRC32 < CharList<'m', CharList<'y', CharList<'D', CharList<'a', CharList<'t', CharList<'a', NullType> > > > > >  >::RESULT, 0, "Test16Simple.myData", "myData", m_myData);
				v.visit(CRC32 < CharList<'m', CharList<'y', CharList<'V', CharList<'a', CharList<'l', CharList<'u', CharList<'e', NullType> > > > > > >  >::RESULT, 0, "Test16Simple.myValue", "myValue", m_myValue);
			}
		
			const string Test16Simple::toString() const {
				stringstream s;
		
		
				s << "MyData: " << getMyData() << " ";
				s << "MyValue: " << getMyValue() << " ";
		
				return s.str();
			}
		
			ostream& Test16Simple::operator<<(ostream &out) const {
		
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				core::SharedPointer<Serializer> s = sf.getSerializer(out);
		
				s->write(CRC32 < CharList<'m', CharList<'y', CharList<'D', CharList<'a', CharList<'t', CharList<'a', NullType> > > > > >  >::RESULT,
						m_myData);
				s->write(CRC32 < CharList<'m', CharList<'y', CharList<'V', CharList<'a', CharList<'l', CharList<'u', CharList<'e', NullType> > > > > > >  >::RESULT,
						m_myValue);
				return out;
			}
		
			istream& Test16Simple::operator>>(istream &in) {
		
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				core::SharedPointer<Deserializer> d = sf.getDeserializer(in);
		
				d->read(CRC32 < CharList<'m', CharList<'y', CharList<'D', CharList<'a', CharList<'t', CharList<'a', NullType> > > > > >  >::RESULT,
						m_myData);
				d->read(CRC32 < CharList<'m', CharList<'y', CharList<'V', CharList<'a', CharList<'l', CharList<'u', CharList<'e', NullType> > > > > > >  >::RESULT,
						m_myValue);
				return in;
			}
	} // structure
} // sub
