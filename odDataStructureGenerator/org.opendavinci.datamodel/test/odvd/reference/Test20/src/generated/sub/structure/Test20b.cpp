/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"


#include "test20/generated/sub/structure/Test20b.h"

namespace sub {
	namespace structure {
			using namespace std;
			using namespace odcore::base;
		
		
			Test20b::Test20b() :
			    SerializableData(), Visitable()
				, m_val2(0)
			{
			}
		
			Test20b::Test20b(
				const uint32_t &val0
			) :
			    SerializableData(), Visitable()
				, m_val2(val0)
			{
			}
		
			Test20b::Test20b(const Test20b &obj) :
			    SerializableData(), Visitable()
				, m_val2(obj.m_val2)
			{
			}
			
			Test20b::~Test20b() {
			}
		
			Test20b& Test20b::operator=(const Test20b &obj) {
				m_val2 = obj.m_val2;
				return (*this);
			}
		
			int32_t Test20b::ID() {
				return 21;
			}
		
			const string Test20b::ShortName() {
				return "Test20b";
			}
		
			const string Test20b::LongName() {
				return "sub.structure.Test20b";
			}
		
			uint32_t Test20b::getVal2() const {
				return m_val2;
			}
			
			void Test20b::setVal2(const uint32_t &val) {
				m_val2 = val;
			}
		
			void Test20b::accept(odcore::base::Visitor &v) {
				v.visit(CRC32 < CharList<'v', CharList<'a', CharList<'l', CharList<'2', NullType> > > >  >::RESULT, 0, "Test20b.val2", "val2", m_val2);
			}
		
			const string Test20b::toString() const {
				stringstream s;
		
		
				s << "Val2: " << getVal2() << " ";
		
				return s.str();
			}
		
			ostream& Test20b::operator<<(ostream &out) const {
		
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				odcore::SharedPointer<Serializer> s = sf.getSerializer(out);
		
				s->write(CRC32 < CharList<'v', CharList<'a', CharList<'l', CharList<'2', NullType> > > >  >::RESULT,
						m_val2);
				return out;
			}
		
			istream& Test20b::operator>>(istream &in) {
		
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);
		
				d->read(CRC32 < CharList<'v', CharList<'a', CharList<'l', CharList<'2', NullType> > > >  >::RESULT,
						m_val2);
				return in;
			}
	} // structure
} // sub
