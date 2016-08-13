/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TEST13_SUBPACKAGE_TEST13SIMPLE_H
#define TEST13_SUBPACKAGE_TEST13SIMPLE_H

#include "opendavinci/odcore/opendavinci.h"


#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/data/SerializableData.h"


namespace test13 {
	namespace subpackage {
		using namespace std;
		
		class OPENDAVINCI_API Test13Simple : public odcore::data::SerializableData, public odcore::base::Visitable {
			public:
				enum ButtonState {
					PRESSED = 1,
					UNDEFINED = -1,
					NOT_PRESSED = 0,
				};
			public:
				Test13Simple();
		
				Test13Simple(
				const ButtonState &val0
				);
		
				virtual ~Test13Simple();
		
				/**
				 * Copy constructor.
				 *
				 * @param obj Reference to an object of this class.
				 */
				Test13Simple(const Test13Simple &obj);
		
				/**
				 * Assignment operator.
				 *
				 * @param obj Reference to an object of this class.
				 * @return Reference to this instance.
				 */
				Test13Simple& operator=(const Test13Simple &obj);
		
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
				virtual void accept(odcore::base::Visitor &v);
		
				virtual ostream& operator<<(ostream &out) const;
				virtual istream& operator>>(istream &in);
		
				virtual const string toString() const;
		
			private:
			private:
				ButtonState m_buttonState;
		
		};
	} // subpackage
} // test13

#endif /*TEST13_SUBPACKAGE_TEST13SIMPLE_H*/
