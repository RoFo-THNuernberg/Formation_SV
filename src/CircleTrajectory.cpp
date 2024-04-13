#include "CircleTrajectory.h"
#include <math.h>
#include <iostream>

CircleTrajectory::CircleTrajectory(float mx, float my, float rx, float ry, bool clockwise): mx(mx), my(my), rx(rx), ry(ry)
{
    // K negativ machen um richtung zu ändern
    if(clockwise)
    {
        k *= -1;
    }
    prevTime = 0;
    delta = 0;
}

CircleTrajectory::CircleTrajectory(ofPoint start, ofPoint end, float angle, bool clockwise):  destination(end)
{
    // K negativ machen um richtung zu ändern
    if(clockwise)
    {
        k *= -1;
    }

    //**Berechnen des Kreis Mittelpunkts und des Radius**
    double alpha= (angle/2)/360*2*3.146;
    
    double dx=end.x-start.x;
    double dy=end.y-start.y;

    double cx = start.x + dx/2;
    double cy = start.y + dy/2;

    double z = sqrt(pow((cx-start.x),2)+pow((cy-start.y),2))/tan(alpha);
    double r = sqrt(pow((cx-start.x),2)+pow((cy-start.y),2))/sin(alpha);

    double AB = sqrt(pow(dx,2)+pow(dy,2));

    mx = cx+z/AB*dy;
    my = cy+z/AB*(-dx);
    rx=r;
    ry=r;

    double start_off_x=r+mx;
    double start_off_y=mx;

    double offset= sqrt((pow(dx,2)+pow(dy,2)));
    double test = offset/2;
    // Berechnen des Delta, damit Kreisbahn bei Startpunkt beginnt (Verbesserungswürdig)
    if((abs(test-r) <= 0.0005) && ((abs(start_off_x - start.x)<=0.0005) || (abs(start_off_y - start.y)<=0.0005)))
    {
        delta=PI;
        std::cout<<"delta: "<< delta <<std::endl;
    }
    else
    {
        delta= asin(offset/(2*r));
    }
    double testx = rx*cos(delta)+mx;
    double testy = ry*sin(delta)+my;
    if((!(abs(testx-start.x)<=0.05)) || !(abs(testy-start.y)<=0.05))
    {
        delta += PI;
        
    }
    prevTime=0;
}

CircleTrajectory::~CircleTrajectory()
{
}

TrajectoryData CircleTrajectory::getTrajec(float dt)
{                                          

    float phi = ((prevTime + dt) * k) + delta; // das ist S  = (s + dt) * k
    float d_phi = k, dd_phi = 0;
    float x_m = mx;         //Versatz des Mittelpunkts in x-Richtung
    float y_m = my;         //Versatz des Mittelpunkts in y-Richtung
    
    // Berechnung von den Koordinaten X, Y und deren 1. und 2. Ableitung
    output.x = rx*cos(phi)+x_m;
    output.y = ry*sin(phi)+y_m;
    output.dx = -rx*sin(phi)*d_phi;
    output.dy = ry*cos(phi)*d_phi;
    output.ddx = -rx*cos(phi) * d_phi*d_phi - rx*sin(phi)*dd_phi;
    output.ddy = -ry*sin(phi) * d_phi*d_phi + ry*cos(phi)*dd_phi;
    output.dt = dt;
    prevTime += dt;
    output.destination = destination;
    
    // Abfrage ob letzter Übergebener Zielpunkt erreicht wurde
    if((abs(output.x - destination.x)<=0.05) && (abs(output.y - destination.y)<=0.05))
    {
        output.position_reached=true;
        std::cout << "DESTINATION REACHED" << std::endl;
    }else{
		output.position_reached=false;
	}

    return output;
}

void CircleTrajectory::setzeK(double neu)
{
    this->k = neu;
}

TrajectoryData CircleTrajectory::getData()
{
	return this->output;
}