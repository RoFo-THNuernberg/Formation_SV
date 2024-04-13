#include "ofMain.h"
#include "ofApp.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Pose.h"
#include <string>

//========================================================================
void test_robot_move(double x, double y, void* userData);

/**
 * @brief Einstiegspunkt des Programms. Initialisiert zunächst ROS und erzeugt dann ein ofAPP Objekt
 * 
 * @param argc Nicht benötigt
 * @param argv Nicht benötigt
 * @return int 
 */
int main(int argc, char** argv){
	ros::init(argc, argv, "RobotFormation");

	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());


}
