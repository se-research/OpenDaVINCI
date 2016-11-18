/*
 * PIDController.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: evgeny
 */

#include "PIDController.h"

PIDController::PIDController(float timestep, float Kd, float Ki, float Kp) : Controller(timestep), D(timestep, Kd), I(timestep, Ki),P(timestep, Kp) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
}

PIDController::~PIDController() {
}

float PIDController::compute(float error) {
	float sum = P.compute(error) + I.compute(error) + D.compute(error);
	return sum;
}


