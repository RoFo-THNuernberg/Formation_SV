#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	// Initialisieren GUI. Anlegen der Textfelder und Buttons
	std::cout << "Setup" << "\n";
	gui.setup();
	gui.setName("--Input Test--");
	gui.setDefaultWidth(5000);
	gui.add(ofxIF_robot.setup("Roboter:", 1, 1, MAX_ROBOTS, 50.0, 20.0));
	gui.add(ofxIF_x_cord.setup("x-Koordinate:", 1.1, 0.0, 2.2, 50.0, 20.0));
	gui.add(ofxIF_y_cord.setup("y-Koordinate:", 1.1, 0.0, 2.2, 50.0, 20.0));
	gui.add(ofxB_execute.setup("Fahre Punkt an"));
	gui.add(ofxT_PtoP.setup("Starte Point to Point", 0, 150.0, 20.0));
	gui.add(ofxT_TrajecTest.setup("Teste Trajektorie 1", 0, 150.0, 20.0));
	gui.add(ofxT_TrajecTest2.setup("Teste Trajektorie 2", 0, 150.0, 20.0));
	gui.add(ofxB_reset.setup("Resete Roboter"));

	// Erzeugen der Roboter
	for(int i = 0; i < MAX_ROBOTS; i++)
	{
		// Anlegen des Roboter Namens
		std::string name = "/robot_" + std::to_string(i+1);
		std::cout << name << endl;
		// Neuen Roboter in die Liste hinzufügen
		robots.push_back(new Robot(name));
	}

	// Initialisierung von Test, Kann entfernt werden, falls Trajectest2 nicht benötogt wird
	test = NULL;

	// Anlegen des Choreographers
	choreographer = new Choreographer(robots);

	// Speichern der Startzeit
	t0 = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
