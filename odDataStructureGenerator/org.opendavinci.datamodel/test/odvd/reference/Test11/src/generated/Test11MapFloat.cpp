/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */


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
		(void)v; // Avoid unused parameter warning.
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

		odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

		{
			// Write number of elements in m_mapOfMyFloatBoolMap.
			const uint32_t numberOfMyFloatBoolMap = static_cast<uint32_t>(m_mapOfMyFloatBoolMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyFloatBoolMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatBoolMap;
			std::map<float, bool>::const_iterator it = m_mapOfMyFloatBoolMap.begin();
			while (it != m_mapOfMyFloatBoolMap.end()) {
			    sstrOfMyFloatBoolMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatBoolMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyFloatBoolMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatCharMap.
			const uint32_t numberOfMyFloatCharMap = static_cast<uint32_t>(m_mapOfMyFloatCharMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyFloatCharMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatCharMap;
			std::map<float, char>::const_iterator it = m_mapOfMyFloatCharMap.begin();
			while (it != m_mapOfMyFloatCharMap.end()) {
			    sstrOfMyFloatCharMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatCharMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyFloatCharMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatInt32Map.
			const uint32_t numberOfMyFloatInt32Map = static_cast<uint32_t>(m_mapOfMyFloatInt32Map.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyFloatInt32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatInt32Map;
			std::map<float, int32_t>::const_iterator it = m_mapOfMyFloatInt32Map.begin();
			while (it != m_mapOfMyFloatInt32Map.end()) {
			    sstrOfMyFloatInt32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatInt32Map > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyFloatInt32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatUint32Map.
			const uint32_t numberOfMyFloatUint32Map = static_cast<uint32_t>(m_mapOfMyFloatUint32Map.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyFloatUint32Map);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatUint32Map;
			std::map<float, uint32_t>::const_iterator it = m_mapOfMyFloatUint32Map.begin();
			while (it != m_mapOfMyFloatUint32Map.end()) {
			    sstrOfMyFloatUint32Map << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatUint32Map > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyFloatUint32Map.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatFloatMap.
			const uint32_t numberOfMyFloatFloatMap = static_cast<uint32_t>(m_mapOfMyFloatFloatMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyFloatFloatMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatFloatMap;
			std::map<float, float>::const_iterator it = m_mapOfMyFloatFloatMap.begin();
			while (it != m_mapOfMyFloatFloatMap.end()) {
			    sstrOfMyFloatFloatMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatFloatMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyFloatFloatMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatDoubleMap.
			const uint32_t numberOfMyFloatDoubleMap = static_cast<uint32_t>(m_mapOfMyFloatDoubleMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyFloatDoubleMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatDoubleMap;
			std::map<float, double>::const_iterator it = m_mapOfMyFloatDoubleMap.begin();
			while (it != m_mapOfMyFloatDoubleMap.end()) {
			    sstrOfMyFloatDoubleMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatDoubleMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyFloatDoubleMap.str());
			}
		}
		{
			// Write number of elements in m_mapOfMyFloatStringMap.
			const uint32_t numberOfMyFloatStringMap = static_cast<uint32_t>(m_mapOfMyFloatStringMap.size());
			s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			        numberOfMyFloatStringMap);
		
			// Write actual elements into a stringstream.
			std::stringstream sstrOfMyFloatStringMap;
			std::map<float, std::string>::const_iterator it = m_mapOfMyFloatStringMap.begin();
			while (it != m_mapOfMyFloatStringMap.end()) {
			    sstrOfMyFloatStringMap << it->first << "=" << it->second << endl;
			    it++;
			}
			
			// Write string of elements.
			if (numberOfMyFloatStringMap > 0) {
				s->write(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
						sstrOfMyFloatStringMap.str());
			}
		}
		return out;
	}

	istream& Test11MapFloat::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing map of MyFloatBoolMap.
		m_mapOfMyFloatBoolMap.clear();
		
		// Read number of elements in m_mapOfMyFloatBoolMap.
		uint32_t numberOfMyFloatBoolMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyFloatBoolMap);
		
		if (numberOfMyFloatBoolMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    bool _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatBoolMap(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatCharMap.
		m_mapOfMyFloatCharMap.clear();
		
		// Read number of elements in m_mapOfMyFloatCharMap.
		uint32_t numberOfMyFloatCharMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyFloatCharMap);
		
		if (numberOfMyFloatCharMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > >  >::RESULT,
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    char _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatCharMap(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatInt32Map.
		m_mapOfMyFloatInt32Map.clear();
		
		// Read number of elements in m_mapOfMyFloatInt32Map.
		uint32_t numberOfMyFloatInt32Map = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyFloatInt32Map);
		
		if (numberOfMyFloatInt32Map > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    int32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatInt32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatUint32Map.
		m_mapOfMyFloatUint32Map.clear();
		
		// Read number of elements in m_mapOfMyFloatUint32Map.
		uint32_t numberOfMyFloatUint32Map = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyFloatUint32Map);
		
		if (numberOfMyFloatUint32Map > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    uint32_t _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatUint32Map(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatFloatMap.
		m_mapOfMyFloatFloatMap.clear();
		
		// Read number of elements in m_mapOfMyFloatFloatMap.
		uint32_t numberOfMyFloatFloatMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyFloatFloatMap);
		
		if (numberOfMyFloatFloatMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > >  >::RESULT,
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    float _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatFloatMap(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatDoubleMap.
		m_mapOfMyFloatDoubleMap.clear();
		
		// Read number of elements in m_mapOfMyFloatDoubleMap.
		uint32_t numberOfMyFloatDoubleMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyFloatDoubleMap);
		
		if (numberOfMyFloatDoubleMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    double _value;
		        sstrValue >> _value;
		
				// Store key/value pair.
				putTo_MapOfMyFloatDoubleMap(_key, _value);
			}
		}
		// Clean up the existing map of MyFloatStringMap.
		m_mapOfMyFloatStringMap.clear();
		
		// Read number of elements in m_mapOfMyFloatStringMap.
		uint32_t numberOfMyFloatStringMap = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > > > > > > > > > >  >::RESULT,
			   numberOfMyFloatStringMap);
		
		if (numberOfMyFloatStringMap > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'M', CharList<'a', CharList<'p', NullType> > > > > > > > > > > > > > > >  >::RESULT,
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
			    float _key;
		        sstrKey >> _key;
		
			    stringstream sstrValue(value);
			    std::string _value;
		        getline(sstrValue, _value);
		
				// Store key/value pair.
				putTo_MapOfMyFloatStringMap(_key, _value);
			}
		}
		return in;
	}
