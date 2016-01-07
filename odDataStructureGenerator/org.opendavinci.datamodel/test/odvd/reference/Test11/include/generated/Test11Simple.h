/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST11SIMPLE_H
#define TEST11SIMPLE_H

#include "core/opendavinci.h"


#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test11Simple : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test11Simple();

		Test11Simple(
		const uint32_t &val0, 
		const uint32_t &val1
		);

		virtual ~Test11Simple();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test11Simple(const Test11Simple &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test11Simple& operator=(const Test11Simple &obj);

	public:
		/**
		 * @return data1.
		 */
		uint32_t getData1() const;
		
		/**
		 * This method sets data1.
		 *
		 * @param val Value for data1.
		 */
		void setData1(const uint32_t &val);
	public:
		/**
		 * @return data2.
		 */
		uint32_t getData2() const;
		
		/**
		 * This method sets data2.
		 *
		 * @param val Value for data2.
		 */
		void setData2(const uint32_t &val);

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
		uint32_t m_data1;
	private:
		uint32_t m_data2;

};

#endif /*TEST11SIMPLE_H*/
