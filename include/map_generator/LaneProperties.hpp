#ifndef LANE_PROPERTIES_HPP
#define LANE_PROPERTIES_HPP

#include "GameActivity.hpp"
#include "Lane.hpp"

namespace LaneUtils
{
unsigned int random_range(int l, int r);
}

class LaneProperties
{
public:
    LaneProperties(unsigned int map_width, GameActivity::GameLevel level);

    void createLane();
    virtual Lane::Type getType() const = 0;

protected:
    virtual void generate() = 0;
    virtual void setExternalStatic() const = 0;

    int m_width;
    GameActivity::GameLevel m_level;
};

#endif
