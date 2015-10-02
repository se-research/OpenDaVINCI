/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST10_H
#define TEST10_H

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include <vector>
#include <map>

#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"

#include "generated/Test10Point.h"
#include "generated/Test10Point.h"

using namespace std;

class Test10 : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test10();

		Test10(
		const vector<std::string> &val0, 
		const vector<Test10Point> &val1, 
		const map<int32_t, std::string> &val2, 
		const map<int32_t, Test10Point> &val3
		);

		virtual ~Test10();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test10(const Test10 &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test10& operator=(const Test10 &obj);

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
		 * @return myPointList.
		 */
		std::vector<Test10Point> getListOfMyPointList() const;
	
		/**
		 * This method sets myPointList.
		 *
		 * @param val Value for myPointList.
		 */
		void setListOfMyPointList(const std::vector<Test10Point> &val);
	
		/**
		 * This method clears the list of myPointList.
		 */
		void clear_ListOfMyPointList();
	
		/**
		 * @return the size of the list of myPointList.
		 */
		uint32_t getSize_ListOfMyPointList() const;
	
		/**
		 * @return true if the list of myPointList is empty.
		 */
		bool isEmpty_ListOfMyPointList() const;
	
		/**
		 * This method adds an element to the end of the list of myPointList.
		 *
		 * @param val Value to be added to the end of the list of myPointList.
		 */
		void addTo_ListOfMyPointList(const Test10Point &val);
	
		/**
		 * This method adds an element to the beginning of the list of myPointList.
		 *
		 * @param val Value to be inserted to the beginning of the list of myPointList.
		 */
		void insertTo_ListOfMyPointList(const Test10Point &val);
	
		/**
		 * @return true if the list of myPointList contains the element val.
		 *              If the list has a complex data type, the entries are compared using their .toString() method.
		 */
		bool contains_ListOfMyPointList(const Test10Point &val) const;
	
		/**
		 * @return Pair of iterators for the begin and end of the list of myPointList.
		 */
		std::pair<std::vector<Test10Point>::iterator, std::vector<Test10Point>::iterator> iteratorPair_ListOfMyPointList();
	public:
		/**
		 * @return myIntStringMap.
		 */
		std::map<int32_t, std::string> getMapOfMyIntStringMap() const;
	
		/**
		 * This method sets myIntStringMap.
		 *
		 * @param val Value for myIntStringMap.
		 */
		void setMapOfMyIntStringMap(const std::map<int32_t, std::string> &val);
	
		/**
		 * This method clears the map of myIntStringMap.
		 */
		void clear_MapOfMyIntStringMap();
	
		/**
		 * @return the size of the map of myIntStringMap.
		 */
		uint32_t getSize_MapOfMyIntStringMap() const;
	
		/**
		 * @return true if the map of myIntStringMap is empty.
		 */
		bool isEmpty_MapOfMyIntStringMap() const;
	
		/**
		 * This method adds an element to the map of myIntStringMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myIntStringMap.
		 * @param val Value of the key/value pair to be added to the map of myIntStringMap.
		 */
		void putTo_MapOfMyIntStringMap(const int32_t &key, const std::string &val);
	
		/**
		 * @return true if the map of myIntStringMap is contains the given key.
		 */
		bool containsKey_MapOfMyIntStringMap(const int32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myIntStringMap.
		 * @return Value to given key from the map of myIntStringMap is contains the given key.
		 */
		std::string getValueForKey_MapOfMyIntStringMap(const int32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myIntStringMap.
		 */
		std::pair<std::map<int32_t, std::string>::iterator, std::map<int32_t, std::string>::iterator> iteratorPair_MapOfMyIntStringMap();
	public:
		/**
		 * @return myIntPointMap.
		 */
		std::map<int32_t, Test10Point> getMapOfMyIntPointMap() const;
	
		/**
		 * This method sets myIntPointMap.
		 *
		 * @param val Value for myIntPointMap.
		 */
		void setMapOfMyIntPointMap(const std::map<int32_t, Test10Point> &val);
	
		/**
		 * This method clears the map of myIntPointMap.
		 */
		void clear_MapOfMyIntPointMap();
	
		/**
		 * @return the size of the map of myIntPointMap.
		 */
		uint32_t getSize_MapOfMyIntPointMap() const;
	
		/**
		 * @return true if the map of myIntPointMap is empty.
		 */
		bool isEmpty_MapOfMyIntPointMap() const;
	
		/**
		 * This method adds an element to the map of myIntPointMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myIntPointMap.
		 * @param val Value of the key/value pair to be added to the map of myIntPointMap.
		 */
		void putTo_MapOfMyIntPointMap(const int32_t &key, const Test10Point &val);
	
		/**
		 * @return true if the map of myIntPointMap is contains the given key.
		 */
		bool containsKey_MapOfMyIntPointMap(const int32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myIntPointMap.
		 * @return Value to given key from the map of myIntPointMap is contains the given key.
		 */
		Test10Point getValueForKey_MapOfMyIntPointMap(const int32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myIntPointMap.
		 */
		std::pair<std::map<int32_t, Test10Point>::iterator, std::map<int32_t, Test10Point>::iterator> iteratorPair_MapOfMyIntPointMap();

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
		std::vector<std::string> m_listOfMyStringList;
	private:
		std::vector<Test10Point> m_listOfMyPointList;
	private:
		std::map<int32_t, std::string> m_mapOfMyIntStringMap;
	private:
		std::map<int32_t, Test10Point> m_mapOfMyIntPointMap;

};

#endif /*TEST10_H*/
