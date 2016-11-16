/*
 * PController.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: evgeny
 */

#include "PController.h"
#include "Controller.h"

PController::PController(float timestep, float Kp) : Controller(timestep){
	this->Kp = Kp;
}

PController::~PController() {
	// TODO Auto-generated destructor stub
}

float PController::compute(float error) {
	return (Kp * error);
}
