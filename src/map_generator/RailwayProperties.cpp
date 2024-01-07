#include "RailwayProperties.hpp"

#include "Railway.hpp"
#include <MyRandom.hpp>

#include <memory>

RailwayProperties::RailwayProperties(unsigned int map_width, unsigned int level)
    : LaneProperties(map_width, level),
      trainInterval(MyRandom::random_range(LEVEL_INV[level][0], LEVEL_INV[level][1])),
      trainDelay(MyRandom::random_range(LEVEL_DELAY[level][0], LEVEL_DELAY[level][1])),
      trainOffSet(MyRandom::random_range(LEVEL_TRAIN_OFFSET[level][0], LEVEL_TRAIN_OFFSET[level][1]))
{
}

Lane::Type RailwayProperties::getType() const
{
    return Lane::Type::Railway;
}

bool RailwayProperties::isReverse() const
{
    return m_reverse_p;
}

float RailwayProperties::getTrainInterval() const
{
    return trainInterval;
}

float RailwayProperties::getTrainDelay() const
{
    return trainDelay;
}

float RailwayProperties::getTrainOffSet() const
{
    return trainOffSet;
}

void RailwayProperties::generate()
{
    m_reverse_p = MyRandom::random_range(0, 1);
}
