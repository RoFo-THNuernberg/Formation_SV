#pragma once
#include "ofMain.h"


/**
 * @brief Speicherklasse für die Berechneten werte der jeweiligen Trajektorien
 * 
 */
struct TrajectoryData
{
        float x;
        float y;
        float dx;
        float dy;
        float ddx;
        float ddy;
        float dt;
        bool position_reached = false;
        ofPoint destination;
        explicit TrajectoryData(float x, float y, float dx, float dy, float ddx, float ddy, float dt);
        TrajectoryData();
};