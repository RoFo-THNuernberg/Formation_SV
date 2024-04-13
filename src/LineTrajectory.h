#ifndef LINETRAJECTORY_H
#define LINETRAJECTORY_H

#include "Trajectory.h"
#include "TrajectoryData.h"
#include "ofMain.h"

/**
 *  Klasse für linienförmige Trajektorien
 *  erbt von der Klasse Trajectory
 */
class LineTrajectory : public Trajectory{

public:

    /**
     * Konstruktor für Linetrajectory
     * @param[in] start_x: X-Koordinate des Startpunkts
     * @param[in] start_y: Y-Koordinate des Startpunkts
     * @param[in] end_x: X-Koordinate des Endpunkts
     * @param[in] end_y: X-Koordinate des Endpunkts
     */
    LineTrajectory(float start_x, float start_y, float end_x, float end_y);
 
    /**
     * Dekonstruktor
     */
    ~LineTrajectory();

    /**
     * Funktion für die x- und y-Koordinate sowie erste und zweite Ableitung
     * Berechnete Werte werden in Trajectory Data zurückgeliefert und können, dann an Regler als Referenz
     * übergeben werden
     * @param[in] dt: Gibt an wie viel zeit zum letzten Aufruf der Funktion vergangen ist
     */
    TrajectoryData getTrajec(float dt);

    /**
     * @brief Get the Data object
     * 
     * @return TrajectoryData 
     */
    TrajectoryData getData();
   
    /**
     * @brief Funktion für das Setzten des Parameters k, bei höherem k wird Trajektorie schneller abgefahren
     * k so wählen, dass die Trajektorie nicht schneller als die Limitierung des Robotors ist.
     * 
     */
    void setzeK(double);

private:
    /**
     * start_x: X-Koordinate des Startpunkts
     * start_y: Y-Koordinate des Startpunkts
     * end_x: X-Koordinate des Endpunkts
     * end_y: X-Koordinate des Endpunkts
    */
    float start_x, start_y, end_x, end_y, prevTime, m=0, b=0;
    double k=0.0003;
    TrajectoryData output;
    
};



#endif //CIRCLETRAJECTORY_H