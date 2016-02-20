/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11MAPBOOL_H
#define TEST11MAPBOOL_H

#include "opendavinci/core/opendavinci.h"

#include <map>

#include "opendavinci/core/base/Visitable.h"
#include "opendavinci/core/data/SerializableData.h"


using namespace std;

class Test11MapBool : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test11MapBool();

		Test11MapBool(
		const map<bool, bool> &val0, 
		const map<bool, char> &val1, 
		const map<bool, int32_t> &val2, 
		const map<bool, uint32_t> &val3, 
		const map<bool, float> &val4, 
		const map<bool, double> &val5, 
		const map<bool, std::string> &val6
		);

		virtual ~Test11MapBool();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test11MapBool(const Test11MapBool &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test11MapBool& operator=(const Test11MapBool &obj);

	public:
		/**
		 * @return myBoolBoolMap.
		 */
		std::map<bool, bool> getMapOfMyBoolBoolMap() const;
	
		/**
		 * This method sets myBoolBoolMap.
		 *
		 * @param val Value for myBoolBoolMap.
		 */
		void setMapOfMyBoolBoolMap(const std::map<bool, bool> &val);
	
		/**
		 * This method clears the map of myBoolBoolMap.
		 */
		void clear_MapOfMyBoolBoolMap();
	
		/**
		 * @return the size of the map of myBoolBoolMap.
		 */
		uint32_t getSize_MapOfMyBoolBoolMap() const;
	
		/**
		 * @return true if the map of myBoolBoolMap is empty.
		 */
		bool isEmpty_MapOfMyBoolBoolMap() const;
	
		/**
		 * This method adds an element to the map of myBoolBoolMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myBoolBoolMap.
		 * @param val Value of the key/value pair to be added to the map of myBoolBoolMap.
		 */
		void putTo_MapOfMyBoolBoolMap(const bool &key, const bool &val);
	
		/**
		 * @return true if the map of myBoolBoolMap is contains the given key.
		 */
		bool containsKey_MapOfMyBoolBoolMap(const bool &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myBoolBoolMap.
		 * @return Value to given key from the map of myBoolBoolMap is contains the given key.
		 */
		bool getValueForKey_MapOfMyBoolBoolMap(const bool &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myBoolBoolMap.
		 */
		std::pair<std::map<bool, bool>::iterator, std::map<bool, bool>::iterator> iteratorPair_MapOfMyBoolBoolMap();
	public:
		/**
		 * @return myBoolCharMap.
		 */
		std::map<bool, char> getMapOfMyBoolCharMap() const;
	
		/**
		 * This method sets myBoolCharMap.
		 *
		 * @param val Value for myBoolCharMap.
		 */
		void setMapOfMyBoolCharMap(const std::map<bool, char> &val);
	
		/**
		 * This method clears the map of myBoolCharMap.
		 */
		void clear_MapOfMyBoolCharMap();
	
		/**
		 * @return the size of the map of myBoolCharMap.
		 */
		uint32_t getSize_MapOfMyBoolCharMap() const;
	
		/**
		 * @return true if the map of myBoolCharMap is empty.
		 */
		bool isEmpty_MapOfMyBoolCharMap() const;
	
		/**
		 * This method adds an element to the map of myBoolCharMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myBoolCharMap.
		 * @param val Value of the key/value pair to be added to the map of myBoolCharMap.
		 */
		void putTo_MapOfMyBoolCharMap(const bool &key, const char &val);
	
		/**
		 * @return true if the map of myBoolCharMap is contains the given key.
		 */
		bool containsKey_MapOfMyBoolCharMap(const bool &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myBoolCharMap.
		 * @return Value to given key from the map of myBoolCharMap is contains the given key.
		 */
		char getValueForKey_MapOfMyBoolCharMap(const bool &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myBoolCharMap.
		 */
		std::pair<std::map<bool, char>::iterator, std::map<bool, char>::iterator> iteratorPair_MapOfMyBoolCharMap();
	public:
		/**
		 * @return myBoolInt32Map.
		 */
		std::map<bool, int32_t> getMapOfMyBoolInt32Map() const;
	
		/**
		 * This method sets myBoolInt32Map.
		 *
		 * @param val Value for myBoolInt32Map.
		 */
		void setMapOfMyBoolInt32Map(const std::map<bool, int32_t> &val);
	
		/**
		 * This method clears the map of myBoolInt32Map.
		 */
		void clear_MapOfMyBoolInt32Map();
	
		/**
		 * @return the size of the map of myBoolInt32Map.
		 */
		uint32_t getSize_MapOfMyBoolInt32Map() const;
	
		/**
		 * @return true if the map of myBoolInt32Map is empty.
		 */
		bool isEmpty_MapOfMyBoolInt32Map() const;
	
		/**
		 * This method adds an element to the map of myBoolInt32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myBoolInt32Map.
		 * @param val Value of the key/value pair to be added to the map of myBoolInt32Map.
		 */
		void putTo_MapOfMyBoolInt32Map(const bool &key, const int32_t &val);
	
		/**
		 * @return true if the map of myBoolInt32Map is contains the given key.
		 */
		bool containsKey_MapOfMyBoolInt32Map(const bool &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myBoolInt32Map.
		 * @return Value to given key from the map of myBoolInt32Map is contains the given key.
		 */
		int32_t getValueForKey_MapOfMyBoolInt32Map(const bool &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myBoolInt32Map.
		 */
		std::pair<std::map<bool, int32_t>::iterator, std::map<bool, int32_t>::iterator> iteratorPair_MapOfMyBoolInt32Map();
	public:
		/**
		 * @return myBoolUint32Map.
		 */
		std::map<bool, uint32_t> getMapOfMyBoolUint32Map() const;
	
		/**
		 * This method sets myBoolUint32Map.
		 *
		 * @param val Value for myBoolUint32Map.
		 */
		void setMapOfMyBoolUint32Map(const std::map<bool, uint32_t> &val);
	
		/**
		 * This method clears the map of myBoolUint32Map.
		 */
		void clear_MapOfMyBoolUint32Map();
	
		/**
		 * @return the size of the map of myBoolUint32Map.
		 */
		uint32_t getSize_MapOfMyBoolUint32Map() const;
	
		/**
		 * @return true if the map of myBoolUint32Map is empty.
		 */
		bool isEmpty_MapOfMyBoolUint32Map() const;
	
		/**
		 * This method adds an element to the map of myBoolUint32Map.
		 *
		 * @param key Key of the key/value pair to be added to the map of myBoolUint32Map.
		 * @param val Value of the key/value pair to be added to the map of myBoolUint32Map.
		 */
		void putTo_MapOfMyBoolUint32Map(const bool &key, const uint32_t &val);
	
		/**
		 * @return true if the map of myBoolUint32Map is contains the given key.
		 */
		bool containsKey_MapOfMyBoolUint32Map(const bool &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myBoolUint32Map.
		 * @return Value to given key from the map of myBoolUint32Map is contains the given key.
		 */
		uint32_t getValueForKey_MapOfMyBoolUint32Map(const bool &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myBoolUint32Map.
		 */
		std::pair<std::map<bool, uint32_t>::iterator, std::map<bool, uint32_t>::iterator> iteratorPair_MapOfMyBoolUint32Map();
	public:
		/**
		 * @return myBoolFloatMap.
		 */
		std::map<bool, float> getMapOfMyBoolFloatMap() const;
	
		/**
		 * This method sets myBoolFloatMap.
		 *
		 * @param val Value for myBoolFloatMap.
		 */
		void setMapOfMyBoolFloatMap(const std::map<bool, float> &val);
	
		/**
		 * This method clears the map of myBoolFloatMap.
		 */
		void clear_MapOfMyBoolFloatMap();
	
		/**
		 * @return the size of the map of myBoolFloatMap.
		 */
		uint32_t getSize_MapOfMyBoolFloatMap() const;
	
		/**
		 * @return true if the map of myBoolFloatMap is empty.
		 */
		bool isEmpty_MapOfMyBoolFloatMap() const;
	
		/**
		 * This method adds an element to the map of myBoolFloatMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myBoolFloatMap.
		 * @param val Value of the key/value pair to be added to the map of myBoolFloatMap.
		 */
		void putTo_MapOfMyBoolFloatMap(const bool &key, const float &val);
	
		/**
		 * @return true if the map of myBoolFloatMap is contains the given key.
		 */
		bool containsKey_MapOfMyBoolFloatMap(const bool &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myBoolFloatMap.
		 * @return Value to given key from the map of myBoolFloatMap is contains the given key.
		 */
		float getValueForKey_MapOfMyBoolFloatMap(const bool &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myBoolFloatMap.
		 */
		std::pair<std::map<bool, float>::iterator, std::map<bool, float>::iterator> iteratorPair_MapOfMyBoolFloatMap();
	public:
		/**
		 * @return myBoolDoubleMap.
		 */
		std::map<bool, double> getMapOfMyBoolDoubleMap() const;
	
		/**
		 * This method sets myBoolDoubleMap.
		 *
		 * @param val Value for myBoolDoubleMap.
		 */
		void setMapOfMyBoolDoubleMap(const std::map<bool, double> &val);
	
		/**
		 * This method clears the map of myBoolDoubleMap.
		 */
		void clear_MapOfMyBoolDoubleMap();
	
		/**
		 * @return the size of the map of myBoolDoubleMap.
		 */
		uint32_t getSize_MapOfMyBoolDoubleMap() const;
	
		/**
		 * @return true if the map of myBoolDoubleMap is empty.
		 */
		bool isEmpty_MapOfMyBoolDoubleMap() const;
	
		/**
		 * This method adds an element to the map of myBoolDoubleMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myBoolDoubleMap.
		 * @param val Value of the key/value pair to be added to the map of myBoolDoubleMap.
		 */
		void putTo_MapOfMyBoolDoubleMap(const bool &key, const double &val);
	
		/**
		 * @return true if the map of myBoolDoubleMap is contains the given key.
		 */
		bool containsKey_MapOfMyBoolDoubleMap(const bool &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myBoolDoubleMap.
		 * @return Value to given key from the map of myBoolDoubleMap is contains the given key.
		 */
		double getValueForKey_MapOfMyBoolDoubleMap(const bool &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myBoolDoubleMap.
		 */
		std::pair<std::map<bool, double>::iterator, std::map<bool, double>::iterator> iteratorPair_MapOfMyBoolDoubleMap();
	public:
		/**
		 * @return myBoolStringMap.
		 */
		std::map<bool, std::string> getMapOfMyBoolStringMap() const;
	
		/**
		 * This method sets myBoolStringMap.
		 *
		 * @param val Value for myBoolStringMap.
		 */
		void setMapOfMyBoolStringMap(const std::map<bool, std::string> &val);
	
		/**
		 * This method clears the map of myBoolStringMap.
		 */
		void clear_MapOfMyBoolStringMap();
	
		/**
		 * @return the size of the map of myBoolStringMap.
		 */
		uint32_t getSize_MapOfMyBoolStringMap() const;
	
		/**
		 * @return true if the map of myBoolStringMap is empty.
		 */
		bool isEmpty_MapOfMyBoolStringMap() const;
	
		/**
		 * This method adds an element to the map of myBoolStringMap.
		 *
		 * @param key Key of the key/value pair to be added to the map of myBoolStringMap.
		 * @param val Value of the key/value pair to be added to the map of myBoolStringMap.
		 */
		void putTo_MapOfMyBoolStringMap(const bool &key, const std::string &val);
	
		/**
		 * @return true if the map of myBoolStringMap is contains the given key.
		 */
		bool containsKey_MapOfMyBoolStringMap(const bool &key) const;
	
		/**
		 * This method returns the value to the given key. Make sure to check if the given key exists otherwise a new key/value pair will be added (cf. C++ standard).
		 *
		 * @param key Key for which the value should be returned from the map of myBoolStringMap.
		 * @return Value to given key from the map of myBoolStringMap is contains the given key.
		 */
		std::string getValueForKey_MapOfMyBoolStringMap(const bool &key);
	
		/**
		 * @return Pair of iterators for the begin and end of the map of myBoolStringMap.
		 */
		std::pair<std::map<bool, std::string>::iterator, std::map<bool, std::string>::iterator> iteratorPair_MapOfMyBoolStringMap();

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
		std::map<bool, bool> m_mapOfMyBoolBoolMap;
	private:
		std::map<bool, char> m_mapOfMyBoolCharMap;
	private:
		std::map<bool, int32_t> m_mapOfMyBoolInt32Map;
	private:
		std::map<bool, uint32_t> m_mapOfMyBoolUint32Map;
	private:
		std::map<bool, float> m_mapOfMyBoolFloatMap;
	private:
		std::map<bool, double> m_mapOfMyBoolDoubleMap;
	private:
		std::map<bool, std::string> m_mapOfMyBoolStringMap;

};

#endif /*TEST11MAPBOOL_H*/
