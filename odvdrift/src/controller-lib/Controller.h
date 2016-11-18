/*
 * Controller.h
 *
 *  Created on: Nov 16, 2016
 *      Author: evgeny
 */

#ifndef SRC_CONTROLLER_LIB_CONTROLLER_H_
#define SRC_CONTROLLER_LIB_CONTROLLER_H_

class Controller {
public:
	Controller(float timestep);
	virtual ~Controller();
	virtual float compute(float error) = 0;
protected:
	float timestep;
};

#endif /* SRC_CONTROLLER_LIB_CONTROLLER_H_ */
