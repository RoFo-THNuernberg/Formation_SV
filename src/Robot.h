#pragma once
#include <string>
#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Point.h"
#include "PositionController.h"
#include "turtlesim/Pose.h"


/**
 * @brief Robot Klasse
 * Dient als Virtuelles Abbild des Roboters. Sämtliche benötigte Roboter Informationen
 * werden hier gespeichert bzw. erstellt.        
 */
class Robot
{
    private:
        /*
            Name des Roboters, wird bei Konstruktion übergeben, sollte passend zum Roboternamen sein, der in der
            ESP-IDF übergeben wird sein. Da daraus der ROS Publisher und gebildet wird
        */
        std::string _name;
        ros::NodeHandle _nh;        // Jeder Roboter benötigt eigenen Node über den er Seine Position bekommt bzw. Nachrichten veröffentlichen kann
        ros::Publisher _pub;        // ROS Publisher 
        ros::Subscriber _sub;       // ROS Subscriber, wird im Konstruktor initialisiert und fängt die Position ab die vom Robot Image Client gesendet wird
        geometry_msgs::Pose2D _ist_pos;		// Speichern der IST-Position des Roboters
        geometry_msgs::Point _goal_point;   // Unnütz Löschen und schauen ob noch alles funktioniert
        PositionController* _controller;    // Speichern des Zugewiesen Reglers, nach Strategie Muster
    public:
        Robot(std::string);
        ~Robot();
        void setController(PositionController* controller);
        PositionController* getController();
        geometry_msgs::Pose2D getIst();
        void move();
        void poseCallback(const turtlesim::Pose::ConstPtr& msg);
        std::string getName();
        void updatePos();
        void reset();
};
