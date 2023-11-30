#include <cstdlib>

#include "PavementProperties.hpp"

const int PavementProperties::CELL_TYPES_CNT = 2;

PavementProperties::PavementProperties(int map_width, Level::Type level)
    : LaneProperties(map_width, level),
      m_cells(map_width)
{
    
}

void PavementProperties::generate()
{
    bool blank_appeared_p = 0;
    for (auto &cell : m_cells)
    {
        cell = static_cast<CellType>(std::rand() % CELL_TYPES_CNT);
        if (cell == CellType::Blank)
        {
            blank_appeared_p = 1;
        }
    }
    if (!blank_appeared_p)
    {
        m_cells.back() = CellType::Blank;
    }
}

Lane::Type PavementProperties::getType() const
{
    return Lane::Type::Pavement;
}

std::vector<PavementProperties::CellType> const&
PavementProperties::getCells() const
{
    return m_cells;
}
