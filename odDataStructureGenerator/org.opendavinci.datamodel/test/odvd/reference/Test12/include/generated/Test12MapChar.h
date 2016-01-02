/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST12MAPCHAR_H
#define TEST12MAPCHAR_H

#include "core/opendavinci.h"

#include <map>

#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test12MapChar : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test12MapChar();

		Test12MapChar(
		const map<char, bool> &val0, 
		const map<char, char> &val1, 
		const map<char, int32_t> &val2, 
		const map<char, uint32_t> &val3, 
		const map<char, float> &val4, 
		const map<char, double> &val5, 
		const map<char, std::string> &val6
		);

		virtual ~Test12MapChar();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test12MapChar(const Test12MapChar &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test12MapChar& operator=(const Test12MapChar &obj);

	public:
		/**
		 * @return myCharBoolMap.
		 */
		std::map<char, bool> getMapOfMyCharBoolMap() const;
	
		/**
		 * This method sets myCharBoolMap.
		 *
		 * @param val Value for myCharBoolMap.
		 */
		void setMapOfMyCharBoolMap(const std::map<char, bool> &val);
	
		/**
		 * This method clears the map of myCharBoolMap.
		 */
		void clear_MapOfMyCharBoolMap();
	
		/**
		 * @return the size of the map of myCharBoolMap.
		 */
		uint32_t getSize_MapOfMyCharBoolMap() const;
	
		/**
		 * @return true if the map of myCharBoolMap is empty.
		 */
		bool isEmpty_MapOfMyCharBoolMap() const;
	
		/**
		 * This method adds an element to the map of myCharBoolMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myCharBoolMap.
		 * @param val Value of the key/value pair to be added to the map of myCharBoolMap.
		 */
		void putTo_MapOfMyCharBoolMap(const char &key, const bool &val);
	
		/**
		 * @return true if the map of myCharBoolMap is contains the given key.
		 */
		bool containsKey_MapOfMyCharBoolMap(const char &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myCharBoolMap.
		 * @return Value to given key from the map of myCharBoolMap is contains the given key.
		 */
		bool getValueForKey_MapOfMyCharBoolMap(const char &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myCharBoolMap.
		 */
		std::pair<std::map<char, bool>::iterator, std::map<char, bool>::iterator> iteratorPair_MapOfMyCharBoolMap();
	public:
		/**
		 * @return myCharCharMap.
		 */
		std::map<char, char> getMapOfMyCharCharMap() const;
	
		/**
		 * This method sets myCharCharMap.
		 *
		 * @param val Value for myCharCharMap.
		 */
		void setMapOfMyCharCharMap(const std::map<char, char> &val);
	
		/**
		 * This method clears the map of myCharCharMap.
		 */
		void clear_MapOfMyCharCharMap();
	
		/**
		 * @return the size of the map of myCharCharMap.
		 */
		uint32_t getSize_MapOfMyCharCharMap() const;
	
		/**
		 * @return true if the map of myCharCharMap is empty.
		 */
		bool isEmpty_MapOfMyCharCharMap() const;
	
		/**
		 * This method adds an element to the map of myCharCharMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myCharCharMap.
		 * @param val Value of the key/value pair to be added to the map of myCharCharMap.
		 */
		void putTo_MapOfMyCharCharMap(const char &key, const char &val);
	
		/**
		 * @return true if the map of myCharCharMap is contains the given key.
		 */
		bool containsKey_MapOfMyCharCharMap(const char &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myCharCharMap.
		 * @return Value to given key from the map of myCharCharMap is contains the given key.
		 */
		char getValueForKey_MapOfMyCharCharMap(const char &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myCharCharMap.
		 */
		std::pair<std::map<char, char>::iterator, std::map<char, char>::iterator> iteratorPair_MapOfMyCharCharMap();
	public:
		/**
		 * @return myCharInt32Map.
		 */
		std::map<char, int32_t> getMapOfMyCharInt32Map() const;
	
		/**
		 * This method sets myCharInt32Map.
		 *
		 * @param val Value for myCharInt32Map.
		 */
		void setMapOfMyCharInt32Map(const std::map<char, int32_t> &val);
	
		/**
		 * This method clears the map of myCharInt32Map.
		 */
		void clear_MapOfMyCharInt32Map();
	
		/**
		 * @return the size of the map of myCharInt32Map.
		 */
		uint32_t getSize_MapOfMyCharInt32Map() const;
	
		/**
		 * @return true if the map of myCharInt32Map is empty.
		 */
		bool isEmpty_MapOfMyCharInt32Map() const;
	
		/**
		 * This method adds an element to the map of myCharInt32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myCharInt32Map.
		 * @param val Value of the key/value pair to be added to the map of myCharInt32Map.
		 */
		void putTo_MapOfMyCharInt32Map(const char &key, const int32_t &val);
	
		/**
		 * @return true if the map of myCharInt32Map is contains the given key.
		 */
		bool containsKey_MapOfMyCharInt32Map(const char &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myCharInt32Map.
		 * @return Value to given key from the map of myCharInt32Map is contains the given key.
		 */
		int32_t getValueForKey_MapOfMyCharInt32Map(const char &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myCharInt32Map.
		 */
		std::pair<std::map<char, int32_t>::iterator, std::map<char, int32_t>::iterator> iteratorPair_MapOfMyCharInt32Map();
	public:
		/**
		 * @return myCharUint32Map.
		 */
		std::map<char, uint32_t> getMapOfMyCharUint32Map() const;
	
		/**
		 * This method sets myCharUint32Map.
		 *
		 * @param val Value for myCharUint32Map.
		 */
		void setMapOfMyCharUint32Map(const std::map<char, uint32_t> &val);
	
		/**
		 * This method clears the map of myCharUint32Map.
		 */
		void clear_MapOfMyCharUint32Map();
	
		/**
		 * @return the size of the map of myCharUint32Map.
		 */
		uint32_t getSize_MapOfMyCharUint32Map() const;
	
		/**
		 * @return true if the map of myCharUint32Map is empty.
		 */
		bool isEmpty_MapOfMyCharUint32Map() const;
	
		/**
		 * This method adds an element to the map of myCharUint32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myCharUint32Map.
		 * @param val Value of the key/value pair to be added to the map of myCharUint32Map.
		 */
		void putTo_MapOfMyCharUint32Map(const char &key, const uint32_t &val);
	
		/**
		 * @return true if the map of myCharUint32Map is contains the given key.
		 */
		bool containsKey_MapOfMyCharUint32Map(const char &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myCharUint32Map.
		 * @return Value to given key from the map of myCharUint32Map is contains the given key.
		 */
		uint32_t getValueForKey_MapOfMyCharUint32Map(const char &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myCharUint32Map.
		 */
		std::pair<std::map<char, uint32_t>::iterator, std::map<char, uint32_t>::iterator> iteratorPair_MapOfMyCharUint32Map();
	public:
		/**
		 * @return myCharFloatMap.
		 */
		std::map<char, float> getMapOfMyCharFloatMap() const;
	
		/**
		 * This method sets myCharFloatMap.
		 *
		 * @param val Value for myCharFloatMap.
		 */
		void setMapOfMyCharFloatMap(const std::map<char, float> &val);
	
		/**
		 * This method clears the map of myCharFloatMap.
		 */
		void clear_MapOfMyCharFloatMap();
	
		/**
		 * @return the size of the map of myCharFloatMap.
		 */
		uint32_t getSize_MapOfMyCharFloatMap() const;
	
		/**
		 * @return true if the map of myCharFloatMap is empty.
		 */
		bool isEmpty_MapOfMyCharFloatMap() const;
	
		/**
		 * This method adds an element to the map of myCharFloatMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myCharFloatMap.
		 * @param val Value of the key/value pair to be added to the map of myCharFloatMap.
		 */
		void putTo_MapOfMyCharFloatMap(const char &key, const float &val);
	
		/**
		 * @return true if the map of myCharFloatMap is contains the given key.
		 */
		bool containsKey_MapOfMyCharFloatMap(const char &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myCharFloatMap.
		 * @return Value to given key from the map of myCharFloatMap is contains the given key.
		 */
		float getValueForKey_MapOfMyCharFloatMap(const char &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myCharFloatMap.
		 */
		std::pair<std::map<char, float>::iterator, std::map<char, float>::iterator> iteratorPair_MapOfMyCharFloatMap();
	public:
		/**
		 * @return myCharDoubleMap.
		 */
		std::map<char, double> getMapOfMyCharDoubleMap() const;
	
		/**
		 * This method sets myCharDoubleMap.
		 *
		 * @param val Value for myCharDoubleMap.
		 */
		void setMapOfMyCharDoubleMap(const std::map<char, double> &val);
	
		/**
		 * This method clears the map of myCharDoubleMap.
		 */
		void clear_MapOfMyCharDoubleMap();
	
		/**
		 * @return the size of the map of myCharDoubleMap.
		 */
		uint32_t getSize_MapOfMyCharDoubleMap() const;
	
		/**
		 * @return true if the map of myCharDoubleMap is empty.
		 */
		bool isEmpty_MapOfMyCharDoubleMap() const;
	
		/**
		 * This method adds an element to the map of myCharDoubleMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myCharDoubleMap.
		 * @param val Value of the key/value pair to be added to the map of myCharDoubleMap.
		 */
		void putTo_MapOfMyCharDoubleMap(const char &key, const double &val);
	
		/**
		 * @return true if the map of myCharDoubleMap is contains the given key.
		 */
		bool containsKey_MapOfMyCharDoubleMap(const char &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myCharDoubleMap.
		 * @return Value to given key from the map of myCharDoubleMap is contains the given key.
		 */
		double getValueForKey_MapOfMyCharDoubleMap(const char &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myCharDoubleMap.
		 */
		std::pair<std::map<char, double>::iterator, std::map<char, double>::iterator> iteratorPair_MapOfMyCharDoubleMap();
	public:
		/**
		 * @return myCharStringMap.
		 */
		std::map<char, std::string> getMapOfMyCharStringMap() const;
	
		/**
		 * This method sets myCharStringMap.
		 *
		 * @param val Value for myCharStringMap.
		 */
		void setMapOfMyCharStringMap(const std::map<char, std::string> &val);
	
		/**
		 * This method clears the map of myCharStringMap.
		 */
		void clear_MapOfMyCharStringMap();
	
		/**
		 * @return the size of the map of myCharStringMap.
		 */
		uint32_t getSize_MapOfMyCharStringMap() const;
	
		/**
		 * @return true if the map of myCharStringMap is empty.
		 */
		bool isEmpty_MapOfMyCharStringMap() const;
	
		/**
		 * This method adds an element to the map of myCharStringMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myCharStringMap.
		 * @param val Value of the key/value pair to be added to the map of myCharStringMap.
		 */
		void putTo_MapOfMyCharStringMap(const char &key, const std::string &val);
	
		/**
		 * @return true if the map of myCharStringMap is contains the given key.
		 */
		bool containsKey_MapOfMyCharStringMap(const char &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myCharStringMap.
		 * @return Value to given key from the map of myCharStringMap is contains the given key.
		 */
		std::string getValueForKey_MapOfMyCharStringMap(const char &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myCharStringMap.
		 */
		std::pair<std::map<char, std::string>::iterator, std::map<char, std::string>::iterator> iteratorPair_MapOfMyCharStringMap();

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
		std::map<char, bool> m_mapOfMyCharBoolMap;
	private:
		std::map<char, char> m_mapOfMyCharCharMap;
	private:
		std::map<char, int32_t> m_mapOfMyCharInt32Map;
	private:
		std::map<char, uint32_t> m_mapOfMyCharUint32Map;
	private:
		std::map<char, float> m_mapOfMyCharFloatMap;
	private:
		std::map<char, double> m_mapOfMyCharDoubleMap;
	private:
		std::map<char, std::string> m_mapOfMyCharStringMap;

};

#endif /*TEST12MAPCHAR_H*/
