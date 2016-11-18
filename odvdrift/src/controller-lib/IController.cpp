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
	this->sum = 0;
}

IController::~IController() {

}

float IController::compute(float error) {
	this->sum += Ki * timestep*(lastError + error)/2;

	this->lastError = error;
	return this->sum;
}
