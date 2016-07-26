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
			std::stringstream sstr_MyUint32BoolMap;
			{
				std::map<uint32_t, bool>::const_iterator it = m_mapOfMyUint32BoolMap.begin();
				while (it != m_mapOfMyUint32BoolMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyUint32BoolMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyUint32BoolMap = sstr_MyUint32BoolMap.str();
			s->write(1, str_sstr_MyUint32BoolMap);
		}
		{
			std::stringstream sstr_MyUint32CharMap;
			{
				std::map<uint32_t, char>::const_iterator it = m_mapOfMyUint32CharMap.begin();
				while (it != m_mapOfMyUint32CharMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyUint32CharMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyUint32CharMap = sstr_MyUint32CharMap.str();
			s->write(2, str_sstr_MyUint32CharMap);
		}
		{
			std::stringstream sstr_MyUint32Int32Map;
			{
				std::map<uint32_t, int32_t>::const_iterator it = m_mapOfMyUint32Int32Map.begin();
				while (it != m_mapOfMyUint32Int32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyUint32Int32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyUint32Int32Map = sstr_MyUint32Int32Map.str();
			s->write(3, str_sstr_MyUint32Int32Map);
		}
		{
			std::stringstream sstr_MyUint32Uint32Map;
			{
				std::map<uint32_t, uint32_t>::const_iterator it = m_mapOfMyUint32Uint32Map.begin();
				while (it != m_mapOfMyUint32Uint32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyUint32Uint32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyUint32Uint32Map = sstr_MyUint32Uint32Map.str();
			s->write(4, str_sstr_MyUint32Uint32Map);
		}
		{
			std::stringstream sstr_MyUint32FloatMap;
			{
				std::map<uint32_t, float>::const_iterator it = m_mapOfMyUint32FloatMap.begin();
				while (it != m_mapOfMyUint32FloatMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyUint32FloatMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyUint32FloatMap = sstr_MyUint32FloatMap.str();
			s->write(5, str_sstr_MyUint32FloatMap);
		}
		{
			std::stringstream sstr_MyUint32DoubleMap;
			{
				std::map<uint32_t, double>::const_iterator it = m_mapOfMyUint32DoubleMap.begin();
				while (it != m_mapOfMyUint32DoubleMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyUint32DoubleMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyUint32DoubleMap = sstr_MyUint32DoubleMap.str();
			s->write(6, str_sstr_MyUint32DoubleMap);
		}
		{
			std::stringstream sstr_MyUint32StringMap;
			{
				std::map<uint32_t, std::string>::const_iterator it = m_mapOfMyUint32StringMap.begin();
				while (it != m_mapOfMyUint32StringMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyUint32StringMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyUint32StringMap = sstr_MyUint32StringMap.str();
			s->write(7, str_sstr_MyUint32StringMap);
		}
		return out;
	}

	istream& Test12MapUint32::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore elements from a string into MyUint32BoolMap.
		{
			// Clean up the existing map of MyUint32BoolMap.
			m_mapOfMyUint32BoolMap.clear();
		
			std::string str_MyUint32BoolMap;
			d->read(1, str_MyUint32BoolMap);
			if (str_MyUint32BoolMap.size() > 0) {
				std::stringstream sstr_str_MyUint32BoolMap(str_MyUint32BoolMap);
		
				// str_MyUint32BoolMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyUint32BoolMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyUint32BoolMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							uint32_t key;
							bool value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyUint32BoolMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyUint32CharMap.
		{
			// Clean up the existing map of MyUint32CharMap.
			m_mapOfMyUint32CharMap.clear();
		
			std::string str_MyUint32CharMap;
			d->read(2, str_MyUint32CharMap);
			if (str_MyUint32CharMap.size() > 0) {
				std::stringstream sstr_str_MyUint32CharMap(str_MyUint32CharMap);
		
				// str_MyUint32CharMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyUint32CharMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyUint32CharMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							uint32_t key;
							char value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyUint32CharMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyUint32Int32Map.
		{
			// Clean up the existing map of MyUint32Int32Map.
			m_mapOfMyUint32Int32Map.clear();
		
			std::string str_MyUint32Int32Map;
			d->read(3, str_MyUint32Int32Map);
			if (str_MyUint32Int32Map.size() > 0) {
				std::stringstream sstr_str_MyUint32Int32Map(str_MyUint32Int32Map);
		
				// str_MyUint32Int32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyUint32Int32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyUint32Int32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							uint32_t key;
							int32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyUint32Int32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyUint32Uint32Map.
		{
			// Clean up the existing map of MyUint32Uint32Map.
			m_mapOfMyUint32Uint32Map.clear();
		
			std::string str_MyUint32Uint32Map;
			d->read(4, str_MyUint32Uint32Map);
			if (str_MyUint32Uint32Map.size() > 0) {
				std::stringstream sstr_str_MyUint32Uint32Map(str_MyUint32Uint32Map);
		
				// str_MyUint32Uint32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyUint32Uint32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyUint32Uint32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							uint32_t key;
							uint32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyUint32Uint32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyUint32FloatMap.
		{
			// Clean up the existing map of MyUint32FloatMap.
			m_mapOfMyUint32FloatMap.clear();
		
			std::string str_MyUint32FloatMap;
			d->read(5, str_MyUint32FloatMap);
			if (str_MyUint32FloatMap.size() > 0) {
				std::stringstream sstr_str_MyUint32FloatMap(str_MyUint32FloatMap);
		
				// str_MyUint32FloatMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyUint32FloatMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyUint32FloatMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							uint32_t key;
							float value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyUint32FloatMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyUint32DoubleMap.
		{
			// Clean up the existing map of MyUint32DoubleMap.
			m_mapOfMyUint32DoubleMap.clear();
		
			std::string str_MyUint32DoubleMap;
			d->read(6, str_MyUint32DoubleMap);
			if (str_MyUint32DoubleMap.size() > 0) {
				std::stringstream sstr_str_MyUint32DoubleMap(str_MyUint32DoubleMap);
		
				// str_MyUint32DoubleMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyUint32DoubleMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyUint32DoubleMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							uint32_t key;
							double value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyUint32DoubleMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyUint32StringMap.
		{
			// Clean up the existing map of MyUint32StringMap.
			m_mapOfMyUint32StringMap.clear();
		
			std::string str_MyUint32StringMap;
			d->read(7, str_MyUint32StringMap);
			if (str_MyUint32StringMap.size() > 0) {
				std::stringstream sstr_str_MyUint32StringMap(str_MyUint32StringMap);
		
				// str_MyUint32StringMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyUint32StringMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyUint32StringMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							uint32_t key;
							std::string value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyUint32StringMap(key, value);
						}
					}
				}
			}
		}
		return in;
	}
