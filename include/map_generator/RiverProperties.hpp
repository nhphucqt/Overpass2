#ifndef RIVER_PROPERTIES_HPP
#define RIVER_PROPERTIES_HPP

#include "LaneProperties.hpp"

class RiverProperties : public LaneProperties
{
public:
    RiverProperties(int map_width, Level::Type level);
    
    virtual void generate() override;
    virtual Lane::Type getType() const override;

private:
    using LaneProperties::m_level;
    
    float m_velocity;
    std::vector<bool> m_cells;
};

#endif
