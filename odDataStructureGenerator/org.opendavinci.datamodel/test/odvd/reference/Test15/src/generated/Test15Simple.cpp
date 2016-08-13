/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include <opendavinci/odcore/serialization/Deserializer.h>
#include <opendavinci/odcore/serialization/SerializationFactory.h>
#include <opendavinci/odcore/serialization/Serializer.h>

#include "test15/generated/Test15Simple.h"

	using namespace std;
	using namespace odcore::base;
	using namespace odcore::serialization;


	Test15Simple::Test15Simple() :
	    SerializableData(), Visitable()
		, m_buttonState(UNDEFINED) // TODO: Validation if the default value is of the desired type.
	{
	}

	Test15Simple::Test15Simple(
		const Test15Simple::ButtonState &val0
	) :
	    SerializableData(), Visitable()
		, m_buttonState(val0)
	{
	}

	Test15Simple::Test15Simple(const Test15Simple &obj) :
	    SerializableData(), Visitable()
		, m_buttonState(obj.m_buttonState)
	{
	}
	
	Test15Simple::~Test15Simple() {
	}

	Test15Simple& Test15Simple::operator=(const Test15Simple &obj) {
		m_buttonState = obj.m_buttonState;
		return (*this);
	}

	int32_t Test15Simple::ID() {
		return 15;
	}

	const string Test15Simple::ShortName() {
		return "Test15Simple";
	}

	const string Test15Simple::LongName() {
		return "Test15Simple";
	}

	int32_t Test15Simple::getID() const {
		return Test15Simple::ID();
	}

	const string Test15Simple::getShortName() const {
		return Test15Simple::ShortName();
	}

	const string Test15Simple::getLongName() const {
		return Test15Simple::LongName();
	}

	Test15Simple::ButtonState Test15Simple::getButtonState() const {
		return m_buttonState;
	}
	
	void Test15Simple::setButtonState(const Test15Simple::ButtonState &val) {
		m_buttonState = val;
	}

	void Test15Simple::accept(odcore::base::Visitor &v) {
		v.beginVisit(ID(), ShortName(), LongName());
		int32_t int32t_buttonState = m_buttonState;
		v.visit(1, "Test15Simple.buttonState", "buttonState", int32t_buttonState);
		m_buttonState = static_cast<Test15Simple::ButtonState>(int32t_buttonState);
		v.endVisit();
	}

	const string Test15Simple::toString() const {
		stringstream s;

		switch(getButtonState()) {
			case PRESSED :
			s << "ButtonState: Test15Simple::PRESSED (1) ";
			break;
			case UNDEFINED :
			s << "ButtonState: Test15Simple::UNDEFINED (-1) ";
			break;
			case NOT_PRESSED :
			s << "ButtonState: Test15Simple::NOT_PRESSED (0) ";
			break;
		}

		return s.str();
	}

	ostream& Test15Simple::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		int32_t int32t_buttonState = m_buttonState;
		s->write(1,
				int32t_buttonState);
		return out;
	}

	istream& Test15Simple::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		int32_t int32t_buttonState = 0;
		d->read(1,
				int32t_buttonState);
		m_buttonState = static_cast<Test15Simple::ButtonState>(int32t_buttonState);
		return in;
	}
