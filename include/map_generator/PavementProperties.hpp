#ifndef PAVEMENT_PROPERTIES_HPP
#define PAVEMENT_PROPERTIES_HPP

#include <vector>

#include "LaneProperties.hpp"

class PavementProperties : public LaneProperties
{
public:
    enum class CellType : int
    {
        Blank, Obstacle
    };
    
    PavementProperties(int map_width, Level::Type level);
    
    virtual void generate() override;
    virtual Lane::Type getType() const override;

private:
    static const int CELL_TYPES_CNT;
    
    using LaneProperties::m_level;
    
    std::vector<CellType> m_cells;
};

#endif
