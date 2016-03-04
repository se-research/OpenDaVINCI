/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"

#include "test17/generated/sub/structure/Test17Super.h"

#include "test17/generated/sub/structure/Test17Child.h"

namespace sub {
	namespace structure {
			using namespace std;
			using namespace odcore::base;
		
		
			Test17Child::Test17Child() :
			    sub::structure::Test17Super()
				, m_myName("ABC") // TODO: Validation if the default value is of the desired type.
			{
			}
		
			Test17Child::Test17Child(
				const std::string &val0
			) :
			    sub::structure::Test17Super()
				, m_myName(val0)
			{
			}
		
			Test17Child::Test17Child(const Test17Child &obj) :
			    sub::structure::Test17Super(obj)
				, m_myName(obj.m_myName)
			{
			}
			
			Test17Child::~Test17Child() {
			}
		
			Test17Child& Test17Child::operator=(const Test17Child &obj) {
				sub::structure::Test17Super::operator=(obj);
				m_myName = obj.m_myName;
				return (*this);
			}
		
			int32_t Test17Child::ID() {
				return 18;
			}
		
			const string Test17Child::ShortName() {
				return "Test17Child";
			}
		
			const string Test17Child::LongName() {
				return "sub.structure.Test17Child";
			}
		
			int32_t Test17Child::getID() const {
				return Test17Child::ID();
			}
		
			const string Test17Child::getShortName() const {
				return Test17Child::ShortName();
			}
		
			const string Test17Child::getLongName() const {
				return Test17Child::LongName();
			}
		
			std::string Test17Child::getMyName() const {
				return m_myName;
			}
			
			void Test17Child::setMyName(const std::string &val) {
				m_myName = val;
			}
		
			void Test17Child::accept(odcore::base::Visitor &v) {
				v.beginVisit();
				sub::structure::Test17Super::accept(v);
				v.visit(CRC32 < CharList<'m', CharList<'y', CharList<'N', CharList<'a', CharList<'m', CharList<'e', NullType> > > > > >  >::RESULT, 0, "Test17Child.myName", "myName", m_myName);
				v.endVisit();
			}
		
			const string Test17Child::toString() const {
				stringstream s;
		
				s << sub::structure::Test17Super::toString() << " ";
		
				s << "MyName: " << getMyName() << " ";
		
				return s.str();
			}
		
			ostream& Test17Child::operator<<(ostream &out) const {
				sub::structure::Test17Super::operator<<(out);
		
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				std::shared_ptr<Serializer> s = sf.getSerializer(out);
		
				s->write(CRC32 < CharList<'m', CharList<'y', CharList<'N', CharList<'a', CharList<'m', CharList<'e', NullType> > > > > >  >::RESULT,
						m_myName);
				return out;
			}
		
			istream& Test17Child::operator>>(istream &in) {
				sub::structure::Test17Super::operator>>(in);
		
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
		
				d->read(CRC32 < CharList<'m', CharList<'y', CharList<'N', CharList<'a', CharList<'m', CharList<'e', NullType> > > > > >  >::RESULT,
						m_myName);
				return in;
			}
	} // structure
} // sub
