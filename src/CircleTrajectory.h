#ifndef CIRCLETRAJECTORY_H
#define CIRCLETRAJECTORY_H

#include "Trajectory.h"
#include "TrajectoryData.h"
#include "ofMain.h"

#define PI 3.146

/**
 *  Klasse für kreisförmige, bzw. ellipsenförmige Trajektorien
 *  erbt von der Klasse Trajectory
 */
class CircleTrajectory : public Trajectory{

public:

    /**
     * Konstruktor für Circletrajectory
     * @param[in] mx: X-Koordinate des Mittelpunkts des Kreis bzw. der Ellipse
     * @param[in] mx: Y-Koordinate des Mittelpunkts des Kreis bzw. der Ellipse
     * @param[in] rx: Radius 1 (Halbachse in x-Koordinatenrichtung) (Kreis für a=b)
     * @param[in] ry: Radius 2 (Halbachse in y-Koordinatenrichtung) (Kreis für a=b)
     * @param[in] clockwise: Gibt an ob Kreis gegen oder mit Uhrzeigersinn abgefahen werden soll
     */
    CircleTrajectory(float mx, float my, float rx, float ry, bool clockwise);
    
    /**
     * Konstruktor für Circletrajectory, berechet Mittelpunkt & Radius des Kreises aus Startpunkt und Endpunkt
     * @param[in] start: Startpunkt für die kreisförmige Trajektorie
     * @param[in] end: Endpunkt für die kreisförmige Trajektorie
     * @param[in] angle: Winkel der angibt wie viel von einem Kreis gefahren werden soll. 180 für Halbkreis...
     * @param[in] clockwise: Gibt an ob Kreis gegen oder mit Uhrzeigersinn abgefahen werden soll
     */
    CircleTrajectory(ofPoint start, ofPoint end, float angle, bool clockwise);
    
    /**
     * Dekonstruktor
     */
    ~CircleTrajectory();

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
     * mx: X-Koordinate des Kreismittelpunktes
     * my: Y-Koordinate des Kreismittelpunktes
     * rx: Radius der Hauptachse der Ellipse (X-Richtung)
     * ry: Radius der Nebenachse der Ellipse (Y-Richtung)
     * prevTime: Speichern der Zeit
     * destination: Zielpunkt der Kreisbahn, wird benötigt damit die keine weiteren Punkte berechnet werden sobald
     *              Zielpunkt erreicht wurde
     * delta: Offset zum normale Kreisstartpunkt, wert zwischen 0 und 2PI
     * output: Speichert die zuletzt berechneten Daten der Trajektorie
    */
    float mx, my, rx, ry, prevTime;
    double k=0.0005;
    double delta=0;
    ofPoint destination;
    TrajectoryData output;
};



#endif //CIRCLETRAJECTORY_H