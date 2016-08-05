/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <memory>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"

#include "test11/generated/Test11MapDouble.h"

	using namespace std;
	using namespace odcore::base;


	Test11MapDouble::Test11MapDouble() :
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

	Test11MapDouble::Test11MapDouble(
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

	Test11MapDouble::Test11MapDouble(const Test11MapDouble &obj) :
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
	
	Test11MapDouble::~Test11MapDouble() {
	}

	Test11MapDouble& Test11MapDouble::operator=(const Test11MapDouble &obj) {
		m_mapOfMyDoubleBoolMap = obj.m_mapOfMyDoubleBoolMap;
		m_mapOfMyDoubleCharMap = obj.m_mapOfMyDoubleCharMap;
		m_mapOfMyDoubleInt32Map = obj.m_mapOfMyDoubleInt32Map;
		m_mapOfMyDoubleUint32Map = obj.m_mapOfMyDoubleUint32Map;
		m_mapOfMyDoubleFloatMap = obj.m_mapOfMyDoubleFloatMap;
		m_mapOfMyDoubleDoubleMap = obj.m_mapOfMyDoubleDoubleMap;
		m_mapOfMyDoubleStringMap = obj.m_mapOfMyDoubleStringMap;
		return (*this);
	}

	int32_t Test11MapDouble::ID() {
		return 18;
	}

	const string Test11MapDouble::ShortName() {
		return "Test11MapDouble";
	}

	const string Test11MapDouble::LongName() {
		return "Test11MapDouble";
	}

	int32_t Test11MapDouble::getID() const {
		return Test11MapDouble::ID();
	}

	const string Test11MapDouble::getShortName() const {
		return Test11MapDouble::ShortName();
	}

	const string Test11MapDouble::getLongName() const {
		return Test11MapDouble::LongName();
	}

	std::map<double, bool> Test11MapDouble::getMapOfMyDoubleBoolMap() const {
		return m_mapOfMyDoubleBoolMap;
	}
	
	void Test11MapDouble::setMapOfMyDoubleBoolMap(const std::map<double, bool> &val) {
		m_mapOfMyDoubleBoolMap = val;
	}
	
	void Test11MapDouble::clear_MapOfMyDoubleBoolMap() {
		m_mapOfMyDoubleBoolMap.clear();
	}
	
	uint32_t Test11MapDouble::getSize_MapOfMyDoubleBoolMap() const {
		return m_mapOfMyDoubleBoolMap.size();
	}
	
	bool Test11MapDouble::isEmpty_MapOfMyDoubleBoolMap() const {
		return m_mapOfMyDoubleBoolMap.empty();
	}
	
	void Test11MapDouble::putTo_MapOfMyDoubleBoolMap(const double &key, const bool &val) {
		m_mapOfMyDoubleBoolMap[key] = val;
	}
	
	bool Test11MapDouble::containsKey_MapOfMyDoubleBoolMap(const double &key) const {
		return (m_mapOfMyDoubleBoolMap.count(key) > 0);
	}
	
	bool Test11MapDouble::getValueForKey_MapOfMyDoubleBoolMap(const double &key) {
		return m_mapOfMyDoubleBoolMap[key];
	}
	
	std::pair<std::map<double, bool>::iterator, std::map<double, bool>::iterator> Test11MapDouble::iteratorPair_MapOfMyDoubleBoolMap() {
		return std::make_pair(m_mapOfMyDoubleBoolMap.begin(), m_mapOfMyDoubleBoolMap.end());
	}
	std::map<double, char> Test11MapDouble::getMapOfMyDoubleCharMap() const {
		return m_mapOfMyDoubleCharMap;
	}
	
	void Test11MapDouble::setMapOfMyDoubleCharMap(const std::map<double, char> &val) {
		m_mapOfMyDoubleCharMap = val;
	}
	
	void Test11MapDouble::clear_MapOfMyDoubleCharMap() {
		m_mapOfMyDoubleCharMap.clear();
	}
	
	uint32_t Test11MapDouble::getSize_MapOfMyDoubleCharMap() const {
		return m_mapOfMyDoubleCharMap.size();
	}
	
	bool Test11MapDouble::isEmpty_MapOfMyDoubleCharMap() const {
		return m_mapOfMyDoubleCharMap.empty();
	}
	
	void Test11MapDouble::putTo_MapOfMyDoubleCharMap(const double &key, const char &val) {
		m_mapOfMyDoubleCharMap[key] = val;
	}
	
	bool Test11MapDouble::containsKey_MapOfMyDoubleCharMap(const double &key) const {
		return (m_mapOfMyDoubleCharMap.count(key) > 0);
	}
	
	char Test11MapDouble::getValueForKey_MapOfMyDoubleCharMap(const double &key) {
		return m_mapOfMyDoubleCharMap[key];
	}
	
	std::pair<std::map<double, char>::iterator, std::map<double, char>::iterator> Test11MapDouble::iteratorPair_MapOfMyDoubleCharMap() {
		return std::make_pair(m_mapOfMyDoubleCharMap.begin(), m_mapOfMyDoubleCharMap.end());
	}
	std::map<double, int32_t> Test11MapDouble::getMapOfMyDoubleInt32Map() const {
		return m_mapOfMyDoubleInt32Map;
	}
	
	void Test11MapDouble::setMapOfMyDoubleInt32Map(const std::map<double, int32_t> &val) {
		m_mapOfMyDoubleInt32Map = val;
	}
	
	void Test11MapDouble::clear_MapOfMyDoubleInt32Map() {
		m_mapOfMyDoubleInt32Map.clear();
	}
	
	uint32_t Test11MapDouble::getSize_MapOfMyDoubleInt32Map() const {
		return m_mapOfMyDoubleInt32Map.size();
	}
	
	bool Test11MapDouble::isEmpty_MapOfMyDoubleInt32Map() const {
		return m_mapOfMyDoubleInt32Map.empty();
	}
	
	void Test11MapDouble::putTo_MapOfMyDoubleInt32Map(const double &key, const int32_t &val) {
		m_mapOfMyDoubleInt32Map[key] = val;
	}
	
	bool Test11MapDouble::containsKey_MapOfMyDoubleInt32Map(const double &key) const {
		return (m_mapOfMyDoubleInt32Map.count(key) > 0);
	}
	
	int32_t Test11MapDouble::getValueForKey_MapOfMyDoubleInt32Map(const double &key) {
		return m_mapOfMyDoubleInt32Map[key];
	}
	
	std::pair<std::map<double, int32_t>::iterator, std::map<double, int32_t>::iterator> Test11MapDouble::iteratorPair_MapOfMyDoubleInt32Map() {
		return std::make_pair(m_mapOfMyDoubleInt32Map.begin(), m_mapOfMyDoubleInt32Map.end());
	}
	std::map<double, uint32_t> Test11MapDouble::getMapOfMyDoubleUint32Map() const {
		return m_mapOfMyDoubleUint32Map;
	}
	
	void Test11MapDouble::setMapOfMyDoubleUint32Map(const std::map<double, uint32_t> &val) {
		m_mapOfMyDoubleUint32Map = val;
	}
	
	void Test11MapDouble::clear_MapOfMyDoubleUint32Map() {
		m_mapOfMyDoubleUint32Map.clear();
	}
	
	uint32_t Test11MapDouble::getSize_MapOfMyDoubleUint32Map() const {
		return m_mapOfMyDoubleUint32Map.size();
	}
	
	bool Test11MapDouble::isEmpty_MapOfMyDoubleUint32Map() const {
		return m_mapOfMyDoubleUint32Map.empty();
	}
	
	void Test11MapDouble::putTo_MapOfMyDoubleUint32Map(const double &key, const uint32_t &val) {
		m_mapOfMyDoubleUint32Map[key] = val;
	}
	
	bool Test11MapDouble::containsKey_MapOfMyDoubleUint32Map(const double &key) const {
		return (m_mapOfMyDoubleUint32Map.count(key) > 0);
	}
	
	uint32_t Test11MapDouble::getValueForKey_MapOfMyDoubleUint32Map(const double &key) {
		return m_mapOfMyDoubleUint32Map[key];
	}
	
	std::pair<std::map<double, uint32_t>::iterator, std::map<double, uint32_t>::iterator> Test11MapDouble::iteratorPair_MapOfMyDoubleUint32Map() {
		return std::make_pair(m_mapOfMyDoubleUint32Map.begin(), m_mapOfMyDoubleUint32Map.end());
	}
	std::map<double, float> Test11MapDouble::getMapOfMyDoubleFloatMap() const {
		return m_mapOfMyDoubleFloatMap;
	}
	
	void Test11MapDouble::setMapOfMyDoubleFloatMap(const std::map<double, float> &val) {
		m_mapOfMyDoubleFloatMap = val;
	}
	
	void Test11MapDouble::clear_MapOfMyDoubleFloatMap() {
		m_mapOfMyDoubleFloatMap.clear();
	}
	
	uint32_t Test11MapDouble::getSize_MapOfMyDoubleFloatMap() const {
		return m_mapOfMyDoubleFloatMap.size();
	}
	
	bool Test11MapDouble::isEmpty_MapOfMyDoubleFloatMap() const {
		return m_mapOfMyDoubleFloatMap.empty();
	}
	
	void Test11MapDouble::putTo_MapOfMyDoubleFloatMap(const double &key, const float &val) {
		m_mapOfMyDoubleFloatMap[key] = val;
	}
	
	bool Test11MapDouble::containsKey_MapOfMyDoubleFloatMap(const double &key) const {
		return (m_mapOfMyDoubleFloatMap.count(key) > 0);
	}
	
	float Test11MapDouble::getValueForKey_MapOfMyDoubleFloatMap(const double &key) {
		return m_mapOfMyDoubleFloatMap[key];
	}
	
	std::pair<std::map<double, float>::iterator, std::map<double, float>::iterator> Test11MapDouble::iteratorPair_MapOfMyDoubleFloatMap() {
		return std::make_pair(m_mapOfMyDoubleFloatMap.begin(), m_mapOfMyDoubleFloatMap.end());
	}
	std::map<double, double> Test11MapDouble::getMapOfMyDoubleDoubleMap() const {
		return m_mapOfMyDoubleDoubleMap;
	}
	
	void Test11MapDouble::setMapOfMyDoubleDoubleMap(const std::map<double, double> &val) {
		m_mapOfMyDoubleDoubleMap = val;
	}
	
	void Test11MapDouble::clear_MapOfMyDoubleDoubleMap() {
		m_mapOfMyDoubleDoubleMap.clear();
	}
	
	uint32_t Test11MapDouble::getSize_MapOfMyDoubleDoubleMap() const {
		return m_mapOfMyDoubleDoubleMap.size();
	}
	
	bool Test11MapDouble::isEmpty_MapOfMyDoubleDoubleMap() const {
		return m_mapOfMyDoubleDoubleMap.empty();
	}
	
	void Test11MapDouble::putTo_MapOfMyDoubleDoubleMap(const double &key, const double &val) {
		m_mapOfMyDoubleDoubleMap[key] = val;
	}
	
	bool Test11MapDouble::containsKey_MapOfMyDoubleDoubleMap(const double &key) const {
		return (m_mapOfMyDoubleDoubleMap.count(key) > 0);
	}
	
	double Test11MapDouble::getValueForKey_MapOfMyDoubleDoubleMap(const double &key) {
		return m_mapOfMyDoubleDoubleMap[key];
	}
	
	std::pair<std::map<double, double>::iterator, std::map<double, double>::iterator> Test11MapDouble::iteratorPair_MapOfMyDoubleDoubleMap() {
		return std::make_pair(m_mapOfMyDoubleDoubleMap.begin(), m_mapOfMyDoubleDoubleMap.end());
	}
	std::map<double, std::string> Test11MapDouble::getMapOfMyDoubleStringMap() const {
		return m_mapOfMyDoubleStringMap;
	}
	
	void Test11MapDouble::setMapOfMyDoubleStringMap(const std::map<double, std::string> &val) {
		m_mapOfMyDoubleStringMap = val;
	}
	
	void Test11MapDouble::clear_MapOfMyDoubleStringMap() {
		m_mapOfMyDoubleStringMap.clear();
	}
	
	uint32_t Test11MapDouble::getSize_MapOfMyDoubleStringMap() const {
		return m_mapOfMyDoubleStringMap.size();
	}
	
	bool Test11MapDouble::isEmpty_MapOfMyDoubleStringMap() const {
		return m_mapOfMyDoubleStringMap.empty();
	}
	
	void Test11MapDouble::putTo_MapOfMyDoubleStringMap(const double &key, const std::string &val) {
		m_mapOfMyDoubleStringMap[key] = val;
	}
	
	bool Test11MapDouble::containsKey_MapOfMyDoubleStringMap(const double &key) const {
		return (m_mapOfMyDoubleStringMap.count(key) > 0);
	}
	
	std::string Test11MapDouble::getValueForKey_MapOfMyDoubleStringMap(const double &key) {
		return m_mapOfMyDoubleStringMap[key];
	}
	
	std::pair<std::map<double, std::string>::iterator, std::map<double, std::string>::iterator> Test11MapDouble::iteratorPair_MapOfMyDoubleStringMap() {
		return std::make_pair(m_mapOfMyDoubleStringMap.begin(), m_mapOfMyDoubleStringMap.end());
	}

	void Test11MapDouble::accept(odcore::base::Visitor &v) {
		v.beginVisit();
		v.endVisit();
	}

	const string Test11MapDouble::toString() const {
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

	ostream& Test11MapDouble::operator<<(ostream &out) const {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Serializer> s = sf.getSerializer(out);

		{
			std::stringstream sstr_MyDoubleBoolMap;
			{
				std::map<double, bool>::const_iterator it = m_mapOfMyDoubleBoolMap.begin();
				while (it != m_mapOfMyDoubleBoolMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyDoubleBoolMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyDoubleBoolMap = sstr_MyDoubleBoolMap.str();
			s->write(1, str_sstr_MyDoubleBoolMap);
		}
		{
			std::stringstream sstr_MyDoubleCharMap;
			{
				std::map<double, char>::const_iterator it = m_mapOfMyDoubleCharMap.begin();
				while (it != m_mapOfMyDoubleCharMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyDoubleCharMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyDoubleCharMap = sstr_MyDoubleCharMap.str();
			s->write(2, str_sstr_MyDoubleCharMap);
		}
		{
			std::stringstream sstr_MyDoubleInt32Map;
			{
				std::map<double, int32_t>::const_iterator it = m_mapOfMyDoubleInt32Map.begin();
				while (it != m_mapOfMyDoubleInt32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyDoubleInt32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyDoubleInt32Map = sstr_MyDoubleInt32Map.str();
			s->write(3, str_sstr_MyDoubleInt32Map);
		}
		{
			std::stringstream sstr_MyDoubleUint32Map;
			{
				std::map<double, uint32_t>::const_iterator it = m_mapOfMyDoubleUint32Map.begin();
				while (it != m_mapOfMyDoubleUint32Map.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyDoubleUint32Map, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyDoubleUint32Map = sstr_MyDoubleUint32Map.str();
			s->write(4, str_sstr_MyDoubleUint32Map);
		}
		{
			std::stringstream sstr_MyDoubleFloatMap;
			{
				std::map<double, float>::const_iterator it = m_mapOfMyDoubleFloatMap.begin();
				while (it != m_mapOfMyDoubleFloatMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyDoubleFloatMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyDoubleFloatMap = sstr_MyDoubleFloatMap.str();
			s->write(5, str_sstr_MyDoubleFloatMap);
		}
		{
			std::stringstream sstr_MyDoubleDoubleMap;
			{
				std::map<double, double>::const_iterator it = m_mapOfMyDoubleDoubleMap.begin();
				while (it != m_mapOfMyDoubleDoubleMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyDoubleDoubleMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyDoubleDoubleMap = sstr_MyDoubleDoubleMap.str();
			s->write(6, str_sstr_MyDoubleDoubleMap);
		}
		{
			std::stringstream sstr_MyDoubleStringMap;
			{
				std::map<double, std::string>::const_iterator it = m_mapOfMyDoubleStringMap.begin();
				while (it != m_mapOfMyDoubleStringMap.end()) {
					// Write key/value into a joint string.
					std::stringstream sstr_keyValueEntry;
					{
						std::shared_ptr<Serializer> keyValueSerializer = sf.getSerializer(sstr_keyValueEntry);
						keyValueSerializer->write(1, it->first);  // Write key as field 1 from a "virtual" class.
						keyValueSerializer->write(2, it->second); // Write value as field 2 from a "virtual" class.
					}
		
					// Write string into super-stringstream.
					const string str_sstr_keyValueEntry = sstr_keyValueEntry.str();
					s->writeValue(sstr_MyDoubleStringMap, str_sstr_keyValueEntry);
		
					// Process next entry.
					it++;
				}
			}
			const std::string str_sstr_MyDoubleStringMap = sstr_MyDoubleStringMap.str();
			s->write(7, str_sstr_MyDoubleStringMap);
		}
		return out;
	}

	istream& Test11MapDouble::operator>>(istream &in) {
		SerializationFactory& sf = SerializationFactory::getInstance();

		std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

		// Restore elements from a string into MyDoubleBoolMap.
		{
			// Clean up the existing map of MyDoubleBoolMap.
			m_mapOfMyDoubleBoolMap.clear();
		
			std::string str_MyDoubleBoolMap;
			d->read(1, str_MyDoubleBoolMap);
			if (str_MyDoubleBoolMap.size() > 0) {
				std::stringstream sstr_str_MyDoubleBoolMap(str_MyDoubleBoolMap);
		
				// str_MyDoubleBoolMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyDoubleBoolMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyDoubleBoolMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							double key;
							bool value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyDoubleBoolMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyDoubleCharMap.
		{
			// Clean up the existing map of MyDoubleCharMap.
			m_mapOfMyDoubleCharMap.clear();
		
			std::string str_MyDoubleCharMap;
			d->read(2, str_MyDoubleCharMap);
			if (str_MyDoubleCharMap.size() > 0) {
				std::stringstream sstr_str_MyDoubleCharMap(str_MyDoubleCharMap);
		
				// str_MyDoubleCharMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyDoubleCharMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyDoubleCharMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							double key;
							char value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyDoubleCharMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyDoubleInt32Map.
		{
			// Clean up the existing map of MyDoubleInt32Map.
			m_mapOfMyDoubleInt32Map.clear();
		
			std::string str_MyDoubleInt32Map;
			d->read(3, str_MyDoubleInt32Map);
			if (str_MyDoubleInt32Map.size() > 0) {
				std::stringstream sstr_str_MyDoubleInt32Map(str_MyDoubleInt32Map);
		
				// str_MyDoubleInt32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyDoubleInt32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyDoubleInt32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							double key;
							int32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyDoubleInt32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyDoubleUint32Map.
		{
			// Clean up the existing map of MyDoubleUint32Map.
			m_mapOfMyDoubleUint32Map.clear();
		
			std::string str_MyDoubleUint32Map;
			d->read(4, str_MyDoubleUint32Map);
			if (str_MyDoubleUint32Map.size() > 0) {
				std::stringstream sstr_str_MyDoubleUint32Map(str_MyDoubleUint32Map);
		
				// str_MyDoubleUint32Map contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyDoubleUint32Map.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyDoubleUint32Map, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							double key;
							uint32_t value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyDoubleUint32Map(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyDoubleFloatMap.
		{
			// Clean up the existing map of MyDoubleFloatMap.
			m_mapOfMyDoubleFloatMap.clear();
		
			std::string str_MyDoubleFloatMap;
			d->read(5, str_MyDoubleFloatMap);
			if (str_MyDoubleFloatMap.size() > 0) {
				std::stringstream sstr_str_MyDoubleFloatMap(str_MyDoubleFloatMap);
		
				// str_MyDoubleFloatMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyDoubleFloatMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyDoubleFloatMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							double key;
							float value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyDoubleFloatMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyDoubleDoubleMap.
		{
			// Clean up the existing map of MyDoubleDoubleMap.
			m_mapOfMyDoubleDoubleMap.clear();
		
			std::string str_MyDoubleDoubleMap;
			d->read(6, str_MyDoubleDoubleMap);
			if (str_MyDoubleDoubleMap.size() > 0) {
				std::stringstream sstr_str_MyDoubleDoubleMap(str_MyDoubleDoubleMap);
		
				// str_MyDoubleDoubleMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyDoubleDoubleMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyDoubleDoubleMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							double key;
							double value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyDoubleDoubleMap(key, value);
						}
					}
				}
			}
		}
		// Restore elements from a string into MyDoubleStringMap.
		{
			// Clean up the existing map of MyDoubleStringMap.
			m_mapOfMyDoubleStringMap.clear();
		
			std::string str_MyDoubleStringMap;
			d->read(7, str_MyDoubleStringMap);
			if (str_MyDoubleStringMap.size() > 0) {
				std::stringstream sstr_str_MyDoubleStringMap(str_MyDoubleStringMap);
		
				// str_MyDoubleStringMap contains a sequence of strings containing pairs of key/values.
				uint32_t length = str_MyDoubleStringMap.size();
				while (length > 0) {
					std::string str_sstr_keyValue;
					length -= d->readValue(sstr_str_MyDoubleStringMap, str_sstr_keyValue);
		
					if (str_sstr_keyValue.size() > 0) {
						// We have in str_sstr_keyValue a string at hand containing a pair key/value.
						// Now, we restore the key and value therefrom.
						std::stringstream sstr_keyValueEntry(str_sstr_keyValue);
		
						{
							std::shared_ptr<Deserializer> keyValueDeserializer = sf.getDeserializer(sstr_keyValueEntry);
							double key;
							std::string value;
							keyValueDeserializer->read(1, key);
							keyValueDeserializer->read(2, value);
							// Store key/value pair in the map.
							putTo_MapOfMyDoubleStringMap(key, value);
						}
					}
				}
			}
		}
		return in;
	}
