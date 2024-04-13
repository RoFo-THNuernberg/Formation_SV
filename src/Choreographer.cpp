#include "Choreographer.h"

Choreographer::Choreographer(std::vector<Robot*>& robots): robots(robots)
{	
	// Initialisieren der letzten TrajektorieDaten
	last.x = 0;
	last.y = 0;
	last2.x = 0;
	last2.y = 0;

	// Initialisieren der Trajektorien
	test = NULL;
	test2 = NULL;
	test3 = NULL;
	test4 = NULL;
}

void Choreographer::choreography_1()
{
    ofPoint start, end;
	// Einstiegpunkt der Choreographie. Roboter fährt mittels p2pRegler an Startposition
	if(!begin)
	{
        geometry_msgs::Point goal_point;
		goal_point.x = 0.6;
		goal_point.y = 1.6;
		goal_point.z = 0.0;
		robots[0]->setController(new p2pController(goal_point));
		begin = true;
	} 
	// Überprüfen ob Roboter an Startposition für 1. Trajektorie, wenn ja erzeugen der Linientrajektorie
	if((robots[0]->getController()->destination_reached() && step == 0) || (robots[0]->getController()->destination_reached() && data4.position_reached && step == 0))
	{
		t0 = 0;
		// Löschen der Trajektorie 4.
		if(test4 != NULL){
			delete test4;
			test4 = NULL;
			data4.position_reached = false;
		}
		test = new LineTrajectory(0.6, 1.6, 1.6, 1.6);
		data = test->getTrajec(t0);
		// Setzen des Controllers im Roboter
		robots[0]->setController(new DynInOutLinController(data));
		// Notieren des Startzeitpunkts
		t0 = ofGetElapsedTimeMillis();
		// Im DynInOutLynController vermerken, dass es sich um Choreographie handelt
		robots[0]->getController()->setPerformance();
		// Nächster Schritt
		step++;

	// Überprüfen ob Roboter an Startposition für 2. Trajektorie, wenn ja erzeugen der Kreistrajektorie
	}else if(data.position_reached && step == 1 && robots[0]->getController()->destination_reached())
	{
				
		t0 = 0;

		// Start und Endpunkt festlegen und dann KreisTrajektorie erzeugen
		start.x = 1.6; start.y = 1.6;
		end.x = 1.6; end.y = 0.6;
		test2 = new CircleTrajectory(start, end, 180, true);
		data2 = test2->getTrajec(t0);

		// Löschen der Trajektorie 1. & zurücksetzen von Data1
		delete test;
		test = NULL;
		data.position_reached = false;

		// Setzen des Controllers im Roboter
		robots[0]->setController(new DynInOutLinController(data2));

		// Notieren des Startzeitpunkts
		t0 = ofGetElapsedTimeMillis();
		// Im DynInOutLynController vermerken, dass es sich um Choreographie handelt
		robots[0]->getController()->setPerformance();
		// Nächster Schritt
		step++;

	// Überprüfen ob Roboter an Startposition für 3. Trajektorie, wenn ja erzeugen der Linientrajektorie
	}else if(data2.position_reached && step == 2 && robots[0]->getController()->destination_reached())
	{
		// Löschen der Trajektorie 2. & zurücksetzen von Data2
		delete test2;
		test2 = NULL;
		data2.position_reached = false;

		t0 = 0;

		// Erzeugen der LinienTrajektorie mit Start und Endpunkt
		test3 = new LineTrajectory(1.6, 0.6, 0.6, 0.6);
		data3 = test3->getTrajec(t0);

	    // Setzen des Controllers im Roboter
		robots[0]->setController(new DynInOutLinController(data3));

		// Notieren des Startzeitpunkts
		t0 = ofGetElapsedTimeMillis();
		// Im DynInOutLynController vermerken, dass es sich um Choreographie handelt
		robots[0]->getController()->setPerformance();
		// Nächster Schritt
		step++;

	// Überprüfen ob Roboter an Startposition für 4. Trajektorie, wenn ja erzeugen der Kreistrajektorie
	}else if(data3.position_reached && step == 3 && robots[0]->getController()->destination_reached())
	{
		// Löschen der Trajektorie 3. & zurücksetzen von Data3
		delete test3;
		test3 = NULL;
		data3.position_reached = false;

		// Start und Endpunkt festlegen und dann KreisTrajektorie erzeugen
		start.x = 0.6; start.y = 0.6;
		end.x = 0.6; end.y = 1.6;
		t0 = 0;
		test4 = new CircleTrajectory(start, end, 180, true);
		data4 = test4->getTrajec(t0);

		// Setzen des Controllers im Roboter
		robots[0]->setController(new DynInOutLinController(data4));

		// Notieren des Startzeitpunkts
		t0 = ofGetElapsedTimeMillis();
		// Im DynInOutLynController vermerken, dass es sich um Choreographie handelt
		robots[0]->getController()->setPerformance();
		// Schritt wird auf 0 setzten um erneut zu beginnen
		step = 0;
	}

	// überprüfen ob 50 ms vergangen sind und dann neue Berechnung von TrajektorieDaten
	t1 = ofGetElapsedTimeMillis();
	if((t1-t0)>dt)
	{
		if(test != NULL && !data.position_reached)
		{
			std::cout << (test != NULL) << std::endl;
			data = test->getTrajec(dt);
			last = data;
		}
		if(test2 != NULL && !data2.position_reached)
		{
			data2 = test2->getTrajec(dt);
			last = data2;
		}
		if(test3 != NULL && !data3.position_reached)
		{
			data3 = test3->getTrajec(dt);
			last = data3;
		}
		if(test4 != NULL && !data4.position_reached)
		{
			data4 = test4->getTrajec(dt);
			last = data4;
		}
		t0 = t1;
	}
}

