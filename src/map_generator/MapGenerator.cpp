#include <cstdlib>
#include <ctime>

#include "MapGenerator.hpp"

const int MapGenerator::MAX_RIVER_WIDTH = 5;
const int MapGenerator::LEVEL_MAX_CONSECUTIVE_LANES_CNT[Level::TYPES_CNT] =
{
    5, 9, 13
};

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
    updateContext();
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
    if (m_consecutive_lanes_cnt == LEVEL_MAX_CONSECUTIVE_LANES_CNT[m_level])
    {
        return static_cast<Lane::Type>((std::rand() & 1) + 1);
    }

    if (m_river_width == MAX_RIVER_WIDTH)
    {
        int lane_type = std::rand() % Lane::TYPES_CNT;
        if (lane_type == static_cast<int>(Lane::Type::River))
        {
            ++lane_type;
        }
        return static_cast<Lane::Type>(lane_type);
    }

    return static_cast<Lane::Type>(std::rand() % Lane::TYPES_CNT);
}

void MapGenerator::updateContext()
{
    Lane::Type back_type = m_lanes.back()->getType();
    m_river_width = (back_type == Lane::Type::River ? m_river_width + 1 : 0);
    m_consecutive_lanes_cnt = (back_type == Lane::Type::Street || back_type == Lane::Type::Rail ?
                               m_consecutive_lanes_cnt + 1 :
                               0);
}
