/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST20A_H
#define TEST20A_H

#include "core/opendavinci.h"


#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"

#include "core/data/TimeStamp.h"

using namespace std;

class Test20a : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test20a();

		Test20a(
		const uint32_t &val0, 
		const core::data::TimeStamp &val1
		);

		virtual ~Test20a();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test20a(const Test20a &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test20a& operator=(const Test20a &obj);

	public:
		/**
		 * @return val1.
		 */
		uint32_t getVal1() const;
		
		/**
		 * This method sets val1.
		 *
		 * @param val Value for val1.
		 */
		void setVal1(const uint32_t &val);
	public:
		/**
		 * @return timeStamp.
		 */
		core::data::TimeStamp getTimeStamp() const;
		
		/**
		 * This method sets timeStamp.
		 *
		 * @param val Value for timeStamp.
		 */
		void setTimeStamp(const core::data::TimeStamp &val);

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
		uint32_t m_val1;
	private:
		core::data::TimeStamp m_timeStamp;

};

#endif /*TEST20A_H*/
