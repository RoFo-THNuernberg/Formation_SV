#pragma once

#include "PositionController.h"
#include "TrajectoryData.h"
#include "math.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Twist.h"
#include <ctime>
#include <chrono>

#include <memory>


/**
 * @brief DynInOutLinController Implementierung. Für Theorie siehe Dokumentation der Mastergruppe
 * Erweitert Interface PositionController um Strategiemuster beizubehalten
 */
class DynInOutLinController : public PositionController
{
public:
    // Bei Konstruktion des Controllers wird eine Konstante Referenz auf die Trajektoriedaten übergeben
    // So müssen diese nicht bei jedem neuen Aufruf erneut übergeben werden
    explicit DynInOutLinController(TrajectoryData const& trajectory);
    geometry_msgs::Twist update(geometry_msgs::Pose2D const& actual_pose) override;
    bool destination_reached() override;
    void setPerformance() override;

private:
    // Regelparameter des Reglers, bevor Änderung mittels Matlab Modell überprüfen
    float _kp_1 = 0.3;
    float _kp_2 = 0.3;
    float _kd_1 = 0.6;
    float _kd_2 = 0.6;

    float _prev_velocity = 0.1;
    float _prev_prev_velocity = 0.1;
    float _prev_acceleration = 0;

    TrajectoryData const& _trajectory;

    bool performance = false;
    bool _destination_reached = false;
};