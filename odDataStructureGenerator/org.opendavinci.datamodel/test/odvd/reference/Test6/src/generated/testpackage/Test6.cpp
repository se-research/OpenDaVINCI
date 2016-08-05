/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>
#include <algorithm>
#include <sstream>
#include <utility>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"

#include "test6/generated/testpackage/Test6.h"

namespace testpackage {
		using namespace std;
		using namespace odcore::base;
		using namespace odcore::serialization;
	
	
		Test6::Test6() :
		    SerializableData(), Visitable()
			, m_attribute1(true) // TODO: Validation if the default value is of the desired type.
			, m_attribute2('c') // TODO: Validation if the default value is of the desired type.
			, m_attribute3(-12) // TODO: Validation if the default value is of the desired type.
			, m_attribute4(+45) // TODO: Validation if the default value is of the desired type.
			, m_attribute5(-0.12) // TODO: Validation if the default value is of the desired type.
			, m_attribute6(+0.45678) // TODO: Validation if the default value is of the desired type.
			, m_attribute7("Hello World.") // TODO: Validation if the default value is of the desired type.
			, m_listOfMyStringList()
		{
		}
	
		Test6::Test6(
			const bool &val0, 
			const char &val1, 
			const int32_t &val2, 
			const uint32_t &val3, 
			const float &val4, 
			const double &val5, 
			const std::string &val6, 
			const vector<std::string> &val7
		) :
		    SerializableData(), Visitable()
			, m_attribute1(val0)
			, m_attribute2(val1)
			, m_attribute3(val2)
			, m_attribute4(val3)
			, m_attribute5(val4)
			, m_attribute6(val5)
			, m_attribute7(val6)
			, m_listOfMyStringList(val7)
		{
		}
	
		Test6::Test6(const Test6 &obj) :
		    SerializableData(), Visitable()
			, m_attribute1(obj.m_attribute1)
			, m_attribute2(obj.m_attribute2)
			, m_attribute3(obj.m_attribute3)
			, m_attribute4(obj.m_attribute4)
			, m_attribute5(obj.m_attribute5)
			, m_attribute6(obj.m_attribute6)
			, m_attribute7(obj.m_attribute7)
			, m_listOfMyStringList(obj.m_listOfMyStringList)
		{
		}
		
		Test6::~Test6() {
		}
	
		Test6& Test6::operator=(const Test6 &obj) {
			m_attribute1 = obj.m_attribute1;
			m_attribute2 = obj.m_attribute2;
			m_attribute3 = obj.m_attribute3;
			m_attribute4 = obj.m_attribute4;
			m_attribute5 = obj.m_attribute5;
			m_attribute6 = obj.m_attribute6;
			m_attribute7 = obj.m_attribute7;
			m_listOfMyStringList = obj.m_listOfMyStringList;
			return (*this);
		}
	
		int32_t Test6::ID() {
			return 6;
		}
	
		const string Test6::ShortName() {
			return "Test6";
		}
	
		const string Test6::LongName() {
			return "testpackage.Test6";
		}
	
		int32_t Test6::getID() const {
			return Test6::ID();
		}
	
		const string Test6::getShortName() const {
			return Test6::ShortName();
		}
	
		const string Test6::getLongName() const {
			return Test6::LongName();
		}
	
		bool Test6::getAttribute1() const {
			return m_attribute1;
		}
		
		void Test6::setAttribute1(const bool &val) {
			m_attribute1 = val;
		}
		char Test6::getAttribute2() const {
			return m_attribute2;
		}
		
		void Test6::setAttribute2(const char &val) {
			m_attribute2 = val;
		}
		int32_t Test6::getAttribute3() const {
			return m_attribute3;
		}
		
		void Test6::setAttribute3(const int32_t &val) {
			m_attribute3 = val;
		}
		uint32_t Test6::getAttribute4() const {
			return m_attribute4;
		}
		
		void Test6::setAttribute4(const uint32_t &val) {
			m_attribute4 = val;
		}
		float Test6::getAttribute5() const {
			return m_attribute5;
		}
		
		void Test6::setAttribute5(const float &val) {
			m_attribute5 = val;
		}
		double Test6::getAttribute6() const {
			return m_attribute6;
		}
		
		void Test6::setAttribute6(const double &val) {
			m_attribute6 = val;
		}
		std::string Test6::getAttribute7() const {
			return m_attribute7;
		}
		
		void Test6::setAttribute7(const std::string &val) {
			m_attribute7 = val;
		}
		std::vector<std::string> Test6::getListOfMyStringList() const {
			return m_listOfMyStringList;
		}
		
