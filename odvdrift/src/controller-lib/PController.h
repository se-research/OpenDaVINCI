/*
 * PController.h
 *
 *  Created on: Nov 16, 2016
 *      Author: evgeny
 */

#ifndef SRC_CONTROLLER_LIB_PCONTROLLER_H_
#define SRC_CONTROLLER_LIB_PCONTROLLER_H_

#include "Controller.h"

class PController : public Controller {
private:
	float Kp;
public:
	PController(float timestep, float Kp);
	virtual ~PController();
	float compute(float error) override;
};

#endif /* SRC_CONTROLLER_LIB_PCONTROLLER_H_ */
