#include "DynInOutLinController.h"
#include <iostream>


//#define DATA_LOGGING
//#include "DataLogger.h"

#define TAG "dynInOutLinController"
DynInOutLinController::DynInOutLinController(TrajectoryData const& trajectory): _trajectory(trajectory)
{
    _prev_velocity = sqrt(pow(_trajectory.dx, 2) + pow(_trajectory.dy, 2));
}

geometry_msgs::Twist DynInOutLinController::update(geometry_msgs::Pose2D const& actual_pose)
{
    geometry_msgs::Twist output_vel;
        float theta = actual_pose.theta;
        float actual_dx = _prev_velocity * cos(theta);
        float actual_dy = _prev_velocity * sin(theta);


        float u1 = _trajectory.ddx + _kp_1 * (_trajectory.x - actual_pose.x) + _kd_1 * (_trajectory.dx - actual_dx);
        float u2 = _trajectory.ddy + _kp_2 * (_trajectory.y - actual_pose.y) + _kd_2 * (_trajectory.dy - actual_dy);

        float output_acceleration = u1 * cos(theta) + u2 * sin(theta);

        output_vel.angular.z = - u1 * sin(theta) / _prev_velocity + u2 * cos(theta) / _prev_velocity;

        _prev_velocity = (_trajectory.dt/1000) * (_prev_acceleration + output_acceleration) / 2. + _prev_velocity;
        _prev_acceleration = output_acceleration;

        if(_prev_velocity == 0)
            _prev_velocity = 0.01;

        output_vel.linear.x = _prev_velocity;


    //calculate distance error
    float error_dist = sqrt(pow(_trajectory.destination.x - actual_pose.x, 2) + pow(_trajectory.destination.y - actual_pose.y, 2));  

    //Vehindern, dass während Performance v = 0 gesetzt wird
    if((output_vel.linear.x <= 0.1 || output_vel.linear.x >= 10 ) && performance)
    {
        output_vel.linear.x = _prev_prev_velocity;
    }

    //Stellbegrenzung für Winkelgeschwindigkeit
    if(output_vel.angular.z >= 3)
    {
        output_vel.angular.z = 3;
    } else if (output_vel.angular.z <= -3)
    {
        output_vel.angular.z = -3;
    }

    //check if destination has been reached
    if(error_dist < 0.1 && !performance)
    {
        _destination_reached = true;
        output_vel.linear.x = 0;
        output_vel.angular.z = 0;
        std::cout << "reached" << std::endl;
    }
    else if(error_dist < 0.1 && performance)
    {
        _destination_reached = true;
        output_vel.linear.x = 0.1;
    } 

    std::cout << "linear: " << output_vel.linear.x << " angular: " << output_vel.angular.z << std::endl;

    return output_vel;
}

bool DynInOutLinController::destination_reached()
{
    return _destination_reached;
}

void DynInOutLinController::setPerformance()
{
    performance = true;
}
