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
			std::stringstream sstr_MyInt32BoolMap;
			{
				std::map<int32_t, bool>::const_iterator it = m_mapOfMyInt32BoolMap.begin();
				while (it != m_mapOfMyInt32BoolMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyInt32BoolMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyInt32BoolMap = sstr_MyInt32BoolMap.str();
			s->write(1, str_sstr_MyInt32BoolMap);
		}
		{
			std::stringstream sstr_MyInt32CharMap;
			{
				std::map<int32_t, char>::const_iterator it = m_mapOfMyInt32CharMap.begin();
				while (it != m_mapOfMyInt32CharMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyInt32CharMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyInt32CharMap = sstr_MyInt32CharMap.str();
			s->write(2, str_sstr_MyInt32CharMap);
		}
		{
			std::stringstream sstr_MyInt32Int32Map;
			{
				std::map<int32_t, int32_t>::const_iterator it = m_mapOfMyInt32Int32Map.begin();
				while (it != m_mapOfMyInt32Int32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyInt32Int32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyInt32Int32Map = sstr_MyInt32Int32Map.str();
			s->write(3, str_sstr_MyInt32Int32Map);
		}
		{
			std::stringstream sstr_MyInt32Uint32Map;
			{
				std::map<int32_t, uint32_t>::const_iterator it = m_mapOfMyInt32Uint32Map.begin();
				while (it != m_mapOfMyInt32Uint32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyInt32Uint32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyInt32Uint32Map = sstr_MyInt32Uint32Map.str();
			s->write(4, str_sstr_MyInt32Uint32Map);
		}
		{
			std::stringstream sstr_MyInt32FloatMap;
			{
				std::map<int32_t, float>::const_iterator it = m_mapOfMyInt32FloatMap.begin();
				while (it != m_mapOfMyInt32FloatMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyInt32FloatMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyInt32FloatMap = sstr_MyInt32FloatMap.str();
			s->write(5, str_sstr_MyInt32FloatMap);
		}
		{
			std::stringstream sstr_MyInt32DoubleMap;
			{
				std::map<int32_t, double>::const_iterator it = m_mapOfMyInt32DoubleMap.begin();
				while (it != m_mapOfMyInt32DoubleMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyInt32DoubleMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyInt32DoubleMap = sstr_MyInt32DoubleMap.str();
			s->write(6, str_sstr_MyInt32DoubleMap);
		}
		{
			std::stringstream sstr_MyInt32StringMap;
			{
				std::map<int32_t, std::string>::const_iterator it = m_mapOfMyInt32StringMap.begin();
				while (it != m_mapOfMyInt32StringMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyInt32StringMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyInt32StringMap = sstr_MyInt32StringMap.str();
			s->write(7, str_sstr_MyInt32StringMap);
		}
		return out;
	}

	istream& Test12MapInt32::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore elements from a string into MyInt32BoolMap.
		{
			// Clean up the existing map of MyInt32BoolMap.
			m_mapOfMyInt32BoolMap.clear();
		
			std::string str_MyInt32BoolMap;
			d->read(1, str_MyInt32BoolMap);
			if (str_MyInt32BoolMap.size() > 0) {
				std::stringstream sstr_str_MyInt32BoolMap(str_MyInt32BoolMap);
		
				// str_MyInt32BoolMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyInt32BoolMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyInt32BoolMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							int32_t key;
							bool value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyInt32BoolMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyInt32CharMap.
		{
			// Clean up the existing map of MyInt32CharMap.
			m_mapOfMyInt32CharMap.clear();
		
			std::string str_MyInt32CharMap;
			d->read(2, str_MyInt32CharMap);
			if (str_MyInt32CharMap.size() > 0) {
				std::stringstream sstr_str_MyInt32CharMap(str_MyInt32CharMap);
		
				// str_MyInt32CharMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyInt32CharMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyInt32CharMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							int32_t key;
							char value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyInt32CharMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyInt32Int32Map.
		{
			// Clean up the existing map of MyInt32Int32Map.
			m_mapOfMyInt32Int32Map.clear();
		
			std::string str_MyInt32Int32Map;
			d->read(3, str_MyInt32Int32Map);
			if (str_MyInt32Int32Map.size() > 0) {
				std::stringstream sstr_str_MyInt32Int32Map(str_MyInt32Int32Map);
		
				// str_MyInt32Int32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyInt32Int32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyInt32Int32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							int32_t key;
							int32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyInt32Int32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyInt32Uint32Map.
		{
			// Clean up the existing map of MyInt32Uint32Map.
			m_mapOfMyInt32Uint32Map.clear();
		
			std::string str_MyInt32Uint32Map;
			d->read(4, str_MyInt32Uint32Map);
			if (str_MyInt32Uint32Map.size() > 0) {
				std::stringstream sstr_str_MyInt32Uint32Map(str_MyInt32Uint32Map);
		
				// str_MyInt32Uint32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyInt32Uint32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyInt32Uint32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							int32_t key;
							uint32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyInt32Uint32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyInt32FloatMap.
		{
			// Clean up the existing map of MyInt32FloatMap.
			m_mapOfMyInt32FloatMap.clear();
		
			std::string str_MyInt32FloatMap;
			d->read(5, str_MyInt32FloatMap);
			if (str_MyInt32FloatMap.size() > 0) {
				std::stringstream sstr_str_MyInt32FloatMap(str_MyInt32FloatMap);
		
				// str_MyInt32FloatMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyInt32FloatMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyInt32FloatMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							int32_t key;
							float value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyInt32FloatMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyInt32DoubleMap.
		{
			// Clean up the existing map of MyInt32DoubleMap.
			m_mapOfMyInt32DoubleMap.clear();
		
			std::string str_MyInt32DoubleMap;
			d->read(6, str_MyInt32DoubleMap);
			if (str_MyInt32DoubleMap.size() > 0) {
				std::stringstream sstr_str_MyInt32DoubleMap(str_MyInt32DoubleMap);
		
				// str_MyInt32DoubleMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyInt32DoubleMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyInt32DoubleMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							int32_t key;
							double value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyInt32DoubleMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyInt32StringMap.
		{
			// Clean up the existing map of MyInt32StringMap.
			m_mapOfMyInt32StringMap.clear();
		
			std::string str_MyInt32StringMap;
			d->read(7, str_MyInt32StringMap);
			if (str_MyInt32StringMap.size() > 0) {
				std::stringstream sstr_str_MyInt32StringMap(str_MyInt32StringMap);
		
				// str_MyInt32StringMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyInt32StringMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyInt32StringMap, str_sstr_keyValue);
		
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
							putTo_MapOfMyInt32StringMap(key, value);
						}
					}
				}
			}
		}
		return in;
	}
