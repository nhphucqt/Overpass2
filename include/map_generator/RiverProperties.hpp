#ifndef RIVER_PROPERTIES_HPP
#define RIVER_PROPERTIES_HPP

#include <vector>

#include "LaneProperties.hpp"

class RiverProperties : public LaneProperties
{
public:
    enum class CellType
    {
        Water = 0, NonWater
    };
    
    RiverProperties(int map_width, Level::Type level);
    
    virtual void generate() override;
    virtual Lane::Type getType() const override;

private:
    static const int CELL_TYPES_CNT;
    static const float LEVEL_VELOCITIES[Level::TYPES_CNT];
    
    using LaneProperties::m_level;
    
    float m_velocity;
    std::vector<CellType> m_cells;
};

#endif
