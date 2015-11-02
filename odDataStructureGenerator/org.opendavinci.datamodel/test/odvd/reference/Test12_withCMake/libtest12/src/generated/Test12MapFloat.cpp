/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"


#include "generated/Test12MapFloat.h"

	using namespace std;
	using namespace core::base;


	Test12MapFloat::Test12MapFloat() :
	    SerializableData(), Visitable()
		, m_mapOfMyFloatBoolMap()
		, m_mapOfMyFloatCharMap()
		, m_mapOfMyFloatInt32Map()
		, m_mapOfMyFloatUint32Map()
		, m_mapOfMyFloatFloatMap()
		, m_mapOfMyFloatDoubleMap()
		, m_mapOfMyFloatStringMap()
	{
	}

	Test12MapFloat::Test12MapFloat(
		const map<float, bool> &val0, 
		const map<float, char> &val1, 
		const map<float, int32_t> &val2, 
		const map<float, uint32_t> &val3, 
		const map<float, float> &val4, 
		const map<float, double> &val5, 
		const map<float, std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_mapOfMyFloatBoolMap(val0)
		, m_mapOfMyFloatCharMap(val1)
		, m_mapOfMyFloatInt32Map(val2)
		, m_mapOfMyFloatUint32Map(val3)
		, m_mapOfMyFloatFloatMap(val4)
		, m_mapOfMyFloatDoubleMap(val5)
		, m_mapOfMyFloatStringMap(val6)
	{
	}

	Test12MapFloat::Test12MapFloat(const Test12MapFloat &obj) :
	    SerializableData(), Visitable()
		, m_mapOfMyFloatBoolMap(obj.m_mapOfMyFloatBoolMap)
		, m_mapOfMyFloatCharMap(obj.m_mapOfMyFloatCharMap)
		, m_mapOfMyFloatInt32Map(obj.m_mapOfMyFloatInt32Map)
		, m_mapOfMyFloatUint32Map(obj.m_mapOfMyFloatUint32Map)
		, m_mapOfMyFloatFloatMap(obj.m_mapOfMyFloatFloatMap)
		, m_mapOfMyFloatDoubleMap(obj.m_mapOfMyFloatDoubleMap)
		, m_mapOfMyFloatStringMap(obj.m_mapOfMyFloatStringMap)
	{
	}
	
	Test12MapFloat::~Test12MapFloat() {
	}

	Test12MapFloat& Test12MapFloat::operator=(const Test12MapFloat &obj) {
		m_mapOfMyFloatBoolMap = obj.m_mapOfMyFloatBoolMap;
		m_mapOfMyFloatCharMap = obj.m_mapOfMyFloatCharMap;
		m_mapOfMyFloatInt32Map = obj.m_mapOfMyFloatInt32Map;
		m_mapOfMyFloatUint32Map = obj.m_mapOfMyFloatUint32Map;
		m_mapOfMyFloatFloatMap = obj.m_mapOfMyFloatFloatMap;
		m_mapOfMyFloatDoubleMap = obj.m_mapOfMyFloatDoubleMap;
		m_mapOfMyFloatStringMap = obj.m_mapOfMyFloatStringMap;
		return (*this);
	}

	int32_t Test12MapFloat::ID() {
		return 18;
	}

	const string Test12MapFloat::ShortName() {
		return "Test12MapFloat";
	}

	const string Test12MapFloat::LongName() {
		return "Test12MapFloat";
	}

	int32_t Test12MapFloat::getID() const {
		return Test12MapFloat::ID();
	}

	const string Test12MapFloat::getShortName() const {
		return Test12MapFloat::ShortName();
	}

	const string Test12MapFloat::getLongName() const {
		return Test12MapFloat::LongName();
	}

	std::map<float, bool> Test12MapFloat::getMapOfMyFloatBoolMap() const {
		return m_mapOfMyFloatBoolMap;
	}
	
	void Test12MapFloat::setMapOfMyFloatBoolMap(const std::map<float, bool> &val) {
		m_mapOfMyFloatBoolMap = val;
	}
	
	void Test12MapFloat::clear_MapOfMyFloatBoolMap() {
		m_mapOfMyFloatBoolMap.clear();
	}
	
	uint32_t Test12MapFloat::getSize_MapOfMyFloatBoolMap() const {
		return m_mapOfMyFloatBoolMap.size();
	}
	
	bool Test12MapFloat::isEmpty_MapOfMyFloatBoolMap() const {
		return m_mapOfMyFloatBoolMap.empty();
	}
	
	void Test12MapFloat::putTo_MapOfMyFloatBoolMap(const float &key, const bool &val) {
		m_mapOfMyFloatBoolMap[key] = val;
	}
	
	bool Test12MapFloat::containsKey_MapOfMyFloatBoolMap(const float &key) const {
		return (m_mapOfMyFloatBoolMap.count(key) > 0);
	}
	
	bool Test12MapFloat::getValueForKey_MapOfMyFloatBoolMap(const float &key) {
		return m_mapOfMyFloatBoolMap[key];
	}
	
	std::pair<std::map<float, bool>::iterator, std::map<float, bool>::iterator> Test12MapFloat::iteratorPair_MapOfMyFloatBoolMap() {
		return std::make_pair(m_mapOfMyFloatBoolMap.begin(), m_mapOfMyFloatBoolMap.end());
	}
	std::map<float, char> Test12MapFloat::getMapOfMyFloatCharMap() const {
		return m_mapOfMyFloatCharMap;
	}
	
	void Test12MapFloat::setMapOfMyFloatCharMap(const std::map<float, char> &val) {
		m_mapOfMyFloatCharMap = val;
	}
	
	void Test12MapFloat::clear_MapOfMyFloatCharMap() {
		m_mapOfMyFloatCharMap.clear();
	}
	
	uint32_t Test12MapFloat::getSize_MapOfMyFloatCharMap() const {
		return m_mapOfMyFloatCharMap.size();
	}
	
	bool Test12MapFloat::isEmpty_MapOfMyFloatCharMap() const {
		return m_mapOfMyFloatCharMap.empty();
	}
	
	void Test12MapFloat::putTo_MapOfMyFloatCharMap(const float &key, const char &val) {
		m_mapOfMyFloatCharMap[key] = val;
	}
	
	bool Test12MapFloat::containsKey_MapOfMyFloatCharMap(const float &key) const {
		return (m_mapOfMyFloatCharMap.count(key) > 0);
	}
	
	char Test12MapFloat::getValueForKey_MapOfMyFloatCharMap(const float &key) {
		return m_mapOfMyFloatCharMap[key];
	}
	
	std::pair<std::map<float, char>::iterator, std::map<float, char>::iterator> Test12MapFloat::iteratorPair_MapOfMyFloatCharMap() {
		return std::make_pair(m_mapOfMyFloatCharMap.begin(), m_mapOfMyFloatCharMap.end());
	}
	std::map<float, int32_t> Test12MapFloat::getMapOfMyFloatInt32Map() const {
		return m_mapOfMyFloatInt32Map;
	}
	
	void Test12MapFloat::setMapOfMyFloatInt32Map(const std::map<float, int32_t> &val) {
		m_mapOfMyFloatInt32Map = val;
	}
	
	void Test12MapFloat::clear_MapOfMyFloatInt32Map() {
		m_mapOfMyFloatInt32Map.clear();
	}
	
	uint32_t Test12MapFloat::getSize_MapOfMyFloatInt32Map() const {
		return m_mapOfMyFloatInt32Map.size();
	}
	
	bool Test12MapFloat::isEmpty_MapOfMyFloatInt32Map() const {
		return m_mapOfMyFloatInt32Map.empty();
	}
	
	void Test12MapFloat::putTo_MapOfMyFloatInt32Map(const float &key, const int32_t &val) {
		m_mapOfMyFloatInt32Map[key] = val;
	}
	
	bool Test12MapFloat::containsKey_MapOfMyFloatInt32Map(const float &key) const {
		return (m_mapOfMyFloatInt32Map.count(key) > 0);
	}
	
	int32_t Test12MapFloat::getValueForKey_MapOfMyFloatInt32Map(const float &key) {
		return m_mapOfMyFloatInt32Map[key];
	}
	
	std::pair<std::map<float, int32_t>::iterator, std::map<float, int32_t>::iterator> Test12MapFloat::iteratorPair_MapOfMyFloatInt32Map() {
		return std::make_pair(m_mapOfMyFloatInt32Map.begin(), m_mapOfMyFloatInt32Map.end());
	}
	std::map<float, uint32_t> Test12MapFloat::getMapOfMyFloatUint32Map() const {
		return m_mapOfMyFloatUint32Map;
	}
	
	void Test12MapFloat::setMapOfMyFloatUint32Map(const std::map<float, uint32_t> &val) {
		m_mapOfMyFloatUint32Map = val;
	}
	
	void Test12MapFloat::clear_MapOfMyFloatUint32Map() {
		m_mapOfMyFloatUint32Map.clear();
	}
	
	uint32_t Test12MapFloat::getSize_MapOfMyFloatUint32Map() const {
		return m_mapOfMyFloatUint32Map.size();
	}
	
	bool Test12MapFloat::isEmpty_MapOfMyFloatUint32Map() const {
		return m_mapOfMyFloatUint32Map.empty();
	}
	
	void Test12MapFloat::putTo_MapOfMyFloatUint32Map(const float &key, const uint32_t &val) {
		m_mapOfMyFloatUint32Map[key] = val;
	}
	
	bool Test12MapFloat::containsKey_MapOfMyFloatUint32Map(const float &key) const {
		return (m_mapOfMyFloatUint32Map.count(key) > 0);
	}
	
	uint32_t Test12MapFloat::getValueForKey_MapOfMyFloatUint32Map(const float &key) {
		return m_mapOfMyFloatUint32Map[key];
	}
	
	std::pair<std::map<float, uint32_t>::iterator, std::map<float, uint32_t>::iterator> Test12MapFloat::iteratorPair_MapOfMyFloatUint32Map() {
		return std::make_pair(m_mapOfMyFloatUint32Map.begin(), m_mapOfMyFloatUint32Map.end());
	}
	std::map<float, float> Test12MapFloat::getMapOfMyFloatFloatMap() const {
		return m_mapOfMyFloatFloatMap;
	}
	
	void Test12MapFloat::setMapOfMyFloatFloatMap(const std::map<float, float> &val) {
		m_mapOfMyFloatFloatMap = val;
	}
	
	void Test12MapFloat::clear_MapOfMyFloatFloatMap() {
		m_mapOfMyFloatFloatMap.clear();
	}
	
	uint32_t Test12MapFloat::getSize_MapOfMyFloatFloatMap() const {
		return m_mapOfMyFloatFloatMap.size();
	}
	
	bool Test12MapFloat::isEmpty_MapOfMyFloatFloatMap() const {
		return m_mapOfMyFloatFloatMap.empty();
	}
	
	void Test12MapFloat::putTo_MapOfMyFloatFloatMap(const float &key, const float &val) {
		m_mapOfMyFloatFloatMap[key] = val;
	}
	
	bool Test12MapFloat::containsKey_MapOfMyFloatFloatMap(const float &key) const {
		return (m_mapOfMyFloatFloatMap.count(key) > 0);
	}
	
	float Test12MapFloat::getValueForKey_MapOfMyFloatFloatMap(const float &key) {
		return m_mapOfMyFloatFloatMap[key];
	}
	
	std::pair<std::map<float, float>::iterator, std::map<float, float>::iterator> Test12MapFloat::iteratorPair_MapOfMyFloatFloatMap() {
		return std::make_pair(m_mapOfMyFloatFloatMap.begin(), m_mapOfMyFloatFloatMap.end());
	}
	std::map<float, double> Test12MapFloat::getMapOfMyFloatDoubleMap() const {
		return m_mapOfMyFloatDoubleMap;
	}
	
	void Test12MapFloat::setMapOfMyFloatDoubleMap(const std::map<float, double> &val) {
		m_mapOfMyFloatDoubleMap = val;
	}
	
	void Test12MapFloat::clear_MapOfMyFloatDoubleMap() {
		m_mapOfMyFloatDoubleMap.clear();
	}
	
	uint32_t Test12MapFloat::getSize_MapOfMyFloatDoubleMap() const {
		return m_mapOfMyFloatDoubleMap.size();
	}
	
	bool Test12MapFloat::isEmpty_MapOfMyFloatDoubleMap() const {
		return m_mapOfMyFloatDoubleMap.empty();
	}
	
	void Test12MapFloat::putTo_MapOfMyFloatDoubleMap(const float &key, const double &val) {
		m_mapOfMyFloatDoubleMap[key] = val;
	}
	
	bool Test12MapFloat::containsKey_MapOfMyFloatDoubleMap(const float &key) const {
		return (m_mapOfMyFloatDoubleMap.count(key) > 0);
	}
	
	double Test12MapFloat::getValueForKey_MapOfMyFloatDoubleMap(const float &key) {
		return m_mapOfMyFloatDoubleMap[key];
	}
	
	std::pair<std::map<float, double>::iterator, std::map<float, double>::iterator> Test12MapFloat::iteratorPair_MapOfMyFloatDoubleMap() {
		return std::make_pair(m_mapOfMyFloatDoubleMap.begin(), m_mapOfMyFloatDoubleMap.end());
	}
	std::map<float, std::string> Test12MapFloat::getMapOfMyFloatStringMap() const {
		return m_mapOfMyFloatStringMap;
	}
	
	void Test12MapFloat::setMapOfMyFloatStringMap(const std::map<float, std::string> &val) {
		m_mapOfMyFloatStringMap = val;
	}
	
	void Test12MapFloat::clear_MapOfMyFloatStringMap() {
		m_mapOfMyFloatStringMap.clear();
	}
	
	uint32_t Test12MapFloat::getSize_MapOfMyFloatStringMap() const {
		return m_mapOfMyFloatStringMap.size();
	}
	
	bool Test12MapFloat::isEmpty_MapOfMyFloatStringMap() const {
		return m_mapOfMyFloatStringMap.empty();
	}
	
	void Test12MapFloat::putTo_MapOfMyFloatStringMap(const float &key, const std::string &val) {
		m_mapOfMyFloatStringMap[key] = val;
	}
	
	bool Test12MapFloat::containsKey_MapOfMyFloatStringMap(const float &key) const {
		return (m_mapOfMyFloatStringMap.count(key) > 0);
	}
	
	std::string Test12MapFloat::getValueForKey_MapOfMyFloatStringMap(const float &key) {
		return m_mapOfMyFloatStringMap[key];
	}
	
	std::pair<std::map<float, std::string>::iterator, std::map<float, std::string>::iterator> Test12MapFloat::iteratorPair_MapOfMyFloatStringMap() {
		return std::make_pair(m_mapOfMyFloatStringMap.begin(), m_mapOfMyFloatStringMap.end());
	}

	void Test12MapFloat::accept(core::base::Visitor &v) {
		(void)v; // Avoid unused parameter warning.
	}

	const string Test12MapFloat::toString() const {
		stringstream s;


		s << "Number of elements in map of MyFloatBoolMap: " << getSize_MapOfMyFloatBoolMap() << " ";
		s << "Number of elements in map of MyFloatCharMap: " << getSize_MapOfMyFloatCharMap() << " ";
		s << "Number of elements in map of MyFloatInt32Map: " << getSize_MapOfMyFloatInt32Map() << " ";
		s << "Number of elements in map of MyFloatUint32Map: " << getSize_MapOfMyFloatUint32Map() << " ";
		s << "Number of elements in map of MyFloatFloatMap: " << getSize_MapOfMyFloatFloatMap() << " ";
		s << "Number of elements in map of MyFloatDoubleMap: " << getSize_MapOfMyFloatDoubleMap() << " ";
		s << "Number of elements in map of MyFloatStringMap: " << getSize_MapOfMyFloatStringMap() << " ";

		return s.str();
	}

	ostream& Test12MapFloat::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		{
			// Write number of elements in m_mapOfMyFloatBoolMap.
			const uint32_t numberOfMyFloatBoolMap = static_cast<uint32_t>(m_mapOfMyFloatBoolMap.size());
			s->write(1, numberOfMyFloatBoolMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatBoolMap;
			std::map<float, bool>::const_iterator it = m_mapOfMyFloatBoolMap.begin();
			while (it != m_mapOfMyFloatBoolMap.end()) {
			    sstrOfMyFloatBoolMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatBoolMap > 0) {
				s->write(1 + 7, sstrOfMyFloatBoolMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatCharMap.
			const uint32_t numberOfMyFloatCharMap = static_cast<uint32_t>(m_mapOfMyFloatCharMap.size());
			s->write(2, numberOfMyFloatCharMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatCharMap;
			std::map<float, char>::const_iterator it = m_mapOfMyFloatCharMap.begin();
			while (it != m_mapOfMyFloatCharMap.end()) {
			    sstrOfMyFloatCharMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatCharMap > 0) {
				s->write(2 + 7, sstrOfMyFloatCharMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatInt32Map.
			const uint32_t numberOfMyFloatInt32Map = static_cast<uint32_t>(m_mapOfMyFloatInt32Map.size());
			s->write(3, numberOfMyFloatInt32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatInt32Map;
			std::map<float, int32_t>::const_iterator it = m_mapOfMyFloatInt32Map.begin();
			while (it != m_mapOfMyFloatInt32Map.end()) {
			    sstrOfMyFloatInt32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatInt32Map > 0) {
				s->write(3 + 7, sstrOfMyFloatInt32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatUint32Map.
			const uint32_t numberOfMyFloatUint32Map = static_cast<uint32_t>(m_mapOfMyFloatUint32Map.size());
			s->write(4, numberOfMyFloatUint32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatUint32Map;
			std::map<float, uint32_t>::const_iterator it = m_mapOfMyFloatUint32Map.begin();
			while (it != m_mapOfMyFloatUint32Map.end()) {
			    sstrOfMyFloatUint32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatUint32Map > 0) {
				s->write(4 + 7, sstrOfMyFloatUint32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatFloatMap.
			const uint32_t numberOfMyFloatFloatMap = static_cast<uint32_t>(m_mapOfMyFloatFloatMap.size());
			s->write(5, numberOfMyFloatFloatMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatFloatMap;
			std::map<float, float>::const_iterator it = m_mapOfMyFloatFloatMap.begin();
			while (it != m_mapOfMyFloatFloatMap.end()) {
			    sstrOfMyFloatFloatMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatFloatMap > 0) {
				s->write(5 + 7, sstrOfMyFloatFloatMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatDoubleMap.
			const uint32_t numberOfMyFloatDoubleMap = static_cast<uint32_t>(m_mapOfMyFloatDoubleMap.size());
			s->write(6, numberOfMyFloatDoubleMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatDoubleMap;
			std::map<float, double>::const_iterator it = m_mapOfMyFloatDoubleMap.begin();
			while (it != m_mapOfMyFloatDoubleMap.end()) {
			    sstrOfMyFloatDoubleMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatDoubleMap > 0) {
				s->write(6 + 7, sstrOfMyFloatDoubleMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatStringMap.
			const uint32_t numberOfMyFloatStringMap = static_cast<uint32_t>(m_mapOfMyFloatStringMap.size());
			s->write(7, numberOfMyFloatStringMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatStringMap;
			std::map<float, std::string>::const_iterator it = m_mapOfMyFloatStringMap.begin();
			while (it != m_mapOfMyFloatStringMap.end()) {
			    sstrOfMyFloatStringMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatStringMap > 0) {
				s->write(7 + 7, sstrOfMyFloatStringMap.str());
			}
		}
		return out;
	}

	istream& Test12MapFloat::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing map of MyFloatBoolMap.
		m_mapOfMyFloatBoolMap.clear();
		
		// Read number of elements in m_mapOfMyFloatBoolMap.
		uint32_t numberOfMyFloatBoolMap = 0;
		d->read(1, numberOfMyFloatBoolMap);
		
		if (numberOfMyFloatBoolMap > 0) {
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    bool _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatBoolMap(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatCharMap.
		m_mapOfMyFloatCharMap.clear();
		
		// Read number of elements in m_mapOfMyFloatCharMap.
		uint32_t numberOfMyFloatCharMap = 0;
		d->read(2, numberOfMyFloatCharMap);
		
		if (numberOfMyFloatCharMap > 0) {
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    char _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatCharMap(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatInt32Map.
		m_mapOfMyFloatInt32Map.clear();
		
		// Read number of elements in m_mapOfMyFloatInt32Map.
		uint32_t numberOfMyFloatInt32Map = 0;
		d->read(3, numberOfMyFloatInt32Map);
		
		if (numberOfMyFloatInt32Map > 0) {
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    int32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatInt32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatUint32Map.
		m_mapOfMyFloatUint32Map.clear();
		
		// Read number of elements in m_mapOfMyFloatUint32Map.
		uint32_t numberOfMyFloatUint32Map = 0;
		d->read(4, numberOfMyFloatUint32Map);
		
		if (numberOfMyFloatUint32Map > 0) {
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    uint32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatUint32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatFloatMap.
		m_mapOfMyFloatFloatMap.clear();
		
		// Read number of elements in m_mapOfMyFloatFloatMap.
		uint32_t numberOfMyFloatFloatMap = 0;
		d->read(5, numberOfMyFloatFloatMap);
		
		if (numberOfMyFloatFloatMap > 0) {
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    float _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatFloatMap(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatDoubleMap.
		m_mapOfMyFloatDoubleMap.clear();
		
		// Read number of elements in m_mapOfMyFloatDoubleMap.
		uint32_t numberOfMyFloatDoubleMap = 0;
		d->read(6, numberOfMyFloatDoubleMap);
		
		if (numberOfMyFloatDoubleMap > 0) {
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    double _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatDoubleMap(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatStringMap.
		m_mapOfMyFloatStringMap.clear();
		
		// Read number of elements in m_mapOfMyFloatStringMap.
		uint32_t numberOfMyFloatStringMap = 0;
		d->read(7, numberOfMyFloatStringMap);
		
		if (numberOfMyFloatStringMap > 0) {
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    std::string _value;
		        getline(sstrValue, _value);
		
				// Store key/value pair.
				putTo_MapOfMyFloatStringMap(_key, _value);
			}
		}
		return in;
	}
