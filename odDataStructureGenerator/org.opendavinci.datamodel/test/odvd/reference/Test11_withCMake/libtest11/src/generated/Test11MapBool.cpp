/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include <opendavinci/odcore/serialization/Deserializer.h>
#include <opendavinci/odcore/serialization/SerializationFactory.h>
#include <opendavinci/odcore/serialization/Serializer.h>

#include "test11/generated/Test11MapBool.h"

	using namespace std;
	using namespace odcore::base;
	using namespace odcore::serialization;


	Test11MapBool::Test11MapBool() :
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

	Test11MapBool::Test11MapBool(
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

	Test11MapBool::Test11MapBool(const Test11MapBool &obj) :
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
	
	Test11MapBool::~Test11MapBool() {
	}

	Test11MapBool& Test11MapBool::operator=(const Test11MapBool &obj) {
		m_mapOfMyBoolBoolMap = obj.m_mapOfMyBoolBoolMap;
		m_mapOfMyBoolCharMap = obj.m_mapOfMyBoolCharMap;
		m_mapOfMyBoolInt32Map = obj.m_mapOfMyBoolInt32Map;
		m_mapOfMyBoolUint32Map = obj.m_mapOfMyBoolUint32Map;
		m_mapOfMyBoolFloatMap = obj.m_mapOfMyBoolFloatMap;
		m_mapOfMyBoolDoubleMap = obj.m_mapOfMyBoolDoubleMap;
		m_mapOfMyBoolStringMap = obj.m_mapOfMyBoolStringMap;
		return (*this);
	}

	int32_t Test11MapBool::ID() {
		return 13;
	}

	const string Test11MapBool::ShortName() {
		return "Test11MapBool";
	}

	const string Test11MapBool::LongName() {
		return "Test11MapBool";
	}

	int32_t Test11MapBool::getID() const {
		return Test11MapBool::ID();
	}

	const string Test11MapBool::getShortName() const {
		return Test11MapBool::ShortName();
	}

	const string Test11MapBool::getLongName() const {
		return Test11MapBool::LongName();
	}

	std::map<bool, bool> Test11MapBool::getMapOfMyBoolBoolMap() const {
		return m_mapOfMyBoolBoolMap;
	}
	
	void Test11MapBool::setMapOfMyBoolBoolMap(const std::map<bool, bool> &val) {
		m_mapOfMyBoolBoolMap = val;
	}
	
	void Test11MapBool::clear_MapOfMyBoolBoolMap() {
		m_mapOfMyBoolBoolMap.clear();
	}
	
	uint32_t Test11MapBool::getSize_MapOfMyBoolBoolMap() const {
		return m_mapOfMyBoolBoolMap.size();
	}
	
	bool Test11MapBool::isEmpty_MapOfMyBoolBoolMap() const {
		return m_mapOfMyBoolBoolMap.empty();
	}
	
	void Test11MapBool::putTo_MapOfMyBoolBoolMap(const bool &key, const bool &val) {
		m_mapOfMyBoolBoolMap[key] = val;
	}
	
	bool Test11MapBool::containsKey_MapOfMyBoolBoolMap(const bool &key) const {
		return (m_mapOfMyBoolBoolMap.count(key) > 0);
	}
	
	bool Test11MapBool::getValueForKey_MapOfMyBoolBoolMap(const bool &key) {
		return m_mapOfMyBoolBoolMap[key];
	}
	
	std::pair<std::map<bool, bool>::iterator, std::map<bool, bool>::iterator> Test11MapBool::iteratorPair_MapOfMyBoolBoolMap() {
		return std::make_pair(m_mapOfMyBoolBoolMap.begin(), m_mapOfMyBoolBoolMap.end());
	}
	std::map<bool, char> Test11MapBool::getMapOfMyBoolCharMap() const {
		return m_mapOfMyBoolCharMap;
	}
	
	void Test11MapBool::setMapOfMyBoolCharMap(const std::map<bool, char> &val) {
		m_mapOfMyBoolCharMap = val;
	}
	
	void Test11MapBool::clear_MapOfMyBoolCharMap() {
		m_mapOfMyBoolCharMap.clear();
	}
	
	uint32_t Test11MapBool::getSize_MapOfMyBoolCharMap() const {
		return m_mapOfMyBoolCharMap.size();
	}
	
	bool Test11MapBool::isEmpty_MapOfMyBoolCharMap() const {
		return m_mapOfMyBoolCharMap.empty();
	}
	
	void Test11MapBool::putTo_MapOfMyBoolCharMap(const bool &key, const char &val) {
		m_mapOfMyBoolCharMap[key] = val;
	}
	
	bool Test11MapBool::containsKey_MapOfMyBoolCharMap(const bool &key) const {
		return (m_mapOfMyBoolCharMap.count(key) > 0);
	}
	
	char Test11MapBool::getValueForKey_MapOfMyBoolCharMap(const bool &key) {
		return m_mapOfMyBoolCharMap[key];
	}
	
	std::pair<std::map<bool, char>::iterator, std::map<bool, char>::iterator> Test11MapBool::iteratorPair_MapOfMyBoolCharMap() {
		return std::make_pair(m_mapOfMyBoolCharMap.begin(), m_mapOfMyBoolCharMap.end());
	}
	std::map<bool, int32_t> Test11MapBool::getMapOfMyBoolInt32Map() const {
		return m_mapOfMyBoolInt32Map;
	}
	
	void Test11MapBool::setMapOfMyBoolInt32Map(const std::map<bool, int32_t> &val) {
		m_mapOfMyBoolInt32Map = val;
	}
	
	void Test11MapBool::clear_MapOfMyBoolInt32Map() {
		m_mapOfMyBoolInt32Map.clear();
	}
	
	uint32_t Test11MapBool::getSize_MapOfMyBoolInt32Map() const {
		return m_mapOfMyBoolInt32Map.size();
	}
	
	bool Test11MapBool::isEmpty_MapOfMyBoolInt32Map() const {
		return m_mapOfMyBoolInt32Map.empty();
	}
	
	void Test11MapBool::putTo_MapOfMyBoolInt32Map(const bool &key, const int32_t &val) {
		m_mapOfMyBoolInt32Map[key] = val;
	}
	
	bool Test11MapBool::containsKey_MapOfMyBoolInt32Map(const bool &key) const {
		return (m_mapOfMyBoolInt32Map.count(key) > 0);
	}
	
	int32_t Test11MapBool::getValueForKey_MapOfMyBoolInt32Map(const bool &key) {
		return m_mapOfMyBoolInt32Map[key];
	}
	
	std::pair<std::map<bool, int32_t>::iterator, std::map<bool, int32_t>::iterator> Test11MapBool::iteratorPair_MapOfMyBoolInt32Map() {
		return std::make_pair(m_mapOfMyBoolInt32Map.begin(), m_mapOfMyBoolInt32Map.end());
	}
	std::map<bool, uint32_t> Test11MapBool::getMapOfMyBoolUint32Map() const {
		return m_mapOfMyBoolUint32Map;
	}
	
	void Test11MapBool::setMapOfMyBoolUint32Map(const std::map<bool, uint32_t> &val) {
		m_mapOfMyBoolUint32Map = val;
	}
	
	void Test11MapBool::clear_MapOfMyBoolUint32Map() {
		m_mapOfMyBoolUint32Map.clear();
	}
	
	uint32_t Test11MapBool::getSize_MapOfMyBoolUint32Map() const {
		return m_mapOfMyBoolUint32Map.size();
	}
	
	bool Test11MapBool::isEmpty_MapOfMyBoolUint32Map() const {
		return m_mapOfMyBoolUint32Map.empty();
	}
	
	void Test11MapBool::putTo_MapOfMyBoolUint32Map(const bool &key, const uint32_t &val) {
		m_mapOfMyBoolUint32Map[key] = val;
	}
	
	bool Test11MapBool::containsKey_MapOfMyBoolUint32Map(const bool &key) const {
		return (m_mapOfMyBoolUint32Map.count(key) > 0);
	}
	
	uint32_t Test11MapBool::getValueForKey_MapOfMyBoolUint32Map(const bool &key) {
		return m_mapOfMyBoolUint32Map[key];
	}
	
	std::pair<std::map<bool, uint32_t>::iterator, std::map<bool, uint32_t>::iterator> Test11MapBool::iteratorPair_MapOfMyBoolUint32Map() {
		return std::make_pair(m_mapOfMyBoolUint32Map.begin(), m_mapOfMyBoolUint32Map.end());
	}
	std::map<bool, float> Test11MapBool::getMapOfMyBoolFloatMap() const {
		return m_mapOfMyBoolFloatMap;
	}
	
	void Test11MapBool::setMapOfMyBoolFloatMap(const std::map<bool, float> &val) {
		m_mapOfMyBoolFloatMap = val;
	}
	
	void Test11MapBool::clear_MapOfMyBoolFloatMap() {
		m_mapOfMyBoolFloatMap.clear();
	}
	
	uint32_t Test11MapBool::getSize_MapOfMyBoolFloatMap() const {
		return m_mapOfMyBoolFloatMap.size();
	}
	
	bool Test11MapBool::isEmpty_MapOfMyBoolFloatMap() const {
		return m_mapOfMyBoolFloatMap.empty();
	}
	
	void Test11MapBool::putTo_MapOfMyBoolFloatMap(const bool &key, const float &val) {
		m_mapOfMyBoolFloatMap[key] = val;
	}
	
	bool Test11MapBool::containsKey_MapOfMyBoolFloatMap(const bool &key) const {
		return (m_mapOfMyBoolFloatMap.count(key) > 0);
	}
	
	float Test11MapBool::getValueForKey_MapOfMyBoolFloatMap(const bool &key) {
		return m_mapOfMyBoolFloatMap[key];
	}
	
	std::pair<std::map<bool, float>::iterator, std::map<bool, float>::iterator> Test11MapBool::iteratorPair_MapOfMyBoolFloatMap() {
		return std::make_pair(m_mapOfMyBoolFloatMap.begin(), m_mapOfMyBoolFloatMap.end());
	}
	std::map<bool, double> Test11MapBool::getMapOfMyBoolDoubleMap() const {
		return m_mapOfMyBoolDoubleMap;
	}
	
	void Test11MapBool::setMapOfMyBoolDoubleMap(const std::map<bool, double> &val) {
		m_mapOfMyBoolDoubleMap = val;
	}
	
	void Test11MapBool::clear_MapOfMyBoolDoubleMap() {
		m_mapOfMyBoolDoubleMap.clear();
	}
	
	uint32_t Test11MapBool::getSize_MapOfMyBoolDoubleMap() const {
		return m_mapOfMyBoolDoubleMap.size();
	}
	
	bool Test11MapBool::isEmpty_MapOfMyBoolDoubleMap() const {
		return m_mapOfMyBoolDoubleMap.empty();
	}
	
	void Test11MapBool::putTo_MapOfMyBoolDoubleMap(const bool &key, const double &val) {
		m_mapOfMyBoolDoubleMap[key] = val;
	}
	
	bool Test11MapBool::containsKey_MapOfMyBoolDoubleMap(const bool &key) const {
		return (m_mapOfMyBoolDoubleMap.count(key) > 0);
	}
	
	double Test11MapBool::getValueForKey_MapOfMyBoolDoubleMap(const bool &key) {
		return m_mapOfMyBoolDoubleMap[key];
	}
	
	std::pair<std::map<bool, double>::iterator, std::map<bool, double>::iterator> Test11MapBool::iteratorPair_MapOfMyBoolDoubleMap() {
		return std::make_pair(m_mapOfMyBoolDoubleMap.begin(), m_mapOfMyBoolDoubleMap.end());
	}
	std::map<bool, std::string> Test11MapBool::getMapOfMyBoolStringMap() const {
		return m_mapOfMyBoolStringMap;
	}
	
	void Test11MapBool::setMapOfMyBoolStringMap(const std::map<bool, std::string> &val) {
		m_mapOfMyBoolStringMap = val;
	}
	
	void Test11MapBool::clear_MapOfMyBoolStringMap() {
		m_mapOfMyBoolStringMap.clear();
	}
	
	uint32_t Test11MapBool::getSize_MapOfMyBoolStringMap() const {
		return m_mapOfMyBoolStringMap.size();
	}
	
	bool Test11MapBool::isEmpty_MapOfMyBoolStringMap() const {
		return m_mapOfMyBoolStringMap.empty();
	}
	
	void Test11MapBool::putTo_MapOfMyBoolStringMap(const bool &key, const std::string &val) {
		m_mapOfMyBoolStringMap[key] = val;
	}
	
	bool Test11MapBool::containsKey_MapOfMyBoolStringMap(const bool &key) const {
		return (m_mapOfMyBoolStringMap.count(key) > 0);
	}
	
	std::string Test11MapBool::getValueForKey_MapOfMyBoolStringMap(const bool &key) {
		return m_mapOfMyBoolStringMap[key];
	}
	
	std::pair<std::map<bool, std::string>::iterator, std::map<bool, std::string>::iterator> Test11MapBool::iteratorPair_MapOfMyBoolStringMap() {
		return std::make_pair(m_mapOfMyBoolStringMap.begin(), m_mapOfMyBoolStringMap.end());
	}

	void Test11MapBool::accept(odcore::base::Visitor &v) {
		v.beginVisit(ID(), ShortName(), LongName());
		v.endVisit();
	}

	const string Test11MapBool::toString() const {
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

	ostream& Test11MapBool::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		{
			std::stringstream sstr_MyBoolBoolMap;
			{
				std::map<bool, bool>::const_iterator it = m_mapOfMyBoolBoolMap.begin();
				while (it != m_mapOfMyBoolBoolMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyBoolBoolMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyBoolBoolMap = sstr_MyBoolBoolMap.str();
			s->write(1, str_sstr_MyBoolBoolMap);
		}
		{
			std::stringstream sstr_MyBoolCharMap;
			{
				std::map<bool, char>::const_iterator it = m_mapOfMyBoolCharMap.begin();
				while (it != m_mapOfMyBoolCharMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyBoolCharMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyBoolCharMap = sstr_MyBoolCharMap.str();
			s->write(2, str_sstr_MyBoolCharMap);
		}
		{
			std::stringstream sstr_MyBoolInt32Map;
			{
				std::map<bool, int32_t>::const_iterator it = m_mapOfMyBoolInt32Map.begin();
				while (it != m_mapOfMyBoolInt32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyBoolInt32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyBoolInt32Map = sstr_MyBoolInt32Map.str();
			s->write(3, str_sstr_MyBoolInt32Map);
		}
		{
			std::stringstream sstr_MyBoolUint32Map;
			{
				std::map<bool, uint32_t>::const_iterator it = m_mapOfMyBoolUint32Map.begin();
				while (it != m_mapOfMyBoolUint32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyBoolUint32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyBoolUint32Map = sstr_MyBoolUint32Map.str();
			s->write(4, str_sstr_MyBoolUint32Map);
		}
		{
			std::stringstream sstr_MyBoolFloatMap;
			{
				std::map<bool, float>::const_iterator it = m_mapOfMyBoolFloatMap.begin();
				while (it != m_mapOfMyBoolFloatMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyBoolFloatMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyBoolFloatMap = sstr_MyBoolFloatMap.str();
			s->write(5, str_sstr_MyBoolFloatMap);
		}
		{
			std::stringstream sstr_MyBoolDoubleMap;
			{
				std::map<bool, double>::const_iterator it = m_mapOfMyBoolDoubleMap.begin();
				while (it != m_mapOfMyBoolDoubleMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyBoolDoubleMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyBoolDoubleMap = sstr_MyBoolDoubleMap.str();
			s->write(6, str_sstr_MyBoolDoubleMap);
		}
		{
			std::stringstream sstr_MyBoolStringMap;
			{
				std::map<bool, std::string>::const_iterator it = m_mapOfMyBoolStringMap.begin();
				while (it != m_mapOfMyBoolStringMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyBoolStringMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyBoolStringMap = sstr_MyBoolStringMap.str();
			s->write(7, str_sstr_MyBoolStringMap);
		}
		return out;
	}

	istream& Test11MapBool::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore elements from a string into MyBoolBoolMap.
		{
			// Clean up the existing map of MyBoolBoolMap.
			m_mapOfMyBoolBoolMap.clear();
		
			std::string str_MyBoolBoolMap;
			d->read(1, str_MyBoolBoolMap);
			if (str_MyBoolBoolMap.size() > 0) {
				std::stringstream sstr_str_MyBoolBoolMap(str_MyBoolBoolMap);
		
				// str_MyBoolBoolMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyBoolBoolMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyBoolBoolMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							bool key;
							bool value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyBoolBoolMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyBoolCharMap.
		{
			// Clean up the existing map of MyBoolCharMap.
			m_mapOfMyBoolCharMap.clear();
		
			std::string str_MyBoolCharMap;
			d->read(2, str_MyBoolCharMap);
			if (str_MyBoolCharMap.size() > 0) {
				std::stringstream sstr_str_MyBoolCharMap(str_MyBoolCharMap);
		
				// str_MyBoolCharMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyBoolCharMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyBoolCharMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							bool key;
							char value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyBoolCharMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyBoolInt32Map.
		{
			// Clean up the existing map of MyBoolInt32Map.
			m_mapOfMyBoolInt32Map.clear();
		
			std::string str_MyBoolInt32Map;
			d->read(3, str_MyBoolInt32Map);
			if (str_MyBoolInt32Map.size() > 0) {
				std::stringstream sstr_str_MyBoolInt32Map(str_MyBoolInt32Map);
		
				// str_MyBoolInt32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyBoolInt32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyBoolInt32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							bool key;
							int32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyBoolInt32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyBoolUint32Map.
		{
			// Clean up the existing map of MyBoolUint32Map.
			m_mapOfMyBoolUint32Map.clear();
		
			std::string str_MyBoolUint32Map;
			d->read(4, str_MyBoolUint32Map);
			if (str_MyBoolUint32Map.size() > 0) {
				std::stringstream sstr_str_MyBoolUint32Map(str_MyBoolUint32Map);
		
				// str_MyBoolUint32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyBoolUint32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyBoolUint32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							bool key;
							uint32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyBoolUint32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyBoolFloatMap.
		{
			// Clean up the existing map of MyBoolFloatMap.
			m_mapOfMyBoolFloatMap.clear();
		
			std::string str_MyBoolFloatMap;
			d->read(5, str_MyBoolFloatMap);
			if (str_MyBoolFloatMap.size() > 0) {
				std::stringstream sstr_str_MyBoolFloatMap(str_MyBoolFloatMap);
		
				// str_MyBoolFloatMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyBoolFloatMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyBoolFloatMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							bool key;
							float value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyBoolFloatMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyBoolDoubleMap.
		{
			// Clean up the existing map of MyBoolDoubleMap.
			m_mapOfMyBoolDoubleMap.clear();
		
			std::string str_MyBoolDoubleMap;
			d->read(6, str_MyBoolDoubleMap);
			if (str_MyBoolDoubleMap.size() > 0) {
				std::stringstream sstr_str_MyBoolDoubleMap(str_MyBoolDoubleMap);
		
				// str_MyBoolDoubleMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyBoolDoubleMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyBoolDoubleMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							bool key;
							double value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyBoolDoubleMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyBoolStringMap.
		{
			// Clean up the existing map of MyBoolStringMap.
			m_mapOfMyBoolStringMap.clear();
		
			std::string str_MyBoolStringMap;
			d->read(7, str_MyBoolStringMap);
			if (str_MyBoolStringMap.size() > 0) {
				std::stringstream sstr_str_MyBoolStringMap(str_MyBoolStringMap);
		
				// str_MyBoolStringMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyBoolStringMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyBoolStringMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							bool key;
							std::string value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyBoolStringMap(key, value);
						}
					}
				}
			}
		}
		return in;
	}
