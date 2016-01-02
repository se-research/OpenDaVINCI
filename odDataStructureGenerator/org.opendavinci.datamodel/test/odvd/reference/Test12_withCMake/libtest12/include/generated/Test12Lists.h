/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST12LISTS_H
#define TEST12LISTS_H

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"

#include <vector>

#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test12Lists : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test12Lists();

		Test12Lists(
		const vector<bool> &val0, 
		const vector<char> &val1, 
		const vector<int32_t> &val2, 
		const vector<uint32_t> &val3, 
		const vector<float> &val4, 
		const vector<double> &val5, 
		const vector<std::string> &val6
		);

		virtual ~Test12Lists();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test12Lists(const Test12Lists &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test12Lists& operator=(const Test12Lists &obj);

	public:
		/**
		 * @return myBoolList.
		 */
		std::vector<bool> getListOfMyBoolList() const;
	
		/**
		 * This method sets myBoolList.
		 *
		 * @param val Value for myBoolList.
		 */
		void setListOfMyBoolList(const std::vector<bool> &val);
	
		/**
		 * This method clears the list of myBoolList.
		 */
		void clear_ListOfMyBoolList();
	
		/**
		 * @return the size of the list of myBoolList.
		 */
		uint32_t getSize_ListOfMyBoolList() const;
	
		/**
		 * @return true if the list of myBoolList is empty.
		 */
		bool isEmpty_ListOfMyBoolList() const;
	
		/**
		 * This method adds an element to the end of the list of myBoolList.
		 *
		 * @param val Value to be added to the end of the list of myBoolList.
		 */
		void addTo_ListOfMyBoolList(const bool &val);
	
		/**
		 * This method adds an element to the beginning of the list of myBoolList.
		 *
		 * @param val Value to be inserted to the beginning of the list of myBoolList.
		 */
		void insertTo_ListOfMyBoolList(const bool &val);
	
		/**
		 * @return true if the list of myBoolList contains the element val.
		 *              If the list has a complex data type, the entries are compared using their .toString() method.
		 */
		bool contains_ListOfMyBoolList(const bool &val) const;
	
		/**
		 * @return Pair of iterators for the begin and end of the list of myBoolList.
		 */
		std::pair<std::vector<bool>::iterator, std::vector<bool>::iterator> iteratorPair_ListOfMyBoolList();
	public:
		/**
		 * @return myCharList.
		 */
		std::vector<char> getListOfMyCharList() const;
	
		/**
		 * This method sets myCharList.
		 *
		 * @param val Value for myCharList.
		 */
		void setListOfMyCharList(const std::vector<char> &val);
	
		/**
		 * This method clears the list of myCharList.
		 */
		void clear_ListOfMyCharList();
	
		/**
		 * @return the size of the list of myCharList.
		 */
		uint32_t getSize_ListOfMyCharList() const;
	
		/**
		 * @return true if the list of myCharList is empty.
		 */
		bool isEmpty_ListOfMyCharList() const;
	
		/**
		 * This method adds an element to the end of the list of myCharList.
		 *
		 * @param val Value to be added to the end of the list of myCharList.
		 */
		void addTo_ListOfMyCharList(const char &val);
	
		/**
		 * This method adds an element to the beginning of the list of myCharList.
		 *
		 * @param val Value to be inserted to the beginning of the list of myCharList.
		 */
		void insertTo_ListOfMyCharList(const char &val);
	
		/**
		 * @return true if the list of myCharList contains the element val.
		 *              If the list has a complex data type, the entries are compared using their .toString() method.
		 */
		bool contains_ListOfMyCharList(const char &val) const;
	
		/**
		 * @return Pair of iterators for the begin and end of the list of myCharList.
		 */
		std::pair<std::vector<char>::iterator, std::vector<char>::iterator> iteratorPair_ListOfMyCharList();
	public:
		/**
		 * @return myInt32List.
		 */
		std::vector<int32_t> getListOfMyInt32List() const;
	
		/**
		 * This method sets myInt32List.
		 *
		 * @param val Value for myInt32List.
		 */
		void setListOfMyInt32List(const std::vector<int32_t> &val);
	
		/**
		 * This method clears the list of myInt32List.
		 */
		void clear_ListOfMyInt32List();
	
		/**
		 * @return the size of the list of myInt32List.
		 */
		uint32_t getSize_ListOfMyInt32List() const;
	
		/**
		 * @return true if the list of myInt32List is empty.
		 */
		bool isEmpty_ListOfMyInt32List() const;
	
		/**
		 * This method adds an element to the end of the list of myInt32List.
		 *
		 * @param val Value to be added to the end of the list of myInt32List.
		 */
		void addTo_ListOfMyInt32List(const int32_t &val);
	
		/**
		 * This method adds an element to the beginning of the list of myInt32List.
		 *
		 * @param val Value to be inserted to the beginning of the list of myInt32List.
		 */
		void insertTo_ListOfMyInt32List(const int32_t &val);
	
		/**
		 * @return true if the list of myInt32List contains the element val.
		 *              If the list has a complex data type, the entries are compared using their .toString() method.
		 */
		bool contains_ListOfMyInt32List(const int32_t &val) const;
	
		/**
		 * @return Pair of iterators for the begin and end of the list of myInt32List.
		 */
		std::pair<std::vector<int32_t>::iterator, std::vector<int32_t>::iterator> iteratorPair_ListOfMyInt32List();
	public:
		/**
		 * @return myUint32List.
		 */
		std::vector<uint32_t> getListOfMyUint32List() const;
	
		/**
		 * This method sets myUint32List.
		 *
		 * @param val Value for myUint32List.
		 */
		void setListOfMyUint32List(const std::vector<uint32_t> &val);
	
		/**
		 * This method clears the list of myUint32List.
		 */
		void clear_ListOfMyUint32List();
	
		/**
		 * @return the size of the list of myUint32List.
		 */
		uint32_t getSize_ListOfMyUint32List() const;
	
		/**
		 * @return true if the list of myUint32List is empty.
		 */
		bool isEmpty_ListOfMyUint32List() const;
	
		/**
		 * This method adds an element to the end of the list of myUint32List.
		 *
		 * @param val Value to be added to the end of the list of myUint32List.
		 */
		void addTo_ListOfMyUint32List(const uint32_t &val);
	
		/**
		 * This method adds an element to the beginning of the list of myUint32List.
		 *
		 * @param val Value to be inserted to the beginning of the list of myUint32List.
		 */
		void insertTo_ListOfMyUint32List(const uint32_t &val);
	
		/**
		 * @return true if the list of myUint32List contains the element val.
		 *              If the list has a complex data type, the entries are compared using their .toString() method.
		 */
		bool contains_ListOfMyUint32List(const uint32_t &val) const;
	
		/**
		 * @return Pair of iterators for the begin and end of the list of myUint32List.
		 */
		std::pair<std::vector<uint32_t>::iterator, std::vector<uint32_t>::iterator> iteratorPair_ListOfMyUint32List();
	public:
		/**
		 * @return myFloatList.
		 */
		std::vector<float> getListOfMyFloatList() const;
	
		/**
		 * This method sets myFloatList.
		 *
		 * @param val Value for myFloatList.
		 */
		void setListOfMyFloatList(const std::vector<float> &val);
	
		/**
		 * This method clears the list of myFloatList.
		 */
		void clear_ListOfMyFloatList();
	
		/**
		 * @return the size of the list of myFloatList.
		 */
		uint32_t getSize_ListOfMyFloatList() const;
	
		/**
		 * @return true if the list of myFloatList is empty.
		 */
		bool isEmpty_ListOfMyFloatList() const;
	
		/**
		 * This method adds an element to the end of the list of myFloatList.
		 *
		 * @param val Value to be added to the end of the list of myFloatList.
		 */
		void addTo_ListOfMyFloatList(const float &val);
	
		/**
		 * This method adds an element to the beginning of the list of myFloatList.
		 *
		 * @param val Value to be inserted to the beginning of the list of myFloatList.
		 */
		void insertTo_ListOfMyFloatList(const float &val);
	
		/**
		 * @return true if the list of myFloatList contains the element val.
		 *              If the list has a complex data type, the entries are compared using their .toString() method.
		 */
		bool contains_ListOfMyFloatList(const float &val) const;
	
		/**
		 * @return Pair of iterators for the begin and end of the list of myFloatList.
		 */
		std::pair<std::vector<float>::iterator, std::vector<float>::iterator> iteratorPair_ListOfMyFloatList();
	public:
		/**
		 * @return myDoubleList.
		 */
		std::vector<double> getListOfMyDoubleList() const;
	
		/**
		 * This method sets myDoubleList.
		 *
		 * @param val Value for myDoubleList.
		 */
		void setListOfMyDoubleList(const std::vector<double> &val);
	
		/**
		 * This method clears the list of myDoubleList.
		 */
		void clear_ListOfMyDoubleList();
	
		/**
		 * @return the size of the list of myDoubleList.
		 */
		uint32_t getSize_ListOfMyDoubleList() const;
	
		/**
		 * @return true if the list of myDoubleList is empty.
		 */
		bool isEmpty_ListOfMyDoubleList() const;
	
		/**
		 * This method adds an element to the end of the list of myDoubleList.
		 *
		 * @param val Value to be added to the end of the list of myDoubleList.
		 */
		void addTo_ListOfMyDoubleList(const double &val);
	
		/**
		 * This method adds an element to the beginning of the list of myDoubleList.
		 *
		 * @param val Value to be inserted to the beginning of the list of myDoubleList.
		 */
		void insertTo_ListOfMyDoubleList(const double &val);
	
		/**
		 * @return true if the list of myDoubleList contains the element val.
		 *              If the list has a complex data type, the entries are compared using their .toString() method.
		 */
		bool contains_ListOfMyDoubleList(const double &val) const;
	
		/**
		 * @return Pair of iterators for the begin and end of the list of myDoubleList.
		 */
		std::pair<std::vector<double>::iterator, std::vector<double>::iterator> iteratorPair_ListOfMyDoubleList();
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
		std::vector<bool> m_listOfMyBoolList;
	private:
		std::vector<char> m_listOfMyCharList;
	private:
		std::vector<int32_t> m_listOfMyInt32List;
	private:
		std::vector<uint32_t> m_listOfMyUint32List;
	private:
		std::vector<float> m_listOfMyFloatList;
	private:
		std::vector<double> m_listOfMyDoubleList;
	private:
		std::vector<std::string> m_listOfMyStringList;

};

#endif /*TEST12LISTS_H*/
