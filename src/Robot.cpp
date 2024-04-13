#include "Robot.h"



Robot::Robot(std::string name): _name(name)
{
    // Erstellen der Addressstrings unter welcher gepublished wird
    std::string pub_name = _name + "/vel";

    // Erstellen der Addressstrings unter welcher der Robot Image Client die Position published
    std::string sub_name = _name + "/pose";

    // Erstellen des Publishers, welche soll geschwindigkeiten veröffentlicht
    this->_pub = _nh.advertise<geometry_msgs::Twist>(pub_name, 1000);
    
    this->_controller = NULL;

    // Erstellen des Subscribers. Übergeben wird Funktion poseCallback, welche mit bind statisch gemacht wird.
    this->_sub = _nh.subscribe<turtlesim::Pose>(sub_name, 1, std::bind(&Robot::poseCallback, this, std::placeholders::_1));
    std::cout << _name << " hinzugefügt" << std::endl;    
}

Robot::~Robot()
{
    std::cout << _name << " gelöscht" << std::endl;
}

// Zuweisen eines Controllers
void Robot::setController(PositionController* controller)
{
    this->_controller = controller;
}

// Zurückliefern des Controllers
PositionController* Robot::getController()
{
    return this->_controller;
}

// Zurücklierfern der aktuellen Position
geometry_msgs::Pose2D Robot::getIst()
{
    return this->_ist_pos;
}

// Move funktion für den Roboter. Beim aufruf führt der jeweilige Controller den nächsten berechnungsschritt durch
// die zurückgelieferten werte werden daraufhin gepublished
void Robot::move()
{
    if(!_controller->destination_reached())
    {
        geometry_msgs::Twist step = this->_controller->update(this->_ist_pos);
        this->_pub.publish(step);
        //std::cout << _name << ": Published \n";
    }
}

// Callback funktion für den Subscriber
void Robot::poseCallback(const turtlesim::Pose::ConstPtr& msg){
	_ist_pos.x = msg->x;
	_ist_pos.y = msg->y;
	_ist_pos.theta = msg->theta;
}

// Zurückliefern des Robotornamen
std::string Robot::getName(){
    return this->_name;
}

// Setzt den Roboter zurück und löscht den Controller
void Robot::reset()
{
    geometry_msgs::Twist step;
    step.linear.x = 0;
    step.angular.z = 0;
    this->_pub.publish(step);
    delete this->_controller;
    std::cout << _name << ": Published \n";
}