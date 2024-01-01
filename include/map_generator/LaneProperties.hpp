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

    void create();
    virtual Lane::Type getType() const = 0;
    virtual std::unique_ptr<Lane> convertToLane() const = 0;

protected:
    virtual void generate() = 0;
    virtual void setExternalStatic() const = 0;

    unsigned int const m_width;
    GameActivity::GameLevel const m_level;
};

#endif
