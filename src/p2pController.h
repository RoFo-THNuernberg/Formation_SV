#pragma once

#include "math.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Point.h"
#include "PositionController.h"



/**
 * @brief PositionController implementation. Für Theorie siehe Dokumentation der Mastergruppe
 * Erweitert Interface PositionController um Strategiemuster beizubehalten
 */
class p2pController : public PositionController
{
    public:
        // Bei Konstruktion des Reglers wird einmal der Zielpunkt übergeben  
        explicit p2pController(geometry_msgs::Point const& goal_point);

        geometry_msgs::Twist update(geometry_msgs::Pose2D const& actual_pose) override;
        bool destination_reached() override;
        void setPerformance() override;

    private:
        // Regelparameter des p2pControllers für anderes Fahrverhalten müssen diese angepasst werden
        float _kp_v = 0.2;
        float _kp_w = 1.0;
        bool performance = false;
        geometry_msgs::Point const _goal_point;
        bool _destination_reached = false;
};