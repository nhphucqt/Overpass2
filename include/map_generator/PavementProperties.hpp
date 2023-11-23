#ifndef PAVEMENT_PROPERTIES_HPP
#define PAVEMENT_PROPERTIES_HPP

#include <vector>

#include "LaneProperties.hpp"

class PavementProperties : public LaneProperties
{
public:
    PavementProperties(int map_width, Level::Type level);
    
    virtual void generate() override;
    virtual Lane::Type getType() const override;

private:
    using LaneProperties::m_level;
    
    std::vector<bool> m_cells;
};

#endif
