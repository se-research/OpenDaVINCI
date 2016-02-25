/*
 * This software is open source. Please see COPYING and AUTHORS for further information.
 *
 * This file is auto-generated. DO NOT CHANGE AS YOUR CHANGES MIGHT BE OVERWRITTEN!
 */

#ifndef TESTPACKAGE_TEST8A_H
#define TESTPACKAGE_TEST8A_H

#include "opendavinci/odcore/opendavinci.h"


#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/data/SerializableData.h"


namespace testpackage {
	using namespace std;
	
	class Test8A : public odcore::data::SerializableData, public odcore::base::Visitable {
		public:
			Test8A();
	
			Test8A(
			const uint32_t &val0
			);
	
			virtual ~Test8A();
	
			/**
			 * Copy constructor.
			 *
			 * @param obj Reference to an object of this class.
			 */
			Test8A(const Test8A &obj);
	
			/**
			 * Assignment operator.
			 *
			 * @param obj Reference to an object of this class.
			 * @return Reference to this instance.
			 */
			Test8A& operator=(const Test8A &obj);
	
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
			virtual void accept(odcore::base::Visitor &v);
	
			virtual ostream& operator<<(ostream &out) const;
			virtual istream& operator>>(istream &in);
	
			virtual const string toString() const;
	
		private:
			uint32_t m_attribute1;
	
	};
} // testpackage

#endif /*TESTPACKAGE_TEST8A_H*/
