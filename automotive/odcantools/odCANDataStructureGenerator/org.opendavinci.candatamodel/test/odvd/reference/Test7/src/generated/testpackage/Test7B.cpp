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


#include "generated/testpackage/Test7B.h"

namespace testpackage {
		using namespace std;
		using namespace core::base;
	
	
		Test7B::Test7B() :
		    SerializableData(), Visitable()
			, m_attribute1(true) // TODO: Validation if the default value is of the desired type.
			, m_attribute2('c') // TODO: Validation if the default value is of the desired type.
			, m_attribute3(-12) // TODO: Validation if the default value is of the desired type.
			, m_attribute4(+45) // TODO: Validation if the default value is of the desired type.
			, m_attribute5(-0.12) // TODO: Validation if the default value is of the desired type.
			, m_attribute6(+0.45678) // TODO: Validation if the default value is of the desired type.
			, m_attribute7("Hello World.") // TODO: Validation if the default value is of the desired type.
			, m_listOfMyStringList()
		{
		}
	
		Test7B::Test7B(
			const bool &val0, 
			const char &val1, 
			const int32_t &val2, 
			const uint32_t &val3, 
			const float &val4, 
			const double &val5, 
			const std::string &val6, 
			const vector<std::string> &val7
		) :
		    SerializableData(), Visitable()
			, m_attribute1(val0)
			, m_attribute2(val1)
			, m_attribute3(val2)
			, m_attribute4(val3)
			, m_attribute5(val4)
			, m_attribute6(val5)
			, m_attribute7(val6)
			, m_listOfMyStringList(val7)
		{
		}
	
		Test7B::Test7B(const Test7B &obj) :
		    SerializableData(), Visitable()
			, m_attribute1(obj.m_attribute1)
			, m_attribute2(obj.m_attribute2)
			, m_attribute3(obj.m_attribute3)
			, m_attribute4(obj.m_attribute4)
			, m_attribute5(obj.m_attribute5)
			, m_attribute6(obj.m_attribute6)
			, m_attribute7(obj.m_attribute7)
			, m_listOfMyStringList(obj.m_listOfMyStringList)
		{
		}
		
		Test7B::~Test7B() {
		}
	
		Test7B& Test7B::operator=(const Test7B &obj) {
			m_attribute1 = obj.m_attribute1;
			m_attribute2 = obj.m_attribute2;
			m_attribute3 = obj.m_attribute3;
			m_attribute4 = obj.m_attribute4;
			m_attribute5 = obj.m_attribute5;
			m_attribute6 = obj.m_attribute6;
			m_attribute7 = obj.m_attribute7;
			m_listOfMyStringList = obj.m_listOfMyStringList;
			return (*this);
		}
	
		int32_t Test7B::ID() {
			return 8;
		}
	
		const string Test7B::ShortName() {
			return "Test7B";
		}
	
		const string Test7B::LongName() {
			return "testpackage.Test7B";
		}
	
		bool Test7B::getAttribute1() const {
			return m_attribute1;
		}
		
		void Test7B::setAttribute1(const bool &val) {
			m_attribute1 = val;
		}
		char Test7B::getAttribute2() const {
			return m_attribute2;
		}
		
		void Test7B::setAttribute2(const char &val) {
			m_attribute2 = val;
		}
		int32_t Test7B::getAttribute3() const {
			return m_attribute3;
		}
		
		void Test7B::setAttribute3(const int32_t &val) {
			m_attribute3 = val;
		}
		uint32_t Test7B::getAttribute4() const {
			return m_attribute4;
		}
		
		void Test7B::setAttribute4(const uint32_t &val) {
			m_attribute4 = val;
		}
		float Test7B::getAttribute5() const {
			return m_attribute5;
		}
		
		void Test7B::setAttribute5(const float &val) {
			m_attribute5 = val;
		}
		double Test7B::getAttribute6() const {
			return m_attribute6;
		}
		
		void Test7B::setAttribute6(const double &val) {
			m_attribute6 = val;
		}
		std::string Test7B::getAttribute7() const {
			return m_attribute7;
		}
		
		void Test7B::setAttribute7(const std::string &val) {
			m_attribute7 = val;
		}
		std::vector<std::string> Test7B::getListOfMyStringList() const {
			return m_listOfMyStringList;
		}
		