void Choreographer::choreography_2()
{
    ofPoint start, end;
	// Einstiegpunkt der Choreographie. Roboter fährt mittels p2pRegler an Startposition
	if(!begin2)
	{
        geometry_msgs::Point goal_point;
		goal_point.x = 1.6;
		goal_point.y = 0.6;
		goal_point.z = 0.0;
		robots[1]->setController(new p2pController(goal_point));
		begin2 = true;
	} 
	// Überprüfen ob Roboter an Startposition für 1. Trajektorie, wenn ja erzeugen der Linientrajektorie
	if((robots[1]->getController()->destination_reached() && step2 == 0) || (robots[1]->getController()->destination_reached() && data2.position_reached && step2 == 0))
	{
		t0 = 0;
		// Löschen der Trajektorie 4.
		if(test2 != NULL){
			delete test2;
			test2 = NULL;
			data2.position_reached = false;
		}
		test3 = new LineTrajectory(1.6, 0.6, 0.6, 0.6);
		data3 = test3->getTrajec(t0);
		// Setzen des Controllers im Roboter
		robots[1]->setController(new DynInOutLinController(data3));
		// Notieren des Startzeitpunkts
		t0 = ofGetElapsedTimeMillis();
		// Im DynInOutLynController vermerken, dass es sich um Choreographie handelt
		robots[1]->getController()->setPerformance();
		// Nächster Schritt
		step2++;

	// Überprüfen ob Roboter an Startposition für 2. Trajektorie, wenn ja erzeugen der Kreistrajektorie
	}else if(data3.position_reached && step2 == 1 && robots[1]->getController()->destination_reached())
	{
				
		t0 = 0;

		// Start und Endpunkt festlegen und dann KreisTrajektorie erzeugen
		start.x = 0.6; start.y = 0.6;
		end.x = 0.6; end.y = 1.6;
		test4 = new CircleTrajectory(start, end, 180, true);
		data4 = test4->getTrajec(t0);

		// Löschen der Trajektorie 1. & zurücksetzen von Data1
		delete test3;
		test3 = NULL;
		data3.position_reached = false;

		// Setzen des Controllers im Roboter
		robots[1]->setController(new DynInOutLinController(data4));

		// Notieren des Startzeitpunkts
		t0 = ofGetElapsedTimeMillis();
		// Im DynInOutLynController vermerken, dass es sich um Choreographie handelt
		robots[1]->getController()->setPerformance();
		// Nächster Schritt
		step2++;

	// Überprüfen ob Roboter an Startposition für 3. Trajektorie, wenn ja erzeugen der Linientrajektorie
	}else if(data4.position_reached && step2 == 2 && robots[1]->getController()->destination_reached())
	{
		// Löschen der Trajektorie 2. & zurücksetzen von Data2
		delete test4;
		test4 = NULL;
		data4.position_reached = false;

		t0 = 0;

		// Erzeugen der LinienTrajektorie mit Start und Endpunkt
		test = new LineTrajectory(0.6, 1.6, 1.6, 1.6);
		data = test->getTrajec(t0);

	    // Setzen des Controllers im Roboter
		robots[1]->setController(new DynInOutLinController(data));

		// Notieren des Startzeitpunkts
		t0 = ofGetElapsedTimeMillis();
		// Im DynInOutLynController vermerken, dass es sich um Choreographie handelt
		robots[1]->getController()->setPerformance();
		// Nächster Schritt
		step2++;

	// Überprüfen ob Roboter an Startposition für 4. Trajektorie, wenn ja erzeugen der Kreistrajektorie
	}else if(data.position_reached && step2 == 3 && robots[1]->getController()->destination_reached())
	{
		// Löschen der Trajektorie 3. & zurücksetzen von Data3
		delete test;
		test = NULL;
		data.position_reached = false;

		// Start und Endpunkt festlegen und dann KreisTrajektorie erzeugen
		start.x = 1.6; start.y = 1.6;
		end.x = 1.6; end.y = 0.6;
		t0 = 0;
		test2 = new CircleTrajectory(start, end, 180, true);
		data2 = test2->getTrajec(t0);

		// Setzen des Controllers im Roboter
		robots[1]->setController(new DynInOutLinController(data2));

		// Notieren des Startzeitpunkts
		t0 = ofGetElapsedTimeMillis();
		// Im DynInOutLynController vermerken, dass es sich um Choreographie handelt
		robots[1]->getController()->setPerformance();
		// Schritt wird auf 0 setzten um erneut zu beginnen
		step2 = 0;
	}

	// überprüfen ob 50 ms vergangen sind und dann neue Berechnung von TrajektorieDaten
	t1 = ofGetElapsedTimeMillis();
	if((t1-t0)>dt)
	{
		if(test != NULL && !data.position_reached)
		{
			std::cout << (test != NULL) << std::endl;
			data = test->getTrajec(dt);
			last2 = data;
		}
		if(test2 != NULL && !data2.position_reached)
		{
			data2 = test2->getTrajec(dt);
			last2 = data2;
		}
		if(test3 != NULL && !data3.position_reached)
		{
			data3 = test3->getTrajec(dt);
			last2 = data3;
		}
		if(test4 != NULL && !data4.position_reached)
		{
			data4 = test4->getTrajec(dt);
			last2 = data4;
		}
		t0 = t1;
	}
}


TrajectoryData Choreographer::getData()
{
	return last;
}

TrajectoryData Choreographer::getData2()
{
	return last2;
}

void Choreographer::reset()
{
	begin = false;
	begin2 = false;
	step = 0;
	step2 = 0;
	t0 = 0;
	if (test != NULL)
	{
		delete test;
		test = NULL;
	}
	if (test2 != NULL)
	{
		delete test2;
		test2 = NULL;
	}
	if (test3 != NULL)
	{
		delete test3;
		test3 = NULL;
	}
	if (test4 != NULL)
	{
		delete test4;
		test4 = NULL;
	}
	data.position_reached = false;
	data2.position_reached = false;
	data3.position_reached = false;
	data4.position_reached = false;
}