/**
 * Update Dauerschleife des Programms, hier werden alle Funktionalitäten aufgerufen
*/
void ofApp::update(){
	t1 = ofGetElapsedTimeMillis();
	float t = t1 - t0;
	/**
	 * Abfrage ob Taster Point to Point betätigt wurde.
	 * Ziel-Koordinaten werden aus Inputfield gelesen und an den Roboter P2PController übergeben
	*/
	if(ofxB_execute){
		geometry_msgs::Point goal_point;
		goal_point.x = ofxIF_x_cord;
		goal_point.y = ofxIF_y_cord;
		goal_point.z = 0.0;
		int index = ofxIF_robot - 1;
		robots[index]->setController(new p2pController(goal_point));
	}

	/*
	 * Abfrage ob Toggle Button für das Testen der Trajektorie betätigt wurde.
	 * Aufrufen der ersten Choreographie des Choreographers
	*/
	if(ofxT_TrajecTest)
	{	
		choreographer->choreography_1();
		choreographer->choreography_2();
	}

	/**
	 * Abfrage ob Toggle Button für das Testen der zweiten Trajektorie betätigt wurde.
	 * Testweise generierung einer LinienTrajektorie
	 * Kann gelöscht werden, falls nicht benötigt
	*/
	if(ofxT_TrajecTest2)
	{
		if(test == NULL)
		{
			ofPoint start;
			start.x=0.6;
			start.y=1.1;
			ofPoint end;
			end.x=1.6;
			end.y=1.1;
			test = new LineTrajectory(0.5, 0.5, 1.6, 1.6);
			data = test->getTrajec(t0);
			robots[0]->setController(new DynInOutLinController(data));
		}
		if(t >dt)
		{
			if(!data.position_reached)
			{
				data = test->getTrajec(dt);
			}
		}

	}
	/*
	 * Abfrage ob Button zum zurücksetzten sämtlicher werte betätigt wurde.
	 * Die zugewiesenen Regler werden gelöscht und auf null gesetzt
	 * Die Choreographie wird ebenfalls zurückgesetzt
	*/
	if(ofxB_reset)
	{
		//Zurücksetzten der Roboter inkl. Regler
		for(int i = 0; i < robots.size(); i++)
		{
			std::cout << "\n\nRESET\n\n" << endl;
			robots[i]->reset();
			robots[i]->setController(NULL);
		}
		// Löschen der Trajektorie aus Test2
		if (test != NULL)
		{
			delete test;
			test = NULL;
		}
		// Zurücksetzten der Choreograhie
		choreographer->reset();
		t0=0;

		// Löschen der gezeichneten Trajektorie
		points.clear();
	}

	// Überprüfung ob seit letzter reglerberechnung min. 20 ms vergangen sind und dann erneute berechnung
	if(t > dt)
	{
		moveRobots();
	}
	t0 = t1;
    ros::spinOnce();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	gui.draw();
	ofPushMatrix();
	int centerX = (ofGetWidth()/2);
	int centerY = (ofGetHeight()/2);
	ofTranslate(centerX/2, ofGetHeight() - 25);
	int xField = 0, yField = 0, heightField = ofGetHeight()-100, widthField = heightField;
	//draw bounding box
	ofNoFill();
	ofDrawRectangle(xField,yField, widthField, -heightField);
	//draw coordinate system
	ofDrawLine(xField,(yField-heightField -30 ),xField, yField);
	ofDrawLine(xField,yField,xField+widthField + 30,yField);
	//insert designations
	ofDrawBitmapString("X", xField + widthField + 40 ,yField);
	ofTranslate(centerX/2, ofGetHeight() - 25);
	ofDrawBitmapString("Y", xField , yField-heightField - 40);
	ofDrawBitmapString("220 cm", xField + (widthField/2),yField + 20);
	ofDrawBitmapString("220 cm", xField - 55 ,yField-(heightField/2));

	// Speichern des aktuellen Trajektorie Punktes in einer Liste
	ofPoint point;
	data = choreographer->getData();
	point.x = (data.x/2.2) * widthField, point.y = -(data.y/2.2) * heightField;
	// Überprüfen ob Punkt nicht im Ursprung liegt
	if(point.x != 0 && point.y != 0) // auch überprüfen ob neuerpunkt == Alter punkt
	{
		points.push_back(point);
		// Überprüfen ob mehr als 500 Punkte in der Liste sind, wenn ja ersten punkt löschen
		if(points.size() > 500)
		{
			points.pop_front();
		}
	}
	ofSetColor(0,0,255);

	// Zeichnen der Liste
	//drawLine(points);


	// Speichern des aktuellen Position von Roboter 1 in einer Liste
	point.x = (robots[0]->getIst().x/2.2) * widthField, point.y = -(robots[0]->getIst().y/2.2) * heightField;
	// Überprüfen ob Punkt nicht im Ursprung liegt
	if(point.x != 0 && point.y != 0)
	{
		pointsRob.push_back(point);
		// Überprüfen ob mehr als 500 Punkte in der Liste sind, wenn ja ersten punkt löschen
		if(pointsRob.size() > 500)
		{
			pointsRob.pop_front();
		}
	}
	ofSetColor(255,0,0);

	// Zeichnen der Liste
	drawLine(pointsRob);

	// Speichern des aktuellen Position von Roboter 2 in einer Liste
	point.x = (robots[1]->getIst().x/2.2) * widthField, point.y = -(robots[1]->getIst().y/2.2) * heightField;
	// Überprüfen ob Punkt nicht im Ursprung liegt
	if(point.x != 0 && point.y != 0)
	{
		pointsRob2.push_back(point);
		// Überprüfen ob mehr als 500 Punkte in der Liste sind, wenn ja ersten punkt löschen
		if(pointsRob2.size() > 500)
		{
			pointsRob2.pop_front();
		}
	}
	ofSetColor(255, 192, 203);
	// Zeichnen der Liste
	drawLine(pointsRob2);

	ofPopMatrix;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::moveRobots()
{
	for(int i = 0; i < robots.size(); i++)
		{
			if(robots[i]->getController() != NULL)
			{
				robots[i]->move();
			}
		}
}

void ofApp::drawLine(deque<ofPoint> const& _points)
{
	// Alle Punkte in der Liste durchgehen und linie dazwischen zeichnen
	for(int i = 1; i < _points.size(); i++)
	{
		ofDrawLine(_points[i-1].x, _points[i-1].y, _points[i].x , _points[i].y);
	}
}