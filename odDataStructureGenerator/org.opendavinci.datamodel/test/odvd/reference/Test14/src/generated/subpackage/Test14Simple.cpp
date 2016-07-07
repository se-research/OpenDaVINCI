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


#include "test14/generated/subpackage/Test14Simple.h"

namespace subpackage {
		using namespace std;
		using namespace odcore::base;
	
	
		Test14Simple::Test14Simple() :
		    SerializableData(), Visitable()
			, m_buttonState(UNDEFINED) // TODO: Validation if the default value is of the desired type.
		{
		}
	
		Test14Simple::Test14Simple(
			const Test14Simple::ButtonState &val0
		) :
		    SerializableData(), Visitable()
			, m_buttonState(val0)
		{
		}
	
		Test14Simple::Test14Simple(const Test14Simple &obj) :
		    SerializableData(), Visitable()
			, m_buttonState(obj.m_buttonState)
		{
		}
		
		Test14Simple::~Test14Simple() {
		}
	
		Test14Simple& Test14Simple::operator=(const Test14Simple &obj) {
			m_buttonState = obj.m_buttonState;
			return (*this);
		}
	
		int32_t Test14Simple::ID() {
			return 14;
		}
	
		const string Test14Simple::ShortName() {
			return "Test14Simple";
		}
	
		const string Test14Simple::LongName() {
			return "subpackage.Test14Simple";
		}
	
		int32_t Test14Simple::getID() const {
			return Test14Simple::ID();
		}
	
		const string Test14Simple::getShortName() const {
			return Test14Simple::ShortName();
		}
	
		const string Test14Simple::getLongName() const {
			return Test14Simple::LongName();
		}
	
		Test14Simple::ButtonState Test14Simple::getButtonState() const {
			return m_buttonState;
		}
		
		void Test14Simple::setButtonState(const Test14Simple::ButtonState &val) {
			m_buttonState = val;
		}
	
		void Test14Simple::accept(odcore::base::Visitor &v) {
			v.beginVisit();
			int32_t int32t_buttonState = m_buttonState;
			v.visit(CRC32 < CharList<'b', CharList<'u', CharList<'t', CharList<'t', CharList<'o', CharList<'n', CharList<'S', CharList<'t', CharList<'a', CharList<'t', CharList<'e', NullType> > > > > > > > > > >  >::RESULT, 0, "Test14Simple.buttonState", "buttonState", int32t_buttonState);
			m_buttonState = static_cast<Test14Simple::ButtonState>(int32t_buttonState);
			v.endVisit();
		}
	
		const string Test14Simple::toString() const {
			stringstream s;
	
	
			switch(getButtonState()) {
				case PRESSED :
				s << "ButtonState: Test14Simple::PRESSED (1) ";
				break;
				case UNDEFINED :
				s << "ButtonState: Test14Simple::UNDEFINED (-1) ";
				break;
				case NOT_PRESSED :
				s << "ButtonState: Test14Simple::NOT_PRESSED (0) ";
				break;
			}
	
			return s.str();
		}
	
		ostream& Test14Simple::operator<<(ostream &out) const {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			std::shared_ptr<Serializer> s = sf.getSerializer(out);
	
			int32_t int32t_buttonState = m_buttonState;
			s->write(CRC32 < CharList<'b', CharList<'u', CharList<'t', CharList<'t', CharList<'o', CharList<'n', CharList<'S', CharList<'t', CharList<'a', CharList<'t', CharList<'e', NullType> > > > > > > > > > >  >::RESULT,
					int32t_buttonState);
			return out;
		}
	
		istream& Test14Simple::operator>>(istream &in) {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
	
			int32_t int32t_buttonState = 0;
			d->read(CRC32 < CharList<'b', CharList<'u', CharList<'t', CharList<'t', CharList<'o', CharList<'n', CharList<'S', CharList<'t', CharList<'a', CharList<'t', CharList<'e', NullType> > > > > > > > > > >  >::RESULT,
					int32t_buttonState);
			m_buttonState = static_cast<Test14Simple::ButtonState>(int32t_buttonState);
			return in;
		}
} // subpackage
