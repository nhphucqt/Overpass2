#include <cstdlib>
#include <ctime>

#include "MapGenerator.hpp"

MapGenerator::MapGenerator(int map_width, int map_height)
    : m_sizes(map_width, map_height),
      m_width(m.sizes.x), m_height(m.sizes.y)
{
    std::srand(std::time(nullptr));
    
    initialize();
}

void MapGenerator::moveView()
{
    m_lanes.pop();
    m_lanes.push(generateLane());
}

LaneQueue const& MapGenerator::getLanes() const
{
    return m_lanes;
}

std::unique_ptr<LaneProperties> MapGenerator::createLane(Lane::Type type,
                                                         int width,
                                                         Level::Type level)
{
    switch (type)
    {
    case Lane::Type::Street:
        return std::make_unique<StreetProperties>(width, level);

    case Lane::Type::River:
        return std::make_unique<RiverProperties>(width, level);

    case Lane::Type::Pavement:
        return std::make_unique<PavementProperties>(width, level);

    default:
        return std::make_unique<RailProperties>(width, level);
    }
    return nullptr;
}

void MapGenerator::initialize()
{
    for (int i = 0; i < m_height; ++i)
    {
        m_lanes.push(generateLane());
    }
}

std::unique_ptr<LaneProperties> MapGenerator::generateLane() const
{
    Lane::Type type = generateLaneType();
    std::unique_ptr<LaneProperties> lane = MapGenerator::createLane(type,
                                                                    m_width,
                                                                    m_level);
    lane->generate();
    return lane;
}

Lane::Type MapGenerator::generateLaneType() const
{
    
}
