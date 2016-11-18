/*
 * DController.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: evgeny
 */

#include "DController.h"

DController::DController(float timestep, float Kd) : Controller(timestep){
	this->Kd = Kd;
	this->lastError = 0;
}

DController::~DController() {
}

float DController::compute(float error) {
	float out = Kd * (error - this->lastError)/timestep;
	this->lastError = error;
	return out;
}
