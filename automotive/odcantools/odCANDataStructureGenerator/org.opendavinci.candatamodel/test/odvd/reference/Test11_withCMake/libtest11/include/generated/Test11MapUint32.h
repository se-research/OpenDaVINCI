/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11MAPUINT32_H
#define TEST11MAPUINT32_H

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include <map>

#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test11MapUint32 : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test11MapUint32();

		Test11MapUint32(
		const map<uint32_t, bool> &val0, 
		const map<uint32_t, char> &val1, 
		const map<uint32_t, int32_t> &val2, 
		const map<uint32_t, uint32_t> &val3, 
		const map<uint32_t, float> &val4, 
		const map<uint32_t, double> &val5, 
		const map<uint32_t, std::string> &val6
		);

		virtual ~Test11MapUint32();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test11MapUint32(const Test11MapUint32 &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test11MapUint32& operator=(const Test11MapUint32 &obj);

	public:
		/**
		 * @return myUint32BoolMap.
		 */
		std::map<uint32_t, bool> getMapOfMyUint32BoolMap() const;
	
		/**
		 * This method sets myUint32BoolMap.
		 *
		 * @param val Value for myUint32BoolMap.
		 */
		void setMapOfMyUint32BoolMap(const std::map<uint32_t, bool> &val);
	
		/**
		 * This method clears the map of myUint32BoolMap.
		 */
		void clear_MapOfMyUint32BoolMap();
	
		/**
		 * @return the size of the map of myUint32BoolMap.
		 */
		uint32_t getSize_MapOfMyUint32BoolMap() const;
	
		/**
		 * @return true if the map of myUint32BoolMap is empty.
		 */
		bool isEmpty_MapOfMyUint32BoolMap() const;
	
		/**
		 * This method adds an element to the map of myUint32BoolMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myUint32BoolMap.
		 * @param val Value of the key/value pair to be added to the map of myUint32BoolMap.
		 */
		void putTo_MapOfMyUint32BoolMap(const uint32_t &key, const bool &val);
	
		/**
		 * @return true if the map of myUint32BoolMap is contains the given key.
		 */
		bool containsKey_MapOfMyUint32BoolMap(const uint32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myUint32BoolMap.
		 * @return Value to given key from the map of myUint32BoolMap is contains the given key.
		 */
		bool getValueForKey_MapOfMyUint32BoolMap(const uint32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myUint32BoolMap.
		 */
		std::pair<std::map<uint32_t, bool>::iterator, std::map<uint32_t, bool>::iterator> iteratorPair_MapOfMyUint32BoolMap();
	public:
		/**
		 * @return myUint32CharMap.
		 */
		std::map<uint32_t, char> getMapOfMyUint32CharMap() const;
	
		/**
		 * This method sets myUint32CharMap.
		 *
		 * @param val Value for myUint32CharMap.
		 */
		void setMapOfMyUint32CharMap(const std::map<uint32_t, char> &val);
	
		/**
		 * This method clears the map of myUint32CharMap.
		 */
		void clear_MapOfMyUint32CharMap();
	
		/**
		 * @return the size of the map of myUint32CharMap.
		 */
		uint32_t getSize_MapOfMyUint32CharMap() const;
	
		/**
		 * @return true if the map of myUint32CharMap is empty.
		 */
		bool isEmpty_MapOfMyUint32CharMap() const;
	
		/**
		 * This method adds an element to the map of myUint32CharMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myUint32CharMap.
		 * @param val Value of the key/value pair to be added to the map of myUint32CharMap.
		 */
		void putTo_MapOfMyUint32CharMap(const uint32_t &key, const char &val);
	
		/**
		 * @return true if the map of myUint32CharMap is contains the given key.
		 */
		bool containsKey_MapOfMyUint32CharMap(const uint32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myUint32CharMap.
		 * @return Value to given key from the map of myUint32CharMap is contains the given key.
		 */
		char getValueForKey_MapOfMyUint32CharMap(const uint32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myUint32CharMap.
		 */
		std::pair<std::map<uint32_t, char>::iterator, std::map<uint32_t, char>::iterator> iteratorPair_MapOfMyUint32CharMap();
	public:
		/**
		 * @return myUint32Int32Map.
		 */
		std::map<uint32_t, int32_t> getMapOfMyUint32Int32Map() const;
	
		/**
		 * This method sets myUint32Int32Map.
		 *
		 * @param val Value for myUint32Int32Map.
		 */
		void setMapOfMyUint32Int32Map(const std::map<uint32_t, int32_t> &val);
	
		/**
		 * This method clears the map of myUint32Int32Map.
		 */
		void clear_MapOfMyUint32Int32Map();
	
		/**
		 * @return the size of the map of myUint32Int32Map.
		 */
		uint32_t getSize_MapOfMyUint32Int32Map() const;
	
		/**
		 * @return true if the map of myUint32Int32Map is empty.
		 */
		bool isEmpty_MapOfMyUint32Int32Map() const;
	
		/**
		 * This method adds an element to the map of myUint32Int32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myUint32Int32Map.
		 * @param val Value of the key/value pair to be added to the map of myUint32Int32Map.
		 */
		void putTo_MapOfMyUint32Int32Map(const uint32_t &key, const int32_t &val);
	
		/**
		 * @return true if the map of myUint32Int32Map is contains the given key.
		 */
		bool containsKey_MapOfMyUint32Int32Map(const uint32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myUint32Int32Map.
		 * @return Value to given key from the map of myUint32Int32Map is contains the given key.
		 */
		int32_t getValueForKey_MapOfMyUint32Int32Map(const uint32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myUint32Int32Map.
		 */
		std::pair<std::map<uint32_t, int32_t>::iterator, std::map<uint32_t, int32_t>::iterator> iteratorPair_MapOfMyUint32Int32Map();
	public:
		/**
		 * @return myUint32Uint32Map.
		 */
		std::map<uint32_t, uint32_t> getMapOfMyUint32Uint32Map() const;
	
		/**
		 * This method sets myUint32Uint32Map.
		 *
		 * @param val Value for myUint32Uint32Map.
		 */
		void setMapOfMyUint32Uint32Map(const std::map<uint32_t, uint32_t> &val);
	
		/**
		 * This method clears the map of myUint32Uint32Map.
		 */
		void clear_MapOfMyUint32Uint32Map();
	
		/**
		 * @return the size of the map of myUint32Uint32Map.
		 */
		uint32_t getSize_MapOfMyUint32Uint32Map() const;
	
		/**
		 * @return true if the map of myUint32Uint32Map is empty.
		 */
		bool isEmpty_MapOfMyUint32Uint32Map() const;
	
		/**
		 * This method adds an element to the map of myUint32Uint32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myUint32Uint32Map.
		 * @param val Value of the key/value pair to be added to the map of myUint32Uint32Map.
		 */
		void putTo_MapOfMyUint32Uint32Map(const uint32_t &key, const uint32_t &val);
	
		/**
		 * @return true if the map of myUint32Uint32Map is contains the given key.
		 */
		bool containsKey_MapOfMyUint32Uint32Map(const uint32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myUint32Uint32Map.
		 * @return Value to given key from the map of myUint32Uint32Map is contains the given key.
		 */
		uint32_t getValueForKey_MapOfMyUint32Uint32Map(const uint32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myUint32Uint32Map.
		 */
		std::pair<std::map<uint32_t, uint32_t>::iterator, std::map<uint32_t, uint32_t>::iterator> iteratorPair_MapOfMyUint32Uint32Map();
	public:
		/**
		 * @return myUint32FloatMap.
		 */
		std::map<uint32_t, float> getMapOfMyUint32FloatMap() const;
	
		/**
		 * This method sets myUint32FloatMap.
		 *
		 * @param val Value for myUint32FloatMap.
		 */
		void setMapOfMyUint32FloatMap(const std::map<uint32_t, float> &val);
	
		/**
		 * This method clears the map of myUint32FloatMap.
		 */
		void clear_MapOfMyUint32FloatMap();
	
		/**
		 * @return the size of the map of myUint32FloatMap.
		 */
		uint32_t getSize_MapOfMyUint32FloatMap() const;
	
		/**
		 * @return true if the map of myUint32FloatMap is empty.
		 */
		bool isEmpty_MapOfMyUint32FloatMap() const;
	
		/**
		 * This method adds an element to the map of myUint32FloatMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myUint32FloatMap.
		 * @param val Value of the key/value pair to be added to the map of myUint32FloatMap.
		 */
		void putTo_MapOfMyUint32FloatMap(const uint32_t &key, const float &val);
	
		/**
		 * @return true if the map of myUint32FloatMap is contains the given key.
		 */
		bool containsKey_MapOfMyUint32FloatMap(const uint32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myUint32FloatMap.
		 * @return Value to given key from the map of myUint32FloatMap is contains the given key.
		 */
		float getValueForKey_MapOfMyUint32FloatMap(const uint32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myUint32FloatMap.
		 */
		std::pair<std::map<uint32_t, float>::iterator, std::map<uint32_t, float>::iterator> iteratorPair_MapOfMyUint32FloatMap();
	public:
		/**
		 * @return myUint32DoubleMap.
		 */
		std::map<uint32_t, double> getMapOfMyUint32DoubleMap() const;
	
		/**
		 * This method sets myUint32DoubleMap.
		 *
		 * @param val Value for myUint32DoubleMap.
		 */
		void setMapOfMyUint32DoubleMap(const std::map<uint32_t, double> &val);
	
		/**
		 * This method clears the map of myUint32DoubleMap.
		 */
		void clear_MapOfMyUint32DoubleMap();
	
		/**
		 * @return the size of the map of myUint32DoubleMap.
		 */
		uint32_t getSize_MapOfMyUint32DoubleMap() const;
	
		/**
		 * @return true if the map of myUint32DoubleMap is empty.
		 */
		bool isEmpty_MapOfMyUint32DoubleMap() const;
	
		/**
		 * This method adds an element to the map of myUint32DoubleMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myUint32DoubleMap.
		 * @param val Value of the key/value pair to be added to the map of myUint32DoubleMap.
		 */
		void putTo_MapOfMyUint32DoubleMap(const uint32_t &key, const double &val);
	
		/**
		 * @return true if the map of myUint32DoubleMap is contains the given key.
		 */
		bool containsKey_MapOfMyUint32DoubleMap(const uint32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myUint32DoubleMap.
		 * @return Value to given key from the map of myUint32DoubleMap is contains the given key.
		 */
		double getValueForKey_MapOfMyUint32DoubleMap(const uint32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myUint32DoubleMap.
		 */
		std::pair<std::map<uint32_t, double>::iterator, std::map<uint32_t, double>::iterator> iteratorPair_MapOfMyUint32DoubleMap();
	public:
		/**
		 * @return myUint32StringMap.
		 */
		std::map<uint32_t, std::string> getMapOfMyUint32StringMap() const;
	
		/**
		 * This method sets myUint32StringMap.
		 *
		 * @param val Value for myUint32StringMap.
		 */
		void setMapOfMyUint32StringMap(const std::map<uint32_t, std::string> &val);
	
		/**
		 * This method clears the map of myUint32StringMap.
		 */
		void clear_MapOfMyUint32StringMap();
	
		/**
		 * @return the size of the map of myUint32StringMap.
		 */
		uint32_t getSize_MapOfMyUint32StringMap() const;
	
		/**
		 * @return true if the map of myUint32StringMap is empty.
		 */
		bool isEmpty_MapOfMyUint32StringMap() const;
	
		/**
		 * This method adds an element to the map of myUint32StringMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myUint32StringMap.
		 * @param val Value of the key/value pair to be added to the map of myUint32StringMap.
		 */
		void putTo_MapOfMyUint32StringMap(const uint32_t &key, const std::string &val);
	
		/**
		 * @return true if the map of myUint32StringMap is contains the given key.
		 */
		bool containsKey_MapOfMyUint32StringMap(const uint32_t &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myUint32StringMap.
		 * @return Value to given key from the map of myUint32StringMap is contains the given key.
		 */
		std::string getValueForKey_MapOfMyUint32StringMap(const uint32_t &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myUint32StringMap.
		 */
		std::pair<std::map<uint32_t, std::string>::iterator, std::map<uint32_t, std::string>::iterator> iteratorPair_MapOfMyUint32StringMap();

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
		std::map<uint32_t, bool> m_mapOfMyUint32BoolMap;
	private:
		std::map<uint32_t, char> m_mapOfMyUint32CharMap;
	private:
		std::map<uint32_t, int32_t> m_mapOfMyUint32Int32Map;
	private:
		std::map<uint32_t, uint32_t> m_mapOfMyUint32Uint32Map;
	private:
		std::map<uint32_t, float> m_mapOfMyUint32FloatMap;
	private:
		std::map<uint32_t, double> m_mapOfMyUint32DoubleMap;
	private:
		std::map<uint32_t, std::string> m_mapOfMyUint32StringMap;

};

#endif /*TEST11MAPUINT32_H*/
