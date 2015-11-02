/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"


#include "generated/Test12MapDouble.h"

	using namespace std;
	using namespace core::base;


	Test12MapDouble::Test12MapDouble() :
	    SerializableData(), Visitable()
		, m_mapOfMyDoubleBoolMap()
		, m_mapOfMyDoubleCharMap()
		, m_mapOfMyDoubleInt32Map()
		, m_mapOfMyDoubleUint32Map()
		, m_mapOfMyDoubleFloatMap()
		, m_mapOfMyDoubleDoubleMap()
		, m_mapOfMyDoubleStringMap()
	{
	}

	Test12MapDouble::Test12MapDouble(
		const map<double, bool> &val0, 
		const map<double, char> &val1, 
		const map<double, int32_t> &val2, 
		const map<double, uint32_t> &val3, 
		const map<double, float> &val4, 
		const map<double, double> &val5, 
		const map<double, std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_mapOfMyDoubleBoolMap(val0)
		, m_mapOfMyDoubleCharMap(val1)
		, m_mapOfMyDoubleInt32Map(val2)
		, m_mapOfMyDoubleUint32Map(val3)
		, m_mapOfMyDoubleFloatMap(val4)
		, m_mapOfMyDoubleDoubleMap(val5)
		, m_mapOfMyDoubleStringMap(val6)
	{
	}

	Test12MapDouble::Test12MapDouble(const Test12MapDouble &obj) :
	    SerializableData(), Visitable()
		, m_mapOfMyDoubleBoolMap(obj.m_mapOfMyDoubleBoolMap)
		, m_mapOfMyDoubleCharMap(obj.m_mapOfMyDoubleCharMap)
		, m_mapOfMyDoubleInt32Map(obj.m_mapOfMyDoubleInt32Map)
		, m_mapOfMyDoubleUint32Map(obj.m_mapOfMyDoubleUint32Map)
		, m_mapOfMyDoubleFloatMap(obj.m_mapOfMyDoubleFloatMap)
		, m_mapOfMyDoubleDoubleMap(obj.m_mapOfMyDoubleDoubleMap)
		, m_mapOfMyDoubleStringMap(obj.m_mapOfMyDoubleStringMap)
	{
	}
	
	Test12MapDouble::~Test12MapDouble() {
	}

	Test12MapDouble& Test12MapDouble::operator=(const Test12MapDouble &obj) {
		m_mapOfMyDoubleBoolMap = obj.m_mapOfMyDoubleBoolMap;
		m_mapOfMyDoubleCharMap = obj.m_mapOfMyDoubleCharMap;
		m_mapOfMyDoubleInt32Map = obj.m_mapOfMyDoubleInt32Map;
		m_mapOfMyDoubleUint32Map = obj.m_mapOfMyDoubleUint32Map;
		m_mapOfMyDoubleFloatMap = obj.m_mapOfMyDoubleFloatMap;
		m_mapOfMyDoubleDoubleMap = obj.m_mapOfMyDoubleDoubleMap;
		m_mapOfMyDoubleStringMap = obj.m_mapOfMyDoubleStringMap;
		return (*this);
	}

	int32_t Test12MapDouble::ID() {
		return 19;
	}

	const string Test12MapDouble::ShortName() {
		return "Test12MapDouble";
	}

	const string Test12MapDouble::LongName() {
		return "Test12MapDouble";
	}

	int32_t Test12MapDouble::getID() const {
		return Test12MapDouble::ID();
	}

	const string Test12MapDouble::getShortName() const {
		return Test12MapDouble::ShortName();
	}

	const string Test12MapDouble::getLongName() const {
		return Test12MapDouble::LongName();
	}

	std::map<double, bool> Test12MapDouble::getMapOfMyDoubleBoolMap() const {
		return m_mapOfMyDoubleBoolMap;
	}
	
	void Test12MapDouble::setMapOfMyDoubleBoolMap(const std::map<double, bool> &val) {
		m_mapOfMyDoubleBoolMap = val;
	}
	
	void Test12MapDouble::clear_MapOfMyDoubleBoolMap() {
		m_mapOfMyDoubleBoolMap.clear();
	}
	
	uint32_t Test12MapDouble::getSize_MapOfMyDoubleBoolMap() const {
		return m_mapOfMyDoubleBoolMap.size();
	}
	
	bool Test12MapDouble::isEmpty_MapOfMyDoubleBoolMap() const {
		return m_mapOfMyDoubleBoolMap.empty();
	}
	
	void Test12MapDouble::putTo_MapOfMyDoubleBoolMap(const double &key, const bool &val) {
		m_mapOfMyDoubleBoolMap[key] = val;
	}
	
	bool Test12MapDouble::containsKey_MapOfMyDoubleBoolMap(const double &key) const {
		return (m_mapOfMyDoubleBoolMap.count(key) > 0);
	}
	
	bool Test12MapDouble::getValueForKey_MapOfMyDoubleBoolMap(const double &key) {
		return m_mapOfMyDoubleBoolMap[key];
	}
	
	std::pair<std::map<double, bool>::iterator, std::map<double, bool>::iterator> Test12MapDouble::iteratorPair_MapOfMyDoubleBoolMap() {
		return std::make_pair(m_mapOfMyDoubleBoolMap.begin(), m_mapOfMyDoubleBoolMap.end());
	}
	std::map<double, char> Test12MapDouble::getMapOfMyDoubleCharMap() const {
		return m_mapOfMyDoubleCharMap;
	}
	
	void Test12MapDouble::setMapOfMyDoubleCharMap(const std::map<double, char> &val) {
		m_mapOfMyDoubleCharMap = val;
	}
	
	void Test12MapDouble::clear_MapOfMyDoubleCharMap() {
		m_mapOfMyDoubleCharMap.clear();
	}
	
	uint32_t Test12MapDouble::getSize_MapOfMyDoubleCharMap() const {
		return m_mapOfMyDoubleCharMap.size();
	}
	
	bool Test12MapDouble::isEmpty_MapOfMyDoubleCharMap() const {
		return m_mapOfMyDoubleCharMap.empty();
	}
	
	void Test12MapDouble::putTo_MapOfMyDoubleCharMap(const double &key, const char &val) {
		m_mapOfMyDoubleCharMap[key] = val;
	}
	
	bool Test12MapDouble::containsKey_MapOfMyDoubleCharMap(const double &key) const {
		return (m_mapOfMyDoubleCharMap.count(key) > 0);
	}
	
	char Test12MapDouble::getValueForKey_MapOfMyDoubleCharMap(const double &key) {
		return m_mapOfMyDoubleCharMap[key];
	}
	
	std::pair<std::map<double, char>::iterator, std::map<double, char>::iterator> Test12MapDouble::iteratorPair_MapOfMyDoubleCharMap() {
		return std::make_pair(m_mapOfMyDoubleCharMap.begin(), m_mapOfMyDoubleCharMap.end());
	}
	std::map<double, int32_t> Test12MapDouble::getMapOfMyDoubleInt32Map() const {
		return m_mapOfMyDoubleInt32Map;
	}
	
	void Test12MapDouble::setMapOfMyDoubleInt32Map(const std::map<double, int32_t> &val) {
		m_mapOfMyDoubleInt32Map = val;
	}
	
	void Test12MapDouble::clear_MapOfMyDoubleInt32Map() {
		m_mapOfMyDoubleInt32Map.clear();
	}
	
	uint32_t Test12MapDouble::getSize_MapOfMyDoubleInt32Map() const {
		return m_mapOfMyDoubleInt32Map.size();
	}
	
	bool Test12MapDouble::isEmpty_MapOfMyDoubleInt32Map() const {
		return m_mapOfMyDoubleInt32Map.empty();
	}
	
	void Test12MapDouble::putTo_MapOfMyDoubleInt32Map(const double &key, const int32_t &val) {
		m_mapOfMyDoubleInt32Map[key] = val;
	}
	
	bool Test12MapDouble::containsKey_MapOfMyDoubleInt32Map(const double &key) const {
		return (m_mapOfMyDoubleInt32Map.count(key) > 0);
	}
	
	int32_t Test12MapDouble::getValueForKey_MapOfMyDoubleInt32Map(const double &key) {
		return m_mapOfMyDoubleInt32Map[key];
	}
	
	std::pair<std::map<double, int32_t>::iterator, std::map<double, int32_t>::iterator> Test12MapDouble::iteratorPair_MapOfMyDoubleInt32Map() {
		return std::make_pair(m_mapOfMyDoubleInt32Map.begin(), m_mapOfMyDoubleInt32Map.end());
	}
	std::map<double, uint32_t> Test12MapDouble::getMapOfMyDoubleUint32Map() const {
		return m_mapOfMyDoubleUint32Map;
	}
	
	void Test12MapDouble::setMapOfMyDoubleUint32Map(const std::map<double, uint32_t> &val) {
		m_mapOfMyDoubleUint32Map = val;
	}
	
	void Test12MapDouble::clear_MapOfMyDoubleUint32Map() {
		m_mapOfMyDoubleUint32Map.clear();
	}
	
	uint32_t Test12MapDouble::getSize_MapOfMyDoubleUint32Map() const {
		return m_mapOfMyDoubleUint32Map.size();
	}
	
	bool Test12MapDouble::isEmpty_MapOfMyDoubleUint32Map() const {
		return m_mapOfMyDoubleUint32Map.empty();
	}
	
	void Test12MapDouble::putTo_MapOfMyDoubleUint32Map(const double &key, const uint32_t &val) {
		m_mapOfMyDoubleUint32Map[key] = val;
	}
	
	bool Test12MapDouble::containsKey_MapOfMyDoubleUint32Map(const double &key) const {
		return (m_mapOfMyDoubleUint32Map.count(key) > 0);
	}
	
	uint32_t Test12MapDouble::getValueForKey_MapOfMyDoubleUint32Map(const double &key) {
		return m_mapOfMyDoubleUint32Map[key];
	}
	
	std::pair<std::map<double, uint32_t>::iterator, std::map<double, uint32_t>::iterator> Test12MapDouble::iteratorPair_MapOfMyDoubleUint32Map() {
		return std::make_pair(m_mapOfMyDoubleUint32Map.begin(), m_mapOfMyDoubleUint32Map.end());
	}
	std::map<double, float> Test12MapDouble::getMapOfMyDoubleFloatMap() const {
		return m_mapOfMyDoubleFloatMap;
	}
	
	void Test12MapDouble::setMapOfMyDoubleFloatMap(const std::map<double, float> &val) {
		m_mapOfMyDoubleFloatMap = val;
	}
	
	void Test12MapDouble::clear_MapOfMyDoubleFloatMap() {
		m_mapOfMyDoubleFloatMap.clear();
	}
	
	uint32_t Test12MapDouble::getSize_MapOfMyDoubleFloatMap() const {
		return m_mapOfMyDoubleFloatMap.size();
	}
	
	bool Test12MapDouble::isEmpty_MapOfMyDoubleFloatMap() const {
		return m_mapOfMyDoubleFloatMap.empty();
	}
	
	void Test12MapDouble::putTo_MapOfMyDoubleFloatMap(const double &key, const float &val) {
		m_mapOfMyDoubleFloatMap[key] = val;
	}
	
	bool Test12MapDouble::containsKey_MapOfMyDoubleFloatMap(const double &key) const {
		return (m_mapOfMyDoubleFloatMap.count(key) > 0);
	}
	
	float Test12MapDouble::getValueForKey_MapOfMyDoubleFloatMap(const double &key) {
		return m_mapOfMyDoubleFloatMap[key];
	}
	
	std::pair<std::map<double, float>::iterator, std::map<double, float>::iterator> Test12MapDouble::iteratorPair_MapOfMyDoubleFloatMap() {
		return std::make_pair(m_mapOfMyDoubleFloatMap.begin(), m_mapOfMyDoubleFloatMap.end());
	}
	std::map<double, double> Test12MapDouble::getMapOfMyDoubleDoubleMap() const {
		return m_mapOfMyDoubleDoubleMap;
	}
	
	void Test12MapDouble::setMapOfMyDoubleDoubleMap(const std::map<double, double> &val) {
		m_mapOfMyDoubleDoubleMap = val;
	}
	
	void Test12MapDouble::clear_MapOfMyDoubleDoubleMap() {
		m_mapOfMyDoubleDoubleMap.clear();
	}
	
	uint32_t Test12MapDouble::getSize_MapOfMyDoubleDoubleMap() const {
		return m_mapOfMyDoubleDoubleMap.size();
	}
	
	bool Test12MapDouble::isEmpty_MapOfMyDoubleDoubleMap() const {
		return m_mapOfMyDoubleDoubleMap.empty();
	}
	
	void Test12MapDouble::putTo_MapOfMyDoubleDoubleMap(const double &key, const double &val) {
		m_mapOfMyDoubleDoubleMap[key] = val;
	}
	
	bool Test12MapDouble::containsKey_MapOfMyDoubleDoubleMap(const double &key) const {
		return (m_mapOfMyDoubleDoubleMap.count(key) > 0);
	}
	
	double Test12MapDouble::getValueForKey_MapOfMyDoubleDoubleMap(const double &key) {
		return m_mapOfMyDoubleDoubleMap[key];
	}
	
	std::pair<std::map<double, double>::iterator, std::map<double, double>::iterator> Test12MapDouble::iteratorPair_MapOfMyDoubleDoubleMap() {
		return std::make_pair(m_mapOfMyDoubleDoubleMap.begin(), m_mapOfMyDoubleDoubleMap.end());
	}
	std::map<double, std::string> Test12MapDouble::getMapOfMyDoubleStringMap() const {
		return m_mapOfMyDoubleStringMap;
	}
	
	void Test12MapDouble::setMapOfMyDoubleStringMap(const std::map<double, std::string> &val) {
		m_mapOfMyDoubleStringMap = val;
	}
	
	void Test12MapDouble::clear_MapOfMyDoubleStringMap() {
		m_mapOfMyDoubleStringMap.clear();
	}
	
	uint32_t Test12MapDouble::getSize_MapOfMyDoubleStringMap() const {
		return m_mapOfMyDoubleStringMap.size();
	}
	
	bool Test12MapDouble::isEmpty_MapOfMyDoubleStringMap() const {
		return m_mapOfMyDoubleStringMap.empty();
	}
	
	void Test12MapDouble::putTo_MapOfMyDoubleStringMap(const double &key, const std::string &val) {
		m_mapOfMyDoubleStringMap[key] = val;
	}
	
	bool Test12MapDouble::containsKey_MapOfMyDoubleStringMap(const double &key) const {
		return (m_mapOfMyDoubleStringMap.count(key) > 0);
	}
	
	std::string Test12MapDouble::getValueForKey_MapOfMyDoubleStringMap(const double &key) {
		return m_mapOfMyDoubleStringMap[key];
	}
	
	std::pair<std::map<double, std::string>::iterator, std::map<double, std::string>::iterator> Test12MapDouble::iteratorPair_MapOfMyDoubleStringMap() {
		return std::make_pair(m_mapOfMyDoubleStringMap.begin(), m_mapOfMyDoubleStringMap.end());
	}

	void Test12MapDouble::accept(core::base::Visitor &v) {
		(void)v; // Avoid unused parameter warning.
	}

	const string Test12MapDouble::toString() const {
		stringstream s;


		s << "Number of elements in map of MyDoubleBoolMap: " << getSize_MapOfMyDoubleBoolMap() << " ";
		s << "Number of elements in map of MyDoubleCharMap: " << getSize_MapOfMyDoubleCharMap() << " ";
		s << "Number of elements in map of MyDoubleInt32Map: " << getSize_MapOfMyDoubleInt32Map() << " ";
		s << "Number of elements in map of MyDoubleUint32Map: " << getSize_MapOfMyDoubleUint32Map() << " ";
		s << "Number of elements in map of MyDoubleFloatMap: " << getSize_MapOfMyDoubleFloatMap() << " ";
		s << "Number of elements in map of MyDoubleDoubleMap: " << getSize_MapOfMyDoubleDoubleMap() << " ";
		s << "Number of elements in map of MyDoubleStringMap: " << getSize_MapOfMyDoubleStringMap() << " ";

		return s.str();
	}

	ostream& Test12MapDouble::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		{
			// Write number of elements in m_mapOfMyDoubleBoolMap.
			const uint32_t numberOfMyDoubleBoolMap = static_cast<uint32_t>(m_mapOfMyDoubleBoolMap.size());
			s->write(1, numberOfMyDoubleBoolMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyDoubleBoolMap;
			std::map<double, bool>::const_iterator it = m_mapOfMyDoubleBoolMap.begin();
			while (it != m_mapOfMyDoubleBoolMap.end()) {
			    sstrOfMyDoubleBoolMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyDoubleBoolMap > 0) {
				s->write(1 + 7, sstrOfMyDoubleBoolMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyDoubleCharMap.
			const uint32_t numberOfMyDoubleCharMap = static_cast<uint32_t>(m_mapOfMyDoubleCharMap.size());
			s->write(2, numberOfMyDoubleCharMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyDoubleCharMap;
			std::map<double, char>::const_iterator it = m_mapOfMyDoubleCharMap.begin();
			while (it != m_mapOfMyDoubleCharMap.end()) {
			    sstrOfMyDoubleCharMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyDoubleCharMap > 0) {
				s->write(2 + 7, sstrOfMyDoubleCharMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyDoubleInt32Map.
			const uint32_t numberOfMyDoubleInt32Map = static_cast<uint32_t>(m_mapOfMyDoubleInt32Map.size());
			s->write(3, numberOfMyDoubleInt32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyDoubleInt32Map;
			std::map<double, int32_t>::const_iterator it = m_mapOfMyDoubleInt32Map.begin();
			while (it != m_mapOfMyDoubleInt32Map.end()) {
			    sstrOfMyDoubleInt32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyDoubleInt32Map > 0) {
				s->write(3 + 7, sstrOfMyDoubleInt32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyDoubleUint32Map.
			const uint32_t numberOfMyDoubleUint32Map = static_cast<uint32_t>(m_mapOfMyDoubleUint32Map.size());
			s->write(4, numberOfMyDoubleUint32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyDoubleUint32Map;
			std::map<double, uint32_t>::const_iterator it = m_mapOfMyDoubleUint32Map.begin();
			while (it != m_mapOfMyDoubleUint32Map.end()) {
			    sstrOfMyDoubleUint32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyDoubleUint32Map > 0) {
				s->write(4 + 7, sstrOfMyDoubleUint32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyDoubleFloatMap.
			const uint32_t numberOfMyDoubleFloatMap = static_cast<uint32_t>(m_mapOfMyDoubleFloatMap.size());
			s->write(5, numberOfMyDoubleFloatMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyDoubleFloatMap;
			std::map<double, float>::const_iterator it = m_mapOfMyDoubleFloatMap.begin();
			while (it != m_mapOfMyDoubleFloatMap.end()) {
			    sstrOfMyDoubleFloatMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyDoubleFloatMap > 0) {
				s->write(5 + 7, sstrOfMyDoubleFloatMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyDoubleDoubleMap.
			const uint32_t numberOfMyDoubleDoubleMap = static_cast<uint32_t>(m_mapOfMyDoubleDoubleMap.size());
			s->write(6, numberOfMyDoubleDoubleMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyDoubleDoubleMap;
			std::map<double, double>::const_iterator it = m_mapOfMyDoubleDoubleMap.begin();
			while (it != m_mapOfMyDoubleDoubleMap.end()) {
			    sstrOfMyDoubleDoubleMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyDoubleDoubleMap > 0) {
				s->write(6 + 7, sstrOfMyDoubleDoubleMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyDoubleStringMap.
			const uint32_t numberOfMyDoubleStringMap = static_cast<uint32_t>(m_mapOfMyDoubleStringMap.size());
			s->write(7, numberOfMyDoubleStringMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyDoubleStringMap;
			std::map<double, std::string>::const_iterator it = m_mapOfMyDoubleStringMap.begin();
			while (it != m_mapOfMyDoubleStringMap.end()) {
			    sstrOfMyDoubleStringMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyDoubleStringMap > 0) {
				s->write(7 + 7, sstrOfMyDoubleStringMap.str());
			}
		}
		return out;
	}

	istream& Test12MapDouble::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing map of MyDoubleBoolMap.
		m_mapOfMyDoubleBoolMap.clear();
		
		// Read number of elements in m_mapOfMyDoubleBoolMap.
		uint32_t numberOfMyDoubleBoolMap = 0;
		d->read(1, numberOfMyDoubleBoolMap);
		
		if (numberOfMyDoubleBoolMap > 0) {
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
			    double _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    bool _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyDoubleBoolMap(_key, _value);
			}
		}
		// Clean up the existing map of MyDoubleCharMap.
		m_mapOfMyDoubleCharMap.clear();
		
		// Read number of elements in m_mapOfMyDoubleCharMap.
		uint32_t numberOfMyDoubleCharMap = 0;
		d->read(2, numberOfMyDoubleCharMap);
		
		if (numberOfMyDoubleCharMap > 0) {
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
			    double _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    char _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyDoubleCharMap(_key, _value);
			}
		}
		// Clean up the existing map of MyDoubleInt32Map.
		m_mapOfMyDoubleInt32Map.clear();
		
		// Read number of elements in m_mapOfMyDoubleInt32Map.
		uint32_t numberOfMyDoubleInt32Map = 0;
		d->read(3, numberOfMyDoubleInt32Map);
		
		if (numberOfMyDoubleInt32Map > 0) {
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
			    double _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    int32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyDoubleInt32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyDoubleUint32Map.
		m_mapOfMyDoubleUint32Map.clear();
		
		// Read number of elements in m_mapOfMyDoubleUint32Map.
		uint32_t numberOfMyDoubleUint32Map = 0;
		d->read(4, numberOfMyDoubleUint32Map);
		
		if (numberOfMyDoubleUint32Map > 0) {
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
			    double _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    uint32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyDoubleUint32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyDoubleFloatMap.
		m_mapOfMyDoubleFloatMap.clear();
		
		// Read number of elements in m_mapOfMyDoubleFloatMap.
		uint32_t numberOfMyDoubleFloatMap = 0;
		d->read(5, numberOfMyDoubleFloatMap);
		
		if (numberOfMyDoubleFloatMap > 0) {
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
			    double _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    float _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyDoubleFloatMap(_key, _value);
			}
		}
		// Clean up the existing map of MyDoubleDoubleMap.
		m_mapOfMyDoubleDoubleMap.clear();
		
		// Read number of elements in m_mapOfMyDoubleDoubleMap.
		uint32_t numberOfMyDoubleDoubleMap = 0;
		d->read(6, numberOfMyDoubleDoubleMap);
		
		if (numberOfMyDoubleDoubleMap > 0) {
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
			    double _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    double _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyDoubleDoubleMap(_key, _value);
			}
		}
		// Clean up the existing map of MyDoubleStringMap.
		m_mapOfMyDoubleStringMap.clear();
		
		// Read number of elements in m_mapOfMyDoubleStringMap.
		uint32_t numberOfMyDoubleStringMap = 0;
		d->read(7, numberOfMyDoubleStringMap);
		
		if (numberOfMyDoubleStringMap > 0) {
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
			    double _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    std::string _value;
		        getline(sstrValue, _value);
		
				// Store key/value pair.
				putTo_MapOfMyDoubleStringMap(_key, _value);
			}
		}
		return in;
	}
