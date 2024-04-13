#include "LineTrajectory.h"
#include <math.h>
#include <iostream>

LineTrajectory::LineTrajectory(float start_x, float start_y, float end_x, float end_y): start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y)
{
    prevTime = 0;
}

LineTrajectory::~LineTrajectory()
{
}

TrajectoryData LineTrajectory::getTrajec(float dt)
{                                          
	output.destination.x=end_x;
	output.destination.y=end_y;

	// Berechnung von den Koordinaten X, Y und deren 1. Ableitung (2. Ableitung immer 0)
	output.x = (1-prevTime*k)*start_x +prevTime*k*end_x;
	output.y = (1-prevTime*k)*start_y +prevTime*k*end_y;
	
	output.dx = (end_x - start_x)*0.15;
	output.dy = (end_y - start_y)*0.15;


	if((abs(output.x - end_x)<=0.05) && (abs(output.y - end_y)<=0.05))
    {
        output.position_reached=true;
    }else{
		output.position_reached=false;
	}
	prevTime += dt;
	return output;
}


void LineTrajectory::setzeK(double neu)
{
    this->k = neu;
}

TrajectoryData LineTrajectory::getData()
{
	return this->output;
}