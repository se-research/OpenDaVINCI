/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


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
		(void)v; // Avoid unused parameter warning.
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

		odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

		{
			// Write number of elements in m_mapOfMyCharBoolMap.
			const uint32_t numberOfMyCharBoolMap = static_cast<uint32_t>(m_mapOfMyCharBoolMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyCharBoolMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyCharBoolMap;
			std::map<char, bool>::const_iterator it = m_mapOfMyCharBoolMap.begin();
			while (it != m_mapOfMyCharBoolMap.end()) {
			    sstrOfMyCharBoolMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyCharBoolMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > >  >::RESULT,
						sstrOfMyCharBoolMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyCharCharMap.
			const uint32_t numberOfMyCharCharMap = static_cast<uint32_t>(m_mapOfMyCharCharMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyCharCharMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyCharCharMap;
			std::map<char, char>::const_iterator it = m_mapOfMyCharCharMap.begin();
			while (it != m_mapOfMyCharCharMap.end()) {
			    sstrOfMyCharCharMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyCharCharMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > >  >::RESULT,
						sstrOfMyCharCharMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyCharInt32Map.
			const uint32_t numberOfMyCharInt32Map = static_cast<uint32_t>(m_mapOfMyCharInt32Map.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyCharInt32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyCharInt32Map;
			std::map<char, int32_t>::const_iterator it = m_mapOfMyCharInt32Map.begin();
			while (it != m_mapOfMyCharInt32Map.end()) {
			    sstrOfMyCharInt32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyCharInt32Map > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyCharInt32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyCharUint32Map.
			const uint32_t numberOfMyCharUint32Map = static_cast<uint32_t>(m_mapOfMyCharUint32Map.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyCharUint32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyCharUint32Map;
			std::map<char, uint32_t>::const_iterator it = m_mapOfMyCharUint32Map.begin();
			while (it != m_mapOfMyCharUint32Map.end()) {
			    sstrOfMyCharUint32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyCharUint32Map > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyCharUint32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyCharFloatMap.
			const uint32_t numberOfMyCharFloatMap = static_cast<uint32_t>(m_mapOfMyCharFloatMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyCharFloatMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyCharFloatMap;
			std::map<char, float>::const_iterator it = m_mapOfMyCharFloatMap.begin();
			while (it != m_mapOfMyCharFloatMap.end()) {
			    sstrOfMyCharFloatMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyCharFloatMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyCharFloatMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyCharDoubleMap.
			const uint32_t numberOfMyCharDoubleMap = static_cast<uint32_t>(m_mapOfMyCharDoubleMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyCharDoubleMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyCharDoubleMap;
			std::map<char, double>::const_iterator it = m_mapOfMyCharDoubleMap.begin();
			while (it != m_mapOfMyCharDoubleMap.end()) {
			    sstrOfMyCharDoubleMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyCharDoubleMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyCharDoubleMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyCharStringMap.
			const uint32_t numberOfMyCharStringMap = static_cast<uint32_t>(m_mapOfMyCharStringMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyCharStringMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyCharStringMap;
			std::map<char, std::string>::const_iterator it = m_mapOfMyCharStringMap.begin();
			while (it != m_mapOfMyCharStringMap.end()) {
			    sstrOfMyCharStringMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyCharStringMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyCharStringMap.str());
			}
		}
		return out;
	}

	istream& Test11MapChar::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing map of MyCharBoolMap.
		m_mapOfMyCharBoolMap.clear();
		
		// Read number of elements in m_mapOfMyCharBoolMap.
		uint32_t numberOfMyCharBoolMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyCharBoolMap);
		
		if (numberOfMyCharBoolMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > >  >::RESULT,
			       elements);
		
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
			    char _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    bool _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyCharBoolMap(_key, _value);
			}
		}
		// Clean up the existing map of MyCharCharMap.
		m_mapOfMyCharCharMap.clear();
		
		// Read number of elements in m_mapOfMyCharCharMap.
		uint32_t numberOfMyCharCharMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyCharCharMap);
		
		if (numberOfMyCharCharMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > >  >::RESULT,
			       elements);
		
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
			    char _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    char _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyCharCharMap(_key, _value);
			}
		}
		// Clean up the existing map of MyCharInt32Map.
		m_mapOfMyCharInt32Map.clear();
		
		// Read number of elements in m_mapOfMyCharInt32Map.
		uint32_t numberOfMyCharInt32Map = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyCharInt32Map);
		
		if (numberOfMyCharInt32Map > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
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
			    char _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    int32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyCharInt32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyCharUint32Map.
		m_mapOfMyCharUint32Map.clear();
		
		// Read number of elements in m_mapOfMyCharUint32Map.
		uint32_t numberOfMyCharUint32Map = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyCharUint32Map);
		
		if (numberOfMyCharUint32Map > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
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
			    char _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    uint32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyCharUint32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyCharFloatMap.
		m_mapOfMyCharFloatMap.clear();
		
		// Read number of elements in m_mapOfMyCharFloatMap.
		uint32_t numberOfMyCharFloatMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyCharFloatMap);
		
		if (numberOfMyCharFloatMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
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
			    char _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    float _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyCharFloatMap(_key, _value);
			}
		}
		// Clean up the existing map of MyCharDoubleMap.
		m_mapOfMyCharDoubleMap.clear();
		
		// Read number of elements in m_mapOfMyCharDoubleMap.
		uint32_t numberOfMyCharDoubleMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyCharDoubleMap);
		
		if (numberOfMyCharDoubleMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
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
			    char _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    double _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyCharDoubleMap(_key, _value);
			}
		}
		// Clean up the existing map of MyCharStringMap.
		m_mapOfMyCharStringMap.clear();
		
		// Read number of elements in m_mapOfMyCharStringMap.
		uint32_t numberOfMyCharStringMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyCharStringMap);
		
		if (numberOfMyCharStringMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
			       elements);
		
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
			    char _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    std::string _value;
		        getline(sstrValue, _value);
		
				// Store key/value pair.
				putTo_MapOfMyCharStringMap(_key, _value);
			}
		}
		return in;
	}
