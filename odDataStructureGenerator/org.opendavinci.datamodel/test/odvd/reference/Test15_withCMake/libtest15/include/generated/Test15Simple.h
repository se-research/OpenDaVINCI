/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST15SIMPLE_H
#define TEST15SIMPLE_H

// core/opendavinci.h must be included to setup platform-dependent header files and configurations.
#include "core/opendavinci.h"


#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


using namespace std;

class Test15Simple : public core::data::SerializableData, public core::base::Visitable {
	public:
		enum ButtonState {
			PRESSED = 1,
			UNDEFINED = -1,
			NOT_PRESSED = 0,
		};
	public:
		Test15Simple();

		Test15Simple(
		const ButtonState &val0
		);

		virtual ~Test15Simple();

		/**
		 * Copy constructor.
		 *
		 * @param obj Reference to an object of this class.
		 */
		Test15Simple(const Test15Simple &obj);

		/**
		 * Assignment operator.
		 *
		 * @param obj Reference to an object of this class.
		 * @return Reference to this instance.
		 */
		Test15Simple& operator=(const Test15Simple &obj);

	public:
	public:
		/**
		 * @return buttonState.
		 */
		ButtonState getButtonState() const;
		
		/**
		 * This method sets buttonState.
		 *
		 * @param val Value for buttonState.
		 */
		void setButtonState(const ButtonState &val);

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
		ButtonState m_buttonState;

};

#endif /*TEST15SIMPLE_H*/
