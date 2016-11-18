/*
 * PIDController.h
 *
 *  Created on: Nov 17, 2016
 *      Author: evgeny
 */

#ifndef SRC_CONTROLLER_LIB_PIDCONTROLLER_H_
#define SRC_CONTROLLER_LIB_PIDCONTROLLER_H_

#include "Controller.h"
#include "PController.h"
#include "IController.h"
#include "DController.h"

class PIDController : Controller {
public:
	float Kd, Ki, Kp;
	PController P;
	IController I;
	DController D;
public:
	PIDController(float timestep, float Kd, float Ki, float Kp);
	virtual ~PIDController();
	float compute(float error) override;
};

#endif /* SRC_CONTROLLER_LIB_PIDCONTROLLER_H_ */
