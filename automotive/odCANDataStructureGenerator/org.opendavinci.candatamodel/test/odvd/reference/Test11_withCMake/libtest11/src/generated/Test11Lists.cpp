/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#include <algorithm>
#include <sstream>
#include <utility>

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"


#include "generated/Test11Lists.h"

	using namespace std;
	using namespace core::base;


	Test11Lists::Test11Lists() :
	    SerializableData(), Visitable()
		, m_listOfMyBoolList()
		, m_listOfMyCharList()
		, m_listOfMyInt32List()
		, m_listOfMyUint32List()
		, m_listOfMyFloatList()
		, m_listOfMyDoubleList()
		, m_listOfMyStringList()
	{
	}

	Test11Lists::Test11Lists(
		const vector<bool> &val0, 
		const vector<char> &val1, 
		const vector<int32_t> &val2, 
		const vector<uint32_t> &val3, 
		const vector<float> &val4, 
		const vector<double> &val5, 
		const vector<std::string> &val6
	) :
	    SerializableData(), Visitable()
		, m_listOfMyBoolList(val0)
		, m_listOfMyCharList(val1)
		, m_listOfMyInt32List(val2)
		, m_listOfMyUint32List(val3)
		, m_listOfMyFloatList(val4)
		, m_listOfMyDoubleList(val5)
		, m_listOfMyStringList(val6)
	{
	}

	Test11Lists::Test11Lists(const Test11Lists &obj) :
	    SerializableData(), Visitable()
		, m_listOfMyBoolList(obj.m_listOfMyBoolList)
		, m_listOfMyCharList(obj.m_listOfMyCharList)
		, m_listOfMyInt32List(obj.m_listOfMyInt32List)
		, m_listOfMyUint32List(obj.m_listOfMyUint32List)
		, m_listOfMyFloatList(obj.m_listOfMyFloatList)
		, m_listOfMyDoubleList(obj.m_listOfMyDoubleList)
		, m_listOfMyStringList(obj.m_listOfMyStringList)
	{
	}
	
	Test11Lists::~Test11Lists() {
	}

	Test11Lists& Test11Lists::operator=(const Test11Lists &obj) {
		m_listOfMyBoolList = obj.m_listOfMyBoolList;
		m_listOfMyCharList = obj.m_listOfMyCharList;
		m_listOfMyInt32List = obj.m_listOfMyInt32List;
		m_listOfMyUint32List = obj.m_listOfMyUint32List;
		m_listOfMyFloatList = obj.m_listOfMyFloatList;
		m_listOfMyDoubleList = obj.m_listOfMyDoubleList;
		m_listOfMyStringList = obj.m_listOfMyStringList;
		return (*this);
	}

	int32_t Test11Lists::ID() {
		return 12;
	}

	const string Test11Lists::ShortName() {
		return "Test11Lists";
	}

	const string Test11Lists::LongName() {
		return "Test11Lists";
	}

	std::vector<bool> Test11Lists::getListOfMyBoolList() const {
		return m_listOfMyBoolList;
	}
	
	void Test11Lists::setListOfMyBoolList(const std::vector<bool> &val) {
		m_listOfMyBoolList = val;
	}
	
	void Test11Lists::clear_ListOfMyBoolList() {
		m_listOfMyBoolList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyBoolList() const {
		return m_listOfMyBoolList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyBoolList() const {
		return m_listOfMyBoolList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyBoolList(const bool &val) {
		m_listOfMyBoolList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyBoolList(const bool &val) {
		m_listOfMyBoolList.insert(m_listOfMyBoolList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyBoolList(const bool &val) const {
		return std::find(m_listOfMyBoolList.begin(), m_listOfMyBoolList.end(), val) != m_listOfMyBoolList.end();
	}
	
	std::pair<std::vector<bool>::iterator, std::vector<bool>::iterator> Test11Lists::iteratorPair_ListOfMyBoolList() {
		return std::make_pair(m_listOfMyBoolList.begin(), m_listOfMyBoolList.end());
	}
	std::vector<char> Test11Lists::getListOfMyCharList() const {
		return m_listOfMyCharList;
	}
	
	void Test11Lists::setListOfMyCharList(const std::vector<char> &val) {
		m_listOfMyCharList = val;
	}
	
	void Test11Lists::clear_ListOfMyCharList() {
		m_listOfMyCharList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyCharList() const {
		return m_listOfMyCharList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyCharList() const {
		return m_listOfMyCharList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyCharList(const char &val) {
		m_listOfMyCharList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyCharList(const char &val) {
		m_listOfMyCharList.insert(m_listOfMyCharList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyCharList(const char &val) const {
		return std::find(m_listOfMyCharList.begin(), m_listOfMyCharList.end(), val) != m_listOfMyCharList.end();
	}
	
	std::pair<std::vector<char>::iterator, std::vector<char>::iterator> Test11Lists::iteratorPair_ListOfMyCharList() {
		return std::make_pair(m_listOfMyCharList.begin(), m_listOfMyCharList.end());
	}
	std::vector<int32_t> Test11Lists::getListOfMyInt32List() const {
		return m_listOfMyInt32List;
	}
	
	void Test11Lists::setListOfMyInt32List(const std::vector<int32_t> &val) {
		m_listOfMyInt32List = val;
	}
	
	void Test11Lists::clear_ListOfMyInt32List() {
		m_listOfMyInt32List.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyInt32List() const {
		return m_listOfMyInt32List.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyInt32List() const {
		return m_listOfMyInt32List.empty();
	}
	
	void Test11Lists::addTo_ListOfMyInt32List(const int32_t &val) {
		m_listOfMyInt32List.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyInt32List(const int32_t &val) {
		m_listOfMyInt32List.insert(m_listOfMyInt32List.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyInt32List(const int32_t &val) const {
		return std::find(m_listOfMyInt32List.begin(), m_listOfMyInt32List.end(), val) != m_listOfMyInt32List.end();
	}
	
	std::pair<std::vector<int32_t>::iterator, std::vector<int32_t>::iterator> Test11Lists::iteratorPair_ListOfMyInt32List() {
		return std::make_pair(m_listOfMyInt32List.begin(), m_listOfMyInt32List.end());
	}
	std::vector<uint32_t> Test11Lists::getListOfMyUint32List() const {
		return m_listOfMyUint32List;
	}
	
	void Test11Lists::setListOfMyUint32List(const std::vector<uint32_t> &val) {
		m_listOfMyUint32List = val;
	}
	
	void Test11Lists::clear_ListOfMyUint32List() {
		m_listOfMyUint32List.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyUint32List() const {
		return m_listOfMyUint32List.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyUint32List() const {
		return m_listOfMyUint32List.empty();
	}
	
	void Test11Lists::addTo_ListOfMyUint32List(const uint32_t &val) {
		m_listOfMyUint32List.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyUint32List(const uint32_t &val) {
		m_listOfMyUint32List.insert(m_listOfMyUint32List.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyUint32List(const uint32_t &val) const {
		return std::find(m_listOfMyUint32List.begin(), m_listOfMyUint32List.end(), val) != m_listOfMyUint32List.end();
	}
	
	std::pair<std::vector<uint32_t>::iterator, std::vector<uint32_t>::iterator> Test11Lists::iteratorPair_ListOfMyUint32List() {
		return std::make_pair(m_listOfMyUint32List.begin(), m_listOfMyUint32List.end());
	}
	std::vector<float> Test11Lists::getListOfMyFloatList() const {
		return m_listOfMyFloatList;
	}
	
	void Test11Lists::setListOfMyFloatList(const std::vector<float> &val) {
		m_listOfMyFloatList = val;
	}
	
	void Test11Lists::clear_ListOfMyFloatList() {
		m_listOfMyFloatList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyFloatList() const {
		return m_listOfMyFloatList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyFloatList() const {
		return m_listOfMyFloatList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyFloatList(const float &val) {
		m_listOfMyFloatList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyFloatList(const float &val) {
		m_listOfMyFloatList.insert(m_listOfMyFloatList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyFloatList(const float &val) const {
		return std::find(m_listOfMyFloatList.begin(), m_listOfMyFloatList.end(), val) != m_listOfMyFloatList.end();
	}
	
	std::pair<std::vector<float>::iterator, std::vector<float>::iterator> Test11Lists::iteratorPair_ListOfMyFloatList() {
		return std::make_pair(m_listOfMyFloatList.begin(), m_listOfMyFloatList.end());
	}
	std::vector<double> Test11Lists::getListOfMyDoubleList() const {
		return m_listOfMyDoubleList;
	}
	
	void Test11Lists::setListOfMyDoubleList(const std::vector<double> &val) {
		m_listOfMyDoubleList = val;
	}
	
	void Test11Lists::clear_ListOfMyDoubleList() {
		m_listOfMyDoubleList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyDoubleList() const {
		return m_listOfMyDoubleList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyDoubleList() const {
		return m_listOfMyDoubleList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyDoubleList(const double &val) {
		m_listOfMyDoubleList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyDoubleList(const double &val) {
		m_listOfMyDoubleList.insert(m_listOfMyDoubleList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyDoubleList(const double &val) const {
		return std::find(m_listOfMyDoubleList.begin(), m_listOfMyDoubleList.end(), val) != m_listOfMyDoubleList.end();
	}
	
	std::pair<std::vector<double>::iterator, std::vector<double>::iterator> Test11Lists::iteratorPair_ListOfMyDoubleList() {
		return std::make_pair(m_listOfMyDoubleList.begin(), m_listOfMyDoubleList.end());
	}
	std::vector<std::string> Test11Lists::getListOfMyStringList() const {
		return m_listOfMyStringList;
	}
	
	void Test11Lists::setListOfMyStringList(const std::vector<std::string> &val) {
		m_listOfMyStringList = val;
	}
	
	void Test11Lists::clear_ListOfMyStringList() {
		m_listOfMyStringList.clear();
	}
	
	uint32_t Test11Lists::getSize_ListOfMyStringList() const {
		return m_listOfMyStringList.size();
	}
	
	bool Test11Lists::isEmpty_ListOfMyStringList() const {
		return m_listOfMyStringList.empty();
	}
	
	void Test11Lists::addTo_ListOfMyStringList(const std::string &val) {
		m_listOfMyStringList.push_back(val);
	}
	
	void Test11Lists::insertTo_ListOfMyStringList(const std::string &val) {
		m_listOfMyStringList.insert(m_listOfMyStringList.begin(), val);
	}
	
	bool Test11Lists::contains_ListOfMyStringList(const std::string &val) const {
		return std::find(m_listOfMyStringList.begin(), m_listOfMyStringList.end(), val) != m_listOfMyStringList.end();
	}
	
	std::pair<std::vector<std::string>::iterator, std::vector<std::string>::iterator> Test11Lists::iteratorPair_ListOfMyStringList() {
		return std::make_pair(m_listOfMyStringList.begin(), m_listOfMyStringList.end());
	}

	void Test11Lists::accept(core::base::Visitor &v) {
		(void)v; // Avoid unused parameter warning.
	}

	const string Test11Lists::toString() const {
		stringstream s;


		s << "Number of elements in list of MyBoolList: " << getSize_ListOfMyBoolList() << " ";
		s << "Number of elements in list of MyCharList: " << getSize_ListOfMyCharList() << " ";
		s << "Number of elements in list of MyInt32List: " << getSize_ListOfMyInt32List() << " ";
		s << "Number of elements in list of MyUint32List: " << getSize_ListOfMyUint32List() << " ";
		s << "Number of elements in list of MyFloatList: " << getSize_ListOfMyFloatList() << " ";
		s << "Number of elements in list of MyDoubleList: " << getSize_ListOfMyDoubleList() << " ";
		s << "Number of elements in list of MyStringList: " << getSize_ListOfMyStringList() << " ";

		return s.str();
	}

	ostream& Test11Lists::operator<<(ostream &out) const {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Serializer> s = sf.getSerializer(out);

		// Write number of elements in m_listOfMyBoolList.
		const uint32_t numberOfMyBoolList = static_cast<uint32_t>(m_listOfMyBoolList.size());
		s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > >  >::RESULT,
		        numberOfMyBoolList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyBoolList;
		for (uint32_t i = 0; i < numberOfMyBoolList; i++) {
		    sstrOfMyBoolList << m_listOfMyBoolList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyBoolList > 0) {
			s->write(CRC32 < CharList<'M', CharList<'y', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > >  >::RESULT,
			        sstrOfMyBoolList.str());
		}
		// Write number of elements in m_listOfMyCharList.
		const uint32_t numberOfMyCharList = static_cast<uint32_t>(m_listOfMyCharList.size());
		s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > >  >::RESULT,
		        numberOfMyCharList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyCharList;
		for (uint32_t i = 0; i < numberOfMyCharList; i++) {
		    sstrOfMyCharList << m_listOfMyCharList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyCharList > 0) {
			s->write(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > >  >::RESULT,
			        sstrOfMyCharList.str());
		}
		// Write number of elements in m_listOfMyInt32List.
		const uint32_t numberOfMyInt32List = static_cast<uint32_t>(m_listOfMyInt32List.size());
		s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > >  >::RESULT,
		        numberOfMyInt32List);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyInt32List;
		for (uint32_t i = 0; i < numberOfMyInt32List; i++) {
		    sstrOfMyInt32List << m_listOfMyInt32List.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyInt32List > 0) {
			s->write(CRC32 < CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > >  >::RESULT,
			        sstrOfMyInt32List.str());
		}
		// Write number of elements in m_listOfMyUint32List.
		const uint32_t numberOfMyUint32List = static_cast<uint32_t>(m_listOfMyUint32List.size());
		s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > > >  >::RESULT,
		        numberOfMyUint32List);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyUint32List;
		for (uint32_t i = 0; i < numberOfMyUint32List; i++) {
		    sstrOfMyUint32List << m_listOfMyUint32List.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyUint32List > 0) {
			s->write(CRC32 < CharList<'M', CharList<'y', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > >  >::RESULT,
			        sstrOfMyUint32List.str());
		}
		// Write number of elements in m_listOfMyFloatList.
		const uint32_t numberOfMyFloatList = static_cast<uint32_t>(m_listOfMyFloatList.size());
		s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > >  >::RESULT,
		        numberOfMyFloatList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyFloatList;
		for (uint32_t i = 0; i < numberOfMyFloatList; i++) {
		    sstrOfMyFloatList << m_listOfMyFloatList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyFloatList > 0) {
			s->write(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > >  >::RESULT,
			        sstrOfMyFloatList.str());
		}
		// Write number of elements in m_listOfMyDoubleList.
		const uint32_t numberOfMyDoubleList = static_cast<uint32_t>(m_listOfMyDoubleList.size());
		s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > > >  >::RESULT,
		        numberOfMyDoubleList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyDoubleList;
		for (uint32_t i = 0; i < numberOfMyDoubleList; i++) {
		    sstrOfMyDoubleList << m_listOfMyDoubleList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyDoubleList > 0) {
			s->write(CRC32 < CharList<'M', CharList<'y', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > >  >::RESULT,
			        sstrOfMyDoubleList.str());
		}
		// Write number of elements in m_listOfMyStringList.
		const uint32_t numberOfMyStringList = static_cast<uint32_t>(m_listOfMyStringList.size());
		s->write(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > > >  >::RESULT,
		        numberOfMyStringList);
		
		// Write actual elements into a stringstream.
		std::stringstream sstrOfMyStringList;
		for (uint32_t i = 0; i < numberOfMyStringList; i++) {
		    sstrOfMyStringList << m_listOfMyStringList.at(i) << endl;
		}
		
		// Write string of elements.
		if (numberOfMyStringList > 0) {
			s->write(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > >  >::RESULT,
			        sstrOfMyStringList.str());
		}
		return out;
	}

	istream& Test11Lists::operator>>(istream &in) {

		SerializationFactory& sf = SerializationFactory::getInstance();

		core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

		// Clean up the existing list of MyBoolList.
		m_listOfMyBoolList.clear();
		
		// Read number of elements in m_listOfMyBoolList.
		uint32_t numberOfMyBoolList = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > >  >::RESULT,
		       numberOfMyBoolList);
		
		if (numberOfMyBoolList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'B', CharList<'o', CharList<'o', CharList<'l', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > >  >::RESULT,
				   elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyBoolList; i++) {
		        bool element;
		        sstr >> element;
		        m_listOfMyBoolList.push_back(element);
		    }
		}
		// Clean up the existing list of MyCharList.
		m_listOfMyCharList.clear();
		
		// Read number of elements in m_listOfMyCharList.
		uint32_t numberOfMyCharList = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > >  >::RESULT,
		       numberOfMyCharList);
		
		if (numberOfMyCharList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'C', CharList<'h', CharList<'a', CharList<'r', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > >  >::RESULT,
				   elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyCharList; i++) {
		        char element;
		        sstr >> element;
		        m_listOfMyCharList.push_back(element);
		    }
		}
		// Clean up the existing list of MyInt32List.
		m_listOfMyInt32List.clear();
		
		// Read number of elements in m_listOfMyInt32List.
		uint32_t numberOfMyInt32List = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > >  >::RESULT,
		       numberOfMyInt32List);
		
		if (numberOfMyInt32List > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'I', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > >  >::RESULT,
				   elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyInt32List; i++) {
		        int32_t element;
		        sstr >> element;
		        m_listOfMyInt32List.push_back(element);
		    }
		}
		// Clean up the existing list of MyUint32List.
		m_listOfMyUint32List.clear();
		
		// Read number of elements in m_listOfMyUint32List.
		uint32_t numberOfMyUint32List = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > > >  >::RESULT,
		       numberOfMyUint32List);
		
		if (numberOfMyUint32List > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'U', CharList<'i', CharList<'n', CharList<'t', CharList<'3', CharList<'2', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > >  >::RESULT,
				   elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyUint32List; i++) {
		        uint32_t element;
		        sstr >> element;
		        m_listOfMyUint32List.push_back(element);
		    }
		}
		// Clean up the existing list of MyFloatList.
		m_listOfMyFloatList.clear();
		
		// Read number of elements in m_listOfMyFloatList.
		uint32_t numberOfMyFloatList = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > >  >::RESULT,
		       numberOfMyFloatList);
		
		if (numberOfMyFloatList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'F', CharList<'l', CharList<'o', CharList<'a', CharList<'t', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > >  >::RESULT,
				   elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyFloatList; i++) {
		        float element;
		        sstr >> element;
		        m_listOfMyFloatList.push_back(element);
		    }
		}
		// Clean up the existing list of MyDoubleList.
		m_listOfMyDoubleList.clear();
		
		// Read number of elements in m_listOfMyDoubleList.
		uint32_t numberOfMyDoubleList = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > > >  >::RESULT,
		       numberOfMyDoubleList);
		
		if (numberOfMyDoubleList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'D', CharList<'o', CharList<'u', CharList<'b', CharList<'l', CharList<'e', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > >  >::RESULT,
				   elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyDoubleList; i++) {
		        double element;
		        sstr >> element;
		        m_listOfMyDoubleList.push_back(element);
		    }
		}
		// Clean up the existing list of MyStringList.
		m_listOfMyStringList.clear();
		
		// Read number of elements in m_listOfMyStringList.
		uint32_t numberOfMyStringList = 0;
		d->read(CRC32 < CharList<'n', CharList<'u', CharList<'m', CharList<'b', CharList<'e', CharList<'r', CharList<'O', CharList<'f', CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > > > > > > > > > >  >::RESULT,
		       numberOfMyStringList);
		
		if (numberOfMyStringList > 0) {
		    // Read string of elements.
		    string elements;
			d->read(CRC32 < CharList<'M', CharList<'y', CharList<'S', CharList<'t', CharList<'r', CharList<'i', CharList<'n', CharList<'g', CharList<'L', CharList<'i', CharList<'s', CharList<'t', NullType> > > > > > > > > > > >  >::RESULT,
				   elements);
		
		    stringstream sstr(elements);
		
		    // Read actual elements from stringstream.
		    for (uint32_t i = 0; i < numberOfMyStringList; i++) {
		        std::string element;
		        getline(sstr, element);
		        m_listOfMyStringList.push_back(element);
		    }
		}
		return in;
	}
