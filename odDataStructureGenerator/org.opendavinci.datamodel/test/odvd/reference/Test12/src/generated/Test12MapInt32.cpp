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


#include "test12/generated/Test12MapInt32.h"

	using namespace std;
	using namespace odcore::base;


	Test12MapInt32::Test12MapInt32() :
	    SerializableData(), Visitable()
		, m_mapOfMyInt32BoolMap()
		, m_mapOfMyInt32CharMap()
		, m_mapOfMyInt32Int32Map()
		, m_mapOfMyInt32Uint32Map()
		, m_mapOfMyInt32FloatMap()
		, m_mapOfMyInt32DoubleMap()
		, m_mapOfMyInt32StringMap()
	{
	}

	Test12MapInt32::Test12MapInt32(
		const map<int32_t, bool> &val0, 
		const map<int32_t, char> &val1, 
		const map<int32_t, int32_t> &val2, 
		const map<int32_t, uint32_t> &val3, 
		const map<int32_t, float> &val4, 
		const map<int32_t, double> &val5, 
		const map<int32_t, std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_mapOfMyInt32BoolMap(val0)
		, m_mapOfMyInt32CharMap(val1)
		, m_mapOfMyInt32Int32Map(val2)
		, m_mapOfMyInt32Uint32Map(val3)
		, m_mapOfMyInt32FloatMap(val4)
		, m_mapOfMyInt32DoubleMap(val5)
		, m_mapOfMyInt32StringMap(val6)
	{
	}

	Test12MapInt32::Test12MapInt32(const Test12MapInt32 &obj) :
	    SerializableData(), Visitable()
		, m_mapOfMyInt32BoolMap(obj.m_mapOfMyInt32BoolMap)
		, m_mapOfMyInt32CharMap(obj.m_mapOfMyInt32CharMap)
		, m_mapOfMyInt32Int32Map(obj.m_mapOfMyInt32Int32Map)
		, m_mapOfMyInt32Uint32Map(obj.m_mapOfMyInt32Uint32Map)
		, m_mapOfMyInt32FloatMap(obj.m_mapOfMyInt32FloatMap)
		, m_mapOfMyInt32DoubleMap(obj.m_mapOfMyInt32DoubleMap)
		, m_mapOfMyInt32StringMap(obj.m_mapOfMyInt32StringMap)
	{
	}
	
	Test12MapInt32::~Test12MapInt32() {
	}

	Test12MapInt32& Test12MapInt32::operator=(const Test12MapInt32 &obj) {
		m_mapOfMyInt32BoolMap = obj.m_mapOfMyInt32BoolMap;
		m_mapOfMyInt32CharMap = obj.m_mapOfMyInt32CharMap;
		m_mapOfMyInt32Int32Map = obj.m_mapOfMyInt32Int32Map;
		m_mapOfMyInt32Uint32Map = obj.m_mapOfMyInt32Uint32Map;
		m_mapOfMyInt32FloatMap = obj.m_mapOfMyInt32FloatMap;
		m_mapOfMyInt32DoubleMap = obj.m_mapOfMyInt32DoubleMap;
		m_mapOfMyInt32StringMap = obj.m_mapOfMyInt32StringMap;
		return (*this);
	}

	int32_t Test12MapInt32::ID() {
		return 16;
	}

	const string Test12MapInt32::ShortName() {
		return "Test12MapInt32";
	}

	const string Test12MapInt32::LongName() {
		return "Test12MapInt32";
	}

	int32_t Test12MapInt32::getID() const {
		return Test12MapInt32::ID();
	}

	const string Test12MapInt32::getShortName() const {
		return Test12MapInt32::ShortName();
	}

	const string Test12MapInt32::getLongName() const {
		return Test12MapInt32::LongName();
	}

	std::map<int32_t, bool> Test12MapInt32::getMapOfMyInt32BoolMap() const {
		return m_mapOfMyInt32BoolMap;
	}
	
	void Test12MapInt32::setMapOfMyInt32BoolMap(const std::map<int32_t, bool> &val) {
		m_mapOfMyInt32BoolMap = val;
	}
	
	void Test12MapInt32::clear_MapOfMyInt32BoolMap() {
		m_mapOfMyInt32BoolMap.clear();
	}
	
	uint32_t Test12MapInt32::getSize_MapOfMyInt32BoolMap() const {
		return m_mapOfMyInt32BoolMap.size();
	}
	
	bool Test12MapInt32::isEmpty_MapOfMyInt32BoolMap() const {
		return m_mapOfMyInt32BoolMap.empty();
	}
	
	void Test12MapInt32::putTo_MapOfMyInt32BoolMap(const int32_t &key, const bool &val) {
		m_mapOfMyInt32BoolMap[key] = val;
	}
	
	bool Test12MapInt32::containsKey_MapOfMyInt32BoolMap(const int32_t &key) const {
		return (m_mapOfMyInt32BoolMap.count(key) > 0);
	}
	
	bool Test12MapInt32::getValueForKey_MapOfMyInt32BoolMap(const int32_t &key) {
		return m_mapOfMyInt32BoolMap[key];
	}
	
	std::pair<std::map<int32_t, bool>::iterator, std::map<int32_t, bool>::iterator> Test12MapInt32::iteratorPair_MapOfMyInt32BoolMap() {
		return std::make_pair(m_mapOfMyInt32BoolMap.begin(), m_mapOfMyInt32BoolMap.end());
	}
	std::map<int32_t, char> Test12MapInt32::getMapOfMyInt32CharMap() const {
		return m_mapOfMyInt32CharMap;
	}
	
	void Test12MapInt32::setMapOfMyInt32CharMap(const std::map<int32_t, char> &val) {
		m_mapOfMyInt32CharMap = val;
	}
	
	void Test12MapInt32::clear_MapOfMyInt32CharMap() {
		m_mapOfMyInt32CharMap.clear();
	}
	
	uint32_t Test12MapInt32::getSize_MapOfMyInt32CharMap() const {
		return m_mapOfMyInt32CharMap.size();
	}
	
	bool Test12MapInt32::isEmpty_MapOfMyInt32CharMap() const {
		return m_mapOfMyInt32CharMap.empty();
	}
	
	void Test12MapInt32::putTo_MapOfMyInt32CharMap(const int32_t &key, const char &val) {
		m_mapOfMyInt32CharMap[key] = val;
	}
	
	bool Test12MapInt32::containsKey_MapOfMyInt32CharMap(const int32_t &key) const {
		return (m_mapOfMyInt32CharMap.count(key) > 0);
	}
	
	char Test12MapInt32::getValueForKey_MapOfMyInt32CharMap(const int32_t &key) {
		return m_mapOfMyInt32CharMap[key];
	}
	
	std::pair<std::map<int32_t, char>::iterator, std::map<int32_t, char>::iterator> Test12MapInt32::iteratorPair_MapOfMyInt32CharMap() {
		return std::make_pair(m_mapOfMyInt32CharMap.begin(), m_mapOfMyInt32CharMap.end());
	}
	std::map<int32_t, int32_t> Test12MapInt32::getMapOfMyInt32Int32Map() const {
		return m_mapOfMyInt32Int32Map;
	}
	
	void Test12MapInt32::setMapOfMyInt32Int32Map(const std::map<int32_t, int32_t> &val) {
		m_mapOfMyInt32Int32Map = val;
	}
	
	void Test12MapInt32::clear_MapOfMyInt32Int32Map() {
		m_mapOfMyInt32Int32Map.clear();
	}
	
	uint32_t Test12MapInt32::getSize_MapOfMyInt32Int32Map() const {
		return m_mapOfMyInt32Int32Map.size();
	}
	
	bool Test12MapInt32::isEmpty_MapOfMyInt32Int32Map() const {
		return m_mapOfMyInt32Int32Map.empty();
	}
	
	void Test12MapInt32::putTo_MapOfMyInt32Int32Map(const int32_t &key, const int32_t &val) {
		m_mapOfMyInt32Int32Map[key] = val;
	}
	
	bool Test12MapInt32::containsKey_MapOfMyInt32Int32Map(const int32_t &key) const {
		return (m_mapOfMyInt32Int32Map.count(key) > 0);
	}
	
	int32_t Test12MapInt32::getValueForKey_MapOfMyInt32Int32Map(const int32_t &key) {
		return m_mapOfMyInt32Int32Map[key];
	}
	
	std::pair<std::map<int32_t, int32_t>::iterator, std::map<int32_t, int32_t>::iterator> Test12MapInt32::iteratorPair_MapOfMyInt32Int32Map() {
		return std::make_pair(m_mapOfMyInt32Int32Map.begin(), m_mapOfMyInt32Int32Map.end());
	}
	std::map<int32_t, uint32_t> Test12MapInt32::getMapOfMyInt32Uint32Map() const {
		return m_mapOfMyInt32Uint32Map;
	}
	
	void Test12MapInt32::setMapOfMyInt32Uint32Map(const std::map<int32_t, uint32_t> &val) {
		m_mapOfMyInt32Uint32Map = val;
	}
	
	void Test12MapInt32::clear_MapOfMyInt32Uint32Map() {
		m_mapOfMyInt32Uint32Map.clear();
	}
	
	uint32_t Test12MapInt32::getSize_MapOfMyInt32Uint32Map() const {
		return m_mapOfMyInt32Uint32Map.size();
	}
	
	bool Test12MapInt32::isEmpty_MapOfMyInt32Uint32Map() const {
		return m_mapOfMyInt32Uint32Map.empty();
	}
	
	void Test12MapInt32::putTo_MapOfMyInt32Uint32Map(const int32_t &key, const uint32_t &val) {
		m_mapOfMyInt32Uint32Map[key] = val;
	}
	
	bool Test12MapInt32::containsKey_MapOfMyInt32Uint32Map(const int32_t &key) const {
		return (m_mapOfMyInt32Uint32Map.count(key) > 0);
	}
	
	uint32_t Test12MapInt32::getValueForKey_MapOfMyInt32Uint32Map(const int32_t &key) {
		return m_mapOfMyInt32Uint32Map[key];
	}
	
	std::pair<std::map<int32_t, uint32_t>::iterator, std::map<int32_t, uint32_t>::iterator> Test12MapInt32::iteratorPair_MapOfMyInt32Uint32Map() {
		return std::make_pair(m_mapOfMyInt32Uint32Map.begin(), m_mapOfMyInt32Uint32Map.end());
	}
	std::map<int32_t, float> Test12MapInt32::getMapOfMyInt32FloatMap() const {
		return m_mapOfMyInt32FloatMap;
	}
	
	void Test12MapInt32::setMapOfMyInt32FloatMap(const std::map<int32_t, float> &val) {
		m_mapOfMyInt32FloatMap = val;
	}
	
	void Test12MapInt32::clear_MapOfMyInt32FloatMap() {
		m_mapOfMyInt32FloatMap.clear();
	}
	
	uint32_t Test12MapInt32::getSize_MapOfMyInt32FloatMap() const {
		return m_mapOfMyInt32FloatMap.size();
	}
	
	bool Test12MapInt32::isEmpty_MapOfMyInt32FloatMap() const {
		return m_mapOfMyInt32FloatMap.empty();
	}
	
	void Test12MapInt32::putTo_MapOfMyInt32FloatMap(const int32_t &key, const float &val) {
		m_mapOfMyInt32FloatMap[key] = val;
	}
	
	bool Test12MapInt32::containsKey_MapOfMyInt32FloatMap(const int32_t &key) const {
		return (m_mapOfMyInt32FloatMap.count(key) > 0);
	}
	
	float Test12MapInt32::getValueForKey_MapOfMyInt32FloatMap(const int32_t &key) {
		return m_mapOfMyInt32FloatMap[key];
	}
	
	std::pair<std::map<int32_t, float>::iterator, std::map<int32_t, float>::iterator> Test12MapInt32::iteratorPair_MapOfMyInt32FloatMap() {
		return std::make_pair(m_mapOfMyInt32FloatMap.begin(), m_mapOfMyInt32FloatMap.end());
	}
	std::map<int32_t, double> Test12MapInt32::getMapOfMyInt32DoubleMap() const {
		return m_mapOfMyInt32DoubleMap;
	}
	
	void Test12MapInt32::setMapOfMyInt32DoubleMap(const std::map<int32_t, double> &val) {
		m_mapOfMyInt32DoubleMap = val;
	}
	
	void Test12MapInt32::clear_MapOfMyInt32DoubleMap() {
		m_mapOfMyInt32DoubleMap.clear();
	}
	
	uint32_t Test12MapInt32::getSize_MapOfMyInt32DoubleMap() const {
		return m_mapOfMyInt32DoubleMap.size();
	}
	
	bool Test12MapInt32::isEmpty_MapOfMyInt32DoubleMap() const {
		return m_mapOfMyInt32DoubleMap.empty();
	}
	
	void Test12MapInt32::putTo_MapOfMyInt32DoubleMap(const int32_t &key, const double &val) {
		m_mapOfMyInt32DoubleMap[key] = val;
	}
	
	bool Test12MapInt32::containsKey_MapOfMyInt32DoubleMap(const int32_t &key) const {
		return (m_mapOfMyInt32DoubleMap.count(key) > 0);
	}
	
	double Test12MapInt32::getValueForKey_MapOfMyInt32DoubleMap(const int32_t &key) {
		return m_mapOfMyInt32DoubleMap[key];
	}
	
	std::pair<std::map<int32_t, double>::iterator, std::map<int32_t, double>::iterator> Test12MapInt32::iteratorPair_MapOfMyInt32DoubleMap() {
		return std::make_pair(m_mapOfMyInt32DoubleMap.begin(), m_mapOfMyInt32DoubleMap.end());
	}
	std::map<int32_t, std::string> Test12MapInt32::getMapOfMyInt32StringMap() const {
		return m_mapOfMyInt32StringMap;
	}
	
	void Test12MapInt32::setMapOfMyInt32StringMap(const std::map<int32_t, std::string> &val) {
		m_mapOfMyInt32StringMap = val;
	}
	
	void Test12MapInt32::clear_MapOfMyInt32StringMap() {
		m_mapOfMyInt32StringMap.clear();
	}
	
	uint32_t Test12MapInt32::getSize_MapOfMyInt32StringMap() const {
		return m_mapOfMyInt32StringMap.size();
	}
	
	bool Test12MapInt32::isEmpty_MapOfMyInt32StringMap() const {
		return m_mapOfMyInt32StringMap.empty();
	}
	
	void Test12MapInt32::putTo_MapOfMyInt32StringMap(const int32_t &key, const std::string &val) {
		m_mapOfMyInt32StringMap[key] = val;
	}
	
	bool Test12MapInt32::containsKey_MapOfMyInt32StringMap(const int32_t &key) const {
		return (m_mapOfMyInt32StringMap.count(key) > 0);
	}
	
	std::string Test12MapInt32::getValueForKey_MapOfMyInt32StringMap(const int32_t &key) {
		return m_mapOfMyInt32StringMap[key];
	}
	
	std::pair<std::map<int32_t, std::string>::iterator, std::map<int32_t, std::string>::iterator> Test12MapInt32::iteratorPair_MapOfMyInt32StringMap() {
		return std::make_pair(m_mapOfMyInt32StringMap.begin(), m_mapOfMyInt32StringMap.end());
	}

	void Test12MapInt32::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test12MapInt32::toString() const {
		stringstream s;


		s << "Number of elements in map of MyInt32BoolMap: " << getSize_MapOfMyInt32BoolMap() << " ";
		s << "Number of elements in map of MyInt32CharMap: " << getSize_MapOfMyInt32CharMap() << " ";
		s << "Number of elements in map of MyInt32Int32Map: " << getSize_MapOfMyInt32Int32Map() << " ";
		s << "Number of elements in map of MyInt32Uint32Map: " << getSize_MapOfMyInt32Uint32Map() << " ";
		s << "Number of elements in map of MyInt32FloatMap: " << getSize_MapOfMyInt32FloatMap() << " ";
		s << "Number of elements in map of MyInt32DoubleMap: " << getSize_MapOfMyInt32DoubleMap() << " ";
		s << "Number of elements in map of MyInt32StringMap: " << getSize_MapOfMyInt32StringMap() << " ";

		return s.str();
	}

	ostream& Test12MapInt32::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		{
			// Write number of elements in m_mapOfMyInt32BoolMap.
			const uint32_t numberOfMyInt32BoolMap = static_cast<uint32_t>(m_mapOfMyInt32BoolMap.size());
			s->write(1, numberOfMyInt32BoolMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyInt32BoolMap;
			std::map<int32_t, bool>::const_iterator it = m_mapOfMyInt32BoolMap.begin();
			while (it != m_mapOfMyInt32BoolMap.end()) {
			    sstrOfMyInt32BoolMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyInt32BoolMap > 0) {
				s->write(1 + 7, sstrOfMyInt32BoolMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyInt32CharMap.
			const uint32_t numberOfMyInt32CharMap = static_cast<uint32_t>(m_mapOfMyInt32CharMap.size());
			s->write(2, numberOfMyInt32CharMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyInt32CharMap;
			std::map<int32_t, char>::const_iterator it = m_mapOfMyInt32CharMap.begin();
			while (it != m_mapOfMyInt32CharMap.end()) {
			    sstrOfMyInt32CharMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyInt32CharMap > 0) {
				s->write(2 + 7, sstrOfMyInt32CharMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyInt32Int32Map.
			const uint32_t numberOfMyInt32Int32Map = static_cast<uint32_t>(m_mapOfMyInt32Int32Map.size());
			s->write(3, numberOfMyInt32Int32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyInt32Int32Map;
			std::map<int32_t, int32_t>::const_iterator it = m_mapOfMyInt32Int32Map.begin();
			while (it != m_mapOfMyInt32Int32Map.end()) {
			    sstrOfMyInt32Int32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyInt32Int32Map > 0) {
				s->write(3 + 7, sstrOfMyInt32Int32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyInt32Uint32Map.
			const uint32_t numberOfMyInt32Uint32Map = static_cast<uint32_t>(m_mapOfMyInt32Uint32Map.size());
			s->write(4, numberOfMyInt32Uint32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyInt32Uint32Map;
			std::map<int32_t, uint32_t>::const_iterator it = m_mapOfMyInt32Uint32Map.begin();
			while (it != m_mapOfMyInt32Uint32Map.end()) {
			    sstrOfMyInt32Uint32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyInt32Uint32Map > 0) {
				s->write(4 + 7, sstrOfMyInt32Uint32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyInt32FloatMap.
			const uint32_t numberOfMyInt32FloatMap = static_cast<uint32_t>(m_mapOfMyInt32FloatMap.size());
			s->write(5, numberOfMyInt32FloatMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyInt32FloatMap;
			std::map<int32_t, float>::const_iterator it = m_mapOfMyInt32FloatMap.begin();
			while (it != m_mapOfMyInt32FloatMap.end()) {
			    sstrOfMyInt32FloatMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyInt32FloatMap > 0) {
				s->write(5 + 7, sstrOfMyInt32FloatMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyInt32DoubleMap.
			const uint32_t numberOfMyInt32DoubleMap = static_cast<uint32_t>(m_mapOfMyInt32DoubleMap.size());
			s->write(6, numberOfMyInt32DoubleMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyInt32DoubleMap;
			std::map<int32_t, double>::const_iterator it = m_mapOfMyInt32DoubleMap.begin();
			while (it != m_mapOfMyInt32DoubleMap.end()) {
			    sstrOfMyInt32DoubleMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyInt32DoubleMap > 0) {
				s->write(6 + 7, sstrOfMyInt32DoubleMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyInt32StringMap.
			const uint32_t numberOfMyInt32StringMap = static_cast<uint32_t>(m_mapOfMyInt32StringMap.size());
			s->write(7, numberOfMyInt32StringMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyInt32StringMap;
			std::map<int32_t, std::string>::const_iterator it = m_mapOfMyInt32StringMap.begin();
			while (it != m_mapOfMyInt32StringMap.end()) {
			    sstrOfMyInt32StringMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyInt32StringMap > 0) {
				s->write(7 + 7, sstrOfMyInt32StringMap.str());
			}
		}
		return out;
	}

	istream& Test12MapInt32::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing map of MyInt32BoolMap.
		m_mapOfMyInt32BoolMap.clear();
		
		// Read number of elements in m_mapOfMyInt32BoolMap.
		uint32_t numberOfMyInt32BoolMap = 0;
		d->read(1, numberOfMyInt32BoolMap);
		
		if (numberOfMyInt32BoolMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(1 + 7, elements);
		
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
			    bool _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyInt32BoolMap(_key, _value);
			}
		}
		// Clean up the existing map of MyInt32CharMap.
		m_mapOfMyInt32CharMap.clear();
		
		// Read number of elements in m_mapOfMyInt32CharMap.
		uint32_t numberOfMyInt32CharMap = 0;
		d->read(2, numberOfMyInt32CharMap);
		
		if (numberOfMyInt32CharMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(2 + 7, elements);
		
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
			    char _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyInt32CharMap(_key, _value);
			}
		}
		// Clean up the existing map of MyInt32Int32Map.
		m_mapOfMyInt32Int32Map.clear();
		
		// Read number of elements in m_mapOfMyInt32Int32Map.
		uint32_t numberOfMyInt32Int32Map = 0;
		d->read(3, numberOfMyInt32Int32Map);
		
		if (numberOfMyInt32Int32Map > 0) {
		    // Read string of elements.
		    string elements;
			d->read(3 + 7, elements);
		
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
			    int32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyInt32Int32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyInt32Uint32Map.
		m_mapOfMyInt32Uint32Map.clear();
		
		// Read number of elements in m_mapOfMyInt32Uint32Map.
		uint32_t numberOfMyInt32Uint32Map = 0;
		d->read(4, numberOfMyInt32Uint32Map);
		
		if (numberOfMyInt32Uint32Map > 0) {
		    // Read string of elements.
		    string elements;
			d->read(4 + 7, elements);
		
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
			    uint32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyInt32Uint32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyInt32FloatMap.
		m_mapOfMyInt32FloatMap.clear();
		
		// Read number of elements in m_mapOfMyInt32FloatMap.
		uint32_t numberOfMyInt32FloatMap = 0;
		d->read(5, numberOfMyInt32FloatMap);
		
		if (numberOfMyInt32FloatMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(5 + 7, elements);
		
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
			    float _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyInt32FloatMap(_key, _value);
			}
		}
		// Clean up the existing map of MyInt32DoubleMap.
		m_mapOfMyInt32DoubleMap.clear();
		
		// Read number of elements in m_mapOfMyInt32DoubleMap.
		uint32_t numberOfMyInt32DoubleMap = 0;
		d->read(6, numberOfMyInt32DoubleMap);
		
		if (numberOfMyInt32DoubleMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(6 + 7, elements);
		
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
			    double _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyInt32DoubleMap(_key, _value);
			}
		}
		// Clean up the existing map of MyInt32StringMap.
		m_mapOfMyInt32StringMap.clear();
		
		// Read number of elements in m_mapOfMyInt32StringMap.
		uint32_t numberOfMyInt32StringMap = 0;
		d->read(7, numberOfMyInt32StringMap);
		
		if (numberOfMyInt32StringMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(7 + 7, elements);
		
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
				putTo_MapOfMyInt32StringMap(_key, _value);
			}
		}
		return in;
	}
