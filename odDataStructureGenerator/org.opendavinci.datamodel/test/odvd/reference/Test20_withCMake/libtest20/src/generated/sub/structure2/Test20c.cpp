/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"

#include "test20/generated/sub/structure2/Test20c.h"

namespace sub {
	namespace structure2 {
			using namespace std;
			using namespace odcore::base;
		
		
			Test20c::Test20c() :
			    SerializableData(), Visitable()
				, m_val3(0)
				, m_val4()
			{
			}
		
			Test20c::Test20c(
				const uint32_t &val0, 
				const sub::structure::Test20b &val1
			) :
			    SerializableData(), Visitable()
				, m_val3(val0)
				, m_val4(val1)
			{
			}
		
			Test20c::Test20c(const Test20c &obj) :
			    SerializableData(), Visitable()
				, m_val3(obj.m_val3)
				, m_val4(obj.m_val4)
			{
			}
			
			Test20c::~Test20c() {
			}
		
			Test20c& Test20c::operator=(const Test20c &obj) {
				m_val3 = obj.m_val3;
				m_val4 = obj.m_val4;
				return (*this);
			}
		
			int32_t Test20c::ID() {
				return 22;
			}
		
			const string Test20c::ShortName() {
				return "Test20c";
			}
		
			const string Test20c::LongName() {
				return "sub.structure2.Test20c";
			}
		
			int32_t Test20c::getID() const {
				return Test20c::ID();
			}
		
			const string Test20c::getShortName() const {
				return Test20c::ShortName();
			}
		
			const string Test20c::getLongName() const {
				return Test20c::LongName();
			}
		
			uint32_t Test20c::getVal3() const {
				return m_val3;
			}
			
			void Test20c::setVal3(const uint32_t &val) {
				m_val3 = val;
			}
			sub::structure::Test20b Test20c::getVal4() const {
				return m_val4;
			}
			
			void Test20c::setVal4(const sub::structure::Test20b &val) {
				m_val4 = val;
			}
		
			void Test20c::accept(odcore::base::Visitor &v) {
				v.beginVisit();
				v.visit(1, "Test20c.val3", "val3", m_val3);
				v.visit(2, "Test20c.val4", "val4", m_val4);
				v.endVisit();
			}
		
			const string Test20c::toString() const {
				stringstream s;
		
				s << "Val3: " << getVal3() << " ";
				s << "Val4: " << getVal4().toString() << " ";
		
				return s.str();
			}
		
			ostream& Test20c::operator<<(ostream &out) const {
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				std::shared_ptr<Serializer> s = sf.getSerializer(out);
		
				s->write(1,
						m_val3);
				s->write(2,
						m_val4);
				return out;
			}
		
			istream& Test20c::operator>>(istream &in) {
				SerializationFactory& sf = SerializationFactory::getInstance();
		
				std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
		
				d->read(1,
						m_val3);
				d->read(2,
						m_val4);
				return in;
			}
	} // structure2
} // sub
