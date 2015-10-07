/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST10POINT_H
#define TEST10POINT_H

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"


#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test10Point : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test10Point();

		Test10Point(
		const float &val0, 
		const float &val1
		);

		virtual ~Test10Point();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test10Point(const Test10Point &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test10Point& operator=(const Test10Point &obj);

	public:
		/**
		 * @return x.
		 */
		float getX() const;
		
		/**
		 * This method sets x.
		 *
		 * @param val Value for x.
		 */
		void setX(const float &val);
	public:
		/**
		 * @return y.
		 */
		float getY() const;
		
		/**
		 * This method sets y.
		 *
		 * @param val Value for y.
		 */
		void setY(const float &val);

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
		float m_x;
	private:
		float m_y;

};

#endif /*TEST10POINT_H*/
