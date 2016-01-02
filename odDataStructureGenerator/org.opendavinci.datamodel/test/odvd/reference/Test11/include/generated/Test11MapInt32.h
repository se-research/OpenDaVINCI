/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11MAPINT32_H
#define TEST11MAPINT32_H

#include "core/opendavinci.h"

#include <map>

#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test11MapInt32 : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test11MapInt32();

		Test11MapInt32(
		const map<int32_t, bool> &val0, 
		const map<int32_t, char> &val1, 
		const map<int32_t, int32_t> &val2, 
		const map<int32_t, uint32_t> &val3, 
		const map<int32_t, float> &val4, 
		const map<int32_t, double> &val5, 
		const map<int32_t, std::string> &val6
		);

		virtual ~Test11MapInt32();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test11MapInt32(const Test11MapInt32 &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test11MapInt32& operator=(const Test11MapInt32 &obj);

	public:
		/**
		 * @return myInt32BoolMap.
		 */
		std::map<int32_t, bool> getMapOfMyInt32BoolMap() const;
	
		/**
		 * This method sets myInt32BoolMap.
		 *
		 * @param val Value for myInt32BoolMap.
		 */
		void setMapOfMyInt32BoolMap(const std::map<int32_t, bool> &val);
	
		/**
		 * This method clears the map of myInt32BoolMap.
		 */
		void clear_MapOfMyInt32BoolMap();
	
		/**
		 * @return the size of the map of myInt32BoolMap.
		 */
		uint32_t getSize_MapOfMyInt32BoolMap() const;
	
		/**
		 * @return true if the map of myInt32BoolMap is empty.
		 */
		bool isEmpty_MapOfMyInt32BoolMap() const;
	
		/**
		 * This method adds an element to the map of myInt32BoolMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myInt32BoolMap.
		 * @param val Value of the key/value pair to be added to the map of myInt32BoolMap.
		 */
		void putTo_MapOfMyInt32BoolMap(const int32_t &key, const bool &val);
	
		/**
		 * @return true if the map of myInt32BoolMap is contains the given key.
		 */
		bool containsKey_MapOfMyInt32BoolMap(const int32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myInt32BoolMap.
		 * @return Value to given key from the map of myInt32BoolMap is contains the given key.
		 */
		bool getValueForKey_MapOfMyInt32BoolMap(const int32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myInt32BoolMap.
		 */
		std::pair<std::map<int32_t, bool>::iterator, std::map<int32_t, bool>::iterator> iteratorPair_MapOfMyInt32BoolMap();
	public:
		/**
		 * @return myInt32CharMap.
		 */
		std::map<int32_t, char> getMapOfMyInt32CharMap() const;
	
		/**
		 * This method sets myInt32CharMap.
		 *
		 * @param val Value for myInt32CharMap.
		 */
		void setMapOfMyInt32CharMap(const std::map<int32_t, char> &val);
	
		/**
		 * This method clears the map of myInt32CharMap.
		 */
		void clear_MapOfMyInt32CharMap();
	
		/**
		 * @return the size of the map of myInt32CharMap.
		 */
		uint32_t getSize_MapOfMyInt32CharMap() const;
	
		/**
		 * @return true if the map of myInt32CharMap is empty.
		 */
		bool isEmpty_MapOfMyInt32CharMap() const;
	
		/**
		 * This method adds an element to the map of myInt32CharMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myInt32CharMap.
		 * @param val Value of the key/value pair to be added to the map of myInt32CharMap.
		 */
		void putTo_MapOfMyInt32CharMap(const int32_t &key, const char &val);
	
		/**
		 * @return true if the map of myInt32CharMap is contains the given key.
		 */
		bool containsKey_MapOfMyInt32CharMap(const int32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myInt32CharMap.
		 * @return Value to given key from the map of myInt32CharMap is contains the given key.
		 */
		char getValueForKey_MapOfMyInt32CharMap(const int32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myInt32CharMap.
		 */
		std::pair<std::map<int32_t, char>::iterator, std::map<int32_t, char>::iterator> iteratorPair_MapOfMyInt32CharMap();
	public:
		/**
		 * @return myInt32Int32Map.
		 */
		std::map<int32_t, int32_t> getMapOfMyInt32Int32Map() const;
	
		/**
		 * This method sets myInt32Int32Map.
		 *
		 * @param val Value for myInt32Int32Map.
		 */
		void setMapOfMyInt32Int32Map(const std::map<int32_t, int32_t> &val);
	
		/**
		 * This method clears the map of myInt32Int32Map.
		 */
		void clear_MapOfMyInt32Int32Map();
	
		/**
		 * @return the size of the map of myInt32Int32Map.
		 */
		uint32_t getSize_MapOfMyInt32Int32Map() const;
	
		/**
		 * @return true if the map of myInt32Int32Map is empty.
		 */
		bool isEmpty_MapOfMyInt32Int32Map() const;
	
		/**
		 * This method adds an element to the map of myInt32Int32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myInt32Int32Map.
		 * @param val Value of the key/value pair to be added to the map of myInt32Int32Map.
		 */
		void putTo_MapOfMyInt32Int32Map(const int32_t &key, const int32_t &val);
	
		/**
		 * @return true if the map of myInt32Int32Map is contains the given key.
		 */
		bool containsKey_MapOfMyInt32Int32Map(const int32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myInt32Int32Map.
		 * @return Value to given key from the map of myInt32Int32Map is contains the given key.
		 */
		int32_t getValueForKey_MapOfMyInt32Int32Map(const int32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myInt32Int32Map.
		 */
		std::pair<std::map<int32_t, int32_t>::iterator, std::map<int32_t, int32_t>::iterator> iteratorPair_MapOfMyInt32Int32Map();
	public:
		/**
		 * @return myInt32Uint32Map.
		 */
		std::map<int32_t, uint32_t> getMapOfMyInt32Uint32Map() const;
	
		/**
		 * This method sets myInt32Uint32Map.
		 *
		 * @param val Value for myInt32Uint32Map.
		 */
		void setMapOfMyInt32Uint32Map(const std::map<int32_t, uint32_t> &val);
	
		/**
		 * This method clears the map of myInt32Uint32Map.
		 */
		void clear_MapOfMyInt32Uint32Map();
	
		/**
		 * @return the size of the map of myInt32Uint32Map.
		 */
		uint32_t getSize_MapOfMyInt32Uint32Map() const;
	
		/**
		 * @return true if the map of myInt32Uint32Map is empty.
		 */
		bool isEmpty_MapOfMyInt32Uint32Map() const;
	
		/**
		 * This method adds an element to the map of myInt32Uint32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myInt32Uint32Map.
		 * @param val Value of the key/value pair to be added to the map of myInt32Uint32Map.
		 */
		void putTo_MapOfMyInt32Uint32Map(const int32_t &key, const uint32_t &val);
	
		/**
		 * @return true if the map of myInt32Uint32Map is contains the given key.
		 */
		bool containsKey_MapOfMyInt32Uint32Map(const int32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myInt32Uint32Map.
		 * @return Value to given key from the map of myInt32Uint32Map is contains the given key.
		 */
		uint32_t getValueForKey_MapOfMyInt32Uint32Map(const int32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myInt32Uint32Map.
		 */
		std::pair<std::map<int32_t, uint32_t>::iterator, std::map<int32_t, uint32_t>::iterator> iteratorPair_MapOfMyInt32Uint32Map();
	public:
		/**
		 * @return myInt32FloatMap.
		 */
		std::map<int32_t, float> getMapOfMyInt32FloatMap() const;
	
		/**
		 * This method sets myInt32FloatMap.
		 *
		 * @param val Value for myInt32FloatMap.
		 */
		void setMapOfMyInt32FloatMap(const std::map<int32_t, float> &val);
	
		/**
		 * This method clears the map of myInt32FloatMap.
		 */
		void clear_MapOfMyInt32FloatMap();
	
		/**
		 * @return the size of the map of myInt32FloatMap.
		 */
		uint32_t getSize_MapOfMyInt32FloatMap() const;
	
		/**
		 * @return true if the map of myInt32FloatMap is empty.
		 */
		bool isEmpty_MapOfMyInt32FloatMap() const;
	
		/**
		 * This method adds an element to the map of myInt32FloatMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myInt32FloatMap.
		 * @param val Value of the key/value pair to be added to the map of myInt32FloatMap.
		 */
		void putTo_MapOfMyInt32FloatMap(const int32_t &key, const float &val);
	
		/**
		 * @return true if the map of myInt32FloatMap is contains the given key.
		 */
		bool containsKey_MapOfMyInt32FloatMap(const int32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myInt32FloatMap.
		 * @return Value to given key from the map of myInt32FloatMap is contains the given key.
		 */
		float getValueForKey_MapOfMyInt32FloatMap(const int32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myInt32FloatMap.
		 */
		std::pair<std::map<int32_t, float>::iterator, std::map<int32_t, float>::iterator> iteratorPair_MapOfMyInt32FloatMap();
	public:
		/**
		 * @return myInt32DoubleMap.
		 */
		std::map<int32_t, double> getMapOfMyInt32DoubleMap() const;
	
		/**
		 * This method sets myInt32DoubleMap.
		 *
		 * @param val Value for myInt32DoubleMap.
		 */
		void setMapOfMyInt32DoubleMap(const std::map<int32_t, double> &val);
	
		/**
		 * This method clears the map of myInt32DoubleMap.
		 */
		void clear_MapOfMyInt32DoubleMap();
	
		/**
		 * @return the size of the map of myInt32DoubleMap.
		 */
		uint32_t getSize_MapOfMyInt32DoubleMap() const;
	
		/**
		 * @return true if the map of myInt32DoubleMap is empty.
		 */
		bool isEmpty_MapOfMyInt32DoubleMap() const;
	
		/**
		 * This method adds an element to the map of myInt32DoubleMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myInt32DoubleMap.
		 * @param val Value of the key/value pair to be added to the map of myInt32DoubleMap.
		 */
		void putTo_MapOfMyInt32DoubleMap(const int32_t &key, const double &val);
	
		/**
		 * @return true if the map of myInt32DoubleMap is contains the given key.
		 */
		bool containsKey_MapOfMyInt32DoubleMap(const int32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myInt32DoubleMap.
		 * @return Value to given key from the map of myInt32DoubleMap is contains the given key.
		 */
		double getValueForKey_MapOfMyInt32DoubleMap(const int32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myInt32DoubleMap.
		 */
		std::pair<std::map<int32_t, double>::iterator, std::map<int32_t, double>::iterator> iteratorPair_MapOfMyInt32DoubleMap();
	public:
		/**
		 * @return myInt32StringMap.
		 */
		std::map<int32_t, std::string> getMapOfMyInt32StringMap() const;
	
		/**
		 * This method sets myInt32StringMap.
		 *
		 * @param val Value for myInt32StringMap.
		 */
		void setMapOfMyInt32StringMap(const std::map<int32_t, std::string> &val);
	
		/**
		 * This method clears the map of myInt32StringMap.
		 */
		void clear_MapOfMyInt32StringMap();
	
		/**
		 * @return the size of the map of myInt32StringMap.
		 */
		uint32_t getSize_MapOfMyInt32StringMap() const;
	
		/**
		 * @return true if the map of myInt32StringMap is empty.
		 */
		bool isEmpty_MapOfMyInt32StringMap() const;
	
		/**
		 * This method adds an element to the map of myInt32StringMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myInt32StringMap.
		 * @param val Value of the key/value pair to be added to the map of myInt32StringMap.
		 */
		void putTo_MapOfMyInt32StringMap(const int32_t &key, const std::string &val);
	
		/**
		 * @return true if the map of myInt32StringMap is contains the given key.
		 */
		bool containsKey_MapOfMyInt32StringMap(const int32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myInt32StringMap.
		 * @return Value to given key from the map of myInt32StringMap is contains the given key.
		 */
		std::string getValueForKey_MapOfMyInt32StringMap(const int32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myInt32StringMap.
		 */
		std::pair<std::map<int32_t, std::string>::iterator, std::map<int32_t, std::string>::iterator> iteratorPair_MapOfMyInt32StringMap();

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
		std::map<int32_t, bool> m_mapOfMyInt32BoolMap;
	private:
		std::map<int32_t, char> m_mapOfMyInt32CharMap;
	private:
		std::map<int32_t, int32_t> m_mapOfMyInt32Int32Map;
	private:
		std::map<int32_t, uint32_t> m_mapOfMyInt32Uint32Map;
	private:
		std::map<int32_t, float> m_mapOfMyInt32FloatMap;
	private:
		std::map<int32_t, double> m_mapOfMyInt32DoubleMap;
	private:
		std::map<int32_t, std::string> m_mapOfMyInt32StringMap;

};

#endif /*TEST11MAPINT32_H*/
