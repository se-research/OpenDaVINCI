/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef SUBPACKAGE_TEST14SIMPLE_H
#define SUBPACKAGE_TEST14SIMPLE_H

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"


#include "core/base/Visitable.h"
#include "core/data/SerializableData.h"


namespace subpackage {
	using namespace std;
	
	class Test14Simple : public core::data::SerializableData, public core::base::Visitable {
		public:
			enum ButtonState {
				PRESSED = 1,
				UNDEFINED = -1,
				NOT_PRESSED = 0,
			};
		public:
			Test14Simple();
	
			Test14Simple(
			const ButtonState &val0
			);
	
			virtual ~Test14Simple();
	
			/**
			 * Copy constructor.
			 *
			 * @param obj Reference to an object of this class.
			 */
			Test14Simple(const Test14Simple &obj);
	
			/**
			 * Assignment operator.
			 *
			 * @param obj Reference to an object of this class.
			 * @return Reference to this instance.
			 */
			Test14Simple& operator=(const Test14Simple &obj);
	
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
		private:
			ButtonState m_buttonState;
	
	};
} // subpackage

#endif /*SUBPACKAGE_TEST14SIMPLE_H*/
