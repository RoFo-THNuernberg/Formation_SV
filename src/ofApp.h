#pragma once

#include<vector>
#include<deque>

#include "ofMain.h"
#include "ofxGui.h"
#include "Robot.h"
#include "Choreographer.h"
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

#define MAX_ROBOTS 4

class ofApp : public ofBaseApp{

	public:
		std::vector<Robot*> robots;
		Choreographer* choreographer;

		Trajectory* test;
		TrajectoryData data;
		TrajectoryData data2;

		unsigned long t1 = 0, t0 = 0;
		deque<ofPoint> points;
		deque<ofPoint> points2;
		deque<ofPoint> pointsRob;
		deque<ofPoint> pointsRob2;
		float dt = 20;

		ofxPanel gui;
		ofxInputField<int> ofxIF_robot; 			//integer input field for Robot selection
		ofxInputField<double> ofxIF_x_cord; 		//integer input field for x coordinate
		ofxInputField<double> ofxIF_y_cord;			//integer input field for y coordinate
		ofxButton ofxB_execute; 					// button to let the robot drive
		ofxToggle ofxT_PtoP;						// Button to toggle point dingens
		ofxToggle ofxT_TrajecTest;					// Toggle Buton to test
		ofxToggle ofxT_TrajecTest2;					// Toggle Buton to test2
		ofxButton ofxB_reset;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		void moveRobots();
		void drawLine(deque<ofPoint> const& _points);
};
