#include "MapGenerator.hpp"

#include "FieldProperties.hpp"
#include "LaneProperties.hpp"
#include "RailwayProperties.hpp"
#include "RiverProperties.hpp"
#include "RoadProperties.hpp"

#include <memory>

MapGenerator::MapGenerator(unsigned int map_width, unsigned int map_max_height,
                           GameActivity::GameLevel level)
    : m_sizes(map_width, map_max_height + OUT_OF_VIEW_LANES_CNT),
      m_width(m_sizes.x),
      m_max_height(m_sizes.y),
      m_level(level)
{
    std::srand(std::time(nullptr));

    initialize();
}

void MapGenerator::moveView()
{
    m_lanes.pop_back();
    m_lanes.push_front(generateLane());
    updateContext();
}

MapGenerator::LaneList const &MapGenerator::getLanes() const
{
    return m_lanes;
}

void MapGenerator::initialize()
{
    for (int i = 0; i < m_max_height; ++i)
    {
        m_lanes.push_front(generateLane());
    }
}

std::unique_ptr<LaneProperties> MapGenerator::generateLane() const
{
    Lane::Type type = generateLaneType();
    std::unique_ptr<LaneProperties> lane =
        MapGenerator::createLaneWithType(type);
    lane->createLane();
    return lane;
}

Lane::Type MapGenerator::generateLaneType() const
{
    if (m_cons_nonfields_cnt
        == LEVEL_MAX_CONS_NONFIELDS_CNTS[static_cast<int>(m_level)])
    {
        return static_cast<Lane::Type>(LaneUtils::random_range(0, 1) + 1);
    }

    if (m_river_width == MAX_RIVER_WIDTH)
    {
        int lane_type = LaneUtils::random_range(
            0, static_cast<unsigned int>(Lane::Type::Count) - 1);
        if (lane_type == static_cast<int>(Lane::Type::River))
        {
            ++lane_type;
        }
        return static_cast<Lane::Type>(lane_type);
    }

    return static_cast<Lane::Type>(LaneUtils::random_range(
        0, static_cast<unsigned int>(Lane::Type::Count) - 1));
}

std::unique_ptr<LaneProperties>
MapGenerator::createLaneWithType(Lane::Type type) const
{
    switch (type)
    {
    case Lane::Type::Field:
    {
        LaneProperties const *prev_lane =
            (m_lanes.empty() ? 0 : m_lanes.back().get());
        return std::make_unique<FieldProperties>(m_width, m_level, prev_lane);
    }

    case Lane::Type::Railway:
        return std::make_unique<RailwayProperties>(m_width, m_level);

    case Lane::Type::Road:
        return std::make_unique<RoadProperties>(m_width, m_level);

    case Lane::Type::River:
        return std::make_unique<RiverProperties>(m_width, m_level);

    default:
        return nullptr;
    }
}

void MapGenerator::updateContext()
{
    Lane::Type back_type = m_lanes.back()->getType();
    m_river_width = (back_type == Lane::Type::River ? m_river_width + 1 : 0);
    m_cons_nonfields_cnt =
        (back_type == Lane::Type::Road || back_type == Lane::Type::Railway
             ? m_cons_nonfields_cnt + 1
             : 0);
}
