#include "RoadProperties.hpp"
#include <MyRandom.hpp>

RoadProperties::RoadProperties(unsigned int map_width, unsigned int level)
    : LaneProperties(map_width, level),
      mVehicleVelocity(MyRandom::random_float(
        LEVEL_VELOCITIES[static_cast<unsigned int>(level)][0],
        LEVEL_VELOCITIES[static_cast<unsigned int>(level)][1])
      ),
      mAnimalVelocity(MyRandom::random_float(
        LEVEL_VELOCITIES[static_cast<unsigned int>(level)][0],
        LEVEL_VELOCITIES[static_cast<unsigned int>(level)][1])
      )
{
}

Lane::Type RoadProperties::getType() const
{
    return Lane::Type::Road;
}

bool RoadProperties::isReverse() const
{
    return m_reverse_p;
}

bool RoadProperties::getHasVehicle() const
{
    return hasVehicle;
}

bool RoadProperties::getHasAnimal() const
{
    return hasAnimal;
}

float RoadProperties::getVehicleVelocity() const
{
    return mVehicleVelocity;
}

float RoadProperties::getAnimalVelocity() const
{
    return mAnimalVelocity;
}

void RoadProperties::generate()
{
    m_reverse_p = MyRandom::random_range(0, 1);
    // hasVehicle = MyRandom::random_range(0, 1);
    // hasAnimal = MyRandom::random_range(0, 1);
    hasVehicle = true;
    hasAnimal = true;
}
