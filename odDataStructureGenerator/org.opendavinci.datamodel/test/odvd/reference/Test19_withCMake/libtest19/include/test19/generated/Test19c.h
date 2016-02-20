/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST19C_H
#define TEST19C_H

#include "opendavinci/odcore/opendavinci.h"


#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/data/SerializableData.h"


using namespace std;

class Test19c : public odcore::data::SerializableData, public odcore::base::Visitable {
	public:
		enum ButtonState {
			PRESSED = 1,
			UNDEFINED = -1,
			NOT_PRESSED = 0,
		};
	public:
		Test19c();


		virtual ~Test19c();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test19c(const Test19c &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test19c& operator=(const Test19c &obj);

	public:
	public:
	public:

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
		virtual void accept(odcore::base::Visitor &v);

		virtual ostream& operator<<(ostream &out) const;
		virtual istream& operator>>(istream &in);

		virtual const string toString() const;

	private:
	private:
	private:

public:
	static const uint32_t MAGIC_NUMBER;
public:
	static const float PI;
public:
};

#endif /*TEST19C_H*/
