/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST19A_H
#define TEST19A_H

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"


#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test19a : public core::data::SerializableData, public core::base::Visitable {
	public:
		Test19a();


		virtual ~Test19a();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test19a(const Test19a &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test19a& operator=(const Test19a &obj);

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

	public:
		virtual void accept(core::base::Visitor &v);

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
	static const std::string HELLOWORLD;
};

#endif /*TEST19A_H*/