		void Test7B::setListOfMyStringList(const std::vector<std::string> &val) {
			m_listOfMyStringList = val;
		}
		
		void Test7B::clear_ListOfMyStringList() {
			m_listOfMyStringList.clear();
		}
		
		uint32_t Test7B::getSize_ListOfMyStringList() const {
			return m_listOfMyStringList.size();
		}
		
		bool Test7B::isEmpty_ListOfMyStringList() const {
			return m_listOfMyStringList.empty();
		}
		
		void Test7B::addTo_ListOfMyStringList(const std::string &val) {
			m_listOfMyStringList.push_back(val);
		}
		
		void Test7B::insertTo_ListOfMyStringList(const std::string &val) {
			m_listOfMyStringList.insert(m_listOfMyStringList.begin(), val);
		}
		
		bool Test7B::contains_ListOfMyStringList(const std::string &val) const {
			return std::find(m_listOfMyStringList.begin(), m_listOfMyStringList.end(), val) != m_listOfMyStringList.end();
		}
		
		std::pair<std::vector<std::string>::iterator, std::vector<std::string>::iterator> Test7B::iteratorPair_ListOfMyStringList() {
			return std::make_pair(m_listOfMyStringList.begin(), m_listOfMyStringList.end());
		}
	
		void Test7B::accept(core::base::Visitor &v) {
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT, 0, "Test7B.attribute1", "attribute1", m_attribute1);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT, 0, "Test7B.attribute2", "attribute2", m_attribute2);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT, 0, "Test7B.attribute3", "attribute3", m_attribute3);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'4', NullType> > > > > > > > > >  >::RESULT, 0, "Test7B.attribute4", "attribute4", m_attribute4);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'5', NullType> > > > > > > > > >  >::RESULT, 0, "Test7B.attribute5", "attribute5", m_attribute5);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'6', NullType> > > > > > > > > >  >::RESULT, 0, "Test7B.attribute6", "attribute6", m_attribute6);
			v.visit(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'7', NullType> > > > > > > > > >  >::RESULT, 0, "Test7B.attribute7", "attribute7", m_attribute7);
		}
	
		const string Test7B::toString() const {
			stringstream s;
	
	
			s << "Attribute1: " << getAttribute1() << " ";
			s << "Attribute2: " << getAttribute2() << " ";
			s << "Attribute3: " << getAttribute3() << " ";
			s << "Attribute4: " << getAttribute4() << " ";
			s << "Attribute5: " << getAttribute5() << " ";
			s << "Attribute6: " << getAttribute6() << " ";
			s << "Attribute7: " << getAttribute7() << " ";
			s << "Number of elements in list of MyStringList: " << getSize_ListOfMyStringList() << " ";
	
			return s.str();
		}
	
		ostream& Test7B::operator<<(ostream &out) const {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			core::SharedPointer<Serializer> s = sf.getSerializer(out);
	
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
					m_attribute1);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT,
					m_attribute2);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT,
					m_attribute3);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'4', NullType> > > > > > > > > >  >::RESULT,
					m_attribute4);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'5', NullType> > > > > > > > > >  >::RESULT,
					m_attribute5);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'6', NullType> > > > > > > > > >  >::RESULT,
					m_attribute6);
			s->write(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'7', NullType> > > > > > > > > >  >::RESULT,
					m_attribute7);
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
	
		istream& Test7B::operator>>(istream &in) {
	
			SerializationFactory& sf = SerializationFactory::getInstance();
	
			core::SharedPointer<Deserializer> d = sf.getDeserializer(in);
	
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'1', NullType> > > > > > > > > >  >::RESULT,
					m_attribute1);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'2', NullType> > > > > > > > > >  >::RESULT,
					m_attribute2);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'3', NullType> > > > > > > > > >  >::RESULT,
					m_attribute3);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'4', NullType> > > > > > > > > >  >::RESULT,
					m_attribute4);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'5', NullType> > > > > > > > > >  >::RESULT,
					m_attribute5);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'6', NullType> > > > > > > > > >  >::RESULT,
					m_attribute6);
			d->read(CRC32 < CharList<'a', CharList<'t', CharList<'t', CharList<'r', CharList<'i', CharList<'b', CharList<'u', CharList<'t', CharList<'e', CharList<'7', NullType> > > > > > > > > >  >::RESULT,
					m_attribute7);
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
} // testpackage
