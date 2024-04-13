#pragma once

#include<vector>

#include "ofMain.h"
#include "Robot.h"
#include "Trajectory.h"
#include "CircleTrajectory.h"
#include "LineTrajectory.h"
#include "TrajectoryData.h"
#include "DynInOutLinController.h"
#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include <string>
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Pose2D.h"
#include "p2pController.h"

/**
 * @brief Klasse zum erstellen von Choreographien bzw. zum Verketten von Trajektorien
 * 
 */
class Choreographer
{
    private:
		std::vector<Robot*> robots;

		Trajectory* test;
		Trajectory* test2;
		Trajectory* test3;
		Trajectory* test4;
		TrajectoryData data;
		TrajectoryData data2;
		TrajectoryData data3;
		TrajectoryData data4;
    TrajectoryData last;
    TrajectoryData last2;
		int step = 0;
    int step2 = 0;

		unsigned long t1 = 0, t0 = 0;
		float dt = 50;
		bool begin = false;
    bool begin2 = false;
    public:
        /**
         * @brief Konstruktor zum Erstellen eines Choreographer Objekts
         * 
         * @param robots die Liste an Robotern die in der OF angelegt wird
         */
        Choreographer(std::vector<Robot*>& robots);

        /**
         * @brief Funktion für die Trajektorie
         * 
         */
        void choreography_1();

        /**
         * @brief Funktion für die Trajektorie
         * 
         */
        void choreography_2();

        /**
         * @brief Funktion zum zurückliefern der Aktuellsten Trajektorie Daten
         * 
        */
        TrajectoryData getData();

        /**
         * @brief Funktion zum zurückliefern der Aktuellsten Trajektorie Daten
         * 
        */
        TrajectoryData getData2();

        /**
         * @brief Funktion zum Zurücksetzten auf Startwerte
         * 
        */
        void reset();

};