		void Test6::setListOfMyStringList(const std::vector<std::string> &val) {
			m_listOfMyStringList = val;
		}
		
		void Test6::clear_ListOfMyStringList() {
			m_listOfMyStringList.clear();
		}
		
		uint32_t Test6::getSize_ListOfMyStringList() const {
			return m_listOfMyStringList.size();
		}
		
		bool Test6::isEmpty_ListOfMyStringList() const {
			return m_listOfMyStringList.empty();
		}
		
		void Test6::addTo_ListOfMyStringList(const std::string &val) {
			m_listOfMyStringList.push_back(val);
		}
		
		void Test6::insertTo_ListOfMyStringList(const std::string &val) {
			m_listOfMyStringList.insert(m_listOfMyStringList.begin(), val);
		}
		
		bool Test6::contains_ListOfMyStringList(const std::string &val) const {
			return std::find(m_listOfMyStringList.begin(), m_listOfMyStringList.end(), val) != m_listOfMyStringList.end();
		}
		
		std::pair<std::vector<std::string>::iterator, std::vector<std::string>::iterator> Test6::iteratorPair_ListOfMyStringList() {
			return std::make_pair(m_listOfMyStringList.begin(), m_listOfMyStringList.end());
		}
	
		void Test6::accept(odcore::base::Visitor &v) {
			v.beginVisit();
			v.visit(1, "Test6.attribute1", "attribute1", m_attribute1);
			v.visit(2, "Test6.attribute2", "attribute2", m_attribute2);
			v.visit(3, "Test6.attribute3", "attribute3", m_attribute3);
			v.visit(4, "Test6.attribute4", "attribute4", m_attribute4);
			v.visit(5, "Test6.attribute5", "attribute5", m_attribute5);
			v.visit(6, "Test6.attribute6", "attribute6", m_attribute6);
			v.visit(7, "Test6.attribute7", "attribute7", m_attribute7);
			v.endVisit();
		}
	
		const string Test6::toString() const {
			stringstream s;
	
			s << "Attribute1: " << getAttribute1() << " ";
			s << "Attribute2: " << getAttribute2() << " ";
			s << "Attribute3: " << getAttribute3() << " ";
			s << "Attribute4: " << getAttribute4() << " ";
			s << "Attribute5: " << getAttribute5() << " ";
			s << "Attribute6: " << getAttribute6() << " ";
			s << "Attribute7: " << getAttribute7() << " ";
			s << "Number of elements in list of MyStringList: " << getSize_ListOfMyStringList() << " ";
	
			return s.str();
		}
	
		ostream& Test6::operator<<(ostream &out) const {
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			std::shared_ptr<Serializer> s = sf.getSerializer(out);
	
			s->write(1,
					m_attribute1);
			s->write(2,
					m_attribute2);
			s->write(3,
					m_attribute3);
			s->write(4,
					m_attribute4);
			s->write(5,
					m_attribute5);
			s->write(6,
					m_attribute6);
			s->write(7,
					m_attribute7);
			// Store elements from m_listOfMyStringList into a string.
			{
				const uint32_t numberOfMyStringList = static_cast<uint32_t>(m_listOfMyStringList.size());
				std::stringstream sstr_MyStringList;
				{
					for(uint32_t i = 0; i < numberOfMyStringList; i++) {
						s->writeValue(sstr_MyStringList, m_listOfMyStringList.at(i));
					}
				}
				const std::string str_sstr_MyStringList = sstr_MyStringList.str();
				s->write(8, str_sstr_MyStringList);
			}
			return out;
		}
	
		istream& Test6::operator>>(istream &in) {
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
	
			d->read(1,
					m_attribute1);
			d->read(2,
					m_attribute2);
			d->read(3,
					m_attribute3);
			d->read(4,
					m_attribute4);
			d->read(5,
					m_attribute5);
			d->read(6,
					m_attribute6);
			d->read(7,
					m_attribute7);
			// Restore elements from a string into m_listOfMyStringList.
			{
				// Clean up the existing list of MyStringList.
				m_listOfMyStringList.clear();
				std::string str_MyStringList;
				d->read(8, str_MyStringList);
				if (str_MyStringList.size() > 0) {
					std::stringstream sstr_str_MyStringList(str_MyStringList);
					uint32_t length = str_MyStringList.size();
					while (length > 0) {
						std::string element;
						length -= d->readValue(sstr_str_MyStringList, element);
						m_listOfMyStringList.push_back(element);
					}
				}
			}
			return in;
		}
} // testpackage
