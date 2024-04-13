#pragma once
#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point.h"


/**
 * @brief Interface für die Regler
 * 
 */
class PositionController
{
private:
    /* data */
public:
    virtual ~PositionController() {}
    virtual geometry_msgs::Twist update(geometry_msgs::Pose2D const&) = 0;
    virtual bool destination_reached() = 0;
    virtual void setPerformance() = 0;
};
