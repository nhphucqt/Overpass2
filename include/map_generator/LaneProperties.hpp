#ifndef LANE_PROPERTIES_HPP
#define LANE_PROPERTIES_HPP

#include "Lane.hpp"

class LaneProperties
{
public:
    LaneProperties(unsigned int map_width, unsigned int level);
    virtual ~LaneProperties() = default;

    void create();
    virtual Lane::Type getType() const = 0;

protected:
    virtual void generate() = 0;

    unsigned int const m_width;
    unsigned int const m_level;
};

#endif
