/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TESTPACKAGE_TEST7B_H
#define TESTPACKAGE_TEST7B_H

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"

#include <vector>

#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


namespace testpackage {
	using namespace std;
	
	class Test7B : public core::data::SerializableData, public core::base::Visitable {
		public:
			Test7B();
	
			Test7B(
			const bool &val0, 
			const char &val1, 
			const int32_t &val2, 
			const uint32_t &val3, 
			const float &val4, 
			const double &val5, 
			const std::string &val6, 
			const vector<std::string> &val7
			);
	
			virtual ~Test7B();
	
			/**
			 * Copy constructor.
			 *
			 * @param obj Reference to an object of this class.
			 */
			Test7B(const Test7B &obj);
	
			/**
			 * Assignment operator.
			 *
			 * @param obj Reference to an object of this class.
			 * @return Reference to this instance.
			 */
			Test7B& operator=(const Test7B &obj);
	
		public:
			/**
			 * @return attribute1.
			 */
			bool getAttribute1() const;
			
			/**
			 * This method sets attribute1.
			 *
			 * @param val Value for attribute1.
			 */
			void setAttribute1(const bool &val);
		public:
			/**
			 * @return attribute2.
			 */
			char getAttribute2() const;
			
			/**
			 * This method sets attribute2.
			 *
			 * @param val Value for attribute2.
			 */
			void setAttribute2(const char &val);
		public:
			/**
			 * @return attribute3.
			 */
			int32_t getAttribute3() const;
			
			/**
			 * This method sets attribute3.
			 *
			 * @param val Value for attribute3.
			 */
			void setAttribute3(const int32_t &val);
		public:
			/**
			 * @return attribute4.
			 */
			uint32_t getAttribute4() const;
			
			/**
			 * This method sets attribute4.
			 *
			 * @param val Value for attribute4.
			 */
			void setAttribute4(const uint32_t &val);
		public:
			/**
			 * @return attribute5.
			 */
			float getAttribute5() const;
			
			/**
			 * This method sets attribute5.
			 *
			 * @param val Value for attribute5.
			 */
			void setAttribute5(const float &val);
		public:
			/**
			 * @return attribute6.
			 */
			double getAttribute6() const;
			
			/**
			 * This method sets attribute6.
			 *
			 * @param val Value for attribute6.
			 */
			void setAttribute6(const double &val);
		public:
			/**
			 * @return attribute7.
			 */
			std::string getAttribute7() const;
			
			/**
			 * This method sets attribute7.
			 *
			 * @param val Value for attribute7.
			 */
			void setAttribute7(const std::string &val);
		public:
			/**
			 * @return myStringList.
			 */
			std::vector<std::string> getListOfMyStringList() const;
		
			/**
			 * This method sets myStringList.
			 *
			 * @param val Value for myStringList.
			 */
			void setListOfMyStringList(const std::vector<std::string> &val);
		
			/**
			 * This method clears the list of myStringList.
			 */
			void clear_ListOfMyStringList();
		
			/**
			 * @return the size of the list of myStringList.
			 */
			uint32_t getSize_ListOfMyStringList() const;
		
			/**
			 * @return true if the list of myStringList is empty.
			 */
			bool isEmpty_ListOfMyStringList() const;
		
			/**
			 * This method adds an element to the end of the list of myStringList.
			 *
			 * @param val Value to be added to the end of the list of myStringList.
			 */
			void addTo_ListOfMyStringList(const std::string &val);
		
			/**
			 * This method adds an element to the beginning of the list of myStringList.
			 *
			 * @param val Value to be inserted to the beginning of the list of myStringList.
			 */
			void insertTo_ListOfMyStringList(const std::string &val);
		
			/**
			 * @return true if the list of myStringList contains the element val.
			 *              If the list has a complex data type, the entries are compared using their .toString() method.
			 */
			bool contains_ListOfMyStringList(const std::string &val) const;
		
			/**
			 * @return Pair of iterators for the begin and end of the list of myStringList.
			 */
			std::pair<std::vector<std::string>::iterator, std::vector<std::string>::iterator> iteratorPair_ListOfMyStringList();
	
		public:
			/**
			 * This method returns the message id.
			 *
			 * @return Message id.
			 */
			static int32_t ID();
	
			/**
			 * This method returns the short message name.
			 *
			 * @return Short message name.
			 */
			static const string ShortName();
	
			/**
			 * This method returns the long message name include package/sub structure.
			 *
			 * @return Long message name.
			 */
			static const string LongName();
	
		public:
			virtual void accept(core::base::Visitor &v);
	
			virtual ostream& operator<<(ostream &out) const;
			virtual istream& operator>>(istream &in);
	
			virtual const string toString() const;
	
		private:
			bool m_attribute1;
		private:
			char m_attribute2;
		private:
			int32_t m_attribute3;
		private:
			uint32_t m_attribute4;
		private:
			float m_attribute5;
		private:
			double m_attribute6;
		private:
			std::string m_attribute7;
		private:
			std::vector<std::string> m_listOfMyStringList;
	
	};
} // testpackage

#endif /*TESTPACKAGE_TEST7B_H*/
