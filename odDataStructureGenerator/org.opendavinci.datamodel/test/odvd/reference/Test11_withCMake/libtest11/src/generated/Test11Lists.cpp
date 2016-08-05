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

#include "test11/generated/Test11Lists.h"

	using namespace std;
	using namespace odcore::base;
	using namespace odcore::serialization;


	Test11Lists::Test11Lists() :
	    SerializableData(), Visitable()
		, m_listOfMyBoolList()
		, m_listOfMyCharList()
		, m_listOfMyInt32List()
		, m_listOfMyUint32List()
		, m_listOfMyFloatList()
		, m_listOfMyDoubleList()
		, m_listOfMyStringList()
	{
	}

	Test11Lists::Test11Lists(
		const vector<bool> &val0, 
		const vector<char> &val1, 
		const vector<int32_t> &val2, 
		const vector<uint32_t> &val3, 
		const vector<float> &val4, 
		const vector<double> &val5, 
		const vector<std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_listOfMyBoolList(val0)
		, m_listOfMyCharList(val1)
		, m_listOfMyInt32List(val2)
		, m_listOfMyUint32List(val3)
		, m_listOfMyFloatList(val4)
		, m_listOfMyDoubleList(val5)
		, m_listOfMyStringList(val6)
	{
	}

	Test11Lists::Test11Lists(const Test11Lists &obj) :
	    SerializableData(), Visitable()
		, m_listOfMyBoolList(obj.m_listOfMyBoolList)
		, m_listOfMyCharList(obj.m_listOfMyCharList)
		, m_listOfMyInt32List(obj.m_listOfMyInt32List)
		, m_listOfMyUint32List(obj.m_listOfMyUint32List)
		, m_listOfMyFloatList(obj.m_listOfMyFloatList)
		, m_listOfMyDoubleList(obj.m_listOfMyDoubleList)
		, m_listOfMyStringList(obj.m_listOfMyStringList)
	{
	}
	
	Test11Lists::~Test11Lists() {
	}

	Test11Lists& Test11Lists::operator=(const Test11Lists &obj) {
		m_listOfMyBoolList = obj.m_listOfMyBoolList;
		m_listOfMyCharList = obj.m_listOfMyCharList;
		m_listOfMyInt32List = obj.m_listOfMyInt32List;
		m_listOfMyUint32List = obj.m_listOfMyUint32List;
		m_listOfMyFloatList = obj.m_listOfMyFloatList;
		m_listOfMyDoubleList = obj.m_listOfMyDoubleList;
		m_listOfMyStringList = obj.m_listOfMyStringList;
		return (*this);
	}

	int32_t Test11Lists::ID() {
		return 12;
	}

	const string Test11Lists::ShortName() {
		return "Test11Lists";
	}

	const string Test11Lists::LongName() {
		return "Test11Lists";
	}

	int32_t Test11Lists::getID() const {
		return Test11Lists::ID();
	}

	const string Test11Lists::getShortName() const {
		return Test11Lists::ShortName();
	}

	const string Test11Lists::getLongName() const {
		return Test11Lists::LongName();
	}

	std::vector<bool> Test11Lists::getListOfMyBoolList() const {
		return m_listOfMyBoolList;
	}
	
	void Test11Lists::setListOfMyBoolList(const std::vector<bool> &val) {
		m_listOfMyBoolList = val;
	}
	
	void Test11Lists::clear_ListOfMyBoolList() {
		m_listOfMyBoolList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyBoolList() const {
		return m_listOfMyBoolList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyBoolList() const {
		return m_listOfMyBoolList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyBoolList(const bool &val) {
		m_listOfMyBoolList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyBoolList(const bool &val) {
		m_listOfMyBoolList.insert(m_listOfMyBoolList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyBoolList(const bool &val) const {
		return std::find(m_listOfMyBoolList.begin(), m_listOfMyBoolList.end(), val) != m_listOfMyBoolList.end();
	}
	
	std::pair<std::vector<bool>::iterator, std::vector<bool>::iterator> Test11Lists::iteratorPair_ListOfMyBoolList() {
		return std::make_pair(m_listOfMyBoolList.begin(), m_listOfMyBoolList.end());
	}
	std::vector<char> Test11Lists::getListOfMyCharList() const {
		return m_listOfMyCharList;
	}
	
	void Test11Lists::setListOfMyCharList(const std::vector<char> &val) {
		m_listOfMyCharList = val;
	}
	
	void Test11Lists::clear_ListOfMyCharList() {
		m_listOfMyCharList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyCharList() const {
		return m_listOfMyCharList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyCharList() const {
		return m_listOfMyCharList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyCharList(const char &val) {
		m_listOfMyCharList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyCharList(const char &val) {
		m_listOfMyCharList.insert(m_listOfMyCharList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyCharList(const char &val) const {
		return std::find(m_listOfMyCharList.begin(), m_listOfMyCharList.end(), val) != m_listOfMyCharList.end();
	}
	
	std::pair<std::vector<char>::iterator, std::vector<char>::iterator> Test11Lists::iteratorPair_ListOfMyCharList() {
		return std::make_pair(m_listOfMyCharList.begin(), m_listOfMyCharList.end());
	}
	std::vector<int32_t> Test11Lists::getListOfMyInt32List() const {
		return m_listOfMyInt32List;
	}
	
	void Test11Lists::setListOfMyInt32List(const std::vector<int32_t> &val) {
		m_listOfMyInt32List = val;
	}
	
	void Test11Lists::clear_ListOfMyInt32List() {
		m_listOfMyInt32List.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyInt32List() const {
		return m_listOfMyInt32List.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyInt32List() const {
		return m_listOfMyInt32List.empty();
	}
	
	void Test11Lists::addTo_ListOfMyInt32List(const int32_t &val) {
		m_listOfMyInt32List.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyInt32List(const int32_t &val) {
		m_listOfMyInt32List.insert(m_listOfMyInt32List.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyInt32List(const int32_t &val) const {
		return std::find(m_listOfMyInt32List.begin(), m_listOfMyInt32List.end(), val) != m_listOfMyInt32List.end();
	}
	
	std::pair<std::vector<int32_t>::iterator, std::vector<int32_t>::iterator> Test11Lists::iteratorPair_ListOfMyInt32List() {
		return std::make_pair(m_listOfMyInt32List.begin(), m_listOfMyInt32List.end());
	}
	std::vector<uint32_t> Test11Lists::getListOfMyUint32List() const {
		return m_listOfMyUint32List;
	}
	
	void Test11Lists::setListOfMyUint32List(const std::vector<uint32_t> &val) {
		m_listOfMyUint32List = val;
	}
	
	void Test11Lists::clear_ListOfMyUint32List() {
		m_listOfMyUint32List.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyUint32List() const {
		return m_listOfMyUint32List.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyUint32List() const {
		return m_listOfMyUint32List.empty();
	}
	
	void Test11Lists::addTo_ListOfMyUint32List(const uint32_t &val) {
		m_listOfMyUint32List.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyUint32List(const uint32_t &val) {
		m_listOfMyUint32List.insert(m_listOfMyUint32List.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyUint32List(const uint32_t &val) const {
		return std::find(m_listOfMyUint32List.begin(), m_listOfMyUint32List.end(), val) != m_listOfMyUint32List.end();
	}
	
	std::pair<std::vector<uint32_t>::iterator, std::vector<uint32_t>::iterator> Test11Lists::iteratorPair_ListOfMyUint32List() {
		return std::make_pair(m_listOfMyUint32List.begin(), m_listOfMyUint32List.end());
	}
	std::vector<float> Test11Lists::getListOfMyFloatList() const {
		return m_listOfMyFloatList;
	}
	
	void Test11Lists::setListOfMyFloatList(const std::vector<float> &val) {
		m_listOfMyFloatList = val;
	}
	
	void Test11Lists::clear_ListOfMyFloatList() {
		m_listOfMyFloatList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyFloatList() const {
		return m_listOfMyFloatList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyFloatList() const {
		return m_listOfMyFloatList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyFloatList(const float &val) {
		m_listOfMyFloatList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyFloatList(const float &val) {
		m_listOfMyFloatList.insert(m_listOfMyFloatList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyFloatList(const float &val) const {
		return std::find(m_listOfMyFloatList.begin(), m_listOfMyFloatList.end(), val) != m_listOfMyFloatList.end();
	}
	
	std::pair<std::vector<float>::iterator, std::vector<float>::iterator> Test11Lists::iteratorPair_ListOfMyFloatList() {
		return std::make_pair(m_listOfMyFloatList.begin(), m_listOfMyFloatList.end());
	}
	std::vector<double> Test11Lists::getListOfMyDoubleList() const {
		return m_listOfMyDoubleList;
	}
	
	void Test11Lists::setListOfMyDoubleList(const std::vector<double> &val) {
		m_listOfMyDoubleList = val;
	}
	
	void Test11Lists::clear_ListOfMyDoubleList() {
		m_listOfMyDoubleList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyDoubleList() const {
		return m_listOfMyDoubleList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyDoubleList() const {
		return m_listOfMyDoubleList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyDoubleList(const double &val) {
		m_listOfMyDoubleList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyDoubleList(const double &val) {
		m_listOfMyDoubleList.insert(m_listOfMyDoubleList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyDoubleList(const double &val) const {
		return std::find(m_listOfMyDoubleList.begin(), m_listOfMyDoubleList.end(), val) != m_listOfMyDoubleList.end();
	}
	
	std::pair<std::vector<double>::iterator, std::vector<double>::iterator> Test11Lists::iteratorPair_ListOfMyDoubleList() {
		return std::make_pair(m_listOfMyDoubleList.begin(), m_listOfMyDoubleList.end());
	}
	std::vector<std::string> Test11Lists::getListOfMyStringList() const {
		return m_listOfMyStringList;
	}
	
	void Test11Lists::setListOfMyStringList(const std::vector<std::string> &val) {
		m_listOfMyStringList = val;
	}
	
	void Test11Lists::clear_ListOfMyStringList() {
		m_listOfMyStringList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyStringList() const {
		return m_listOfMyStringList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyStringList() const {
		return m_listOfMyStringList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyStringList(const std::string &val) {
		m_listOfMyStringList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyStringList(const std::string &val) {
		m_listOfMyStringList.insert(m_listOfMyStringList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyStringList(const std::string &val) const {
		return std::find(m_listOfMyStringList.begin(), m_listOfMyStringList.end(), val) != m_listOfMyStringList.end();
	}
	
	std::pair<std::vector<std::string>::iterator, std::vector<std::string>::iterator> Test11Lists::iteratorPair_ListOfMyStringList() {
		return std::make_pair(m_listOfMyStringList.begin(), m_listOfMyStringList.end());
	}

	void Test11Lists::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test11Lists::toString() const {
		stringstream s;

		s << "Number of elements in list of MyBoolList: " << getSize_ListOfMyBoolList() << " ";
		s << "Number of elements in list of MyCharList: " << getSize_ListOfMyCharList() << " ";
		s << "Number of elements in list of MyInt32List: " << getSize_ListOfMyInt32List() << " ";
		s << "Number of elements in list of MyUint32List: " << getSize_ListOfMyUint32List() << " ";
		s << "Number of elements in list of MyFloatList: " << getSize_ListOfMyFloatList() << " ";
		s << "Number of elements in list of MyDoubleList: " << getSize_ListOfMyDoubleList() << " ";
		s << "Number of elements in list of MyStringList: " << getSize_ListOfMyStringList() << " ";

		return s.str();
	}

	ostream& Test11Lists::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		// Store elements from m_listOfMyBoolList into a string.
		{
			const uint32_t numberOfMyBoolList = static_cast<uint32_t>(m_listOfMyBoolList.size());
			std::stringstream sstr_MyBoolList;
			{
				for(uint32_t i = 0; i < numberOfMyBoolList; i++) {
					s->writeValue(sstr_MyBoolList, m_listOfMyBoolList.at(i));
				}
			}
			const std::string str_sstr_MyBoolList = sstr_MyBoolList.str();
			s->write(1, str_sstr_MyBoolList);
		}
		// Store elements from m_listOfMyCharList into a string.
		{
			const uint32_t numberOfMyCharList = static_cast<uint32_t>(m_listOfMyCharList.size());
			std::stringstream sstr_MyCharList;
			{
				for(uint32_t i = 0; i < numberOfMyCharList; i++) {
					s->writeValue(sstr_MyCharList, m_listOfMyCharList.at(i));
				}
			}
			const std::string str_sstr_MyCharList = sstr_MyCharList.str();
			s->write(2, str_sstr_MyCharList);
		}
		// Store elements from m_listOfMyInt32List into a string.
		{
			const uint32_t numberOfMyInt32List = static_cast<uint32_t>(m_listOfMyInt32List.size());
			std::stringstream sstr_MyInt32List;
			{
				for(uint32_t i = 0; i < numberOfMyInt32List; i++) {
					s->writeValue(sstr_MyInt32List, m_listOfMyInt32List.at(i));
				}
			}
			const std::string str_sstr_MyInt32List = sstr_MyInt32List.str();
			s->write(3, str_sstr_MyInt32List);
		}
		// Store elements from m_listOfMyUint32List into a string.
		{
			const uint32_t numberOfMyUint32List = static_cast<uint32_t>(m_listOfMyUint32List.size());
			std::stringstream sstr_MyUint32List;
			{
				for(uint32_t i = 0; i < numberOfMyUint32List; i++) {
					s->writeValue(sstr_MyUint32List, m_listOfMyUint32List.at(i));
				}
			}
			const std::string str_sstr_MyUint32List = sstr_MyUint32List.str();
			s->write(4, str_sstr_MyUint32List);
		}
		// Store elements from m_listOfMyFloatList into a string.
		{
			const uint32_t numberOfMyFloatList = static_cast<uint32_t>(m_listOfMyFloatList.size());
			std::stringstream sstr_MyFloatList;
			{
				for(uint32_t i = 0; i < numberOfMyFloatList; i++) {
					s->writeValue(sstr_MyFloatList, m_listOfMyFloatList.at(i));
				}
			}
			const std::string str_sstr_MyFloatList = sstr_MyFloatList.str();
			s->write(5, str_sstr_MyFloatList);
		}
		// Store elements from m_listOfMyDoubleList into a string.
		{
			const uint32_t numberOfMyDoubleList = static_cast<uint32_t>(m_listOfMyDoubleList.size());
			std::stringstream sstr_MyDoubleList;
			{
				for(uint32_t i = 0; i < numberOfMyDoubleList; i++) {
					s->writeValue(sstr_MyDoubleList, m_listOfMyDoubleList.at(i));
				}
			}
			const std::string str_sstr_MyDoubleList = sstr_MyDoubleList.str();
			s->write(6, str_sstr_MyDoubleList);
		}
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
			s->write(7, str_sstr_MyStringList);
		}
		return out;
	}

	istream& Test11Lists::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore elements from a string into m_listOfMyBoolList.
		{
			// Clean up the existing list of MyBoolList.
			m_listOfMyBoolList.clear();
			std::string str_MyBoolList;
			d->read(1, str_MyBoolList);
			if (str_MyBoolList.size() > 0) {
				std::stringstream sstr_str_MyBoolList(str_MyBoolList);
				uint32_t length = str_MyBoolList.size();
				while (length > 0) {
					bool element;
					length -= d->readValue(sstr_str_MyBoolList, element);
					m_listOfMyBoolList.push_back(element);
				}
			}
		}
		// Restore elements from a string into m_listOfMyCharList.
		{
			// Clean up the existing list of MyCharList.
			m_listOfMyCharList.clear();
			std::string str_MyCharList;
			d->read(2, str_MyCharList);
			if (str_MyCharList.size() > 0) {
				std::stringstream sstr_str_MyCharList(str_MyCharList);
				uint32_t length = str_MyCharList.size();
				while (length > 0) {
					char element;
					length -= d->readValue(sstr_str_MyCharList, element);
					m_listOfMyCharList.push_back(element);
				}
			}
		}
		// Restore elements from a string into m_listOfMyInt32List.
		{
			// Clean up the existing list of MyInt32List.
			m_listOfMyInt32List.clear();
			std::string str_MyInt32List;
			d->read(3, str_MyInt32List);
			if (str_MyInt32List.size() > 0) {
				std::stringstream sstr_str_MyInt32List(str_MyInt32List);
				uint32_t length = str_MyInt32List.size();
				while (length > 0) {
					int32_t element;
					length -= d->readValue(sstr_str_MyInt32List, element);
					m_listOfMyInt32List.push_back(element);
				}
			}
		}
		// Restore elements from a string into m_listOfMyUint32List.
		{
			// Clean up the existing list of MyUint32List.
			m_listOfMyUint32List.clear();
			std::string str_MyUint32List;
			d->read(4, str_MyUint32List);
			if (str_MyUint32List.size() > 0) {
				std::stringstream sstr_str_MyUint32List(str_MyUint32List);
				uint32_t length = str_MyUint32List.size();
				while (length > 0) {
					uint32_t element;
					length -= d->readValue(sstr_str_MyUint32List, element);
					m_listOfMyUint32List.push_back(element);
				}
			}
		}
		// Restore elements from a string into m_listOfMyFloatList.
		{
			// Clean up the existing list of MyFloatList.
			m_listOfMyFloatList.clear();
			std::string str_MyFloatList;
			d->read(5, str_MyFloatList);
			if (str_MyFloatList.size() > 0) {
				std::stringstream sstr_str_MyFloatList(str_MyFloatList);
				uint32_t length = str_MyFloatList.size();
				while (length > 0) {
					float element;
					length -= d->readValue(sstr_str_MyFloatList, element);
					m_listOfMyFloatList.push_back(element);
				}
			}
		}
		// Restore elements from a string into m_listOfMyDoubleList.
		{
			// Clean up the existing list of MyDoubleList.
			m_listOfMyDoubleList.clear();
			std::string str_MyDoubleList;
			d->read(6, str_MyDoubleList);
			if (str_MyDoubleList.size() > 0) {
				std::stringstream sstr_str_MyDoubleList(str_MyDoubleList);
				uint32_t length = str_MyDoubleList.size();
				while (length > 0) {
					double element;
					length -= d->readValue(sstr_str_MyDoubleList, element);
					m_listOfMyDoubleList.push_back(element);
				}
			}
		}
		// Restore elements from a string into m_listOfMyStringList.
		{
			// Clean up the existing list of MyStringList.
			m_listOfMyStringList.clear();
			std::string str_MyStringList;
			d->read(7, str_MyStringList);
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
