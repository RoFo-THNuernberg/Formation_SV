#include "TrajectoryData.h"


TrajectoryData::TrajectoryData(float x, float y, float dx, float dy, float ddx, float ddy, float dt)
: x{x}, y{y}, dx{dx}, dy{dy}, ddx{ddx}, ddy{ddy} , dt{dt}
{
}
        
TrajectoryData::TrajectoryData(): x{0}, y{0}, dx{0}, dy{0}, ddx{0}, ddy{0}, dt{0}
{

}
        