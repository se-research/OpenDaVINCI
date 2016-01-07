/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST2_H
#define TEST2_H

#include "core/opendavinci.h"


#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test2 : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test2();

		Test2(
		const uint32_t &val0
		);

		virtual ~Test2();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test2(const Test2 &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test2& operator=(const Test2 &obj);

	public:
		/**
		 * @return attribute1.
		 */
		uint32_t getAttribute1() const;
		
		/**
		 * This method sets attribute1.
		 *
		 * @param val Value for attribute1.
		 */
		void setAttribute1(const uint32_t &val);

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
		uint32_t m_attribute1;

};

#endif /*TEST2_H*/
