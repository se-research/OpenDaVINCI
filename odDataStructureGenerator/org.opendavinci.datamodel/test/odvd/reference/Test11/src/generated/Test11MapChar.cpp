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


#include "test11/generated/Test11MapChar.h"

	using namespace std;
	using namespace odcore::base;


	Test11MapChar::Test11MapChar() :
	    SerializableData(), Visitable()
		, m_mapOfMyCharBoolMap()
		, m_mapOfMyCharCharMap()
		, m_mapOfMyCharInt32Map()
		, m_mapOfMyCharUint32Map()
		, m_mapOfMyCharFloatMap()
		, m_mapOfMyCharDoubleMap()
		, m_mapOfMyCharStringMap()
	{
	}

	Test11MapChar::Test11MapChar(
		const map<char, bool> &val0, 
		const map<char, char> &val1, 
		const map<char, int32_t> &val2, 
		const map<char, uint32_t> &val3, 
		const map<char, float> &val4, 
		const map<char, double> &val5, 
		const map<char, std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_mapOfMyCharBoolMap(val0)
		, m_mapOfMyCharCharMap(val1)
		, m_mapOfMyCharInt32Map(val2)
		, m_mapOfMyCharUint32Map(val3)
		, m_mapOfMyCharFloatMap(val4)
		, m_mapOfMyCharDoubleMap(val5)
		, m_mapOfMyCharStringMap(val6)
	{
	}

	Test11MapChar::Test11MapChar(const Test11MapChar &obj) :
	    SerializableData(), Visitable()
		, m_mapOfMyCharBoolMap(obj.m_mapOfMyCharBoolMap)
		, m_mapOfMyCharCharMap(obj.m_mapOfMyCharCharMap)
		, m_mapOfMyCharInt32Map(obj.m_mapOfMyCharInt32Map)
		, m_mapOfMyCharUint32Map(obj.m_mapOfMyCharUint32Map)
		, m_mapOfMyCharFloatMap(obj.m_mapOfMyCharFloatMap)
		, m_mapOfMyCharDoubleMap(obj.m_mapOfMyCharDoubleMap)
		, m_mapOfMyCharStringMap(obj.m_mapOfMyCharStringMap)
	{
	}
	
	Test11MapChar::~Test11MapChar() {
	}

	Test11MapChar& Test11MapChar::operator=(const Test11MapChar &obj) {
		m_mapOfMyCharBoolMap = obj.m_mapOfMyCharBoolMap;
		m_mapOfMyCharCharMap = obj.m_mapOfMyCharCharMap;
		m_mapOfMyCharInt32Map = obj.m_mapOfMyCharInt32Map;
		m_mapOfMyCharUint32Map = obj.m_mapOfMyCharUint32Map;
		m_mapOfMyCharFloatMap = obj.m_mapOfMyCharFloatMap;
		m_mapOfMyCharDoubleMap = obj.m_mapOfMyCharDoubleMap;
		m_mapOfMyCharStringMap = obj.m_mapOfMyCharStringMap;
		return (*this);
	}

	int32_t Test11MapChar::ID() {
		return 14;
	}

	const string Test11MapChar::ShortName() {
		return "Test11MapChar";
	}

	const string Test11MapChar::LongName() {
		return "Test11MapChar";
	}

	int32_t Test11MapChar::getID() const {
		return Test11MapChar::ID();
	}

	const string Test11MapChar::getShortName() const {
		return Test11MapChar::ShortName();
	}

	const string Test11MapChar::getLongName() const {
		return Test11MapChar::LongName();
	}

	std::map<char, bool> Test11MapChar::getMapOfMyCharBoolMap() const {
		return m_mapOfMyCharBoolMap;
	}
	
	void Test11MapChar::setMapOfMyCharBoolMap(const std::map<char, bool> &val) {
		m_mapOfMyCharBoolMap = val;
	}
	
	void Test11MapChar::clear_MapOfMyCharBoolMap() {
		m_mapOfMyCharBoolMap.clear();
	}
	
	uint32_t Test11MapChar::getSize_MapOfMyCharBoolMap() const {
		return m_mapOfMyCharBoolMap.size();
	}
	
	bool Test11MapChar::isEmpty_MapOfMyCharBoolMap() const {
		return m_mapOfMyCharBoolMap.empty();
	}
	
	void Test11MapChar::putTo_MapOfMyCharBoolMap(const char &key, const bool &val) {
		m_mapOfMyCharBoolMap[key] = val;
	}
	
	bool Test11MapChar::containsKey_MapOfMyCharBoolMap(const char &key) const {
		return (m_mapOfMyCharBoolMap.count(key) > 0);
	}
	
	bool Test11MapChar::getValueForKey_MapOfMyCharBoolMap(const char &key) {
		return m_mapOfMyCharBoolMap[key];
	}
	
	std::pair<std::map<char, bool>::iterator, std::map<char, bool>::iterator> Test11MapChar::iteratorPair_MapOfMyCharBoolMap() {
		return std::make_pair(m_mapOfMyCharBoolMap.begin(), m_mapOfMyCharBoolMap.end());
	}
	std::map<char, char> Test11MapChar::getMapOfMyCharCharMap() const {
		return m_mapOfMyCharCharMap;
	}
	
	void Test11MapChar::setMapOfMyCharCharMap(const std::map<char, char> &val) {
		m_mapOfMyCharCharMap = val;
	}
	
	void Test11MapChar::clear_MapOfMyCharCharMap() {
		m_mapOfMyCharCharMap.clear();
	}
	
	uint32_t Test11MapChar::getSize_MapOfMyCharCharMap() const {
		return m_mapOfMyCharCharMap.size();
	}
	
	bool Test11MapChar::isEmpty_MapOfMyCharCharMap() const {
		return m_mapOfMyCharCharMap.empty();
	}
	
	void Test11MapChar::putTo_MapOfMyCharCharMap(const char &key, const char &val) {
		m_mapOfMyCharCharMap[key] = val;
	}
	
	bool Test11MapChar::containsKey_MapOfMyCharCharMap(const char &key) const {
		return (m_mapOfMyCharCharMap.count(key) > 0);
	}
	
	char Test11MapChar::getValueForKey_MapOfMyCharCharMap(const char &key) {
		return m_mapOfMyCharCharMap[key];
	}
	
	std::pair<std::map<char, char>::iterator, std::map<char, char>::iterator> Test11MapChar::iteratorPair_MapOfMyCharCharMap() {
		return std::make_pair(m_mapOfMyCharCharMap.begin(), m_mapOfMyCharCharMap.end());
	}
	std::map<char, int32_t> Test11MapChar::getMapOfMyCharInt32Map() const {
		return m_mapOfMyCharInt32Map;
	}
	
	void Test11MapChar::setMapOfMyCharInt32Map(const std::map<char, int32_t> &val) {
		m_mapOfMyCharInt32Map = val;
	}
	
	void Test11MapChar::clear_MapOfMyCharInt32Map() {
		m_mapOfMyCharInt32Map.clear();
	}
	
	uint32_t Test11MapChar::getSize_MapOfMyCharInt32Map() const {
		return m_mapOfMyCharInt32Map.size();
	}
	
	bool Test11MapChar::isEmpty_MapOfMyCharInt32Map() const {
		return m_mapOfMyCharInt32Map.empty();
	}
	
	void Test11MapChar::putTo_MapOfMyCharInt32Map(const char &key, const int32_t &val) {
		m_mapOfMyCharInt32Map[key] = val;
	}
	
	bool Test11MapChar::containsKey_MapOfMyCharInt32Map(const char &key) const {
		return (m_mapOfMyCharInt32Map.count(key) > 0);
	}
	
	int32_t Test11MapChar::getValueForKey_MapOfMyCharInt32Map(const char &key) {
		return m_mapOfMyCharInt32Map[key];
	}
	
	std::pair<std::map<char, int32_t>::iterator, std::map<char, int32_t>::iterator> Test11MapChar::iteratorPair_MapOfMyCharInt32Map() {
		return std::make_pair(m_mapOfMyCharInt32Map.begin(), m_mapOfMyCharInt32Map.end());
	}
	std::map<char, uint32_t> Test11MapChar::getMapOfMyCharUint32Map() const {
		return m_mapOfMyCharUint32Map;
	}
	
	void Test11MapChar::setMapOfMyCharUint32Map(const std::map<char, uint32_t> &val) {
		m_mapOfMyCharUint32Map = val;
	}
	
	void Test11MapChar::clear_MapOfMyCharUint32Map() {
		m_mapOfMyCharUint32Map.clear();
	}
	
	uint32_t Test11MapChar::getSize_MapOfMyCharUint32Map() const {
		return m_mapOfMyCharUint32Map.size();
	}
	
	bool Test11MapChar::isEmpty_MapOfMyCharUint32Map() const {
		return m_mapOfMyCharUint32Map.empty();
	}
	
	void Test11MapChar::putTo_MapOfMyCharUint32Map(const char &key, const uint32_t &val) {
		m_mapOfMyCharUint32Map[key] = val;
	}
	
	bool Test11MapChar::containsKey_MapOfMyCharUint32Map(const char &key) const {
		return (m_mapOfMyCharUint32Map.count(key) > 0);
	}
	
	uint32_t Test11MapChar::getValueForKey_MapOfMyCharUint32Map(const char &key) {
		return m_mapOfMyCharUint32Map[key];
	}
	
	std::pair<std::map<char, uint32_t>::iterator, std::map<char, uint32_t>::iterator> Test11MapChar::iteratorPair_MapOfMyCharUint32Map() {
		return std::make_pair(m_mapOfMyCharUint32Map.begin(), m_mapOfMyCharUint32Map.end());
	}
	std::map<char, float> Test11MapChar::getMapOfMyCharFloatMap() const {
		return m_mapOfMyCharFloatMap;
	}
	
	void Test11MapChar::setMapOfMyCharFloatMap(const std::map<char, float> &val) {
		m_mapOfMyCharFloatMap = val;
	}
	
	void Test11MapChar::clear_MapOfMyCharFloatMap() {
		m_mapOfMyCharFloatMap.clear();
	}
	
	uint32_t Test11MapChar::getSize_MapOfMyCharFloatMap() const {
		return m_mapOfMyCharFloatMap.size();
	}
	
	bool Test11MapChar::isEmpty_MapOfMyCharFloatMap() const {
		return m_mapOfMyCharFloatMap.empty();
	}
	
	void Test11MapChar::putTo_MapOfMyCharFloatMap(const char &key, const float &val) {
		m_mapOfMyCharFloatMap[key] = val;
	}
	
	bool Test11MapChar::containsKey_MapOfMyCharFloatMap(const char &key) const {
		return (m_mapOfMyCharFloatMap.count(key) > 0);
	}
	
	float Test11MapChar::getValueForKey_MapOfMyCharFloatMap(const char &key) {
		return m_mapOfMyCharFloatMap[key];
	}
	
	std::pair<std::map<char, float>::iterator, std::map<char, float>::iterator> Test11MapChar::iteratorPair_MapOfMyCharFloatMap() {
		return std::make_pair(m_mapOfMyCharFloatMap.begin(), m_mapOfMyCharFloatMap.end());
	}
	std::map<char, double> Test11MapChar::getMapOfMyCharDoubleMap() const {
		return m_mapOfMyCharDoubleMap;
	}
	
	void Test11MapChar::setMapOfMyCharDoubleMap(const std::map<char, double> &val) {
		m_mapOfMyCharDoubleMap = val;
	}
	
	void Test11MapChar::clear_MapOfMyCharDoubleMap() {
		m_mapOfMyCharDoubleMap.clear();
	}
	
	uint32_t Test11MapChar::getSize_MapOfMyCharDoubleMap() const {
		return m_mapOfMyCharDoubleMap.size();
	}
	
	bool Test11MapChar::isEmpty_MapOfMyCharDoubleMap() const {
		return m_mapOfMyCharDoubleMap.empty();
	}
	
	void Test11MapChar::putTo_MapOfMyCharDoubleMap(const char &key, const double &val) {
		m_mapOfMyCharDoubleMap[key] = val;
	}
	
	bool Test11MapChar::containsKey_MapOfMyCharDoubleMap(const char &key) const {
		return (m_mapOfMyCharDoubleMap.count(key) > 0);
	}
	
	double Test11MapChar::getValueForKey_MapOfMyCharDoubleMap(const char &key) {
		return m_mapOfMyCharDoubleMap[key];
	}
	
	std::pair<std::map<char, double>::iterator, std::map<char, double>::iterator> Test11MapChar::iteratorPair_MapOfMyCharDoubleMap() {
		return std::make_pair(m_mapOfMyCharDoubleMap.begin(), m_mapOfMyCharDoubleMap.end());
	}
	std::map<char, std::string> Test11MapChar::getMapOfMyCharStringMap() const {
		return m_mapOfMyCharStringMap;
	}
	
	void Test11MapChar::setMapOfMyCharStringMap(const std::map<char, std::string> &val) {
		m_mapOfMyCharStringMap = val;
	}
	
	void Test11MapChar::clear_MapOfMyCharStringMap() {
		m_mapOfMyCharStringMap.clear();
	}
	
	uint32_t Test11MapChar::getSize_MapOfMyCharStringMap() const {
		return m_mapOfMyCharStringMap.size();
	}
	
	bool Test11MapChar::isEmpty_MapOfMyCharStringMap() const {
		return m_mapOfMyCharStringMap.empty();
	}
	
	void Test11MapChar::putTo_MapOfMyCharStringMap(const char &key, const std::string &val) {
		m_mapOfMyCharStringMap[key] = val;
	}
	
	bool Test11MapChar::containsKey_MapOfMyCharStringMap(const char &key) const {
		return (m_mapOfMyCharStringMap.count(key) > 0);
	}
	
	std::string Test11MapChar::getValueForKey_MapOfMyCharStringMap(const char &key) {
		return m_mapOfMyCharStringMap[key];
	}
	
	std::pair<std::map<char, std::string>::iterator, std::map<char, std::string>::iterator> Test11MapChar::iteratorPair_MapOfMyCharStringMap() {
		return std::make_pair(m_mapOfMyCharStringMap.begin(), m_mapOfMyCharStringMap.end());
	}

	void Test11MapChar::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test11MapChar::toString() const {
		stringstream s;


		s << "Number of elements in map of MyCharBoolMap: " << getSize_MapOfMyCharBoolMap() << " ";
		s << "Number of elements in map of MyCharCharMap: " << getSize_MapOfMyCharCharMap() << " ";
		s << "Number of elements in map of MyCharInt32Map: " << getSize_MapOfMyCharInt32Map() << " ";
		s << "Number of elements in map of MyCharUint32Map: " << getSize_MapOfMyCharUint32Map() << " ";
		s << "Number of elements in map of MyCharFloatMap: " << getSize_MapOfMyCharFloatMap() << " ";
		s << "Number of elements in map of MyCharDoubleMap: " << getSize_MapOfMyCharDoubleMap() << " ";
		s << "Number of elements in map of MyCharStringMap: " << getSize_MapOfMyCharStringMap() << " ";

		return s.str();
	}

	ostream& Test11MapChar::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		{
			std::stringstream sstr_MyCharBoolMap;
			{
				std::map<char, bool>::const_iterator it = m_mapOfMyCharBoolMap.begin();
				while (it != m_mapOfMyCharBoolMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyCharBoolMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyCharBoolMap = sstr_MyCharBoolMap.str();
			s->write(1, str_sstr_MyCharBoolMap);
		}
		{
			std::stringstream sstr_MyCharCharMap;
			{
				std::map<char, char>::const_iterator it = m_mapOfMyCharCharMap.begin();
				while (it != m_mapOfMyCharCharMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyCharCharMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyCharCharMap = sstr_MyCharCharMap.str();
			s->write(2, str_sstr_MyCharCharMap);
		}
		{
			std::stringstream sstr_MyCharInt32Map;
			{
				std::map<char, int32_t>::const_iterator it = m_mapOfMyCharInt32Map.begin();
				while (it != m_mapOfMyCharInt32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyCharInt32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyCharInt32Map = sstr_MyCharInt32Map.str();
			s->write(3, str_sstr_MyCharInt32Map);
		}
		{
			std::stringstream sstr_MyCharUint32Map;
			{
				std::map<char, uint32_t>::const_iterator it = m_mapOfMyCharUint32Map.begin();
				while (it != m_mapOfMyCharUint32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyCharUint32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyCharUint32Map = sstr_MyCharUint32Map.str();
			s->write(4, str_sstr_MyCharUint32Map);
		}
		{
			std::stringstream sstr_MyCharFloatMap;
			{
				std::map<char, float>::const_iterator it = m_mapOfMyCharFloatMap.begin();
				while (it != m_mapOfMyCharFloatMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyCharFloatMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyCharFloatMap = sstr_MyCharFloatMap.str();
			s->write(5, str_sstr_MyCharFloatMap);
		}
		{
			std::stringstream sstr_MyCharDoubleMap;
			{
				std::map<char, double>::const_iterator it = m_mapOfMyCharDoubleMap.begin();
				while (it != m_mapOfMyCharDoubleMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyCharDoubleMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyCharDoubleMap = sstr_MyCharDoubleMap.str();
			s->write(6, str_sstr_MyCharDoubleMap);
		}
		{
			std::stringstream sstr_MyCharStringMap;
			{
				std::map<char, std::string>::const_iterator it = m_mapOfMyCharStringMap.begin();
				while (it != m_mapOfMyCharStringMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyCharStringMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyCharStringMap = sstr_MyCharStringMap.str();
			s->write(7, str_sstr_MyCharStringMap);
		}
		return out;
	}

	istream& Test11MapChar::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore elements from a string into MyCharBoolMap.
		{
			// Clean up the existing map of MyCharBoolMap.
			m_mapOfMyCharBoolMap.clear();
		
			std::string str_MyCharBoolMap;
			d->read(1, str_MyCharBoolMap);
			if (str_MyCharBoolMap.size() > 0) {
				std::stringstream sstr_str_MyCharBoolMap(str_MyCharBoolMap);
		
				// str_MyCharBoolMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyCharBoolMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyCharBoolMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							char key;
							bool value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyCharBoolMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyCharCharMap.
		{
			// Clean up the existing map of MyCharCharMap.
			m_mapOfMyCharCharMap.clear();
		
			std::string str_MyCharCharMap;
			d->read(2, str_MyCharCharMap);
			if (str_MyCharCharMap.size() > 0) {
				std::stringstream sstr_str_MyCharCharMap(str_MyCharCharMap);
		
				// str_MyCharCharMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyCharCharMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyCharCharMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							char key;
							char value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyCharCharMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyCharInt32Map.
		{
			// Clean up the existing map of MyCharInt32Map.
			m_mapOfMyCharInt32Map.clear();
		
			std::string str_MyCharInt32Map;
			d->read(3, str_MyCharInt32Map);
			if (str_MyCharInt32Map.size() > 0) {
				std::stringstream sstr_str_MyCharInt32Map(str_MyCharInt32Map);
		
				// str_MyCharInt32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyCharInt32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyCharInt32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							char key;
							int32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyCharInt32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyCharUint32Map.
		{
			// Clean up the existing map of MyCharUint32Map.
			m_mapOfMyCharUint32Map.clear();
		
			std::string str_MyCharUint32Map;
			d->read(4, str_MyCharUint32Map);
			if (str_MyCharUint32Map.size() > 0) {
				std::stringstream sstr_str_MyCharUint32Map(str_MyCharUint32Map);
		
				// str_MyCharUint32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyCharUint32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyCharUint32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							char key;
							uint32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyCharUint32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyCharFloatMap.
		{
			// Clean up the existing map of MyCharFloatMap.
			m_mapOfMyCharFloatMap.clear();
		
			std::string str_MyCharFloatMap;
			d->read(5, str_MyCharFloatMap);
			if (str_MyCharFloatMap.size() > 0) {
				std::stringstream sstr_str_MyCharFloatMap(str_MyCharFloatMap);
		
				// str_MyCharFloatMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyCharFloatMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyCharFloatMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							char key;
							float value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyCharFloatMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyCharDoubleMap.
		{
			// Clean up the existing map of MyCharDoubleMap.
			m_mapOfMyCharDoubleMap.clear();
		
			std::string str_MyCharDoubleMap;
			d->read(6, str_MyCharDoubleMap);
			if (str_MyCharDoubleMap.size() > 0) {
				std::stringstream sstr_str_MyCharDoubleMap(str_MyCharDoubleMap);
		
				// str_MyCharDoubleMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyCharDoubleMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyCharDoubleMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							char key;
							double value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyCharDoubleMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyCharStringMap.
		{
			// Clean up the existing map of MyCharStringMap.
			m_mapOfMyCharStringMap.clear();
		
			std::string str_MyCharStringMap;
			d->read(7, str_MyCharStringMap);
			if (str_MyCharStringMap.size() > 0) {
				std::stringstream sstr_str_MyCharStringMap(str_MyCharStringMap);
		
				// str_MyCharStringMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyCharStringMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyCharStringMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							char key;
							std::string value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyCharStringMap(key, value);
						}
					}
				}
			}
		}
		return in;
	}
