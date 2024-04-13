#include "p2pController.h"
#include <iostream>

//#define DATA_LOGGING

#define TAG "p2pController"

p2pController::p2pController(geometry_msgs::Point const& goal_point) : _goal_point{goal_point} {}

geometry_msgs::Twist p2pController::update(geometry_msgs::Pose2D const& actual_pose)
{   
    geometry_msgs::Twist output_vel;

    //calculate new orientation setpoint
    float setpoint_theta =  atan2(_goal_point.y - actual_pose.y, _goal_point.x - actual_pose.x); 

    //Calculate orientation error and keep it between -pi - pi
    float error_theta = setpoint_theta - actual_pose.theta;
    error_theta = atan2(sin(error_theta), cos(error_theta)); 
    
    //calculate distance error
    float error_dist = sqrt(pow(_goal_point.x - actual_pose.x, 2) + pow(_goal_point.y - actual_pose.y, 2));  

    //Calculate output
    output_vel.linear.x = _kp_v * error_dist;
    output_vel.angular.z = _kp_w * error_theta;

    //check if destination has been reached
    if(error_dist < 0.1 && !performance)
    {
        _destination_reached = true;
        output_vel.linear.x = 0;
        output_vel.angular.z = 0;
        std::cout << "reached" << std::endl;
    }else if (error_dist < 0.1 && performance)
    {
        _destination_reached = true;
    }

    std::cout << "P2P: Linear: " << output_vel.linear.x << " Angular: " << output_vel.angular.z << std::endl;
    return output_vel;
}

bool p2pController::destination_reached()
{   
    return _destination_reached;
}

void p2pController::setPerformance()
{
    performance = true;
}
