/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <algorithm>
#include <sstream>
#include <utility>

#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"


#include "test10/generated/Test10.h"

	using namespace std;
	using namespace core::base;


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

	void Test10::accept(core::base::Visitor &v) {
		(void)v; // Avoid unused parameter warning.
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

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		// Write number of elements in m_listOfMyStringList.
		const uint32_t numberOfMyStringList = static_cast<uint32_t>(m_listOfMyStringList.size());
		s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > > >  >::RESULT,
		        numberOfMyStringList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyStringList;
		for (uint32_t i = 0; i < numberOfMyStringList; i++) {
		    sstrOfMyStringList << m_listOfMyStringList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyStringList > 0) {
			s->write(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > >  >::RESULT,
			        sstrOfMyStringList.str());
		}
		// Write number of elements in m_listOfMyPointList.
		const uint32_t numberOfMyPointList = static_cast<uint32_t>(m_listOfMyPointList.size());
		s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'P', CharList<'o', CharList<'i', CharList<'n', CharList<'t', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > >  >::RESULT,
		        numberOfMyPointList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyPointList;
		for (uint32_t i = 0; i < numberOfMyPointList; i++) {
		    sstrOfMyPointList << m_listOfMyPointList.at(i);
		}
		
		// Write string of elements.
		if (numberOfMyPointList > 0) {
			s->write(CRC32 < CharList<'M', CharList<'y', CharList<'P', CharList<'o', CharList<'i', CharList<'n', CharList<'t', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > >  >::RESULT,
			        sstrOfMyPointList.str());
		}
		{
			// Write number of elements in m_mapOfMyIntStringMap.
			const uint32_t numberOfMyIntStringMap = static_cast<uint32_t>(m_mapOfMyIntStringMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyIntStringMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyIntStringMap;
			std::map<int32_t, std::string>::const_iterator it = m_mapOfMyIntStringMap.begin();
			while (it != m_mapOfMyIntStringMap.end()) {
			    sstrOfMyIntStringMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyIntStringMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyIntStringMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyIntPointMap.
			const uint32_t numberOfMyIntPointMap = static_cast<uint32_t>(m_mapOfMyIntPointMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'P', CharList<'o', CharList<'i', CharList<'n', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyIntPointMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyIntPointMap;
			std::map<int32_t, Test10Point>::const_iterator it = m_mapOfMyIntPointMap.begin();
			while (it != m_mapOfMyIntPointMap.end()) {
			    sstrOfMyIntPointMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyIntPointMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'P', CharList<'o', CharList<'i', CharList<'n', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > >  >::RESULT,
						sstrOfMyIntPointMap.str());
			}
		}
		return out;
	}

	istream& Test10::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing list of MyStringList.
		m_listOfMyStringList.clear();
		
		// Read number of elements in m_listOfMyStringList.
		uint32_t numberOfMyStringList = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > > >  >::RESULT,
		       numberOfMyStringList);
		
		if (numberOfMyStringList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > >  >::RESULT,
			   elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyStringList; i++) {
		        std::string element;
		        getline(sstr, element);
		        m_listOfMyStringList.push_back(element);
		    }
		}
		// Clean up the existing list of MyPointList.
		m_listOfMyPointList.clear();
		
		// Read number of elements in m_listOfMyPointList.
		uint32_t numberOfMyPointList = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'P', CharList<'o', CharList<'i', CharList<'n', CharList<'t', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > >  >::RESULT,
		       numberOfMyPointList);
		
		if (numberOfMyPointList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'P', CharList<'o', CharList<'i', CharList<'n', CharList<'t', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > >  >::RESULT,
			   elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyPointList; i++) {
		        Test10Point element;
		        sstr >> element;
		        m_listOfMyPointList.push_back(element);
		    }
		}
		// Clean up the existing map of MyIntStringMap.
		m_mapOfMyIntStringMap.clear();
		
		// Read number of elements in m_mapOfMyIntStringMap.
		uint32_t numberOfMyIntStringMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyIntStringMap);
		
		if (numberOfMyIntStringMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    int32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    std::string _value;
		        getline(sstrValue, _value);
		
				// Store key/value pair.
				putTo_MapOfMyIntStringMap(_key, _value);
			}
		}
		// Clean up the existing map of MyIntPointMap.
		m_mapOfMyIntPointMap.clear();
		
		// Read number of elements in m_mapOfMyIntPointMap.
		uint32_t numberOfMyIntPointMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'P', CharList<'o', CharList<'i', CharList<'n', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyIntPointMap);
		
		if (numberOfMyIntPointMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'P', CharList<'o', CharList<'i', CharList<'n', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > >  >::RESULT,
			       elements);
		
			stringstream sstr(elements);
		
			while (!sstr.eof()) {
			    string line;
			    getline(sstr, line);
		
			    // Trying to find key-value-pair.
			    size_t delimiter = line.find_first_of("=");
		
			    // Compute length of value-entry by allowing comments right after values.
			    size_t valueLength = line.length();
		
			    // Skip lines with invalid position pointers.
			    if (! ( (delimiter > 0) && (valueLength > 0) ) ) {
			        continue;
			    }
		
			    string key = line.substr(0, delimiter);
			    string value = line.substr(delimiter + 1, valueLength);
		
			    // Skip lines with invalid keys or values.
			    if ( (key.length() == 0) || (value.length() == 0) ) {
			        continue;
			    }
		
			    stringstream sstrKey(key);
			    int32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    Test10Point _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyIntPointMap(_key, _value);
			}
		}
		return in;
	}
