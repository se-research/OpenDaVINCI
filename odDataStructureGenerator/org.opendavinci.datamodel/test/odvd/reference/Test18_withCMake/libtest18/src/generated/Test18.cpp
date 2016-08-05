/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>
#include <cstring>
#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"

#include "test18/generated/Test18.h"

	using namespace std;
	using namespace odcore::base;
	using namespace odcore::serialization;


	Test18::Test18() :
	    SerializableData(), Visitable()
		, m_myArray1()
		, m_myArray2()
		, m_myAtt1(0)
		, m_myAtt2(0)
		, m_myAtt3(0)
	{
		m_myArray1 = new uint32_t[getSize_MyArray1()];
		for(uint32_t i = 0; i < getSize_MyArray1(); i++) {
			m_myArray1[i] = 0;
		}
		m_myArray2 = new float[getSize_MyArray2()];
		for(uint32_t i = 0; i < getSize_MyArray2(); i++) {
			m_myArray2[i] = 0;
		}
	}

	Test18::Test18(
		const uint32_t *val0, 
		const float *val1, 
		const uint32_t &val2, 
		const uint32_t &val3, 
		const uint32_t &val4
	) :
	    SerializableData(), Visitable()
		, m_myArray1() // The content from obj will be copied in the copy-constructor's body.
		, m_myArray2() // The content from obj will be copied in the copy-constructor's body.
		, m_myAtt1(val2)
		, m_myAtt2(val3)
		, m_myAtt3(val4)
	{
		m_myArray1 = new uint32_t[getSize_MyArray1()];
		::memcpy(m_myArray1, val0, getSize_MyArray1() * sizeof(*m_myArray1));
		m_myArray2 = new float[getSize_MyArray2()];
		::memcpy(m_myArray2, val1, getSize_MyArray2() * sizeof(*m_myArray2));
	}

	Test18::Test18(const Test18 &obj) :
	    SerializableData(), Visitable()
		, m_myArray1() // The content from obj will be copied in the copy-constructor's body.
		, m_myArray2() // The content from obj will be copied in the copy-constructor's body.
		, m_myAtt1(obj.m_myAtt1)
		, m_myAtt2(obj.m_myAtt2)
		, m_myAtt3(obj.m_myAtt3)
	{
		m_myArray1 = new uint32_t[getSize_MyArray1()];
		::memcpy(m_myArray1, obj.m_myArray1, obj.getSize_MyArray1() * sizeof(*m_myArray1));
		m_myArray2 = new float[getSize_MyArray2()];
		::memcpy(m_myArray2, obj.m_myArray2, obj.getSize_MyArray2() * sizeof(*m_myArray2));
	}
	
	Test18::~Test18() {
		OPENDAVINCI_CORE_DELETE_ARRAY(m_myArray1);
		OPENDAVINCI_CORE_DELETE_ARRAY(m_myArray2);
	}

	Test18& Test18::operator=(const Test18 &obj) {
		::memcpy(m_myArray1, obj.m_myArray1, obj.getSize_MyArray1() * sizeof(*m_myArray1));
		::memcpy(m_myArray2, obj.m_myArray2, obj.getSize_MyArray2() * sizeof(*m_myArray2));
		m_myAtt1 = obj.m_myAtt1;
		m_myAtt2 = obj.m_myAtt2;
		m_myAtt3 = obj.m_myAtt3;
		return (*this);
	}

	int32_t Test18::ID() {
		return 18;
	}

	const string Test18::ShortName() {
		return "Test18";
	}

	const string Test18::LongName() {
		return "Test18";
	}

	int32_t Test18::getID() const {
		return Test18::ID();
	}

	const string Test18::getShortName() const {
		return Test18::ShortName();
	}

	const string Test18::getLongName() const {
		return Test18::LongName();
	}

	uint32_t* Test18::getMyArray1() {
		return m_myArray1;
	}
	
	uint32_t Test18::getSize_MyArray1() const {
		return 2;
	}
	float* Test18::getMyArray2() {
		return m_myArray2;
	}
	
	uint32_t Test18::getSize_MyArray2() const {
		return 3;
	}
	uint32_t Test18::getMyAtt1() const {
		return m_myAtt1;
	}
	
	void Test18::setMyAtt1(const uint32_t &val) {
		m_myAtt1 = val;
	}
	uint32_t Test18::getMyAtt2() const {
		return m_myAtt2;
	}
	
	void Test18::setMyAtt2(const uint32_t &val) {
		m_myAtt2 = val;
	}
	uint32_t Test18::getMyAtt3() const {
		return m_myAtt3;
	}
	
	void Test18::setMyAtt3(const uint32_t &val) {
		m_myAtt3 = val;
	}

	void Test18::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.visit(3, "Test18.myAtt1", "myAtt1", m_myAtt1);
		v.visit(4, "Test18.myAtt2", "myAtt2", m_myAtt2);
		v.visit(5, "Test18.myAtt3", "myAtt3", m_myAtt3);
		v.endVisit();
	}

	const string Test18::toString() const {
		stringstream s;

		s << "myArray1: (";
		for(uint32_t i = 0; i < getSize_MyArray1(); i++) {
			s << (m_myArray1[i]) << (((i+1) < getSize_MyArray1()) ? ", " : "");
		}
		s << ")" << " ";
		s << "myArray2: (";
		for(uint32_t i = 0; i < getSize_MyArray2(); i++) {
			s << (m_myArray2[i]) << (((i+1) < getSize_MyArray2()) ? ", " : "");
		}
		s << ")" << " ";
		s << "MyAtt1: " << getMyAtt1() << " ";
		s << "MyAtt2: " << getMyAtt2() << " ";
		s << "MyAtt3: " << getMyAtt3() << " ";

		return s.str();
	}

	ostream& Test18::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		// Store elements from m_myArray1 into a string.
		{
			std::stringstream sstr_MyArray1;
			{
				for(uint32_t i = 0; i < getSize_MyArray1(); i++) {
					s->writeValue(sstr_MyArray1, m_myArray1[i]);
				}
			}
			const std::string str_sstr_MyArray1 = sstr_MyArray1.str();
			s->write(1, str_sstr_MyArray1);
		}
		// Store elements from m_myArray2 into a string.
		{
			std::stringstream sstr_MyArray2;
			{
				for(uint32_t i = 0; i < getSize_MyArray2(); i++) {
					s->writeValue(sstr_MyArray2, m_myArray2[i]);
				}
			}
			const std::string str_sstr_MyArray2 = sstr_MyArray2.str();
			s->write(2, str_sstr_MyArray2);
		}
		s->write(3,
				m_myAtt1);
		s->write(4,
				m_myAtt2);
		s->write(5,
				m_myAtt3);
		return out;
	}

	istream& Test18::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore values for myArray1
		{
			std::string str_MyArray1;
			d->read(1, str_MyArray1);
		
			if (str_MyArray1.size() > 0) {
				std::stringstream sstr_str_MyArray1(str_MyArray1);
				uint32_t length = str_MyArray1.size();
				uint32_t elementCounter = 0;
				while (length > 0) {
					uint32_t element;
					length -= d->readValue(sstr_str_MyArray1, element);
					if (elementCounter < getSize_MyArray1()) {
						m_myArray1[elementCounter] = element;
					}
					elementCounter++;
				}
			}
		}
		// Restore values for myArray2
		{
			std::string str_MyArray2;
			d->read(2, str_MyArray2);
		
			if (str_MyArray2.size() > 0) {
				std::stringstream sstr_str_MyArray2(str_MyArray2);
				uint32_t length = str_MyArray2.size();
				uint32_t elementCounter = 0;
				while (length > 0) {
					float element;
					length -= d->readValue(sstr_str_MyArray2, element);
					if (elementCounter < getSize_MyArray2()) {
						m_myArray2[elementCounter] = element;
					}
					elementCounter++;
				}
			}
		}
		d->read(3,
				m_myAtt1);
		d->read(4,
				m_myAtt2);
		d->read(5,
				m_myAtt3);
		return in;
	}
