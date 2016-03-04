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


#include "test12/generated/Test12MapUint32.h"

	using namespace std;
	using namespace odcore::base;


	Test12MapUint32::Test12MapUint32() :
	    SerializableData(), Visitable()
		, m_mapOfMyUint32BoolMap()
		, m_mapOfMyUint32CharMap()
		, m_mapOfMyUint32Int32Map()
		, m_mapOfMyUint32Uint32Map()
		, m_mapOfMyUint32FloatMap()
		, m_mapOfMyUint32DoubleMap()
		, m_mapOfMyUint32StringMap()
	{
	}

	Test12MapUint32::Test12MapUint32(
		const map<uint32_t, bool> &val0, 
		const map<uint32_t, char> &val1, 
		const map<uint32_t, int32_t> &val2, 
		const map<uint32_t, uint32_t> &val3, 
		const map<uint32_t, float> &val4, 
		const map<uint32_t, double> &val5, 
		const map<uint32_t, std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_mapOfMyUint32BoolMap(val0)
		, m_mapOfMyUint32CharMap(val1)
		, m_mapOfMyUint32Int32Map(val2)
		, m_mapOfMyUint32Uint32Map(val3)
		, m_mapOfMyUint32FloatMap(val4)
		, m_mapOfMyUint32DoubleMap(val5)
		, m_mapOfMyUint32StringMap(val6)
	{
	}

	Test12MapUint32::Test12MapUint32(const Test12MapUint32 &obj) :
	    SerializableData(), Visitable()
		, m_mapOfMyUint32BoolMap(obj.m_mapOfMyUint32BoolMap)
		, m_mapOfMyUint32CharMap(obj.m_mapOfMyUint32CharMap)
		, m_mapOfMyUint32Int32Map(obj.m_mapOfMyUint32Int32Map)
		, m_mapOfMyUint32Uint32Map(obj.m_mapOfMyUint32Uint32Map)
		, m_mapOfMyUint32FloatMap(obj.m_mapOfMyUint32FloatMap)
		, m_mapOfMyUint32DoubleMap(obj.m_mapOfMyUint32DoubleMap)
		, m_mapOfMyUint32StringMap(obj.m_mapOfMyUint32StringMap)
	{
	}
	
	Test12MapUint32::~Test12MapUint32() {
	}

	Test12MapUint32& Test12MapUint32::operator=(const Test12MapUint32 &obj) {
		m_mapOfMyUint32BoolMap = obj.m_mapOfMyUint32BoolMap;
		m_mapOfMyUint32CharMap = obj.m_mapOfMyUint32CharMap;
		m_mapOfMyUint32Int32Map = obj.m_mapOfMyUint32Int32Map;
		m_mapOfMyUint32Uint32Map = obj.m_mapOfMyUint32Uint32Map;
		m_mapOfMyUint32FloatMap = obj.m_mapOfMyUint32FloatMap;
		m_mapOfMyUint32DoubleMap = obj.m_mapOfMyUint32DoubleMap;
		m_mapOfMyUint32StringMap = obj.m_mapOfMyUint32StringMap;
		return (*this);
	}

	int32_t Test12MapUint32::ID() {
		return 17;
	}

	const string Test12MapUint32::ShortName() {
		return "Test12MapUint32";
	}

	const string Test12MapUint32::LongName() {
		return "Test12MapUint32";
	}

	int32_t Test12MapUint32::getID() const {
		return Test12MapUint32::ID();
	}

	const string Test12MapUint32::getShortName() const {
		return Test12MapUint32::ShortName();
	}

	const string Test12MapUint32::getLongName() const {
		return Test12MapUint32::LongName();
	}

	std::map<uint32_t, bool> Test12MapUint32::getMapOfMyUint32BoolMap() const {
		return m_mapOfMyUint32BoolMap;
	}
	
	void Test12MapUint32::setMapOfMyUint32BoolMap(const std::map<uint32_t, bool> &val) {
		m_mapOfMyUint32BoolMap = val;
	}
	
	void Test12MapUint32::clear_MapOfMyUint32BoolMap() {
		m_mapOfMyUint32BoolMap.clear();
	}
	
	uint32_t Test12MapUint32::getSize_MapOfMyUint32BoolMap() const {
		return m_mapOfMyUint32BoolMap.size();
	}
	
	bool Test12MapUint32::isEmpty_MapOfMyUint32BoolMap() const {
		return m_mapOfMyUint32BoolMap.empty();
	}
	
	void Test12MapUint32::putTo_MapOfMyUint32BoolMap(const uint32_t &key, const bool &val) {
		m_mapOfMyUint32BoolMap[key] = val;
	}
	
	bool Test12MapUint32::containsKey_MapOfMyUint32BoolMap(const uint32_t &key) const {
		return (m_mapOfMyUint32BoolMap.count(key) > 0);
	}
	
	bool Test12MapUint32::getValueForKey_MapOfMyUint32BoolMap(const uint32_t &key) {
		return m_mapOfMyUint32BoolMap[key];
	}
	
	std::pair<std::map<uint32_t, bool>::iterator, std::map<uint32_t, bool>::iterator> Test12MapUint32::iteratorPair_MapOfMyUint32BoolMap() {
		return std::make_pair(m_mapOfMyUint32BoolMap.begin(), m_mapOfMyUint32BoolMap.end());
	}
	std::map<uint32_t, char> Test12MapUint32::getMapOfMyUint32CharMap() const {
		return m_mapOfMyUint32CharMap;
	}
	
	void Test12MapUint32::setMapOfMyUint32CharMap(const std::map<uint32_t, char> &val) {
		m_mapOfMyUint32CharMap = val;
	}
	
	void Test12MapUint32::clear_MapOfMyUint32CharMap() {
		m_mapOfMyUint32CharMap.clear();
	}
	
	uint32_t Test12MapUint32::getSize_MapOfMyUint32CharMap() const {
		return m_mapOfMyUint32CharMap.size();
	}
	
	bool Test12MapUint32::isEmpty_MapOfMyUint32CharMap() const {
		return m_mapOfMyUint32CharMap.empty();
	}
	
	void Test12MapUint32::putTo_MapOfMyUint32CharMap(const uint32_t &key, const char &val) {
		m_mapOfMyUint32CharMap[key] = val;
	}
	
	bool Test12MapUint32::containsKey_MapOfMyUint32CharMap(const uint32_t &key) const {
		return (m_mapOfMyUint32CharMap.count(key) > 0);
	}
	
	char Test12MapUint32::getValueForKey_MapOfMyUint32CharMap(const uint32_t &key) {
		return m_mapOfMyUint32CharMap[key];
	}
	
	std::pair<std::map<uint32_t, char>::iterator, std::map<uint32_t, char>::iterator> Test12MapUint32::iteratorPair_MapOfMyUint32CharMap() {
		return std::make_pair(m_mapOfMyUint32CharMap.begin(), m_mapOfMyUint32CharMap.end());
	}
	std::map<uint32_t, int32_t> Test12MapUint32::getMapOfMyUint32Int32Map() const {
		return m_mapOfMyUint32Int32Map;
	}
	
	void Test12MapUint32::setMapOfMyUint32Int32Map(const std::map<uint32_t, int32_t> &val) {
		m_mapOfMyUint32Int32Map = val;
	}
	
	void Test12MapUint32::clear_MapOfMyUint32Int32Map() {
		m_mapOfMyUint32Int32Map.clear();
	}
	
	uint32_t Test12MapUint32::getSize_MapOfMyUint32Int32Map() const {
		return m_mapOfMyUint32Int32Map.size();
	}
	
	bool Test12MapUint32::isEmpty_MapOfMyUint32Int32Map() const {
		return m_mapOfMyUint32Int32Map.empty();
	}
	
	void Test12MapUint32::putTo_MapOfMyUint32Int32Map(const uint32_t &key, const int32_t &val) {
		m_mapOfMyUint32Int32Map[key] = val;
	}
	
	bool Test12MapUint32::containsKey_MapOfMyUint32Int32Map(const uint32_t &key) const {
		return (m_mapOfMyUint32Int32Map.count(key) > 0);
	}
	
	int32_t Test12MapUint32::getValueForKey_MapOfMyUint32Int32Map(const uint32_t &key) {
		return m_mapOfMyUint32Int32Map[key];
	}
	
	std::pair<std::map<uint32_t, int32_t>::iterator, std::map<uint32_t, int32_t>::iterator> Test12MapUint32::iteratorPair_MapOfMyUint32Int32Map() {
		return std::make_pair(m_mapOfMyUint32Int32Map.begin(), m_mapOfMyUint32Int32Map.end());
	}
	std::map<uint32_t, uint32_t> Test12MapUint32::getMapOfMyUint32Uint32Map() const {
		return m_mapOfMyUint32Uint32Map;
	}
	
	void Test12MapUint32::setMapOfMyUint32Uint32Map(const std::map<uint32_t, uint32_t> &val) {
		m_mapOfMyUint32Uint32Map = val;
	}
	
	void Test12MapUint32::clear_MapOfMyUint32Uint32Map() {
		m_mapOfMyUint32Uint32Map.clear();
	}
	
	uint32_t Test12MapUint32::getSize_MapOfMyUint32Uint32Map() const {
		return m_mapOfMyUint32Uint32Map.size();
	}
	
	bool Test12MapUint32::isEmpty_MapOfMyUint32Uint32Map() const {
		return m_mapOfMyUint32Uint32Map.empty();
	}
	
	void Test12MapUint32::putTo_MapOfMyUint32Uint32Map(const uint32_t &key, const uint32_t &val) {
		m_mapOfMyUint32Uint32Map[key] = val;
	}
	
	bool Test12MapUint32::containsKey_MapOfMyUint32Uint32Map(const uint32_t &key) const {
		return (m_mapOfMyUint32Uint32Map.count(key) > 0);
	}
	
	uint32_t Test12MapUint32::getValueForKey_MapOfMyUint32Uint32Map(const uint32_t &key) {
		return m_mapOfMyUint32Uint32Map[key];
	}
	
	std::pair<std::map<uint32_t, uint32_t>::iterator, std::map<uint32_t, uint32_t>::iterator> Test12MapUint32::iteratorPair_MapOfMyUint32Uint32Map() {
		return std::make_pair(m_mapOfMyUint32Uint32Map.begin(), m_mapOfMyUint32Uint32Map.end());
	}
	std::map<uint32_t, float> Test12MapUint32::getMapOfMyUint32FloatMap() const {
		return m_mapOfMyUint32FloatMap;
	}
	
	void Test12MapUint32::setMapOfMyUint32FloatMap(const std::map<uint32_t, float> &val) {
		m_mapOfMyUint32FloatMap = val;
	}
	
	void Test12MapUint32::clear_MapOfMyUint32FloatMap() {
		m_mapOfMyUint32FloatMap.clear();
	}
	
	uint32_t Test12MapUint32::getSize_MapOfMyUint32FloatMap() const {
		return m_mapOfMyUint32FloatMap.size();
	}
	
	bool Test12MapUint32::isEmpty_MapOfMyUint32FloatMap() const {
		return m_mapOfMyUint32FloatMap.empty();
	}
	
	void Test12MapUint32::putTo_MapOfMyUint32FloatMap(const uint32_t &key, const float &val) {
		m_mapOfMyUint32FloatMap[key] = val;
	}
	
	bool Test12MapUint32::containsKey_MapOfMyUint32FloatMap(const uint32_t &key) const {
		return (m_mapOfMyUint32FloatMap.count(key) > 0);
	}
	
	float Test12MapUint32::getValueForKey_MapOfMyUint32FloatMap(const uint32_t &key) {
		return m_mapOfMyUint32FloatMap[key];
	}
	
	std::pair<std::map<uint32_t, float>::iterator, std::map<uint32_t, float>::iterator> Test12MapUint32::iteratorPair_MapOfMyUint32FloatMap() {
		return std::make_pair(m_mapOfMyUint32FloatMap.begin(), m_mapOfMyUint32FloatMap.end());
	}
	std::map<uint32_t, double> Test12MapUint32::getMapOfMyUint32DoubleMap() const {
		return m_mapOfMyUint32DoubleMap;
	}
	
	void Test12MapUint32::setMapOfMyUint32DoubleMap(const std::map<uint32_t, double> &val) {
		m_mapOfMyUint32DoubleMap = val;
	}
	
	void Test12MapUint32::clear_MapOfMyUint32DoubleMap() {
		m_mapOfMyUint32DoubleMap.clear();
	}
	
	uint32_t Test12MapUint32::getSize_MapOfMyUint32DoubleMap() const {
		return m_mapOfMyUint32DoubleMap.size();
	}
	
	bool Test12MapUint32::isEmpty_MapOfMyUint32DoubleMap() const {
		return m_mapOfMyUint32DoubleMap.empty();
	}
	
	void Test12MapUint32::putTo_MapOfMyUint32DoubleMap(const uint32_t &key, const double &val) {
		m_mapOfMyUint32DoubleMap[key] = val;
	}
	
	bool Test12MapUint32::containsKey_MapOfMyUint32DoubleMap(const uint32_t &key) const {
		return (m_mapOfMyUint32DoubleMap.count(key) > 0);
	}
	
	double Test12MapUint32::getValueForKey_MapOfMyUint32DoubleMap(const uint32_t &key) {
		return m_mapOfMyUint32DoubleMap[key];
	}
	
	std::pair<std::map<uint32_t, double>::iterator, std::map<uint32_t, double>::iterator> Test12MapUint32::iteratorPair_MapOfMyUint32DoubleMap() {
		return std::make_pair(m_mapOfMyUint32DoubleMap.begin(), m_mapOfMyUint32DoubleMap.end());
	}
	std::map<uint32_t, std::string> Test12MapUint32::getMapOfMyUint32StringMap() const {
		return m_mapOfMyUint32StringMap;
	}
	
	void Test12MapUint32::setMapOfMyUint32StringMap(const std::map<uint32_t, std::string> &val) {
		m_mapOfMyUint32StringMap = val;
	}
	
	void Test12MapUint32::clear_MapOfMyUint32StringMap() {
		m_mapOfMyUint32StringMap.clear();
	}
	
	uint32_t Test12MapUint32::getSize_MapOfMyUint32StringMap() const {
		return m_mapOfMyUint32StringMap.size();
	}
	
	bool Test12MapUint32::isEmpty_MapOfMyUint32StringMap() const {
		return m_mapOfMyUint32StringMap.empty();
	}
	
	void Test12MapUint32::putTo_MapOfMyUint32StringMap(const uint32_t &key, const std::string &val) {
		m_mapOfMyUint32StringMap[key] = val;
	}
	
	bool Test12MapUint32::containsKey_MapOfMyUint32StringMap(const uint32_t &key) const {
		return (m_mapOfMyUint32StringMap.count(key) > 0);
	}
	
	std::string Test12MapUint32::getValueForKey_MapOfMyUint32StringMap(const uint32_t &key) {
		return m_mapOfMyUint32StringMap[key];
	}
	
	std::pair<std::map<uint32_t, std::string>::iterator, std::map<uint32_t, std::string>::iterator> Test12MapUint32::iteratorPair_MapOfMyUint32StringMap() {
		return std::make_pair(m_mapOfMyUint32StringMap.begin(), m_mapOfMyUint32StringMap.end());
	}

	void Test12MapUint32::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test12MapUint32::toString() const {
		stringstream s;


		s << "Number of elements in map of MyUint32BoolMap: " << getSize_MapOfMyUint32BoolMap() << " ";
		s << "Number of elements in map of MyUint32CharMap: " << getSize_MapOfMyUint32CharMap() << " ";
		s << "Number of elements in map of MyUint32Int32Map: " << getSize_MapOfMyUint32Int32Map() << " ";
		s << "Number of elements in map of MyUint32Uint32Map: " << getSize_MapOfMyUint32Uint32Map() << " ";
		s << "Number of elements in map of MyUint32FloatMap: " << getSize_MapOfMyUint32FloatMap() << " ";
		s << "Number of elements in map of MyUint32DoubleMap: " << getSize_MapOfMyUint32DoubleMap() << " ";
		s << "Number of elements in map of MyUint32StringMap: " << getSize_MapOfMyUint32StringMap() << " ";

		return s.str();
	}

	ostream& Test12MapUint32::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		{
			// Write number of elements in m_mapOfMyUint32BoolMap.
			const uint32_t numberOfMyUint32BoolMap = static_cast<uint32_t>(m_mapOfMyUint32BoolMap.size());
			s->write(1, numberOfMyUint32BoolMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyUint32BoolMap;
			std::map<uint32_t, bool>::const_iterator it = m_mapOfMyUint32BoolMap.begin();
			while (it != m_mapOfMyUint32BoolMap.end()) {
			    sstrOfMyUint32BoolMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyUint32BoolMap > 0) {
				s->write(1 + 7, sstrOfMyUint32BoolMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyUint32CharMap.
			const uint32_t numberOfMyUint32CharMap = static_cast<uint32_t>(m_mapOfMyUint32CharMap.size());
			s->write(2, numberOfMyUint32CharMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyUint32CharMap;
			std::map<uint32_t, char>::const_iterator it = m_mapOfMyUint32CharMap.begin();
			while (it != m_mapOfMyUint32CharMap.end()) {
			    sstrOfMyUint32CharMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyUint32CharMap > 0) {
				s->write(2 + 7, sstrOfMyUint32CharMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyUint32Int32Map.
			const uint32_t numberOfMyUint32Int32Map = static_cast<uint32_t>(m_mapOfMyUint32Int32Map.size());
			s->write(3, numberOfMyUint32Int32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyUint32Int32Map;
			std::map<uint32_t, int32_t>::const_iterator it = m_mapOfMyUint32Int32Map.begin();
			while (it != m_mapOfMyUint32Int32Map.end()) {
			    sstrOfMyUint32Int32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyUint32Int32Map > 0) {
				s->write(3 + 7, sstrOfMyUint32Int32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyUint32Uint32Map.
			const uint32_t numberOfMyUint32Uint32Map = static_cast<uint32_t>(m_mapOfMyUint32Uint32Map.size());
			s->write(4, numberOfMyUint32Uint32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyUint32Uint32Map;
			std::map<uint32_t, uint32_t>::const_iterator it = m_mapOfMyUint32Uint32Map.begin();
			while (it != m_mapOfMyUint32Uint32Map.end()) {
			    sstrOfMyUint32Uint32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyUint32Uint32Map > 0) {
				s->write(4 + 7, sstrOfMyUint32Uint32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyUint32FloatMap.
			const uint32_t numberOfMyUint32FloatMap = static_cast<uint32_t>(m_mapOfMyUint32FloatMap.size());
			s->write(5, numberOfMyUint32FloatMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyUint32FloatMap;
			std::map<uint32_t, float>::const_iterator it = m_mapOfMyUint32FloatMap.begin();
			while (it != m_mapOfMyUint32FloatMap.end()) {
			    sstrOfMyUint32FloatMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyUint32FloatMap > 0) {
				s->write(5 + 7, sstrOfMyUint32FloatMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyUint32DoubleMap.
			const uint32_t numberOfMyUint32DoubleMap = static_cast<uint32_t>(m_mapOfMyUint32DoubleMap.size());
			s->write(6, numberOfMyUint32DoubleMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyUint32DoubleMap;
			std::map<uint32_t, double>::const_iterator it = m_mapOfMyUint32DoubleMap.begin();
			while (it != m_mapOfMyUint32DoubleMap.end()) {
			    sstrOfMyUint32DoubleMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyUint32DoubleMap > 0) {
				s->write(6 + 7, sstrOfMyUint32DoubleMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyUint32StringMap.
			const uint32_t numberOfMyUint32StringMap = static_cast<uint32_t>(m_mapOfMyUint32StringMap.size());
			s->write(7, numberOfMyUint32StringMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyUint32StringMap;
			std::map<uint32_t, std::string>::const_iterator it = m_mapOfMyUint32StringMap.begin();
			while (it != m_mapOfMyUint32StringMap.end()) {
			    sstrOfMyUint32StringMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyUint32StringMap > 0) {
				s->write(7 + 7, sstrOfMyUint32StringMap.str());
			}
		}
		return out;
	}

	istream& Test12MapUint32::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing map of MyUint32BoolMap.
		m_mapOfMyUint32BoolMap.clear();
		
		// Read number of elements in m_mapOfMyUint32BoolMap.
		uint32_t numberOfMyUint32BoolMap = 0;
		d->read(1, numberOfMyUint32BoolMap);
		
		if (numberOfMyUint32BoolMap > 0) {
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
			    uint32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    bool _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyUint32BoolMap(_key, _value);
			}
		}
		// Clean up the existing map of MyUint32CharMap.
		m_mapOfMyUint32CharMap.clear();
		
		// Read number of elements in m_mapOfMyUint32CharMap.
		uint32_t numberOfMyUint32CharMap = 0;
		d->read(2, numberOfMyUint32CharMap);
		
		if (numberOfMyUint32CharMap > 0) {
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
			    uint32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    char _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyUint32CharMap(_key, _value);
			}
		}
		// Clean up the existing map of MyUint32Int32Map.
		m_mapOfMyUint32Int32Map.clear();
		
		// Read number of elements in m_mapOfMyUint32Int32Map.
		uint32_t numberOfMyUint32Int32Map = 0;
		d->read(3, numberOfMyUint32Int32Map);
		
		if (numberOfMyUint32Int32Map > 0) {
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
			    uint32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    int32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyUint32Int32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyUint32Uint32Map.
		m_mapOfMyUint32Uint32Map.clear();
		
		// Read number of elements in m_mapOfMyUint32Uint32Map.
		uint32_t numberOfMyUint32Uint32Map = 0;
		d->read(4, numberOfMyUint32Uint32Map);
		
		if (numberOfMyUint32Uint32Map > 0) {
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
			    uint32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    uint32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyUint32Uint32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyUint32FloatMap.
		m_mapOfMyUint32FloatMap.clear();
		
		// Read number of elements in m_mapOfMyUint32FloatMap.
		uint32_t numberOfMyUint32FloatMap = 0;
		d->read(5, numberOfMyUint32FloatMap);
		
		if (numberOfMyUint32FloatMap > 0) {
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
			    uint32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    float _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyUint32FloatMap(_key, _value);
			}
		}
		// Clean up the existing map of MyUint32DoubleMap.
		m_mapOfMyUint32DoubleMap.clear();
		
		// Read number of elements in m_mapOfMyUint32DoubleMap.
		uint32_t numberOfMyUint32DoubleMap = 0;
		d->read(6, numberOfMyUint32DoubleMap);
		
		if (numberOfMyUint32DoubleMap > 0) {
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
			    uint32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    double _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyUint32DoubleMap(_key, _value);
			}
		}
		// Clean up the existing map of MyUint32StringMap.
		m_mapOfMyUint32StringMap.clear();
		
		// Read number of elements in m_mapOfMyUint32StringMap.
		uint32_t numberOfMyUint32StringMap = 0;
		d->read(7, numberOfMyUint32StringMap);
		
		if (numberOfMyUint32StringMap > 0) {
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
			    uint32_t _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    std::string _value;
		        getline(sstrValue, _value);
		
				// Store key/value pair.
				putTo_MapOfMyUint32StringMap(_key, _value);
			}
		}
		return in;
	}
