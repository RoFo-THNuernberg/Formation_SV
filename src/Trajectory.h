#ifndef _TRAJECTORY_H
#define _TRAJECTORY_H

//#include <ros/ros.h>
#include "TrajectoryData.h"
//#include "gnuplot-iostream.h"

/**
 * Abstrakte Klasse für Trajektorien
 */
class Trajectory{

    public:

    ///Konstruktor
    Trajectory();
    ///Dekonstruktor
    ~Trajectory();

    /**
     * Funktion für die x und y sowie erste und zweite Ableitung des Splines zum Wert des Kurvenparameter
     * Berechnete Werte werden in Trajectory Data zurückgeliefert und können, dann an Regler als Referenz
     * übergeben werden
     * @param[in] dt: Gibt an wie viel zeit zum letzten Aufruf der Funktion vergangen ist
     */
    virtual TrajectoryData getTrajec(float dt) = 0;
    virtual TrajectoryData getData() = 0;
};

#endif //_TRAJECTORY_H