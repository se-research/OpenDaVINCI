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


#include "test11/generated/Test11MapFloat.h"

	using namespace std;
	using namespace odcore::base;


	Test11MapFloat::Test11MapFloat() :
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

	Test11MapFloat::Test11MapFloat(
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

	Test11MapFloat::Test11MapFloat(const Test11MapFloat &obj) :
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
	
	Test11MapFloat::~Test11MapFloat() {
	}

	Test11MapFloat& Test11MapFloat::operator=(const Test11MapFloat &obj) {
		m_mapOfMyFloatBoolMap = obj.m_mapOfMyFloatBoolMap;
		m_mapOfMyFloatCharMap = obj.m_mapOfMyFloatCharMap;
		m_mapOfMyFloatInt32Map = obj.m_mapOfMyFloatInt32Map;
		m_mapOfMyFloatUint32Map = obj.m_mapOfMyFloatUint32Map;
		m_mapOfMyFloatFloatMap = obj.m_mapOfMyFloatFloatMap;
		m_mapOfMyFloatDoubleMap = obj.m_mapOfMyFloatDoubleMap;
		m_mapOfMyFloatStringMap = obj.m_mapOfMyFloatStringMap;
		return (*this);
	}

	int32_t Test11MapFloat::ID() {
		return 17;
	}

	const string Test11MapFloat::ShortName() {
		return "Test11MapFloat";
	}

	const string Test11MapFloat::LongName() {
		return "Test11MapFloat";
	}

	int32_t Test11MapFloat::getID() const {
		return Test11MapFloat::ID();
	}

	const string Test11MapFloat::getShortName() const {
		return Test11MapFloat::ShortName();
	}

	const string Test11MapFloat::getLongName() const {
		return Test11MapFloat::LongName();
	}

	std::map<float, bool> Test11MapFloat::getMapOfMyFloatBoolMap() const {
		return m_mapOfMyFloatBoolMap;
	}
	
	void Test11MapFloat::setMapOfMyFloatBoolMap(const std::map<float, bool> &val) {
		m_mapOfMyFloatBoolMap = val;
	}
	
	void Test11MapFloat::clear_MapOfMyFloatBoolMap() {
		m_mapOfMyFloatBoolMap.clear();
	}
	
	uint32_t Test11MapFloat::getSize_MapOfMyFloatBoolMap() const {
		return m_mapOfMyFloatBoolMap.size();
	}
	
	bool Test11MapFloat::isEmpty_MapOfMyFloatBoolMap() const {
		return m_mapOfMyFloatBoolMap.empty();
	}
	
	void Test11MapFloat::putTo_MapOfMyFloatBoolMap(const float &key, const bool &val) {
		m_mapOfMyFloatBoolMap[key] = val;
	}
	
	bool Test11MapFloat::containsKey_MapOfMyFloatBoolMap(const float &key) const {
		return (m_mapOfMyFloatBoolMap.count(key) > 0);
	}
	
	bool Test11MapFloat::getValueForKey_MapOfMyFloatBoolMap(const float &key) {
		return m_mapOfMyFloatBoolMap[key];
	}
	
	std::pair<std::map<float, bool>::iterator, std::map<float, bool>::iterator> Test11MapFloat::iteratorPair_MapOfMyFloatBoolMap() {
		return std::make_pair(m_mapOfMyFloatBoolMap.begin(), m_mapOfMyFloatBoolMap.end());
	}
	std::map<float, char> Test11MapFloat::getMapOfMyFloatCharMap() const {
		return m_mapOfMyFloatCharMap;
	}
	
	void Test11MapFloat::setMapOfMyFloatCharMap(const std::map<float, char> &val) {
		m_mapOfMyFloatCharMap = val;
	}
	
	void Test11MapFloat::clear_MapOfMyFloatCharMap() {
		m_mapOfMyFloatCharMap.clear();
	}
	
	uint32_t Test11MapFloat::getSize_MapOfMyFloatCharMap() const {
		return m_mapOfMyFloatCharMap.size();
	}
	
	bool Test11MapFloat::isEmpty_MapOfMyFloatCharMap() const {
		return m_mapOfMyFloatCharMap.empty();
	}
	
	void Test11MapFloat::putTo_MapOfMyFloatCharMap(const float &key, const char &val) {
		m_mapOfMyFloatCharMap[key] = val;
	}
	
	bool Test11MapFloat::containsKey_MapOfMyFloatCharMap(const float &key) const {
		return (m_mapOfMyFloatCharMap.count(key) > 0);
	}
	
	char Test11MapFloat::getValueForKey_MapOfMyFloatCharMap(const float &key) {
		return m_mapOfMyFloatCharMap[key];
	}
	
	std::pair<std::map<float, char>::iterator, std::map<float, char>::iterator> Test11MapFloat::iteratorPair_MapOfMyFloatCharMap() {
		return std::make_pair(m_mapOfMyFloatCharMap.begin(), m_mapOfMyFloatCharMap.end());
	}
	std::map<float, int32_t> Test11MapFloat::getMapOfMyFloatInt32Map() const {
		return m_mapOfMyFloatInt32Map;
	}
	
	void Test11MapFloat::setMapOfMyFloatInt32Map(const std::map<float, int32_t> &val) {
		m_mapOfMyFloatInt32Map = val;
	}
	
	void Test11MapFloat::clear_MapOfMyFloatInt32Map() {
		m_mapOfMyFloatInt32Map.clear();
	}
	
	uint32_t Test11MapFloat::getSize_MapOfMyFloatInt32Map() const {
		return m_mapOfMyFloatInt32Map.size();
	}
	
	bool Test11MapFloat::isEmpty_MapOfMyFloatInt32Map() const {
		return m_mapOfMyFloatInt32Map.empty();
	}
	
	void Test11MapFloat::putTo_MapOfMyFloatInt32Map(const float &key, const int32_t &val) {
		m_mapOfMyFloatInt32Map[key] = val;
	}
	
	bool Test11MapFloat::containsKey_MapOfMyFloatInt32Map(const float &key) const {
		return (m_mapOfMyFloatInt32Map.count(key) > 0);
	}
	
	int32_t Test11MapFloat::getValueForKey_MapOfMyFloatInt32Map(const float &key) {
		return m_mapOfMyFloatInt32Map[key];
	}
	
	std::pair<std::map<float, int32_t>::iterator, std::map<float, int32_t>::iterator> Test11MapFloat::iteratorPair_MapOfMyFloatInt32Map() {
		return std::make_pair(m_mapOfMyFloatInt32Map.begin(), m_mapOfMyFloatInt32Map.end());
	}
	std::map<float, uint32_t> Test11MapFloat::getMapOfMyFloatUint32Map() const {
		return m_mapOfMyFloatUint32Map;
	}
	
	void Test11MapFloat::setMapOfMyFloatUint32Map(const std::map<float, uint32_t> &val) {
		m_mapOfMyFloatUint32Map = val;
	}
	
	void Test11MapFloat::clear_MapOfMyFloatUint32Map() {
		m_mapOfMyFloatUint32Map.clear();
	}
	
	uint32_t Test11MapFloat::getSize_MapOfMyFloatUint32Map() const {
		return m_mapOfMyFloatUint32Map.size();
	}
	
	bool Test11MapFloat::isEmpty_MapOfMyFloatUint32Map() const {
		return m_mapOfMyFloatUint32Map.empty();
	}
	
	void Test11MapFloat::putTo_MapOfMyFloatUint32Map(const float &key, const uint32_t &val) {
		m_mapOfMyFloatUint32Map[key] = val;
	}
	
	bool Test11MapFloat::containsKey_MapOfMyFloatUint32Map(const float &key) const {
		return (m_mapOfMyFloatUint32Map.count(key) > 0);
	}
	
	uint32_t Test11MapFloat::getValueForKey_MapOfMyFloatUint32Map(const float &key) {
		return m_mapOfMyFloatUint32Map[key];
	}
	
	std::pair<std::map<float, uint32_t>::iterator, std::map<float, uint32_t>::iterator> Test11MapFloat::iteratorPair_MapOfMyFloatUint32Map() {
		return std::make_pair(m_mapOfMyFloatUint32Map.begin(), m_mapOfMyFloatUint32Map.end());
	}
	std::map<float, float> Test11MapFloat::getMapOfMyFloatFloatMap() const {
		return m_mapOfMyFloatFloatMap;
	}
	
	void Test11MapFloat::setMapOfMyFloatFloatMap(const std::map<float, float> &val) {
		m_mapOfMyFloatFloatMap = val;
	}
	
	void Test11MapFloat::clear_MapOfMyFloatFloatMap() {
		m_mapOfMyFloatFloatMap.clear();
	}
	
	uint32_t Test11MapFloat::getSize_MapOfMyFloatFloatMap() const {
		return m_mapOfMyFloatFloatMap.size();
	}
	
	bool Test11MapFloat::isEmpty_MapOfMyFloatFloatMap() const {
		return m_mapOfMyFloatFloatMap.empty();
	}
	
	void Test11MapFloat::putTo_MapOfMyFloatFloatMap(const float &key, const float &val) {
		m_mapOfMyFloatFloatMap[key] = val;
	}
	
	bool Test11MapFloat::containsKey_MapOfMyFloatFloatMap(const float &key) const {
		return (m_mapOfMyFloatFloatMap.count(key) > 0);
	}
	
	float Test11MapFloat::getValueForKey_MapOfMyFloatFloatMap(const float &key) {
		return m_mapOfMyFloatFloatMap[key];
	}
	
	std::pair<std::map<float, float>::iterator, std::map<float, float>::iterator> Test11MapFloat::iteratorPair_MapOfMyFloatFloatMap() {
		return std::make_pair(m_mapOfMyFloatFloatMap.begin(), m_mapOfMyFloatFloatMap.end());
	}
	std::map<float, double> Test11MapFloat::getMapOfMyFloatDoubleMap() const {
		return m_mapOfMyFloatDoubleMap;
	}
	
	void Test11MapFloat::setMapOfMyFloatDoubleMap(const std::map<float, double> &val) {
		m_mapOfMyFloatDoubleMap = val;
	}
	
	void Test11MapFloat::clear_MapOfMyFloatDoubleMap() {
		m_mapOfMyFloatDoubleMap.clear();
	}
	
	uint32_t Test11MapFloat::getSize_MapOfMyFloatDoubleMap() const {
		return m_mapOfMyFloatDoubleMap.size();
	}
	
	bool Test11MapFloat::isEmpty_MapOfMyFloatDoubleMap() const {
		return m_mapOfMyFloatDoubleMap.empty();
	}
	
	void Test11MapFloat::putTo_MapOfMyFloatDoubleMap(const float &key, const double &val) {
		m_mapOfMyFloatDoubleMap[key] = val;
	}
	
	bool Test11MapFloat::containsKey_MapOfMyFloatDoubleMap(const float &key) const {
		return (m_mapOfMyFloatDoubleMap.count(key) > 0);
	}
	
	double Test11MapFloat::getValueForKey_MapOfMyFloatDoubleMap(const float &key) {
		return m_mapOfMyFloatDoubleMap[key];
	}
	
	std::pair<std::map<float, double>::iterator, std::map<float, double>::iterator> Test11MapFloat::iteratorPair_MapOfMyFloatDoubleMap() {
		return std::make_pair(m_mapOfMyFloatDoubleMap.begin(), m_mapOfMyFloatDoubleMap.end());
	}
	std::map<float, std::string> Test11MapFloat::getMapOfMyFloatStringMap() const {
		return m_mapOfMyFloatStringMap;
	}
	
	void Test11MapFloat::setMapOfMyFloatStringMap(const std::map<float, std::string> &val) {
		m_mapOfMyFloatStringMap = val;
	}
	
	void Test11MapFloat::clear_MapOfMyFloatStringMap() {
		m_mapOfMyFloatStringMap.clear();
	}
	
	uint32_t Test11MapFloat::getSize_MapOfMyFloatStringMap() const {
		return m_mapOfMyFloatStringMap.size();
	}
	
	bool Test11MapFloat::isEmpty_MapOfMyFloatStringMap() const {
		return m_mapOfMyFloatStringMap.empty();
	}
	
	void Test11MapFloat::putTo_MapOfMyFloatStringMap(const float &key, const std::string &val) {
		m_mapOfMyFloatStringMap[key] = val;
	}
	
	bool Test11MapFloat::containsKey_MapOfMyFloatStringMap(const float &key) const {
		return (m_mapOfMyFloatStringMap.count(key) > 0);
	}
	
	std::string Test11MapFloat::getValueForKey_MapOfMyFloatStringMap(const float &key) {
		return m_mapOfMyFloatStringMap[key];
	}
	
	std::pair<std::map<float, std::string>::iterator, std::map<float, std::string>::iterator> Test11MapFloat::iteratorPair_MapOfMyFloatStringMap() {
		return std::make_pair(m_mapOfMyFloatStringMap.begin(), m_mapOfMyFloatStringMap.end());
	}

	void Test11MapFloat::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test11MapFloat::toString() const {
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

	ostream& Test11MapFloat::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		{
			std::stringstream sstr_MyFloatBoolMap;
			{
				std::map<float, bool>::const_iterator it = m_mapOfMyFloatBoolMap.begin();
				while (it != m_mapOfMyFloatBoolMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyFloatBoolMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyFloatBoolMap = sstr_MyFloatBoolMap.str();
			s->write(1, str_sstr_MyFloatBoolMap);
		}
		{
			std::stringstream sstr_MyFloatCharMap;
			{
				std::map<float, char>::const_iterator it = m_mapOfMyFloatCharMap.begin();
				while (it != m_mapOfMyFloatCharMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyFloatCharMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyFloatCharMap = sstr_MyFloatCharMap.str();
			s->write(2, str_sstr_MyFloatCharMap);
		}
		{
			std::stringstream sstr_MyFloatInt32Map;
			{
				std::map<float, int32_t>::const_iterator it = m_mapOfMyFloatInt32Map.begin();
				while (it != m_mapOfMyFloatInt32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyFloatInt32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyFloatInt32Map = sstr_MyFloatInt32Map.str();
			s->write(3, str_sstr_MyFloatInt32Map);
		}
		{
			std::stringstream sstr_MyFloatUint32Map;
			{
				std::map<float, uint32_t>::const_iterator it = m_mapOfMyFloatUint32Map.begin();
				while (it != m_mapOfMyFloatUint32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyFloatUint32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyFloatUint32Map = sstr_MyFloatUint32Map.str();
			s->write(4, str_sstr_MyFloatUint32Map);
		}
		{
			std::stringstream sstr_MyFloatFloatMap;
			{
				std::map<float, float>::const_iterator it = m_mapOfMyFloatFloatMap.begin();
				while (it != m_mapOfMyFloatFloatMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyFloatFloatMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyFloatFloatMap = sstr_MyFloatFloatMap.str();
			s->write(5, str_sstr_MyFloatFloatMap);
		}
		{
			std::stringstream sstr_MyFloatDoubleMap;
			{
				std::map<float, double>::const_iterator it = m_mapOfMyFloatDoubleMap.begin();
				while (it != m_mapOfMyFloatDoubleMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyFloatDoubleMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyFloatDoubleMap = sstr_MyFloatDoubleMap.str();
			s->write(6, str_sstr_MyFloatDoubleMap);
		}
		{
			std::stringstream sstr_MyFloatStringMap;
			{
				std::map<float, std::string>::const_iterator it = m_mapOfMyFloatStringMap.begin();
				while (it != m_mapOfMyFloatStringMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyFloatStringMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyFloatStringMap = sstr_MyFloatStringMap.str();
			s->write(7, str_sstr_MyFloatStringMap);
		}
		return out;
	}

	istream& Test11MapFloat::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore elements from a string into MyFloatBoolMap.
		{
			// Clean up the existing map of MyFloatBoolMap.
			m_mapOfMyFloatBoolMap.clear();
		
			std::string str_MyFloatBoolMap;
			d->read(1, str_MyFloatBoolMap);
			if (str_MyFloatBoolMap.size() > 0) {
				std::stringstream sstr_str_MyFloatBoolMap(str_MyFloatBoolMap);
		
				// str_MyFloatBoolMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyFloatBoolMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyFloatBoolMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							float key;
							bool value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyFloatBoolMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyFloatCharMap.
		{
			// Clean up the existing map of MyFloatCharMap.
			m_mapOfMyFloatCharMap.clear();
		
			std::string str_MyFloatCharMap;
			d->read(2, str_MyFloatCharMap);
			if (str_MyFloatCharMap.size() > 0) {
				std::stringstream sstr_str_MyFloatCharMap(str_MyFloatCharMap);
		
				// str_MyFloatCharMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyFloatCharMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyFloatCharMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							float key;
							char value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyFloatCharMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyFloatInt32Map.
		{
			// Clean up the existing map of MyFloatInt32Map.
			m_mapOfMyFloatInt32Map.clear();
		
			std::string str_MyFloatInt32Map;
			d->read(3, str_MyFloatInt32Map);
			if (str_MyFloatInt32Map.size() > 0) {
				std::stringstream sstr_str_MyFloatInt32Map(str_MyFloatInt32Map);
		
				// str_MyFloatInt32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyFloatInt32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyFloatInt32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							float key;
							int32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyFloatInt32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyFloatUint32Map.
		{
			// Clean up the existing map of MyFloatUint32Map.
			m_mapOfMyFloatUint32Map.clear();
		
			std::string str_MyFloatUint32Map;
			d->read(4, str_MyFloatUint32Map);
			if (str_MyFloatUint32Map.size() > 0) {
				std::stringstream sstr_str_MyFloatUint32Map(str_MyFloatUint32Map);
		
				// str_MyFloatUint32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyFloatUint32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyFloatUint32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							float key;
							uint32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyFloatUint32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyFloatFloatMap.
		{
			// Clean up the existing map of MyFloatFloatMap.
			m_mapOfMyFloatFloatMap.clear();
		
			std::string str_MyFloatFloatMap;
			d->read(5, str_MyFloatFloatMap);
			if (str_MyFloatFloatMap.size() > 0) {
				std::stringstream sstr_str_MyFloatFloatMap(str_MyFloatFloatMap);
		
				// str_MyFloatFloatMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyFloatFloatMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyFloatFloatMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							float key;
							float value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyFloatFloatMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyFloatDoubleMap.
		{
			// Clean up the existing map of MyFloatDoubleMap.
			m_mapOfMyFloatDoubleMap.clear();
		
			std::string str_MyFloatDoubleMap;
			d->read(6, str_MyFloatDoubleMap);
			if (str_MyFloatDoubleMap.size() > 0) {
				std::stringstream sstr_str_MyFloatDoubleMap(str_MyFloatDoubleMap);
		
				// str_MyFloatDoubleMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyFloatDoubleMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyFloatDoubleMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							float key;
							double value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyFloatDoubleMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyFloatStringMap.
		{
			// Clean up the existing map of MyFloatStringMap.
			m_mapOfMyFloatStringMap.clear();
		
			std::string str_MyFloatStringMap;
			d->read(7, str_MyFloatStringMap);
			if (str_MyFloatStringMap.size() > 0) {
				std::stringstream sstr_str_MyFloatStringMap(str_MyFloatStringMap);
		
				// str_MyFloatStringMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyFloatStringMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyFloatStringMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							float key;
							std::string value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyFloatStringMap(key, value);
						}
					}
				}
			}
		}
		return in;
	}
