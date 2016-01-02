/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST12MAPFLOAT_H
#define TEST12MAPFLOAT_H

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"

#include <map>

#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test12MapFloat : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test12MapFloat();

		Test12MapFloat(
		const map<float, bool> &val0, 
		const map<float, char> &val1, 
		const map<float, int32_t> &val2, 
		const map<float, uint32_t> &val3, 
		const map<float, float> &val4, 
		const map<float, double> &val5, 
		const map<float, std::string> &val6
		);

		virtual ~Test12MapFloat();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test12MapFloat(const Test12MapFloat &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test12MapFloat& operator=(const Test12MapFloat &obj);

	public:
		/**
		 * @return myFloatBoolMap.
		 */
		std::map<float, bool> getMapOfMyFloatBoolMap() const;
	
		/**
		 * This method sets myFloatBoolMap.
		 *
		 * @param val Value for myFloatBoolMap.
		 */
		void setMapOfMyFloatBoolMap(const std::map<float, bool> &val);
	
		/**
		 * This method clears the map of myFloatBoolMap.
		 */
		void clear_MapOfMyFloatBoolMap();
	
		/**
		 * @return the size of the map of myFloatBoolMap.
		 */
		uint32_t getSize_MapOfMyFloatBoolMap() const;
	
		/**
		 * @return true if the map of myFloatBoolMap is empty.
		 */
		bool isEmpty_MapOfMyFloatBoolMap() const;
	
		/**
		 * This method adds an element to the map of myFloatBoolMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myFloatBoolMap.
		 * @param val Value of the key/value pair to be added to the map of myFloatBoolMap.
		 */
		void putTo_MapOfMyFloatBoolMap(const float &key, const bool &val);
	
		/**
		 * @return true if the map of myFloatBoolMap is contains the given key.
		 */
		bool containsKey_MapOfMyFloatBoolMap(const float &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myFloatBoolMap.
		 * @return Value to given key from the map of myFloatBoolMap is contains the given key.
		 */
		bool getValueForKey_MapOfMyFloatBoolMap(const float &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myFloatBoolMap.
		 */
		std::pair<std::map<float, bool>::iterator, std::map<float, bool>::iterator> iteratorPair_MapOfMyFloatBoolMap();
	public:
		/**
		 * @return myFloatCharMap.
		 */
		std::map<float, char> getMapOfMyFloatCharMap() const;
	
		/**
		 * This method sets myFloatCharMap.
		 *
		 * @param val Value for myFloatCharMap.
		 */
		void setMapOfMyFloatCharMap(const std::map<float, char> &val);
	
		/**
		 * This method clears the map of myFloatCharMap.
		 */
		void clear_MapOfMyFloatCharMap();
	
		/**
		 * @return the size of the map of myFloatCharMap.
		 */
		uint32_t getSize_MapOfMyFloatCharMap() const;
	
		/**
		 * @return true if the map of myFloatCharMap is empty.
		 */
		bool isEmpty_MapOfMyFloatCharMap() const;
	
		/**
		 * This method adds an element to the map of myFloatCharMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myFloatCharMap.
		 * @param val Value of the key/value pair to be added to the map of myFloatCharMap.
		 */
		void putTo_MapOfMyFloatCharMap(const float &key, const char &val);
	
		/**
		 * @return true if the map of myFloatCharMap is contains the given key.
		 */
		bool containsKey_MapOfMyFloatCharMap(const float &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myFloatCharMap.
		 * @return Value to given key from the map of myFloatCharMap is contains the given key.
		 */
		char getValueForKey_MapOfMyFloatCharMap(const float &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myFloatCharMap.
		 */
		std::pair<std::map<float, char>::iterator, std::map<float, char>::iterator> iteratorPair_MapOfMyFloatCharMap();
	public:
		/**
		 * @return myFloatInt32Map.
		 */
		std::map<float, int32_t> getMapOfMyFloatInt32Map() const;
	
		/**
		 * This method sets myFloatInt32Map.
		 *
		 * @param val Value for myFloatInt32Map.
		 */
		void setMapOfMyFloatInt32Map(const std::map<float, int32_t> &val);
	
		/**
		 * This method clears the map of myFloatInt32Map.
		 */
		void clear_MapOfMyFloatInt32Map();
	
		/**
		 * @return the size of the map of myFloatInt32Map.
		 */
		uint32_t getSize_MapOfMyFloatInt32Map() const;
	
		/**
		 * @return true if the map of myFloatInt32Map is empty.
		 */
		bool isEmpty_MapOfMyFloatInt32Map() const;
	
		/**
		 * This method adds an element to the map of myFloatInt32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myFloatInt32Map.
		 * @param val Value of the key/value pair to be added to the map of myFloatInt32Map.
		 */
		void putTo_MapOfMyFloatInt32Map(const float &key, const int32_t &val);
	
		/**
		 * @return true if the map of myFloatInt32Map is contains the given key.
		 */
		bool containsKey_MapOfMyFloatInt32Map(const float &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myFloatInt32Map.
		 * @return Value to given key from the map of myFloatInt32Map is contains the given key.
		 */
		int32_t getValueForKey_MapOfMyFloatInt32Map(const float &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myFloatInt32Map.
		 */
		std::pair<std::map<float, int32_t>::iterator, std::map<float, int32_t>::iterator> iteratorPair_MapOfMyFloatInt32Map();
	public:
		/**
		 * @return myFloatUint32Map.
		 */
		std::map<float, uint32_t> getMapOfMyFloatUint32Map() const;
	
		/**
		 * This method sets myFloatUint32Map.
		 *
		 * @param val Value for myFloatUint32Map.
		 */
		void setMapOfMyFloatUint32Map(const std::map<float, uint32_t> &val);
	
		/**
		 * This method clears the map of myFloatUint32Map.
		 */
		void clear_MapOfMyFloatUint32Map();
	
		/**
		 * @return the size of the map of myFloatUint32Map.
		 */
		uint32_t getSize_MapOfMyFloatUint32Map() const;
	
		/**
		 * @return true if the map of myFloatUint32Map is empty.
		 */
		bool isEmpty_MapOfMyFloatUint32Map() const;
	
		/**
		 * This method adds an element to the map of myFloatUint32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myFloatUint32Map.
		 * @param val Value of the key/value pair to be added to the map of myFloatUint32Map.
		 */
		void putTo_MapOfMyFloatUint32Map(const float &key, const uint32_t &val);
	
		/**
		 * @return true if the map of myFloatUint32Map is contains the given key.
		 */
		bool containsKey_MapOfMyFloatUint32Map(const float &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myFloatUint32Map.
		 * @return Value to given key from the map of myFloatUint32Map is contains the given key.
		 */
		uint32_t getValueForKey_MapOfMyFloatUint32Map(const float &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myFloatUint32Map.
		 */
		std::pair<std::map<float, uint32_t>::iterator, std::map<float, uint32_t>::iterator> iteratorPair_MapOfMyFloatUint32Map();
	public:
		/**
		 * @return myFloatFloatMap.
		 */
		std::map<float, float> getMapOfMyFloatFloatMap() const;
	
		/**
		 * This method sets myFloatFloatMap.
		 *
		 * @param val Value for myFloatFloatMap.
		 */
		void setMapOfMyFloatFloatMap(const std::map<float, float> &val);
	
		/**
		 * This method clears the map of myFloatFloatMap.
		 */
		void clear_MapOfMyFloatFloatMap();
	
		/**
		 * @return the size of the map of myFloatFloatMap.
		 */
		uint32_t getSize_MapOfMyFloatFloatMap() const;
	
		/**
		 * @return true if the map of myFloatFloatMap is empty.
		 */
		bool isEmpty_MapOfMyFloatFloatMap() const;
	
		/**
		 * This method adds an element to the map of myFloatFloatMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myFloatFloatMap.
		 * @param val Value of the key/value pair to be added to the map of myFloatFloatMap.
		 */
		void putTo_MapOfMyFloatFloatMap(const float &key, const float &val);
	
		/**
		 * @return true if the map of myFloatFloatMap is contains the given key.
		 */
		bool containsKey_MapOfMyFloatFloatMap(const float &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myFloatFloatMap.
		 * @return Value to given key from the map of myFloatFloatMap is contains the given key.
		 */
		float getValueForKey_MapOfMyFloatFloatMap(const float &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myFloatFloatMap.
		 */
		std::pair<std::map<float, float>::iterator, std::map<float, float>::iterator> iteratorPair_MapOfMyFloatFloatMap();
	public:
		/**
		 * @return myFloatDoubleMap.
		 */
		std::map<float, double> getMapOfMyFloatDoubleMap() const;
	
		/**
		 * This method sets myFloatDoubleMap.
		 *
		 * @param val Value for myFloatDoubleMap.
		 */
		void setMapOfMyFloatDoubleMap(const std::map<float, double> &val);
	
		/**
		 * This method clears the map of myFloatDoubleMap.
		 */
		void clear_MapOfMyFloatDoubleMap();
	
		/**
		 * @return the size of the map of myFloatDoubleMap.
		 */
		uint32_t getSize_MapOfMyFloatDoubleMap() const;
	
		/**
		 * @return true if the map of myFloatDoubleMap is empty.
		 */
		bool isEmpty_MapOfMyFloatDoubleMap() const;
	
		/**
		 * This method adds an element to the map of myFloatDoubleMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myFloatDoubleMap.
		 * @param val Value of the key/value pair to be added to the map of myFloatDoubleMap.
		 */
		void putTo_MapOfMyFloatDoubleMap(const float &key, const double &val);
	
		/**
		 * @return true if the map of myFloatDoubleMap is contains the given key.
		 */
		bool containsKey_MapOfMyFloatDoubleMap(const float &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myFloatDoubleMap.
		 * @return Value to given key from the map of myFloatDoubleMap is contains the given key.
		 */
		double getValueForKey_MapOfMyFloatDoubleMap(const float &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myFloatDoubleMap.
		 */
		std::pair<std::map<float, double>::iterator, std::map<float, double>::iterator> iteratorPair_MapOfMyFloatDoubleMap();
	public:
		/**
		 * @return myFloatStringMap.
		 */
		std::map<float, std::string> getMapOfMyFloatStringMap() const;
	
		/**
		 * This method sets myFloatStringMap.
		 *
		 * @param val Value for myFloatStringMap.
		 */
		void setMapOfMyFloatStringMap(const std::map<float, std::string> &val);
	
		/**
		 * This method clears the map of myFloatStringMap.
		 */
		void clear_MapOfMyFloatStringMap();
	
		/**
		 * @return the size of the map of myFloatStringMap.
		 */
		uint32_t getSize_MapOfMyFloatStringMap() const;
	
		/**
		 * @return true if the map of myFloatStringMap is empty.
		 */
		bool isEmpty_MapOfMyFloatStringMap() const;
	
		/**
		 * This method adds an element to the map of myFloatStringMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myFloatStringMap.
		 * @param val Value of the key/value pair to be added to the map of myFloatStringMap.
		 */
		void putTo_MapOfMyFloatStringMap(const float &key, const std::string &val);
	
		/**
		 * @return true if the map of myFloatStringMap is contains the given key.
		 */
		bool containsKey_MapOfMyFloatStringMap(const float &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myFloatStringMap.
		 * @return Value to given key from the map of myFloatStringMap is contains the given key.
		 */
		std::string getValueForKey_MapOfMyFloatStringMap(const float &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myFloatStringMap.
		 */
		std::pair<std::map<float, std::string>::iterator, std::map<float, std::string>::iterator> iteratorPair_MapOfMyFloatStringMap();

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
		std::map<float, bool> m_mapOfMyFloatBoolMap;
	private:
		std::map<float, char> m_mapOfMyFloatCharMap;
	private:
		std::map<float, int32_t> m_mapOfMyFloatInt32Map;
	private:
		std::map<float, uint32_t> m_mapOfMyFloatUint32Map;
	private:
		std::map<float, float> m_mapOfMyFloatFloatMap;
	private:
		std::map<float, double> m_mapOfMyFloatDoubleMap;
	private:
		std::map<float, std::string> m_mapOfMyFloatStringMap;

};

#endif /*TEST12MAPFLOAT_H*/
