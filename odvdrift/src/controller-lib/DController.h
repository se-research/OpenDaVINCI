/*
 * DController.h
 *
 *  Created on: Nov 17, 2016
 *      Author: evgeny
 */

#ifndef SRC_CONTROLLER_LIB_DCONTROLLER_H_
#define SRC_CONTROLLER_LIB_DCONTROLLER_H_

#include "Controller.h"

class DController : public Controller {
private:
	float Kd;
	float lastError;
public:
	DController(float timestep, float Kd);
	virtual ~DController();
	float compute(float error) override;
};


#endif /* SRC_CONTROLLER_LIB_DCONTROLLER_H_ */
