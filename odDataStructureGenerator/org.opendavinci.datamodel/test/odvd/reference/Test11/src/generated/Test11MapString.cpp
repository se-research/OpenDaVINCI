/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"

#include "test11/generated/Test11MapString.h"

	using namespace std;
	using namespace odcore::base;
	using namespace odcore::serialization;


	Test11MapString::Test11MapString() :
	    SerializableData(), Visitable()
		, m_mapOfMyStringBoolMap()
		, m_mapOfMyStringCharMap()
		, m_mapOfMyStringInt32Map()
		, m_mapOfMyStringUint32Map()
		, m_mapOfMyStringFloatMap()
		, m_mapOfMyStringDoubleMap()
		, m_mapOfMyStringStringMap()
	{
	}

	Test11MapString::Test11MapString(
		const map<std::string, bool> &val0, 
		const map<std::string, char> &val1, 
		const map<std::string, int32_t> &val2, 
		const map<std::string, uint32_t> &val3, 
		const map<std::string, float> &val4, 
		const map<std::string, double> &val5, 
		const map<std::string, std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_mapOfMyStringBoolMap(val0)
		, m_mapOfMyStringCharMap(val1)
		, m_mapOfMyStringInt32Map(val2)
		, m_mapOfMyStringUint32Map(val3)
		, m_mapOfMyStringFloatMap(val4)
		, m_mapOfMyStringDoubleMap(val5)
		, m_mapOfMyStringStringMap(val6)
	{
	}

	Test11MapString::Test11MapString(const Test11MapString &obj) :
	    SerializableData(), Visitable()
		, m_mapOfMyStringBoolMap(obj.m_mapOfMyStringBoolMap)
		, m_mapOfMyStringCharMap(obj.m_mapOfMyStringCharMap)
		, m_mapOfMyStringInt32Map(obj.m_mapOfMyStringInt32Map)
		, m_mapOfMyStringUint32Map(obj.m_mapOfMyStringUint32Map)
		, m_mapOfMyStringFloatMap(obj.m_mapOfMyStringFloatMap)
		, m_mapOfMyStringDoubleMap(obj.m_mapOfMyStringDoubleMap)
		, m_mapOfMyStringStringMap(obj.m_mapOfMyStringStringMap)
	{
	}
	
	Test11MapString::~Test11MapString() {
	}

	Test11MapString& Test11MapString::operator=(const Test11MapString &obj) {
		m_mapOfMyStringBoolMap = obj.m_mapOfMyStringBoolMap;
		m_mapOfMyStringCharMap = obj.m_mapOfMyStringCharMap;
		m_mapOfMyStringInt32Map = obj.m_mapOfMyStringInt32Map;
		m_mapOfMyStringUint32Map = obj.m_mapOfMyStringUint32Map;
		m_mapOfMyStringFloatMap = obj.m_mapOfMyStringFloatMap;
		m_mapOfMyStringDoubleMap = obj.m_mapOfMyStringDoubleMap;
		m_mapOfMyStringStringMap = obj.m_mapOfMyStringStringMap;
		return (*this);
	}

	int32_t Test11MapString::ID() {
		return 19;
	}

	const string Test11MapString::ShortName() {
		return "Test11MapString";
	}

	const string Test11MapString::LongName() {
		return "Test11MapString";
	}

	int32_t Test11MapString::getID() const {
		return Test11MapString::ID();
	}

	const string Test11MapString::getShortName() const {
		return Test11MapString::ShortName();
	}

	const string Test11MapString::getLongName() const {
		return Test11MapString::LongName();
	}

	std::map<std::string, bool> Test11MapString::getMapOfMyStringBoolMap() const {
		return m_mapOfMyStringBoolMap;
	}
	
	void Test11MapString::setMapOfMyStringBoolMap(const std::map<std::string, bool> &val) {
		m_mapOfMyStringBoolMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringBoolMap() {
		m_mapOfMyStringBoolMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringBoolMap() const {
		return m_mapOfMyStringBoolMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringBoolMap() const {
		return m_mapOfMyStringBoolMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringBoolMap(const std::string &key, const bool &val) {
		m_mapOfMyStringBoolMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringBoolMap(const std::string &key) const {
		return (m_mapOfMyStringBoolMap.count(key) > 0);
	}
	
	bool Test11MapString::getValueForKey_MapOfMyStringBoolMap(const std::string &key) {
		return m_mapOfMyStringBoolMap[key];
	}
	
	std::pair<std::map<std::string, bool>::iterator, std::map<std::string, bool>::iterator> Test11MapString::iteratorPair_MapOfMyStringBoolMap() {
		return std::make_pair(m_mapOfMyStringBoolMap.begin(), m_mapOfMyStringBoolMap.end());
	}
	std::map<std::string, char> Test11MapString::getMapOfMyStringCharMap() const {
		return m_mapOfMyStringCharMap;
	}
	
	void Test11MapString::setMapOfMyStringCharMap(const std::map<std::string, char> &val) {
		m_mapOfMyStringCharMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringCharMap() {
		m_mapOfMyStringCharMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringCharMap() const {
		return m_mapOfMyStringCharMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringCharMap() const {
		return m_mapOfMyStringCharMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringCharMap(const std::string &key, const char &val) {
		m_mapOfMyStringCharMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringCharMap(const std::string &key) const {
		return (m_mapOfMyStringCharMap.count(key) > 0);
	}
	
	char Test11MapString::getValueForKey_MapOfMyStringCharMap(const std::string &key) {
		return m_mapOfMyStringCharMap[key];
	}
	
	std::pair<std::map<std::string, char>::iterator, std::map<std::string, char>::iterator> Test11MapString::iteratorPair_MapOfMyStringCharMap() {
		return std::make_pair(m_mapOfMyStringCharMap.begin(), m_mapOfMyStringCharMap.end());
	}
	std::map<std::string, int32_t> Test11MapString::getMapOfMyStringInt32Map() const {
		return m_mapOfMyStringInt32Map;
	}
	
	void Test11MapString::setMapOfMyStringInt32Map(const std::map<std::string, int32_t> &val) {
		m_mapOfMyStringInt32Map = val;
	}
	
	void Test11MapString::clear_MapOfMyStringInt32Map() {
		m_mapOfMyStringInt32Map.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringInt32Map() const {
		return m_mapOfMyStringInt32Map.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringInt32Map() const {
		return m_mapOfMyStringInt32Map.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringInt32Map(const std::string &key, const int32_t &val) {
		m_mapOfMyStringInt32Map[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringInt32Map(const std::string &key) const {
		return (m_mapOfMyStringInt32Map.count(key) > 0);
	}
	
	int32_t Test11MapString::getValueForKey_MapOfMyStringInt32Map(const std::string &key) {
		return m_mapOfMyStringInt32Map[key];
	}
	
	std::pair<std::map<std::string, int32_t>::iterator, std::map<std::string, int32_t>::iterator> Test11MapString::iteratorPair_MapOfMyStringInt32Map() {
		return std::make_pair(m_mapOfMyStringInt32Map.begin(), m_mapOfMyStringInt32Map.end());
	}
	std::map<std::string, uint32_t> Test11MapString::getMapOfMyStringUint32Map() const {
		return m_mapOfMyStringUint32Map;
	}
	
	void Test11MapString::setMapOfMyStringUint32Map(const std::map<std::string, uint32_t> &val) {
		m_mapOfMyStringUint32Map = val;
	}
	
	void Test11MapString::clear_MapOfMyStringUint32Map() {
		m_mapOfMyStringUint32Map.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringUint32Map() const {
		return m_mapOfMyStringUint32Map.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringUint32Map() const {
		return m_mapOfMyStringUint32Map.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringUint32Map(const std::string &key, const uint32_t &val) {
		m_mapOfMyStringUint32Map[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringUint32Map(const std::string &key) const {
		return (m_mapOfMyStringUint32Map.count(key) > 0);
	}
	
	uint32_t Test11MapString::getValueForKey_MapOfMyStringUint32Map(const std::string &key) {
		return m_mapOfMyStringUint32Map[key];
	}
	
	std::pair<std::map<std::string, uint32_t>::iterator, std::map<std::string, uint32_t>::iterator> Test11MapString::iteratorPair_MapOfMyStringUint32Map() {
		return std::make_pair(m_mapOfMyStringUint32Map.begin(), m_mapOfMyStringUint32Map.end());
	}
	std::map<std::string, float> Test11MapString::getMapOfMyStringFloatMap() const {
		return m_mapOfMyStringFloatMap;
	}
	
	void Test11MapString::setMapOfMyStringFloatMap(const std::map<std::string, float> &val) {
		m_mapOfMyStringFloatMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringFloatMap() {
		m_mapOfMyStringFloatMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringFloatMap() const {
		return m_mapOfMyStringFloatMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringFloatMap() const {
		return m_mapOfMyStringFloatMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringFloatMap(const std::string &key, const float &val) {
		m_mapOfMyStringFloatMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringFloatMap(const std::string &key) const {
		return (m_mapOfMyStringFloatMap.count(key) > 0);
	}
	
	float Test11MapString::getValueForKey_MapOfMyStringFloatMap(const std::string &key) {
		return m_mapOfMyStringFloatMap[key];
	}
	
	std::pair<std::map<std::string, float>::iterator, std::map<std::string, float>::iterator> Test11MapString::iteratorPair_MapOfMyStringFloatMap() {
		return std::make_pair(m_mapOfMyStringFloatMap.begin(), m_mapOfMyStringFloatMap.end());
	}
	std::map<std::string, double> Test11MapString::getMapOfMyStringDoubleMap() const {
		return m_mapOfMyStringDoubleMap;
	}
	
	void Test11MapString::setMapOfMyStringDoubleMap(const std::map<std::string, double> &val) {
		m_mapOfMyStringDoubleMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringDoubleMap() {
		m_mapOfMyStringDoubleMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringDoubleMap() const {
		return m_mapOfMyStringDoubleMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringDoubleMap() const {
		return m_mapOfMyStringDoubleMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringDoubleMap(const std::string &key, const double &val) {
		m_mapOfMyStringDoubleMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringDoubleMap(const std::string &key) const {
		return (m_mapOfMyStringDoubleMap.count(key) > 0);
	}
	
	double Test11MapString::getValueForKey_MapOfMyStringDoubleMap(const std::string &key) {
		return m_mapOfMyStringDoubleMap[key];
	}
	
	std::pair<std::map<std::string, double>::iterator, std::map<std::string, double>::iterator> Test11MapString::iteratorPair_MapOfMyStringDoubleMap() {
		return std::make_pair(m_mapOfMyStringDoubleMap.begin(), m_mapOfMyStringDoubleMap.end());
	}
	std::map<std::string, std::string> Test11MapString::getMapOfMyStringStringMap() const {
		return m_mapOfMyStringStringMap;
	}
	
	void Test11MapString::setMapOfMyStringStringMap(const std::map<std::string, std::string> &val) {
		m_mapOfMyStringStringMap = val;
	}
	
	void Test11MapString::clear_MapOfMyStringStringMap() {
		m_mapOfMyStringStringMap.clear();
	}
	
	uint32_t Test11MapString::getSize_MapOfMyStringStringMap() const {
		return m_mapOfMyStringStringMap.size();
	}
	
	bool Test11MapString::isEmpty_MapOfMyStringStringMap() const {
		return m_mapOfMyStringStringMap.empty();
	}
	
	void Test11MapString::putTo_MapOfMyStringStringMap(const std::string &key, const std::string &val) {
		m_mapOfMyStringStringMap[key] = val;
	}
	
	bool Test11MapString::containsKey_MapOfMyStringStringMap(const std::string &key) const {
		return (m_mapOfMyStringStringMap.count(key) > 0);
	}
	
	std::string Test11MapString::getValueForKey_MapOfMyStringStringMap(const std::string &key) {
		return m_mapOfMyStringStringMap[key];
	}
	
	std::pair<std::map<std::string, std::string>::iterator, std::map<std::string, std::string>::iterator> Test11MapString::iteratorPair_MapOfMyStringStringMap() {
		return std::make_pair(m_mapOfMyStringStringMap.begin(), m_mapOfMyStringStringMap.end());
	}

	void Test11MapString::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test11MapString::toString() const {
		stringstream s;

		s << "Number of elements in map of MyStringBoolMap: " << getSize_MapOfMyStringBoolMap() << " ";
		s << "Number of elements in map of MyStringCharMap: " << getSize_MapOfMyStringCharMap() << " ";
		s << "Number of elements in map of MyStringInt32Map: " << getSize_MapOfMyStringInt32Map() << " ";
		s << "Number of elements in map of MyStringUint32Map: " << getSize_MapOfMyStringUint32Map() << " ";
		s << "Number of elements in map of MyStringFloatMap: " << getSize_MapOfMyStringFloatMap() << " ";
		s << "Number of elements in map of MyStringDoubleMap: " << getSize_MapOfMyStringDoubleMap() << " ";
		s << "Number of elements in map of MyStringStringMap: " << getSize_MapOfMyStringStringMap() << " ";

		return s.str();
	}

	ostream& Test11MapString::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		{
			std::stringstream sstr_MyStringBoolMap;
			{
				std::map<std::string, bool>::const_iterator it = m_mapOfMyStringBoolMap.begin();
				while (it != m_mapOfMyStringBoolMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyStringBoolMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyStringBoolMap = sstr_MyStringBoolMap.str();
			s->write(1, str_sstr_MyStringBoolMap);
		}
		{
			std::stringstream sstr_MyStringCharMap;
			{
				std::map<std::string, char>::const_iterator it = m_mapOfMyStringCharMap.begin();
				while (it != m_mapOfMyStringCharMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyStringCharMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyStringCharMap = sstr_MyStringCharMap.str();
			s->write(2, str_sstr_MyStringCharMap);
		}
		{
			std::stringstream sstr_MyStringInt32Map;
			{
				std::map<std::string, int32_t>::const_iterator it = m_mapOfMyStringInt32Map.begin();
				while (it != m_mapOfMyStringInt32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyStringInt32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyStringInt32Map = sstr_MyStringInt32Map.str();
			s->write(3, str_sstr_MyStringInt32Map);
		}
		{
			std::stringstream sstr_MyStringUint32Map;
			{
				std::map<std::string, uint32_t>::const_iterator it = m_mapOfMyStringUint32Map.begin();
				while (it != m_mapOfMyStringUint32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyStringUint32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyStringUint32Map = sstr_MyStringUint32Map.str();
			s->write(4, str_sstr_MyStringUint32Map);
		}
		{
			std::stringstream sstr_MyStringFloatMap;
			{
				std::map<std::string, float>::const_iterator it = m_mapOfMyStringFloatMap.begin();
				while (it != m_mapOfMyStringFloatMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyStringFloatMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyStringFloatMap = sstr_MyStringFloatMap.str();
			s->write(5, str_sstr_MyStringFloatMap);
		}
		{
			std::stringstream sstr_MyStringDoubleMap;
			{
				std::map<std::string, double>::const_iterator it = m_mapOfMyStringDoubleMap.begin();
				while (it != m_mapOfMyStringDoubleMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyStringDoubleMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyStringDoubleMap = sstr_MyStringDoubleMap.str();
			s->write(6, str_sstr_MyStringDoubleMap);
		}
		{
			std::stringstream sstr_MyStringStringMap;
			{
				std::map<std::string, std::string>::const_iterator it = m_mapOfMyStringStringMap.begin();
				while (it != m_mapOfMyStringStringMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyStringStringMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyStringStringMap = sstr_MyStringStringMap.str();
			s->write(7, str_sstr_MyStringStringMap);
		}
		return out;
	}

	istream& Test11MapString::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore elements from a string into MyStringBoolMap.
		{
			// Clean up the existing map of MyStringBoolMap.
			m_mapOfMyStringBoolMap.clear();
		
			std::string str_MyStringBoolMap;
			d->read(1, str_MyStringBoolMap);
			if (str_MyStringBoolMap.size() > 0) {
				std::stringstream sstr_str_MyStringBoolMap(str_MyStringBoolMap);
		
				// str_MyStringBoolMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyStringBoolMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyStringBoolMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							std::string key;
							bool value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyStringBoolMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyStringCharMap.
		{
			// Clean up the existing map of MyStringCharMap.
			m_mapOfMyStringCharMap.clear();
		
			std::string str_MyStringCharMap;
			d->read(2, str_MyStringCharMap);
			if (str_MyStringCharMap.size() > 0) {
				std::stringstream sstr_str_MyStringCharMap(str_MyStringCharMap);
		
				// str_MyStringCharMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyStringCharMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyStringCharMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							std::string key;
							char value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyStringCharMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyStringInt32Map.
		{
			// Clean up the existing map of MyStringInt32Map.
			m_mapOfMyStringInt32Map.clear();
		
			std::string str_MyStringInt32Map;
			d->read(3, str_MyStringInt32Map);
			if (str_MyStringInt32Map.size() > 0) {
				std::stringstream sstr_str_MyStringInt32Map(str_MyStringInt32Map);
		
				// str_MyStringInt32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyStringInt32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyStringInt32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							std::string key;
							int32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyStringInt32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyStringUint32Map.
		{
			// Clean up the existing map of MyStringUint32Map.
			m_mapOfMyStringUint32Map.clear();
		
			std::string str_MyStringUint32Map;
			d->read(4, str_MyStringUint32Map);
			if (str_MyStringUint32Map.size() > 0) {
				std::stringstream sstr_str_MyStringUint32Map(str_MyStringUint32Map);
		
				// str_MyStringUint32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyStringUint32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyStringUint32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							std::string key;
							uint32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyStringUint32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyStringFloatMap.
		{
			// Clean up the existing map of MyStringFloatMap.
			m_mapOfMyStringFloatMap.clear();
		
			std::string str_MyStringFloatMap;
			d->read(5, str_MyStringFloatMap);
			if (str_MyStringFloatMap.size() > 0) {
				std::stringstream sstr_str_MyStringFloatMap(str_MyStringFloatMap);
		
				// str_MyStringFloatMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyStringFloatMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyStringFloatMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							std::string key;
							float value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyStringFloatMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyStringDoubleMap.
		{
			// Clean up the existing map of MyStringDoubleMap.
			m_mapOfMyStringDoubleMap.clear();
		
			std::string str_MyStringDoubleMap;
			d->read(6, str_MyStringDoubleMap);
			if (str_MyStringDoubleMap.size() > 0) {
				std::stringstream sstr_str_MyStringDoubleMap(str_MyStringDoubleMap);
		
				// str_MyStringDoubleMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyStringDoubleMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyStringDoubleMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							std::string key;
							double value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyStringDoubleMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyStringStringMap.
		{
			// Clean up the existing map of MyStringStringMap.
			m_mapOfMyStringStringMap.clear();
		
			std::string str_MyStringStringMap;
			d->read(7, str_MyStringStringMap);
			if (str_MyStringStringMap.size() > 0) {
				std::stringstream sstr_str_MyStringStringMap(str_MyStringStringMap);
		
				// str_MyStringStringMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyStringStringMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyStringStringMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							std::string key;
							std::string value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyStringStringMap(key, value);
						}
					}
				}
			}
		}
		return in;
	}
