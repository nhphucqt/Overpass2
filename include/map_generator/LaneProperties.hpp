#ifndef LANE_PROPERTIES_HPP
#define LANE_PROPERTIES_HPP

#include <memory>

namespace Lane
{
    enum class Type : int
    {
        Street = 0, River, Pavement, Rail
    };

    const int TYPES_CNT = 4;
}

namespace Level
{
    enum Type
    {
        Easy = 0, Medium, Hard
    };

    const int TYPES_CNT = 3;
}

class LaneProperties
{
public:
    LaneProperties(int map_width, Level::Type level);
    
    virtual void generate() = 0;
    virtual Lane::Type getType() const = 0;

protected:
    int m_width;
    Level::Type m_level;
};

#endif
