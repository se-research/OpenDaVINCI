/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11MAPDOUBLE_H
#define TEST11MAPDOUBLE_H

#include "opendavinci/core/opendavinci.h"

#include <map>

#include "opendavinci/core/base/Visitable.h"
#include "opendavinci/core/data/SerializableData.h"


using namespace std;

class Test11MapDouble : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test11MapDouble();

		Test11MapDouble(
		const map<double, bool> &val0, 
		const map<double, char> &val1, 
		const map<double, int32_t> &val2, 
		const map<double, uint32_t> &val3, 
		const map<double, float> &val4, 
		const map<double, double> &val5, 
		const map<double, std::string> &val6
		);

		virtual ~Test11MapDouble();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test11MapDouble(const Test11MapDouble &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test11MapDouble& operator=(const Test11MapDouble &obj);

	public:
		/**
		 * @return myDoubleBoolMap.
		 */
		std::map<double, bool> getMapOfMyDoubleBoolMap() const;
	
		/**
		 * This method sets myDoubleBoolMap.
		 *
		 * @param val Value for myDoubleBoolMap.
		 */
		void setMapOfMyDoubleBoolMap(const std::map<double, bool> &val);
	
		/**
		 * This method clears the map of myDoubleBoolMap.
		 */
		void clear_MapOfMyDoubleBoolMap();
	
		/**
		 * @return the size of the map of myDoubleBoolMap.
		 */
		uint32_t getSize_MapOfMyDoubleBoolMap() const;
	
		/**
		 * @return true if the map of myDoubleBoolMap is empty.
		 */
		bool isEmpty_MapOfMyDoubleBoolMap() const;
	
		/**
		 * This method adds an element to the map of myDoubleBoolMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myDoubleBoolMap.
		 * @param val Value of the key/value pair to be added to the map of myDoubleBoolMap.
		 */
		void putTo_MapOfMyDoubleBoolMap(const double &key, const bool &val);
	
		/**
		 * @return true if the map of myDoubleBoolMap is contains the given key.
		 */
		bool containsKey_MapOfMyDoubleBoolMap(const double &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myDoubleBoolMap.
		 * @return Value to given key from the map of myDoubleBoolMap is contains the given key.
		 */
		bool getValueForKey_MapOfMyDoubleBoolMap(const double &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myDoubleBoolMap.
		 */
		std::pair<std::map<double, bool>::iterator, std::map<double, bool>::iterator> iteratorPair_MapOfMyDoubleBoolMap();
	public:
		/**
		 * @return myDoubleCharMap.
		 */
		std::map<double, char> getMapOfMyDoubleCharMap() const;
	
		/**
		 * This method sets myDoubleCharMap.
		 *
		 * @param val Value for myDoubleCharMap.
		 */
		void setMapOfMyDoubleCharMap(const std::map<double, char> &val);
	
		/**
		 * This method clears the map of myDoubleCharMap.
		 */
		void clear_MapOfMyDoubleCharMap();
	
		/**
		 * @return the size of the map of myDoubleCharMap.
		 */
		uint32_t getSize_MapOfMyDoubleCharMap() const;
	
		/**
		 * @return true if the map of myDoubleCharMap is empty.
		 */
		bool isEmpty_MapOfMyDoubleCharMap() const;
	
		/**
		 * This method adds an element to the map of myDoubleCharMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myDoubleCharMap.
		 * @param val Value of the key/value pair to be added to the map of myDoubleCharMap.
		 */
		void putTo_MapOfMyDoubleCharMap(const double &key, const char &val);
	
		/**
		 * @return true if the map of myDoubleCharMap is contains the given key.
		 */
		bool containsKey_MapOfMyDoubleCharMap(const double &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myDoubleCharMap.
		 * @return Value to given key from the map of myDoubleCharMap is contains the given key.
		 */
		char getValueForKey_MapOfMyDoubleCharMap(const double &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myDoubleCharMap.
		 */
		std::pair<std::map<double, char>::iterator, std::map<double, char>::iterator> iteratorPair_MapOfMyDoubleCharMap();
	public:
		/**
		 * @return myDoubleInt32Map.
		 */
		std::map<double, int32_t> getMapOfMyDoubleInt32Map() const;
	
		/**
		 * This method sets myDoubleInt32Map.
		 *
		 * @param val Value for myDoubleInt32Map.
		 */
		void setMapOfMyDoubleInt32Map(const std::map<double, int32_t> &val);
	
		/**
		 * This method clears the map of myDoubleInt32Map.
		 */
		void clear_MapOfMyDoubleInt32Map();
	
		/**
		 * @return the size of the map of myDoubleInt32Map.
		 */
		uint32_t getSize_MapOfMyDoubleInt32Map() const;
	
		/**
		 * @return true if the map of myDoubleInt32Map is empty.
		 */
		bool isEmpty_MapOfMyDoubleInt32Map() const;
	
		/**
		 * This method adds an element to the map of myDoubleInt32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myDoubleInt32Map.
		 * @param val Value of the key/value pair to be added to the map of myDoubleInt32Map.
		 */
		void putTo_MapOfMyDoubleInt32Map(const double &key, const int32_t &val);
	
		/**
		 * @return true if the map of myDoubleInt32Map is contains the given key.
		 */
		bool containsKey_MapOfMyDoubleInt32Map(const double &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myDoubleInt32Map.
		 * @return Value to given key from the map of myDoubleInt32Map is contains the given key.
		 */
		int32_t getValueForKey_MapOfMyDoubleInt32Map(const double &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myDoubleInt32Map.
		 */
		std::pair<std::map<double, int32_t>::iterator, std::map<double, int32_t>::iterator> iteratorPair_MapOfMyDoubleInt32Map();
	public:
		/**
		 * @return myDoubleUint32Map.
		 */
		std::map<double, uint32_t> getMapOfMyDoubleUint32Map() const;
	
		/**
		 * This method sets myDoubleUint32Map.
		 *
		 * @param val Value for myDoubleUint32Map.
		 */
		void setMapOfMyDoubleUint32Map(const std::map<double, uint32_t> &val);
	
		/**
		 * This method clears the map of myDoubleUint32Map.
		 */
		void clear_MapOfMyDoubleUint32Map();
	
		/**
		 * @return the size of the map of myDoubleUint32Map.
		 */
		uint32_t getSize_MapOfMyDoubleUint32Map() const;
	
		/**
		 * @return true if the map of myDoubleUint32Map is empty.
		 */
		bool isEmpty_MapOfMyDoubleUint32Map() const;
	
		/**
		 * This method adds an element to the map of myDoubleUint32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myDoubleUint32Map.
		 * @param val Value of the key/value pair to be added to the map of myDoubleUint32Map.
		 */
		void putTo_MapOfMyDoubleUint32Map(const double &key, const uint32_t &val);
	
		/**
		 * @return true if the map of myDoubleUint32Map is contains the given key.
		 */
		bool containsKey_MapOfMyDoubleUint32Map(const double &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myDoubleUint32Map.
		 * @return Value to given key from the map of myDoubleUint32Map is contains the given key.
		 */
		uint32_t getValueForKey_MapOfMyDoubleUint32Map(const double &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myDoubleUint32Map.
		 */
		std::pair<std::map<double, uint32_t>::iterator, std::map<double, uint32_t>::iterator> iteratorPair_MapOfMyDoubleUint32Map();
	public:
		/**
		 * @return myDoubleFloatMap.
		 */
		std::map<double, float> getMapOfMyDoubleFloatMap() const;
	
		/**
		 * This method sets myDoubleFloatMap.
		 *
		 * @param val Value for myDoubleFloatMap.
		 */
		void setMapOfMyDoubleFloatMap(const std::map<double, float> &val);
	
		/**
		 * This method clears the map of myDoubleFloatMap.
		 */
		void clear_MapOfMyDoubleFloatMap();
	
		/**
		 * @return the size of the map of myDoubleFloatMap.
		 */
		uint32_t getSize_MapOfMyDoubleFloatMap() const;
	
		/**
		 * @return true if the map of myDoubleFloatMap is empty.
		 */
		bool isEmpty_MapOfMyDoubleFloatMap() const;
	
		/**
		 * This method adds an element to the map of myDoubleFloatMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myDoubleFloatMap.
		 * @param val Value of the key/value pair to be added to the map of myDoubleFloatMap.
		 */
		void putTo_MapOfMyDoubleFloatMap(const double &key, const float &val);
	
		/**
		 * @return true if the map of myDoubleFloatMap is contains the given key.
		 */
		bool containsKey_MapOfMyDoubleFloatMap(const double &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myDoubleFloatMap.
		 * @return Value to given key from the map of myDoubleFloatMap is contains the given key.
		 */
		float getValueForKey_MapOfMyDoubleFloatMap(const double &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myDoubleFloatMap.
		 */
		std::pair<std::map<double, float>::iterator, std::map<double, float>::iterator> iteratorPair_MapOfMyDoubleFloatMap();
	public:
		/**
		 * @return myDoubleDoubleMap.
		 */
		std::map<double, double> getMapOfMyDoubleDoubleMap() const;
	
		/**
		 * This method sets myDoubleDoubleMap.
		 *
		 * @param val Value for myDoubleDoubleMap.
		 */
		void setMapOfMyDoubleDoubleMap(const std::map<double, double> &val);
	
		/**
		 * This method clears the map of myDoubleDoubleMap.
		 */
		void clear_MapOfMyDoubleDoubleMap();
	
		/**
		 * @return the size of the map of myDoubleDoubleMap.
		 */
		uint32_t getSize_MapOfMyDoubleDoubleMap() const;
	
		/**
		 * @return true if the map of myDoubleDoubleMap is empty.
		 */
		bool isEmpty_MapOfMyDoubleDoubleMap() const;
	
		/**
		 * This method adds an element to the map of myDoubleDoubleMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myDoubleDoubleMap.
		 * @param val Value of the key/value pair to be added to the map of myDoubleDoubleMap.
		 */
		void putTo_MapOfMyDoubleDoubleMap(const double &key, const double &val);
	
		/**
		 * @return true if the map of myDoubleDoubleMap is contains the given key.
		 */
		bool containsKey_MapOfMyDoubleDoubleMap(const double &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myDoubleDoubleMap.
		 * @return Value to given key from the map of myDoubleDoubleMap is contains the given key.
		 */
		double getValueForKey_MapOfMyDoubleDoubleMap(const double &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myDoubleDoubleMap.
		 */
		std::pair<std::map<double, double>::iterator, std::map<double, double>::iterator> iteratorPair_MapOfMyDoubleDoubleMap();
	public:
		/**
		 * @return myDoubleStringMap.
		 */
		std::map<double, std::string> getMapOfMyDoubleStringMap() const;
	
		/**
		 * This method sets myDoubleStringMap.
		 *
		 * @param val Value for myDoubleStringMap.
		 */
		void setMapOfMyDoubleStringMap(const std::map<double, std::string> &val);
	
		/**
		 * This method clears the map of myDoubleStringMap.
		 */
		void clear_MapOfMyDoubleStringMap();
	
		/**
		 * @return the size of the map of myDoubleStringMap.
		 */
		uint32_t getSize_MapOfMyDoubleStringMap() const;
	
		/**
		 * @return true if the map of myDoubleStringMap is empty.
		 */
		bool isEmpty_MapOfMyDoubleStringMap() const;
	
		/**
		 * This method adds an element to the map of myDoubleStringMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myDoubleStringMap.
		 * @param val Value of the key/value pair to be added to the map of myDoubleStringMap.
		 */
		void putTo_MapOfMyDoubleStringMap(const double &key, const std::string &val);
	
		/**
		 * @return true if the map of myDoubleStringMap is contains the given key.
		 */
		bool containsKey_MapOfMyDoubleStringMap(const double &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myDoubleStringMap.
		 * @return Value to given key from the map of myDoubleStringMap is contains the given key.
		 */
		std::string getValueForKey_MapOfMyDoubleStringMap(const double &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myDoubleStringMap.
		 */
		std::pair<std::map<double, std::string>::iterator, std::map<double, std::string>::iterator> iteratorPair_MapOfMyDoubleStringMap();

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
		virtual void accept(core::base::Visitor &v);

		virtual ostream& operator<<(ostream &out) const;
		virtual istream& operator>>(istream &in);

		virtual const string toString() const;

	private:
		std::map<double, bool> m_mapOfMyDoubleBoolMap;
	private:
		std::map<double, char> m_mapOfMyDoubleCharMap;
	private:
		std::map<double, int32_t> m_mapOfMyDoubleInt32Map;
	private:
		std::map<double, uint32_t> m_mapOfMyDoubleUint32Map;
	private:
		std::map<double, float> m_mapOfMyDoubleFloatMap;
	private:
		std::map<double, double> m_mapOfMyDoubleDoubleMap;
	private:
		std::map<double, std::string> m_mapOfMyDoubleStringMap;

};

#endif /*TEST11MAPDOUBLE_H*/
