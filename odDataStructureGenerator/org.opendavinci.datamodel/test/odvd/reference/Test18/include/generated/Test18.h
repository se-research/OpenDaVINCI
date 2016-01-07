/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST18_H
#define TEST18_H

#include "core/opendavinci.h"


#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test18 : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test18();

		Test18(
		const uint32_t *val0, 
		const float *val1, 
		const uint32_t &val2, 
		const uint32_t &val3, 
		const uint32_t &val4
		);

		virtual ~Test18();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test18(const Test18 &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test18& operator=(const Test18 &obj);

	public:
		/**
		 * @return myArray1.
		 */
		uint32_t* getMyArray1();
		
		/**
		 * This method gets the size of the fixed size array myArray1.
		 *
		 * @return Size of the fixed size array myArray1.
		 */
		uint32_t getSize_MyArray1() const;
	public:
		/**
		 * @return myArray2.
		 */
		float* getMyArray2();
		
		/**
		 * This method gets the size of the fixed size array myArray2.
		 *
		 * @return Size of the fixed size array myArray2.
		 */
		uint32_t getSize_MyArray2() const;
	public:
		/**
		 * @return myAtt1.
		 */
		uint32_t getMyAtt1() const;
		
		/**
		 * This method sets myAtt1.
		 *
		 * @param val Value for myAtt1.
		 */
		void setMyAtt1(const uint32_t &val);
	public:
		/**
		 * @return myAtt2.
		 */
		uint32_t getMyAtt2() const;
		
		/**
		 * This method sets myAtt2.
		 *
		 * @param val Value for myAtt2.
		 */
		void setMyAtt2(const uint32_t &val);
	public:
		/**
		 * @return myAtt3.
		 */
		uint32_t getMyAtt3() const;
		
		/**
		 * This method sets myAtt3.
		 *
		 * @param val Value for myAtt3.
		 */
		void setMyAtt3(const uint32_t &val);

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
		uint32_t* m_myArray1;
	private:
		float* m_myArray2;
	private:
		uint32_t m_myAtt1;
	private:
		uint32_t m_myAtt2;
	private:
		uint32_t m_myAtt3;

};

#endif /*TEST18_H*/
