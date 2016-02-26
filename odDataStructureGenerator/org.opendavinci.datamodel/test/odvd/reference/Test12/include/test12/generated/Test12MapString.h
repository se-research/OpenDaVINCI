/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST12MAPSTRING_H
#define TEST12MAPSTRING_H

#include "opendavinci/odcore/opendavinci.h"

#include <map>

#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/data/SerializableData.h"


using namespace std;

class Test12MapString : public odcore::data::SerializableData, public odcore::base::Visitable {
	public:
		Test12MapString();

		Test12MapString(
		const map<std::string, bool> &val0, 
		const map<std::string, char> &val1, 
		const map<std::string, int32_t> &val2, 
		const map<std::string, uint32_t> &val3, 
		const map<std::string, float> &val4, 
		const map<std::string, double> &val5, 
		const map<std::string, std::string> &val6
		);

		virtual ~Test12MapString();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test12MapString(const Test12MapString &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test12MapString& operator=(const Test12MapString &obj);

	public:
		/**
		 * @return myStringBoolMap.
		 */
		std::map<std::string, bool> getMapOfMyStringBoolMap() const;
	
		/**
		 * This method sets myStringBoolMap.
		 *
		 * @param val Value for myStringBoolMap.
		 */
		void setMapOfMyStringBoolMap(const std::map<std::string, bool> &val);
	
		/**
		 * This method clears the map of myStringBoolMap.
		 */
		void clear_MapOfMyStringBoolMap();
	
		/**
		 * @return the size of the map of myStringBoolMap.
		 */
		uint32_t getSize_MapOfMyStringBoolMap() const;
	
		/**
		 * @return true if the map of myStringBoolMap is empty.
		 */
		bool isEmpty_MapOfMyStringBoolMap() const;
	
		/**
		 * This method adds an element to the map of myStringBoolMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myStringBoolMap.
		 * @param val Value of the key/value pair to be added to the map of myStringBoolMap.
		 */
		void putTo_MapOfMyStringBoolMap(const std::string &key, const bool &val);
	
		/**
		 * @return true if the map of myStringBoolMap is contains the given key.
		 */
		bool containsKey_MapOfMyStringBoolMap(const std::string &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myStringBoolMap.
		 * @return Value to given key from the map of myStringBoolMap is contains the given key.
		 */
		bool getValueForKey_MapOfMyStringBoolMap(const std::string &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myStringBoolMap.
		 */
		std::pair<std::map<std::string, bool>::iterator, std::map<std::string, bool>::iterator> iteratorPair_MapOfMyStringBoolMap();
	public:
		/**
		 * @return myStringCharMap.
		 */
		std::map<std::string, char> getMapOfMyStringCharMap() const;
	
		/**
		 * This method sets myStringCharMap.
		 *
		 * @param val Value for myStringCharMap.
		 */
		void setMapOfMyStringCharMap(const std::map<std::string, char> &val);
	
		/**
		 * This method clears the map of myStringCharMap.
		 */
		void clear_MapOfMyStringCharMap();
	
		/**
		 * @return the size of the map of myStringCharMap.
		 */
		uint32_t getSize_MapOfMyStringCharMap() const;
	
		/**
		 * @return true if the map of myStringCharMap is empty.
		 */
		bool isEmpty_MapOfMyStringCharMap() const;
	
		/**
		 * This method adds an element to the map of myStringCharMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myStringCharMap.
		 * @param val Value of the key/value pair to be added to the map of myStringCharMap.
		 */
		void putTo_MapOfMyStringCharMap(const std::string &key, const char &val);
	
		/**
		 * @return true if the map of myStringCharMap is contains the given key.
		 */
		bool containsKey_MapOfMyStringCharMap(const std::string &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myStringCharMap.
		 * @return Value to given key from the map of myStringCharMap is contains the given key.
		 */
		char getValueForKey_MapOfMyStringCharMap(const std::string &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myStringCharMap.
		 */
		std::pair<std::map<std::string, char>::iterator, std::map<std::string, char>::iterator> iteratorPair_MapOfMyStringCharMap();
	public:
		/**
		 * @return myStringInt32Map.
		 */
		std::map<std::string, int32_t> getMapOfMyStringInt32Map() const;
	
		/**
		 * This method sets myStringInt32Map.
		 *
		 * @param val Value for myStringInt32Map.
		 */
		void setMapOfMyStringInt32Map(const std::map<std::string, int32_t> &val);
	
		/**
		 * This method clears the map of myStringInt32Map.
		 */
		void clear_MapOfMyStringInt32Map();
	
		/**
		 * @return the size of the map of myStringInt32Map.
		 */
		uint32_t getSize_MapOfMyStringInt32Map() const;
	
		/**
		 * @return true if the map of myStringInt32Map is empty.
		 */
		bool isEmpty_MapOfMyStringInt32Map() const;
	
		/**
		 * This method adds an element to the map of myStringInt32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myStringInt32Map.
		 * @param val Value of the key/value pair to be added to the map of myStringInt32Map.
		 */
		void putTo_MapOfMyStringInt32Map(const std::string &key, const int32_t &val);
	
		/**
		 * @return true if the map of myStringInt32Map is contains the given key.
		 */
		bool containsKey_MapOfMyStringInt32Map(const std::string &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myStringInt32Map.
		 * @return Value to given key from the map of myStringInt32Map is contains the given key.
		 */
		int32_t getValueForKey_MapOfMyStringInt32Map(const std::string &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myStringInt32Map.
		 */
		std::pair<std::map<std::string, int32_t>::iterator, std::map<std::string, int32_t>::iterator> iteratorPair_MapOfMyStringInt32Map();
	public:
		/**
		 * @return myStringUint32Map.
		 */
		std::map<std::string, uint32_t> getMapOfMyStringUint32Map() const;
	
		/**
		 * This method sets myStringUint32Map.
		 *
		 * @param val Value for myStringUint32Map.
		 */
		void setMapOfMyStringUint32Map(const std::map<std::string, uint32_t> &val);
	
		/**
		 * This method clears the map of myStringUint32Map.
		 */
		void clear_MapOfMyStringUint32Map();
	
		/**
		 * @return the size of the map of myStringUint32Map.
		 */
		uint32_t getSize_MapOfMyStringUint32Map() const;
	
		/**
		 * @return true if the map of myStringUint32Map is empty.
		 */
		bool isEmpty_MapOfMyStringUint32Map() const;
	
		/**
		 * This method adds an element to the map of myStringUint32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myStringUint32Map.
		 * @param val Value of the key/value pair to be added to the map of myStringUint32Map.
		 */
		void putTo_MapOfMyStringUint32Map(const std::string &key, const uint32_t &val);
	
		/**
		 * @return true if the map of myStringUint32Map is contains the given key.
		 */
		bool containsKey_MapOfMyStringUint32Map(const std::string &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myStringUint32Map.
		 * @return Value to given key from the map of myStringUint32Map is contains the given key.
		 */
		uint32_t getValueForKey_MapOfMyStringUint32Map(const std::string &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myStringUint32Map.
		 */
		std::pair<std::map<std::string, uint32_t>::iterator, std::map<std::string, uint32_t>::iterator> iteratorPair_MapOfMyStringUint32Map();
	public:
		/**
		 * @return myStringFloatMap.
		 */
		std::map<std::string, float> getMapOfMyStringFloatMap() const;
	
		/**
		 * This method sets myStringFloatMap.
		 *
		 * @param val Value for myStringFloatMap.
		 */
		void setMapOfMyStringFloatMap(const std::map<std::string, float> &val);
	
		/**
		 * This method clears the map of myStringFloatMap.
		 */
		void clear_MapOfMyStringFloatMap();
	
		/**
		 * @return the size of the map of myStringFloatMap.
		 */
		uint32_t getSize_MapOfMyStringFloatMap() const;
	
		/**
		 * @return true if the map of myStringFloatMap is empty.
		 */
		bool isEmpty_MapOfMyStringFloatMap() const;
	
		/**
		 * This method adds an element to the map of myStringFloatMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myStringFloatMap.
		 * @param val Value of the key/value pair to be added to the map of myStringFloatMap.
		 */
		void putTo_MapOfMyStringFloatMap(const std::string &key, const float &val);
	
		/**
		 * @return true if the map of myStringFloatMap is contains the given key.
		 */
		bool containsKey_MapOfMyStringFloatMap(const std::string &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myStringFloatMap.
		 * @return Value to given key from the map of myStringFloatMap is contains the given key.
		 */
		float getValueForKey_MapOfMyStringFloatMap(const std::string &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myStringFloatMap.
		 */
		std::pair<std::map<std::string, float>::iterator, std::map<std::string, float>::iterator> iteratorPair_MapOfMyStringFloatMap();
	public:
		/**
		 * @return myStringDoubleMap.
		 */
		std::map<std::string, double> getMapOfMyStringDoubleMap() const;
	
		/**
		 * This method sets myStringDoubleMap.
		 *
		 * @param val Value for myStringDoubleMap.
		 */
		void setMapOfMyStringDoubleMap(const std::map<std::string, double> &val);
	
		/**
		 * This method clears the map of myStringDoubleMap.
		 */
		void clear_MapOfMyStringDoubleMap();
	
		/**
		 * @return the size of the map of myStringDoubleMap.
		 */
		uint32_t getSize_MapOfMyStringDoubleMap() const;
	
		/**
		 * @return true if the map of myStringDoubleMap is empty.
		 */
		bool isEmpty_MapOfMyStringDoubleMap() const;
	
		/**
		 * This method adds an element to the map of myStringDoubleMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myStringDoubleMap.
		 * @param val Value of the key/value pair to be added to the map of myStringDoubleMap.
		 */
		void putTo_MapOfMyStringDoubleMap(const std::string &key, const double &val);
	
		/**
		 * @return true if the map of myStringDoubleMap is contains the given key.
		 */
		bool containsKey_MapOfMyStringDoubleMap(const std::string &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myStringDoubleMap.
		 * @return Value to given key from the map of myStringDoubleMap is contains the given key.
		 */
		double getValueForKey_MapOfMyStringDoubleMap(const std::string &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myStringDoubleMap.
		 */
		std::pair<std::map<std::string, double>::iterator, std::map<std::string, double>::iterator> iteratorPair_MapOfMyStringDoubleMap();
	public:
		/**
		 * @return myStringStringMap.
		 */
		std::map<std::string, std::string> getMapOfMyStringStringMap() const;
	
		/**
		 * This method sets myStringStringMap.
		 *
		 * @param val Value for myStringStringMap.
		 */
		void setMapOfMyStringStringMap(const std::map<std::string, std::string> &val);
	
		/**
		 * This method clears the map of myStringStringMap.
		 */
		void clear_MapOfMyStringStringMap();
	
		/**
		 * @return the size of the map of myStringStringMap.
		 */
		uint32_t getSize_MapOfMyStringStringMap() const;
	
		/**
		 * @return true if the map of myStringStringMap is empty.
		 */
		bool isEmpty_MapOfMyStringStringMap() const;
	
		/**
		 * This method adds an element to the map of myStringStringMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myStringStringMap.
		 * @param val Value of the key/value pair to be added to the map of myStringStringMap.
		 */
		void putTo_MapOfMyStringStringMap(const std::string &key, const std::string &val);
	
		/**
		 * @return true if the map of myStringStringMap is contains the given key.
		 */
		bool containsKey_MapOfMyStringStringMap(const std::string &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myStringStringMap.
		 * @return Value to given key from the map of myStringStringMap is contains the given key.
		 */
		std::string getValueForKey_MapOfMyStringStringMap(const std::string &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myStringStringMap.
		 */
		std::pair<std::map<std::string, std::string>::iterator, std::map<std::string, std::string>::iterator> iteratorPair_MapOfMyStringStringMap();

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

		/**
		 * This method returns the message id.
		 *
		 * @return Message id.
		 */
		virtual int32_t getID() const;

		/**
		 * This method returns the short message name.
		 *
		 * @return Short message name.
		 */
		virtual const string getShortName() const;

		/**
		 * This method returns the long message name include package/sub structure.
		 *
		 * @return Long message name.
		 */
		virtual const string getLongName() const;

	public:
		virtual void accept(odcore::base::Visitor &v);

		virtual ostream& operator<<(ostream &out) const;
		virtual istream& operator>>(istream &in);

		virtual const string toString() const;

	private:
		std::map<std::string, bool> m_mapOfMyStringBoolMap;
	private:
		std::map<std::string, char> m_mapOfMyStringCharMap;
	private:
		std::map<std::string, int32_t> m_mapOfMyStringInt32Map;
	private:
		std::map<std::string, uint32_t> m_mapOfMyStringUint32Map;
	private:
		std::map<std::string, float> m_mapOfMyStringFloatMap;
	private:
		std::map<std::string, double> m_mapOfMyStringDoubleMap;
	private:
		std::map<std::string, std::string> m_mapOfMyStringStringMap;

};

#endif /*TEST12MAPSTRING_H*/
