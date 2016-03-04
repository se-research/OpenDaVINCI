/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>
#include <algorithm>
#include <sstream>
#include <utility>

#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"


#include "test12/generated/Test12Lists.h"

	using namespace std;
	using namespace odcore::base;


	Test12Lists::Test12Lists() :
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

	Test12Lists::Test12Lists(
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

	Test12Lists::Test12Lists(const Test12Lists &obj) :
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
	
	Test12Lists::~Test12Lists() {
	}

	Test12Lists& Test12Lists::operator=(const Test12Lists &obj) {
		m_listOfMyBoolList = obj.m_listOfMyBoolList;
		m_listOfMyCharList = obj.m_listOfMyCharList;
		m_listOfMyInt32List = obj.m_listOfMyInt32List;
		m_listOfMyUint32List = obj.m_listOfMyUint32List;
		m_listOfMyFloatList = obj.m_listOfMyFloatList;
		m_listOfMyDoubleList = obj.m_listOfMyDoubleList;
		m_listOfMyStringList = obj.m_listOfMyStringList;
		return (*this);
	}

	int32_t Test12Lists::ID() {
		return 13;
	}

	const string Test12Lists::ShortName() {
		return "Test12Lists";
	}

	const string Test12Lists::LongName() {
		return "Test12Lists";
	}

	int32_t Test12Lists::getID() const {
		return Test12Lists::ID();
	}

	const string Test12Lists::getShortName() const {
		return Test12Lists::ShortName();
	}

	const string Test12Lists::getLongName() const {
		return Test12Lists::LongName();
	}

	std::vector<bool> Test12Lists::getListOfMyBoolList() const {
		return m_listOfMyBoolList;
	}
	
	void Test12Lists::setListOfMyBoolList(const std::vector<bool> &val) {
		m_listOfMyBoolList = val;
	}
	
	void Test12Lists::clear_ListOfMyBoolList() {
		m_listOfMyBoolList.clear();
	}
	
	uint32_t Test12Lists::getSize_ListOfMyBoolList() const {
		return m_listOfMyBoolList.size();
	}
	
	bool Test12Lists::isEmpty_ListOfMyBoolList() const {
		return m_listOfMyBoolList.empty();
	}
	
	void Test12Lists::addTo_ListOfMyBoolList(const bool &val) {
		m_listOfMyBoolList.push_back(val);
	}
	
	void Test12Lists::insertTo_ListOfMyBoolList(const bool &val) {
		m_listOfMyBoolList.insert(m_listOfMyBoolList.begin(), val);
	}
	
	bool Test12Lists::contains_ListOfMyBoolList(const bool &val) const {
		return std::find(m_listOfMyBoolList.begin(), m_listOfMyBoolList.end(), val) != m_listOfMyBoolList.end();
	}
	
	std::pair<std::vector<bool>::iterator, std::vector<bool>::iterator> Test12Lists::iteratorPair_ListOfMyBoolList() {
		return std::make_pair(m_listOfMyBoolList.begin(), m_listOfMyBoolList.end());
	}
	std::vector<char> Test12Lists::getListOfMyCharList() const {
		return m_listOfMyCharList;
	}
	
	void Test12Lists::setListOfMyCharList(const std::vector<char> &val) {
		m_listOfMyCharList = val;
	}
	
	void Test12Lists::clear_ListOfMyCharList() {
		m_listOfMyCharList.clear();
	}
	
	uint32_t Test12Lists::getSize_ListOfMyCharList() const {
		return m_listOfMyCharList.size();
	}
	
	bool Test12Lists::isEmpty_ListOfMyCharList() const {
		return m_listOfMyCharList.empty();
	}
	
	void Test12Lists::addTo_ListOfMyCharList(const char &val) {
		m_listOfMyCharList.push_back(val);
	}
	
	void Test12Lists::insertTo_ListOfMyCharList(const char &val) {
		m_listOfMyCharList.insert(m_listOfMyCharList.begin(), val);
	}
	
	bool Test12Lists::contains_ListOfMyCharList(const char &val) const {
		return std::find(m_listOfMyCharList.begin(), m_listOfMyCharList.end(), val) != m_listOfMyCharList.end();
	}
	
	std::pair<std::vector<char>::iterator, std::vector<char>::iterator> Test12Lists::iteratorPair_ListOfMyCharList() {
		return std::make_pair(m_listOfMyCharList.begin(), m_listOfMyCharList.end());
	}
	std::vector<int32_t> Test12Lists::getListOfMyInt32List() const {
		return m_listOfMyInt32List;
	}
	
	void Test12Lists::setListOfMyInt32List(const std::vector<int32_t> &val) {
		m_listOfMyInt32List = val;
	}
	
	void Test12Lists::clear_ListOfMyInt32List() {
		m_listOfMyInt32List.clear();
	}
	
	uint32_t Test12Lists::getSize_ListOfMyInt32List() const {
		return m_listOfMyInt32List.size();
	}
	
	bool Test12Lists::isEmpty_ListOfMyInt32List() const {
		return m_listOfMyInt32List.empty();
	}
	
	void Test12Lists::addTo_ListOfMyInt32List(const int32_t &val) {
		m_listOfMyInt32List.push_back(val);
	}
	
	void Test12Lists::insertTo_ListOfMyInt32List(const int32_t &val) {
		m_listOfMyInt32List.insert(m_listOfMyInt32List.begin(), val);
	}
	
	bool Test12Lists::contains_ListOfMyInt32List(const int32_t &val) const {
		return std::find(m_listOfMyInt32List.begin(), m_listOfMyInt32List.end(), val) != m_listOfMyInt32List.end();
	}
	
	std::pair<std::vector<int32_t>::iterator, std::vector<int32_t>::iterator> Test12Lists::iteratorPair_ListOfMyInt32List() {
		return std::make_pair(m_listOfMyInt32List.begin(), m_listOfMyInt32List.end());
	}
	std::vector<uint32_t> Test12Lists::getListOfMyUint32List() const {
		return m_listOfMyUint32List;
	}
	
	void Test12Lists::setListOfMyUint32List(const std::vector<uint32_t> &val) {
		m_listOfMyUint32List = val;
	}
	
	void Test12Lists::clear_ListOfMyUint32List() {
		m_listOfMyUint32List.clear();
	}
	
	uint32_t Test12Lists::getSize_ListOfMyUint32List() const {
		return m_listOfMyUint32List.size();
	}
	
	bool Test12Lists::isEmpty_ListOfMyUint32List() const {
		return m_listOfMyUint32List.empty();
	}
	
	void Test12Lists::addTo_ListOfMyUint32List(const uint32_t &val) {
		m_listOfMyUint32List.push_back(val);
	}
	
	void Test12Lists::insertTo_ListOfMyUint32List(const uint32_t &val) {
		m_listOfMyUint32List.insert(m_listOfMyUint32List.begin(), val);
	}
	
	bool Test12Lists::contains_ListOfMyUint32List(const uint32_t &val) const {
		return std::find(m_listOfMyUint32List.begin(), m_listOfMyUint32List.end(), val) != m_listOfMyUint32List.end();
	}
	
	std::pair<std::vector<uint32_t>::iterator, std::vector<uint32_t>::iterator> Test12Lists::iteratorPair_ListOfMyUint32List() {
		return std::make_pair(m_listOfMyUint32List.begin(), m_listOfMyUint32List.end());
	}
	std::vector<float> Test12Lists::getListOfMyFloatList() const {
		return m_listOfMyFloatList;
	}
	
	void Test12Lists::setListOfMyFloatList(const std::vector<float> &val) {
		m_listOfMyFloatList = val;
	}
	
	void Test12Lists::clear_ListOfMyFloatList() {
		m_listOfMyFloatList.clear();
	}
	
	uint32_t Test12Lists::getSize_ListOfMyFloatList() const {
		return m_listOfMyFloatList.size();
	}
	
	bool Test12Lists::isEmpty_ListOfMyFloatList() const {
		return m_listOfMyFloatList.empty();
	}
	
	void Test12Lists::addTo_ListOfMyFloatList(const float &val) {
		m_listOfMyFloatList.push_back(val);
	}
	
	void Test12Lists::insertTo_ListOfMyFloatList(const float &val) {
		m_listOfMyFloatList.insert(m_listOfMyFloatList.begin(), val);
	}
	
	bool Test12Lists::contains_ListOfMyFloatList(const float &val) const {
		return std::find(m_listOfMyFloatList.begin(), m_listOfMyFloatList.end(), val) != m_listOfMyFloatList.end();
	}
	
	std::pair<std::vector<float>::iterator, std::vector<float>::iterator> Test12Lists::iteratorPair_ListOfMyFloatList() {
		return std::make_pair(m_listOfMyFloatList.begin(), m_listOfMyFloatList.end());
	}
	std::vector<double> Test12Lists::getListOfMyDoubleList() const {
		return m_listOfMyDoubleList;
	}
	
	void Test12Lists::setListOfMyDoubleList(const std::vector<double> &val) {
		m_listOfMyDoubleList = val;
	}
	
	void Test12Lists::clear_ListOfMyDoubleList() {
		m_listOfMyDoubleList.clear();
	}
	
	uint32_t Test12Lists::getSize_ListOfMyDoubleList() const {
		return m_listOfMyDoubleList.size();
	}
	
	bool Test12Lists::isEmpty_ListOfMyDoubleList() const {
		return m_listOfMyDoubleList.empty();
	}
	
	void Test12Lists::addTo_ListOfMyDoubleList(const double &val) {
		m_listOfMyDoubleList.push_back(val);
	}
	
	void Test12Lists::insertTo_ListOfMyDoubleList(const double &val) {
		m_listOfMyDoubleList.insert(m_listOfMyDoubleList.begin(), val);
	}
	
	bool Test12Lists::contains_ListOfMyDoubleList(const double &val) const {
		return std::find(m_listOfMyDoubleList.begin(), m_listOfMyDoubleList.end(), val) != m_listOfMyDoubleList.end();
	}
	
	std::pair<std::vector<double>::iterator, std::vector<double>::iterator> Test12Lists::iteratorPair_ListOfMyDoubleList() {
		return std::make_pair(m_listOfMyDoubleList.begin(), m_listOfMyDoubleList.end());
	}
	std::vector<std::string> Test12Lists::getListOfMyStringList() const {
		return m_listOfMyStringList;
	}
	
	void Test12Lists::setListOfMyStringList(const std::vector<std::string> &val) {
		m_listOfMyStringList = val;
	}
	
	void Test12Lists::clear_ListOfMyStringList() {
		m_listOfMyStringList.clear();
	}
	
	uint32_t Test12Lists::getSize_ListOfMyStringList() const {
		return m_listOfMyStringList.size();
	}
	
	bool Test12Lists::isEmpty_ListOfMyStringList() const {
		return m_listOfMyStringList.empty();
	}
	
	void Test12Lists::addTo_ListOfMyStringList(const std::string &val) {
		m_listOfMyStringList.push_back(val);
	}
	
	void Test12Lists::insertTo_ListOfMyStringList(const std::string &val) {
		m_listOfMyStringList.insert(m_listOfMyStringList.begin(), val);
	}
	
	bool Test12Lists::contains_ListOfMyStringList(const std::string &val) const {
		return std::find(m_listOfMyStringList.begin(), m_listOfMyStringList.end(), val) != m_listOfMyStringList.end();
	}
	
	std::pair<std::vector<std::string>::iterator, std::vector<std::string>::iterator> Test12Lists::iteratorPair_ListOfMyStringList() {
		return std::make_pair(m_listOfMyStringList.begin(), m_listOfMyStringList.end());
	}

	void Test12Lists::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test12Lists::toString() const {
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

	ostream& Test12Lists::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		// Write number of elements in m_listOfMyBoolList.
		const uint32_t numberOfMyBoolList = static_cast<uint32_t>(m_listOfMyBoolList.size());
		s->write(1, numberOfMyBoolList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyBoolList;
		for (uint32_t i = 0; i < numberOfMyBoolList; i++) {
		    sstrOfMyBoolList << m_listOfMyBoolList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyBoolList > 0) {
			s->write(1 + 7, sstrOfMyBoolList.str());
		}
		// Write number of elements in m_listOfMyCharList.
		const uint32_t numberOfMyCharList = static_cast<uint32_t>(m_listOfMyCharList.size());
		s->write(2, numberOfMyCharList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyCharList;
		for (uint32_t i = 0; i < numberOfMyCharList; i++) {
		    sstrOfMyCharList << m_listOfMyCharList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyCharList > 0) {
			s->write(2 + 7, sstrOfMyCharList.str());
		}
		// Write number of elements in m_listOfMyInt32List.
		const uint32_t numberOfMyInt32List = static_cast<uint32_t>(m_listOfMyInt32List.size());
		s->write(3, numberOfMyInt32List);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyInt32List;
		for (uint32_t i = 0; i < numberOfMyInt32List; i++) {
		    sstrOfMyInt32List << m_listOfMyInt32List.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyInt32List > 0) {
			s->write(3 + 7, sstrOfMyInt32List.str());
		}
		// Write number of elements in m_listOfMyUint32List.
		const uint32_t numberOfMyUint32List = static_cast<uint32_t>(m_listOfMyUint32List.size());
		s->write(4, numberOfMyUint32List);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyUint32List;
		for (uint32_t i = 0; i < numberOfMyUint32List; i++) {
		    sstrOfMyUint32List << m_listOfMyUint32List.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyUint32List > 0) {
			s->write(4 + 7, sstrOfMyUint32List.str());
		}
		// Write number of elements in m_listOfMyFloatList.
		const uint32_t numberOfMyFloatList = static_cast<uint32_t>(m_listOfMyFloatList.size());
		s->write(5, numberOfMyFloatList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyFloatList;
		for (uint32_t i = 0; i < numberOfMyFloatList; i++) {
		    sstrOfMyFloatList << m_listOfMyFloatList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyFloatList > 0) {
			s->write(5 + 7, sstrOfMyFloatList.str());
		}
		// Write number of elements in m_listOfMyDoubleList.
		const uint32_t numberOfMyDoubleList = static_cast<uint32_t>(m_listOfMyDoubleList.size());
		s->write(6, numberOfMyDoubleList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyDoubleList;
		for (uint32_t i = 0; i < numberOfMyDoubleList; i++) {
		    sstrOfMyDoubleList << m_listOfMyDoubleList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyDoubleList > 0) {
			s->write(6 + 7, sstrOfMyDoubleList.str());
		}
		// Write number of elements in m_listOfMyStringList.
		const uint32_t numberOfMyStringList = static_cast<uint32_t>(m_listOfMyStringList.size());
		s->write(7, numberOfMyStringList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyStringList;
		for (uint32_t i = 0; i < numberOfMyStringList; i++) {
		    sstrOfMyStringList << m_listOfMyStringList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyStringList > 0) {
			s->write(7 + 7, sstrOfMyStringList.str());
		}
		return out;
	}

	istream& Test12Lists::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing list of MyBoolList.
		m_listOfMyBoolList.clear();
		
		// Read number of elements in m_listOfMyBoolList.
		uint32_t numberOfMyBoolList = 0;
		d->read(1, numberOfMyBoolList);
		
		if (numberOfMyBoolList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(1 + 7, elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyBoolList; i++) {
		        bool element;
		        sstr >> element;
		        m_listOfMyBoolList.push_back(element);
		    }
		}
		// Clean up the existing list of MyCharList.
		m_listOfMyCharList.clear();
		
		// Read number of elements in m_listOfMyCharList.
		uint32_t numberOfMyCharList = 0;
		d->read(2, numberOfMyCharList);
		
		if (numberOfMyCharList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(2 + 7, elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyCharList; i++) {
		        char element;
		        sstr >> element;
		        m_listOfMyCharList.push_back(element);
		    }
		}
		// Clean up the existing list of MyInt32List.
		m_listOfMyInt32List.clear();
		
		// Read number of elements in m_listOfMyInt32List.
		uint32_t numberOfMyInt32List = 0;
		d->read(3, numberOfMyInt32List);
		
		if (numberOfMyInt32List > 0) {
		    // Read string of elements.
		    string elements;
			d->read(3 + 7, elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyInt32List; i++) {
		        int32_t element;
		        sstr >> element;
		        m_listOfMyInt32List.push_back(element);
		    }
		}
		// Clean up the existing list of MyUint32List.
		m_listOfMyUint32List.clear();
		
		// Read number of elements in m_listOfMyUint32List.
		uint32_t numberOfMyUint32List = 0;
		d->read(4, numberOfMyUint32List);
		
		if (numberOfMyUint32List > 0) {
		    // Read string of elements.
		    string elements;
			d->read(4 + 7, elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyUint32List; i++) {
		        uint32_t element;
		        sstr >> element;
		        m_listOfMyUint32List.push_back(element);
		    }
		}
		// Clean up the existing list of MyFloatList.
		m_listOfMyFloatList.clear();
		
		// Read number of elements in m_listOfMyFloatList.
		uint32_t numberOfMyFloatList = 0;
		d->read(5, numberOfMyFloatList);
		
		if (numberOfMyFloatList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(5 + 7, elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyFloatList; i++) {
		        float element;
		        sstr >> element;
		        m_listOfMyFloatList.push_back(element);
		    }
		}
		// Clean up the existing list of MyDoubleList.
		m_listOfMyDoubleList.clear();
		
		// Read number of elements in m_listOfMyDoubleList.
		uint32_t numberOfMyDoubleList = 0;
		d->read(6, numberOfMyDoubleList);
		
		if (numberOfMyDoubleList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(6 + 7, elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyDoubleList; i++) {
		        double element;
		        sstr >> element;
		        m_listOfMyDoubleList.push_back(element);
		    }
		}
		// Clean up the existing list of MyStringList.
		m_listOfMyStringList.clear();
		
		// Read number of elements in m_listOfMyStringList.
		uint32_t numberOfMyStringList = 0;
		d->read(7, numberOfMyStringList);
		
		if (numberOfMyStringList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(7 + 7, elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyStringList; i++) {
		        std::string element;
		        getline(sstr, element);
		        m_listOfMyStringList.push_back(element);
		    }
		}
		return in;
	}
