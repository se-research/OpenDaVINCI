/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"


#include "generated/Test12MapBool.h"

	using namespace std;
	using namespace core::base;


	Test12MapBool::Test12MapBool() :
	    SerializableData(), Visitable()
		, m_mapOfMyBoolBoolMap()
		, m_mapOfMyBoolCharMap()
		, m_mapOfMyBoolInt32Map()
		, m_mapOfMyBoolUint32Map()
		, m_mapOfMyBoolFloatMap()
		, m_mapOfMyBoolDoubleMap()
		, m_mapOfMyBoolStringMap()
	{
	}

	Test12MapBool::Test12MapBool(
		const map<bool, bool> &val0, 
		const map<bool, char> &val1, 
		const map<bool, int32_t> &val2, 
		const map<bool, uint32_t> &val3, 
		const map<bool, float> &val4, 
		const map<bool, double> &val5, 
		const map<bool, std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_mapOfMyBoolBoolMap(val0)
		, m_mapOfMyBoolCharMap(val1)
		, m_mapOfMyBoolInt32Map(val2)
		, m_mapOfMyBoolUint32Map(val3)
		, m_mapOfMyBoolFloatMap(val4)
		, m_mapOfMyBoolDoubleMap(val5)
		, m_mapOfMyBoolStringMap(val6)
	{
	}

	Test12MapBool::Test12MapBool(const Test12MapBool &obj) :
	    SerializableData(), Visitable()
		, m_mapOfMyBoolBoolMap(obj.m_mapOfMyBoolBoolMap)
		, m_mapOfMyBoolCharMap(obj.m_mapOfMyBoolCharMap)
		, m_mapOfMyBoolInt32Map(obj.m_mapOfMyBoolInt32Map)
		, m_mapOfMyBoolUint32Map(obj.m_mapOfMyBoolUint32Map)
		, m_mapOfMyBoolFloatMap(obj.m_mapOfMyBoolFloatMap)
		, m_mapOfMyBoolDoubleMap(obj.m_mapOfMyBoolDoubleMap)
		, m_mapOfMyBoolStringMap(obj.m_mapOfMyBoolStringMap)
	{
	}
	
	Test12MapBool::~Test12MapBool() {
	}

	Test12MapBool& Test12MapBool::operator=(const Test12MapBool &obj) {
		m_mapOfMyBoolBoolMap = obj.m_mapOfMyBoolBoolMap;
		m_mapOfMyBoolCharMap = obj.m_mapOfMyBoolCharMap;
		m_mapOfMyBoolInt32Map = obj.m_mapOfMyBoolInt32Map;
		m_mapOfMyBoolUint32Map = obj.m_mapOfMyBoolUint32Map;
		m_mapOfMyBoolFloatMap = obj.m_mapOfMyBoolFloatMap;
		m_mapOfMyBoolDoubleMap = obj.m_mapOfMyBoolDoubleMap;
		m_mapOfMyBoolStringMap = obj.m_mapOfMyBoolStringMap;
		return (*this);
	}

	int32_t Test12MapBool::ID() {
		return 14;
	}

	const string Test12MapBool::ShortName() {
		return "Test12MapBool";
	}

	const string Test12MapBool::LongName() {
		return "Test12MapBool";
	}

	std::map<bool, bool> Test12MapBool::getMapOfMyBoolBoolMap() const {
		return m_mapOfMyBoolBoolMap;
	}
	
	void Test12MapBool::setMapOfMyBoolBoolMap(const std::map<bool, bool> &val) {
		m_mapOfMyBoolBoolMap = val;
	}
	
	void Test12MapBool::clear_MapOfMyBoolBoolMap() {
		m_mapOfMyBoolBoolMap.clear();
	}
	
	uint32_t Test12MapBool::getSize_MapOfMyBoolBoolMap() const {
		return m_mapOfMyBoolBoolMap.size();
	}
	
	bool Test12MapBool::isEmpty_MapOfMyBoolBoolMap() const {
		return m_mapOfMyBoolBoolMap.empty();
	}
	
	void Test12MapBool::putTo_MapOfMyBoolBoolMap(const bool &key, const bool &val) {
		m_mapOfMyBoolBoolMap[key] = val;
	}
	
	bool Test12MapBool::containsKey_MapOfMyBoolBoolMap(const bool &key) const {
		return (m_mapOfMyBoolBoolMap.count(key) > 0);
	}
	
	bool Test12MapBool::getValueForKey_MapOfMyBoolBoolMap(const bool &key) {
		return m_mapOfMyBoolBoolMap[key];
	}
	
	std::pair<std::map<bool, bool>::iterator, std::map<bool, bool>::iterator> Test12MapBool::iteratorPair_MapOfMyBoolBoolMap() {
		return std::make_pair(m_mapOfMyBoolBoolMap.begin(), m_mapOfMyBoolBoolMap.end());
	}
	std::map<bool, char> Test12MapBool::getMapOfMyBoolCharMap() const {
		return m_mapOfMyBoolCharMap;
	}
	
	void Test12MapBool::setMapOfMyBoolCharMap(const std::map<bool, char> &val) {
		m_mapOfMyBoolCharMap = val;
	}
	
	void Test12MapBool::clear_MapOfMyBoolCharMap() {
		m_mapOfMyBoolCharMap.clear();
	}
	
	uint32_t Test12MapBool::getSize_MapOfMyBoolCharMap() const {
		return m_mapOfMyBoolCharMap.size();
	}
	
	bool Test12MapBool::isEmpty_MapOfMyBoolCharMap() const {
		return m_mapOfMyBoolCharMap.empty();
	}
	
	void Test12MapBool::putTo_MapOfMyBoolCharMap(const bool &key, const char &val) {
		m_mapOfMyBoolCharMap[key] = val;
	}
	
	bool Test12MapBool::containsKey_MapOfMyBoolCharMap(const bool &key) const {
		return (m_mapOfMyBoolCharMap.count(key) > 0);
	}
	
	char Test12MapBool::getValueForKey_MapOfMyBoolCharMap(const bool &key) {
		return m_mapOfMyBoolCharMap[key];
	}
	
	std::pair<std::map<bool, char>::iterator, std::map<bool, char>::iterator> Test12MapBool::iteratorPair_MapOfMyBoolCharMap() {
		return std::make_pair(m_mapOfMyBoolCharMap.begin(), m_mapOfMyBoolCharMap.end());
	}
	std::map<bool, int32_t> Test12MapBool::getMapOfMyBoolInt32Map() const {
		return m_mapOfMyBoolInt32Map;
	}
	
	void Test12MapBool::setMapOfMyBoolInt32Map(const std::map<bool, int32_t> &val) {
		m_mapOfMyBoolInt32Map = val;
	}
	
	void Test12MapBool::clear_MapOfMyBoolInt32Map() {
		m_mapOfMyBoolInt32Map.clear();
	}
	
	uint32_t Test12MapBool::getSize_MapOfMyBoolInt32Map() const {
		return m_mapOfMyBoolInt32Map.size();
	}
	
	bool Test12MapBool::isEmpty_MapOfMyBoolInt32Map() const {
		return m_mapOfMyBoolInt32Map.empty();
	}
	
	void Test12MapBool::putTo_MapOfMyBoolInt32Map(const bool &key, const int32_t &val) {
		m_mapOfMyBoolInt32Map[key] = val;
	}
	
	bool Test12MapBool::containsKey_MapOfMyBoolInt32Map(const bool &key) const {
		return (m_mapOfMyBoolInt32Map.count(key) > 0);
	}
	
	int32_t Test12MapBool::getValueForKey_MapOfMyBoolInt32Map(const bool &key) {
		return m_mapOfMyBoolInt32Map[key];
	}
	
	std::pair<std::map<bool, int32_t>::iterator, std::map<bool, int32_t>::iterator> Test12MapBool::iteratorPair_MapOfMyBoolInt32Map() {
		return std::make_pair(m_mapOfMyBoolInt32Map.begin(), m_mapOfMyBoolInt32Map.end());
	}
	std::map<bool, uint32_t> Test12MapBool::getMapOfMyBoolUint32Map() const {
		return m_mapOfMyBoolUint32Map;
	}
	
	void Test12MapBool::setMapOfMyBoolUint32Map(const std::map<bool, uint32_t> &val) {
		m_mapOfMyBoolUint32Map = val;
	}
	
	void Test12MapBool::clear_MapOfMyBoolUint32Map() {
		m_mapOfMyBoolUint32Map.clear();
	}
	
	uint32_t Test12MapBool::getSize_MapOfMyBoolUint32Map() const {
		return m_mapOfMyBoolUint32Map.size();
	}
	
	bool Test12MapBool::isEmpty_MapOfMyBoolUint32Map() const {
		return m_mapOfMyBoolUint32Map.empty();
	}
	
	void Test12MapBool::putTo_MapOfMyBoolUint32Map(const bool &key, const uint32_t &val) {
		m_mapOfMyBoolUint32Map[key] = val;
	}
	
	bool Test12MapBool::containsKey_MapOfMyBoolUint32Map(const bool &key) const {
		return (m_mapOfMyBoolUint32Map.count(key) > 0);
	}
	
	uint32_t Test12MapBool::getValueForKey_MapOfMyBoolUint32Map(const bool &key) {
		return m_mapOfMyBoolUint32Map[key];
	}
	
	std::pair<std::map<bool, uint32_t>::iterator, std::map<bool, uint32_t>::iterator> Test12MapBool::iteratorPair_MapOfMyBoolUint32Map() {
		return std::make_pair(m_mapOfMyBoolUint32Map.begin(), m_mapOfMyBoolUint32Map.end());
	}
	std::map<bool, float> Test12MapBool::getMapOfMyBoolFloatMap() const {
		return m_mapOfMyBoolFloatMap;
	}
	
	void Test12MapBool::setMapOfMyBoolFloatMap(const std::map<bool, float> &val) {
		m_mapOfMyBoolFloatMap = val;
	}
	
	void Test12MapBool::clear_MapOfMyBoolFloatMap() {
		m_mapOfMyBoolFloatMap.clear();
	}
	
	uint32_t Test12MapBool::getSize_MapOfMyBoolFloatMap() const {
		return m_mapOfMyBoolFloatMap.size();
	}
	
	bool Test12MapBool::isEmpty_MapOfMyBoolFloatMap() const {
		return m_mapOfMyBoolFloatMap.empty();
	}
	
	void Test12MapBool::putTo_MapOfMyBoolFloatMap(const bool &key, const float &val) {
		m_mapOfMyBoolFloatMap[key] = val;
	}
	
	bool Test12MapBool::containsKey_MapOfMyBoolFloatMap(const bool &key) const {
		return (m_mapOfMyBoolFloatMap.count(key) > 0);
	}
	
	float Test12MapBool::getValueForKey_MapOfMyBoolFloatMap(const bool &key) {
		return m_mapOfMyBoolFloatMap[key];
	}
	
	std::pair<std::map<bool, float>::iterator, std::map<bool, float>::iterator> Test12MapBool::iteratorPair_MapOfMyBoolFloatMap() {
		return std::make_pair(m_mapOfMyBoolFloatMap.begin(), m_mapOfMyBoolFloatMap.end());
	}
	std::map<bool, double> Test12MapBool::getMapOfMyBoolDoubleMap() const {
		return m_mapOfMyBoolDoubleMap;
	}
	
	void Test12MapBool::setMapOfMyBoolDoubleMap(const std::map<bool, double> &val) {
		m_mapOfMyBoolDoubleMap = val;
	}
	
	void Test12MapBool::clear_MapOfMyBoolDoubleMap() {
		m_mapOfMyBoolDoubleMap.clear();
	}
	
	uint32_t Test12MapBool::getSize_MapOfMyBoolDoubleMap() const {
		return m_mapOfMyBoolDoubleMap.size();
	}
	
	bool Test12MapBool::isEmpty_MapOfMyBoolDoubleMap() const {
		return m_mapOfMyBoolDoubleMap.empty();
	}
	
	void Test12MapBool::putTo_MapOfMyBoolDoubleMap(const bool &key, const double &val) {
		m_mapOfMyBoolDoubleMap[key] = val;
	}
	
	bool Test12MapBool::containsKey_MapOfMyBoolDoubleMap(const bool &key) const {
		return (m_mapOfMyBoolDoubleMap.count(key) > 0);
	}
	
	double Test12MapBool::getValueForKey_MapOfMyBoolDoubleMap(const bool &key) {
		return m_mapOfMyBoolDoubleMap[key];
	}
	
	std::pair<std::map<bool, double>::iterator, std::map<bool, double>::iterator> Test12MapBool::iteratorPair_MapOfMyBoolDoubleMap() {
		return std::make_pair(m_mapOfMyBoolDoubleMap.begin(), m_mapOfMyBoolDoubleMap.end());
	}
	std::map<bool, std::string> Test12MapBool::getMapOfMyBoolStringMap() const {
		return m_mapOfMyBoolStringMap;
	}
	
	void Test12MapBool::setMapOfMyBoolStringMap(const std::map<bool, std::string> &val) {
		m_mapOfMyBoolStringMap = val;
	}
	
	void Test12MapBool::clear_MapOfMyBoolStringMap() {
		m_mapOfMyBoolStringMap.clear();
	}
	
	uint32_t Test12MapBool::getSize_MapOfMyBoolStringMap() const {
		return m_mapOfMyBoolStringMap.size();
	}
	
	bool Test12MapBool::isEmpty_MapOfMyBoolStringMap() const {
		return m_mapOfMyBoolStringMap.empty();
	}
	
	void Test12MapBool::putTo_MapOfMyBoolStringMap(const bool &key, const std::string &val) {
		m_mapOfMyBoolStringMap[key] = val;
	}
	
	bool Test12MapBool::containsKey_MapOfMyBoolStringMap(const bool &key) const {
		return (m_mapOfMyBoolStringMap.count(key) > 0);
	}
	
	std::string Test12MapBool::getValueForKey_MapOfMyBoolStringMap(const bool &key) {
		return m_mapOfMyBoolStringMap[key];
	}
	
	std::pair<std::map<bool, std::string>::iterator, std::map<bool, std::string>::iterator> Test12MapBool::iteratorPair_MapOfMyBoolStringMap() {
		return std::make_pair(m_mapOfMyBoolStringMap.begin(), m_mapOfMyBoolStringMap.end());
	}

	void Test12MapBool::accept(core::base::Visitor &v) {
		(void)v; // Avoid unused parameter warning.
	}

	const string Test12MapBool::toString() const {
		stringstream s;


		s << "Number of elements in map of MyBoolBoolMap: " << getSize_MapOfMyBoolBoolMap() << " ";
		s << "Number of elements in map of MyBoolCharMap: " << getSize_MapOfMyBoolCharMap() << " ";
		s << "Number of elements in map of MyBoolInt32Map: " << getSize_MapOfMyBoolInt32Map() << " ";
		s << "Number of elements in map of MyBoolUint32Map: " << getSize_MapOfMyBoolUint32Map() << " ";
		s << "Number of elements in map of MyBoolFloatMap: " << getSize_MapOfMyBoolFloatMap() << " ";
		s << "Number of elements in map of MyBoolDoubleMap: " << getSize_MapOfMyBoolDoubleMap() << " ";
		s << "Number of elements in map of MyBoolStringMap: " << getSize_MapOfMyBoolStringMap() << " ";

		return s.str();
	}

	ostream& Test12MapBool::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		{
			// Write number of elements in m_mapOfMyBoolBoolMap.
			const uint32_t numberOfMyBoolBoolMap = static_cast<uint32_t>(m_mapOfMyBoolBoolMap.size());
			s->write(1, numberOfMyBoolBoolMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyBoolBoolMap;
			std::map<bool, bool>::const_iterator it = m_mapOfMyBoolBoolMap.begin();
			while (it != m_mapOfMyBoolBoolMap.end()) {
			    sstrOfMyBoolBoolMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyBoolBoolMap > 0) {
				s->write(1 + 7, sstrOfMyBoolBoolMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyBoolCharMap.
			const uint32_t numberOfMyBoolCharMap = static_cast<uint32_t>(m_mapOfMyBoolCharMap.size());
			s->write(2, numberOfMyBoolCharMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyBoolCharMap;
			std::map<bool, char>::const_iterator it = m_mapOfMyBoolCharMap.begin();
			while (it != m_mapOfMyBoolCharMap.end()) {
			    sstrOfMyBoolCharMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyBoolCharMap > 0) {
				s->write(2 + 7, sstrOfMyBoolCharMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyBoolInt32Map.
			const uint32_t numberOfMyBoolInt32Map = static_cast<uint32_t>(m_mapOfMyBoolInt32Map.size());
			s->write(3, numberOfMyBoolInt32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyBoolInt32Map;
			std::map<bool, int32_t>::const_iterator it = m_mapOfMyBoolInt32Map.begin();
			while (it != m_mapOfMyBoolInt32Map.end()) {
			    sstrOfMyBoolInt32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyBoolInt32Map > 0) {
				s->write(3 + 7, sstrOfMyBoolInt32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyBoolUint32Map.
			const uint32_t numberOfMyBoolUint32Map = static_cast<uint32_t>(m_mapOfMyBoolUint32Map.size());
			s->write(4, numberOfMyBoolUint32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyBoolUint32Map;
			std::map<bool, uint32_t>::const_iterator it = m_mapOfMyBoolUint32Map.begin();
			while (it != m_mapOfMyBoolUint32Map.end()) {
			    sstrOfMyBoolUint32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyBoolUint32Map > 0) {
				s->write(4 + 7, sstrOfMyBoolUint32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyBoolFloatMap.
			const uint32_t numberOfMyBoolFloatMap = static_cast<uint32_t>(m_mapOfMyBoolFloatMap.size());
			s->write(5, numberOfMyBoolFloatMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyBoolFloatMap;
			std::map<bool, float>::const_iterator it = m_mapOfMyBoolFloatMap.begin();
			while (it != m_mapOfMyBoolFloatMap.end()) {
			    sstrOfMyBoolFloatMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyBoolFloatMap > 0) {
				s->write(5 + 7, sstrOfMyBoolFloatMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyBoolDoubleMap.
			const uint32_t numberOfMyBoolDoubleMap = static_cast<uint32_t>(m_mapOfMyBoolDoubleMap.size());
			s->write(6, numberOfMyBoolDoubleMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyBoolDoubleMap;
			std::map<bool, double>::const_iterator it = m_mapOfMyBoolDoubleMap.begin();
			while (it != m_mapOfMyBoolDoubleMap.end()) {
			    sstrOfMyBoolDoubleMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyBoolDoubleMap > 0) {
				s->write(6 + 7, sstrOfMyBoolDoubleMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyBoolStringMap.
			const uint32_t numberOfMyBoolStringMap = static_cast<uint32_t>(m_mapOfMyBoolStringMap.size());
			s->write(7, numberOfMyBoolStringMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyBoolStringMap;
			std::map<bool, std::string>::const_iterator it = m_mapOfMyBoolStringMap.begin();
			while (it != m_mapOfMyBoolStringMap.end()) {
			    sstrOfMyBoolStringMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyBoolStringMap > 0) {
				s->write(7 + 7, sstrOfMyBoolStringMap.str());
			}
		}
		return out;
	}

	istream& Test12MapBool::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing map of MyBoolBoolMap.
		m_mapOfMyBoolBoolMap.clear();
		
		// Read number of elements in m_mapOfMyBoolBoolMap.
		uint32_t numberOfMyBoolBoolMap = 0;
		d->read(1, numberOfMyBoolBoolMap);
		
		if (numberOfMyBoolBoolMap > 0) {
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
			    bool _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    bool _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyBoolBoolMap(_key, _value);
			}
		}
		// Clean up the existing map of MyBoolCharMap.
		m_mapOfMyBoolCharMap.clear();
		
		// Read number of elements in m_mapOfMyBoolCharMap.
		uint32_t numberOfMyBoolCharMap = 0;
		d->read(2, numberOfMyBoolCharMap);
		
		if (numberOfMyBoolCharMap > 0) {
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
			    bool _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    char _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyBoolCharMap(_key, _value);
			}
		}
		// Clean up the existing map of MyBoolInt32Map.
		m_mapOfMyBoolInt32Map.clear();
		
		// Read number of elements in m_mapOfMyBoolInt32Map.
		uint32_t numberOfMyBoolInt32Map = 0;
		d->read(3, numberOfMyBoolInt32Map);
		
		if (numberOfMyBoolInt32Map > 0) {
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
			    bool _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    int32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyBoolInt32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyBoolUint32Map.
		m_mapOfMyBoolUint32Map.clear();
		
		// Read number of elements in m_mapOfMyBoolUint32Map.
		uint32_t numberOfMyBoolUint32Map = 0;
		d->read(4, numberOfMyBoolUint32Map);
		
		if (numberOfMyBoolUint32Map > 0) {
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
			    bool _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    uint32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyBoolUint32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyBoolFloatMap.
		m_mapOfMyBoolFloatMap.clear();
		
		// Read number of elements in m_mapOfMyBoolFloatMap.
		uint32_t numberOfMyBoolFloatMap = 0;
		d->read(5, numberOfMyBoolFloatMap);
		
		if (numberOfMyBoolFloatMap > 0) {
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
			    bool _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    float _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyBoolFloatMap(_key, _value);
			}
		}
		// Clean up the existing map of MyBoolDoubleMap.
		m_mapOfMyBoolDoubleMap.clear();
		
		// Read number of elements in m_mapOfMyBoolDoubleMap.
		uint32_t numberOfMyBoolDoubleMap = 0;
		d->read(6, numberOfMyBoolDoubleMap);
		
		if (numberOfMyBoolDoubleMap > 0) {
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
			    bool _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    double _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyBoolDoubleMap(_key, _value);
			}
		}
		// Clean up the existing map of MyBoolStringMap.
		m_mapOfMyBoolStringMap.clear();
		
		// Read number of elements in m_mapOfMyBoolStringMap.
		uint32_t numberOfMyBoolStringMap = 0;
		d->read(7, numberOfMyBoolStringMap);
		
		if (numberOfMyBoolStringMap > 0) {
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
			    bool _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    std::string _value;
		        getline(sstrValue, _value);
		
				// Store key/value pair.
				putTo_MapOfMyBoolStringMap(_key, _value);
			}
		}
		return in;
	}
