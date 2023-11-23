#include <cstdlib>

#include "RiverProperties.hpp"

const int RiverProperties::CELL_TYPES_CNT = 2;
const float RiverProperties::LEVEL_VELOCITIES[] =
{
    1.f, 2.f, 3.f
};

RiverProperties::RiverProperties(int map_width, Level::Type level)
    : LaneProperties(map_width, level),
      m_cells(map_width),
      m_velocity(LEVEL_VELOCITIES[static_cast<int>(level)])
{
    
}

void RiverProperties::generate()
{
    bool non_water_appeared_p = 0;
    for (auto &cell : m_cells)
    {
        cell = static_cast<CellType>(std::rand() % CELL_TYPES_CNT);
        if (cell != CellType::Water)
        {
            non_water_appeared_p = 1;
        }
    }
    if (!non_water_appeared_p)
    {
        m_cells.back() = CellType::NonWater;
    }
}

Lane::Type RiverProperties::getType() const
{
    return Lane::Type::River;
}
