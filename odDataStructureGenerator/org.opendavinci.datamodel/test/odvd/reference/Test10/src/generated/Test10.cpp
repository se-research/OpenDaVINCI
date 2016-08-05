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

#include "test10/generated/Test10.h"

	using namespace std;
	using namespace odcore::base;


	Test10::Test10() :
	    SerializableData(), Visitable()
		, m_listOfMyStringList()
		, m_listOfMyPointList()
		, m_mapOfMyIntStringMap()
		, m_mapOfMyIntPointMap()
	{
	}

	Test10::Test10(
		const vector<std::string> &val0, 
		const vector<Test10Point> &val1, 
		const map<int32_t, std::string> &val2, 
		const map<int32_t, Test10Point> &val3
	) :
	    SerializableData(), Visitable()
		, m_listOfMyStringList(val0)
		, m_listOfMyPointList(val1)
		, m_mapOfMyIntStringMap(val2)
		, m_mapOfMyIntPointMap(val3)
	{
	}

	Test10::Test10(const Test10 &obj) :
	    SerializableData(), Visitable()
		, m_listOfMyStringList(obj.m_listOfMyStringList)
		, m_listOfMyPointList(obj.m_listOfMyPointList)
		, m_mapOfMyIntStringMap(obj.m_mapOfMyIntStringMap)
		, m_mapOfMyIntPointMap(obj.m_mapOfMyIntPointMap)
	{
	}
	
	Test10::~Test10() {
	}

	Test10& Test10::operator=(const Test10 &obj) {
		m_listOfMyStringList = obj.m_listOfMyStringList;
		m_listOfMyPointList = obj.m_listOfMyPointList;
		m_mapOfMyIntStringMap = obj.m_mapOfMyIntStringMap;
		m_mapOfMyIntPointMap = obj.m_mapOfMyIntPointMap;
		return (*this);
	}

	int32_t Test10::ID() {
		return 11;
	}

	const string Test10::ShortName() {
		return "Test10";
	}

	const string Test10::LongName() {
		return "Test10";
	}

	int32_t Test10::getID() const {
		return Test10::ID();
	}

	const string Test10::getShortName() const {
		return Test10::ShortName();
	}

	const string Test10::getLongName() const {
		return Test10::LongName();
	}

	std::vector<std::string> Test10::getListOfMyStringList() const {
		return m_listOfMyStringList;
	}
	
	void Test10::setListOfMyStringList(const std::vector<std::string> &val) {
		m_listOfMyStringList = val;
	}
	
	void Test10::clear_ListOfMyStringList() {
		m_listOfMyStringList.clear();
	}
	
	uint32_t Test10::getSize_ListOfMyStringList() const {
		return m_listOfMyStringList.size();
	}
	
	bool Test10::isEmpty_ListOfMyStringList() const {
		return m_listOfMyStringList.empty();
	}
	
	void Test10::addTo_ListOfMyStringList(const std::string &val) {
		m_listOfMyStringList.push_back(val);
	}
	
	void Test10::insertTo_ListOfMyStringList(const std::string &val) {
		m_listOfMyStringList.insert(m_listOfMyStringList.begin(), val);
	}
	
	bool Test10::contains_ListOfMyStringList(const std::string &val) const {
		return std::find(m_listOfMyStringList.begin(), m_listOfMyStringList.end(), val) != m_listOfMyStringList.end();
	}
	
	std::pair<std::vector<std::string>::iterator, std::vector<std::string>::iterator> Test10::iteratorPair_ListOfMyStringList() {
		return std::make_pair(m_listOfMyStringList.begin(), m_listOfMyStringList.end());
	}
	std::vector<Test10Point> Test10::getListOfMyPointList() const {
		return m_listOfMyPointList;
	}
	
	void Test10::setListOfMyPointList(const std::vector<Test10Point> &val) {
		m_listOfMyPointList = val;
	}
	
	void Test10::clear_ListOfMyPointList() {
		m_listOfMyPointList.clear();
	}
	
	uint32_t Test10::getSize_ListOfMyPointList() const {
		return m_listOfMyPointList.size();
	}
	
	bool Test10::isEmpty_ListOfMyPointList() const {
		return m_listOfMyPointList.empty();
	}
	
	void Test10::addTo_ListOfMyPointList(const Test10Point &val) {
		m_listOfMyPointList.push_back(val);
	}
	
	void Test10::insertTo_ListOfMyPointList(const Test10Point &val) {
		m_listOfMyPointList.insert(m_listOfMyPointList.begin(), val);
	}
	
	bool Test10::contains_ListOfMyPointList(const Test10Point &val) const {
		bool found = false;
		std::vector<Test10Point>::const_iterator it = m_listOfMyPointList.begin();
		while (it != m_listOfMyPointList.end() && !found) {
		    found |= (*it).toString() == val.toString();
		    it++;
		}
		return found;
	}
	
	std::pair<std::vector<Test10Point>::iterator, std::vector<Test10Point>::iterator> Test10::iteratorPair_ListOfMyPointList() {
		return std::make_pair(m_listOfMyPointList.begin(), m_listOfMyPointList.end());
	}
	std::map<int32_t, std::string> Test10::getMapOfMyIntStringMap() const {
		return m_mapOfMyIntStringMap;
	}
	
	void Test10::setMapOfMyIntStringMap(const std::map<int32_t, std::string> &val) {
		m_mapOfMyIntStringMap = val;
	}
	
	void Test10::clear_MapOfMyIntStringMap() {
		m_mapOfMyIntStringMap.clear();
	}
	
	uint32_t Test10::getSize_MapOfMyIntStringMap() const {
		return m_mapOfMyIntStringMap.size();
	}
	
	bool Test10::isEmpty_MapOfMyIntStringMap() const {
		return m_mapOfMyIntStringMap.empty();
	}
	
	void Test10::putTo_MapOfMyIntStringMap(const int32_t &key, const std::string &val) {
		m_mapOfMyIntStringMap[key] = val;
	}
	
	bool Test10::containsKey_MapOfMyIntStringMap(const int32_t &key) const {
		return (m_mapOfMyIntStringMap.count(key) > 0);
	}
	
	std::string Test10::getValueForKey_MapOfMyIntStringMap(const int32_t &key) {
		return m_mapOfMyIntStringMap[key];
	}
	
	std::pair<std::map<int32_t, std::string>::iterator, std::map<int32_t, std::string>::iterator> Test10::iteratorPair_MapOfMyIntStringMap() {
		return std::make_pair(m_mapOfMyIntStringMap.begin(), m_mapOfMyIntStringMap.end());
	}
	std::map<int32_t, Test10Point> Test10::getMapOfMyIntPointMap() const {
		return m_mapOfMyIntPointMap;
	}
	
	void Test10::setMapOfMyIntPointMap(const std::map<int32_t, Test10Point> &val) {
		m_mapOfMyIntPointMap = val;
	}
	
	void Test10::clear_MapOfMyIntPointMap() {
		m_mapOfMyIntPointMap.clear();
	}
	
	uint32_t Test10::getSize_MapOfMyIntPointMap() const {
		return m_mapOfMyIntPointMap.size();
	}
	
	bool Test10::isEmpty_MapOfMyIntPointMap() const {
		return m_mapOfMyIntPointMap.empty();
	}
	
	void Test10::putTo_MapOfMyIntPointMap(const int32_t &key, const Test10Point &val) {
		m_mapOfMyIntPointMap[key] = val;
	}
	
	bool Test10::containsKey_MapOfMyIntPointMap(const int32_t &key) const {
		return (m_mapOfMyIntPointMap.count(key) > 0);
	}
	
	Test10Point Test10::getValueForKey_MapOfMyIntPointMap(const int32_t &key) {
		return m_mapOfMyIntPointMap[key];
	}
	
	std::pair<std::map<int32_t, Test10Point>::iterator, std::map<int32_t, Test10Point>::iterator> Test10::iteratorPair_MapOfMyIntPointMap() {
		return std::make_pair(m_mapOfMyIntPointMap.begin(), m_mapOfMyIntPointMap.end());
	}

	void Test10::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test10::toString() const {
		stringstream s;

		s << "Number of elements in list of MyStringList: " << getSize_ListOfMyStringList() << " ";
		s << "Number of elements in list of MyPointList: " << getSize_ListOfMyPointList() << " ";
		s << "Number of elements in map of MyIntStringMap: " << getSize_MapOfMyIntStringMap() << " ";
		s << "Number of elements in map of MyIntPointMap: " << getSize_MapOfMyIntPointMap() << " ";

		return s.str();
	}

	ostream& Test10::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

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
			s->write(1, str_sstr_MyStringList);
		}
		// Store elements from m_listOfMyPointList into a string.
		{
			const uint32_t numberOfMyPointList = static_cast<uint32_t>(m_listOfMyPointList.size());
			std::stringstream sstr_MyPointList;
			{
				for(uint32_t i = 0; i < numberOfMyPointList; i++) {
					s->writeValue(sstr_MyPointList, m_listOfMyPointList.at(i));
				}
			}
			const std::string str_sstr_MyPointList = sstr_MyPointList.str();
			s->write(2, str_sstr_MyPointList);
		}
		{
			std::stringstream sstr_MyIntStringMap;
			{
				std::map<int32_t, std::string>::const_iterator it = m_mapOfMyIntStringMap.begin();
				while (it != m_mapOfMyIntStringMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyIntStringMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyIntStringMap = sstr_MyIntStringMap.str();
			s->write(3, str_sstr_MyIntStringMap);
		}
		{
			std::stringstream sstr_MyIntPointMap;
			{
				std::map<int32_t, Test10Point>::const_iterator it = m_mapOfMyIntPointMap.begin();
				while (it != m_mapOfMyIntPointMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyIntPointMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyIntPointMap = sstr_MyIntPointMap.str();
			s->write(4, str_sstr_MyIntPointMap);
		}
		return out;
	}

	istream& Test10::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore elements from a string into m_listOfMyStringList.
		{
			// Clean up the existing list of MyStringList.
			m_listOfMyStringList.clear();
			std::string str_MyStringList;
			d->read(1, str_MyStringList);
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
		// Restore elements from a string into m_listOfMyPointList.
		{
			// Clean up the existing list of MyPointList.
			m_listOfMyPointList.clear();
			std::string str_MyPointList;
			d->read(2, str_MyPointList);
			if (str_MyPointList.size() > 0) {
				std::stringstream sstr_str_MyPointList(str_MyPointList);
				uint32_t length = str_MyPointList.size();
				while (length > 0) {
					Test10Point element;
					length -= d->readValue(sstr_str_MyPointList, element);
					m_listOfMyPointList.push_back(element);
				}
			}
		}
		// Restore elements from a string into MyIntStringMap.
		{
			// Clean up the existing map of MyIntStringMap.
			m_mapOfMyIntStringMap.clear();
		
			std::string str_MyIntStringMap;
			d->read(3, str_MyIntStringMap);
			if (str_MyIntStringMap.size() > 0) {
				std::stringstream sstr_str_MyIntStringMap(str_MyIntStringMap);
		
				// str_MyIntStringMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyIntStringMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyIntStringMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							int32_t key;
							std::string value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyIntStringMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyIntPointMap.
		{
			// Clean up the existing map of MyIntPointMap.
			m_mapOfMyIntPointMap.clear();
		
			std::string str_MyIntPointMap;
			d->read(4, str_MyIntPointMap);
			if (str_MyIntPointMap.size() > 0) {
				std::stringstream sstr_str_MyIntPointMap(str_MyIntPointMap);
		
				// str_MyIntPointMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyIntPointMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyIntPointMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							int32_t key;
							Test10Point value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyIntPointMap(key, value);
						}
					}
				}
			}
		}
		return in;
	}
