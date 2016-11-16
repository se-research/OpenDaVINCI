/*
 * IController.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: evgeny
 */

#include "IController.h"

#include "Controller.h"

IController::IController(float timestep, float Ki) : Controller(timestep){
	this->Ki = Ki;
	this->lastError=0;
}

IController::~IController() {
	// TODO Auto-generated destructor stub
}

float IController::compute(float error) {
	return (Kp * error);
}
