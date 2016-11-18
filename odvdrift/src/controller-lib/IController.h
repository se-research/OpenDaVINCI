/*
 * IController.h
 *
 *  Created on: Nov 16, 2016
 *      Author: evgeny
 */

#ifndef SRC_CONTROLLER_LIB_ICONTROLLER_H_
#define SRC_CONTROLLER_LIB_ICONTROLLER_H_

#include "Controller.h"

class IController : public Controller {
private:
	float Ki;
	float lastError;
	float sum;
public:
	IController(float timestep, float Ki);
	virtual ~IController();
	float compute(float error) override;
};

#endif /* SRC_CONTROLLER_LIB_ICONTROLLER_H_ */
