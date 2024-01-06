#include "MapGenerator.hpp"

#include "FieldProperties.hpp"
#include "GameActivity.hpp"
#include "LaneProperties.hpp"
#include "RailwayProperties.hpp"
#include "RiverProperties.hpp"
#include "RoadProperties.hpp"
#include <MyRandom.hpp>

#include <memory>

MapGenerator::MapGenerator(unsigned int map_width, unsigned int map_max_height,
                           unsigned int level)
    : m_sizes(map_width, map_max_height),
      m_width(m_sizes.x),
      m_max_height(m_sizes.y),
      m_level(level),
      m_level_lanes_cnts{0, 0, 0},
      m_initial_lanes_cnt(0)
{
}

void MapGenerator::moveView(bool initializing_p)
{
    m_prev_lane = std::move(m_curr_lane);
    m_curr_lane = generateLaneProperties(initializing_p);
    updateContext(initializing_p);
}

LaneProperties const &MapGenerator::getPrevLane() const
{
    return *m_prev_lane;
}

LaneProperties const &MapGenerator::getCurrLane() const
{
    return *m_curr_lane;
}

std::unique_ptr<LaneProperties>
MapGenerator::generateLaneProperties(bool initializing_p) const
{
    Lane::Type type = generateLaneType(initializing_p);
    std::unique_ptr<LaneProperties> lane_properties =
        MapGenerator::createLanePropertiesWithType(type, initializing_p);
    lane_properties->create();
    return lane_properties;
}

Lane::Type MapGenerator::generateLaneType(bool initializing_p) const
{
    if (initializing_p && m_initial_lanes_cnt < INITIAL_FIELDS_CNT)
    {
        return Lane::Type::Field;
    }

    if (m_cons_nonfields_cnt
        == LEVEL_MAX_CONS_NONFIELDS_CNTS[static_cast<unsigned int>(m_level)])
    {
        return static_cast<Lane::Type>(MyRandom::random_range(2) + 1);
    }

    if (m_river_width == MAX_RIVER_WIDTH)
    {
        int lane_type = MyRandom::random_range(
            0, static_cast<unsigned int>(Lane::Type::Count) - 1);
        if (lane_type == static_cast<unsigned int>(Lane::Type::River))
        {
            ++lane_type;
        }
        return static_cast<Lane::Type>(lane_type);
    }

    return static_cast<Lane::Type>(MyRandom::random_range(
        0, static_cast<unsigned int>(Lane::Type::Count) - 1));
}

std::unique_ptr<LaneProperties>
MapGenerator::createLanePropertiesWithType(Lane::Type type,
                                           bool initializing_p) const
{
    unsigned int real_level = getRealLevel();
    switch (type)
    {
    case Lane::Type::Field:
    {
        return std::make_unique<FieldProperties>(
            m_width, real_level, m_prev_lane.get(), initializing_p);
    }

    case Lane::Type::Railway:
        return std::make_unique<RailwayProperties>(m_width, real_level);

    case Lane::Type::Road:
        return std::make_unique<RoadProperties>(m_width, real_level);

    case Lane::Type::River:
        return std::make_unique<RiverProperties>(m_width, real_level);

    default:
        return nullptr;
    }
}

void MapGenerator::updateContext(bool initializing_p)
{
    m_initial_lanes_cnt += initializing_p;
    ++m_level_lanes_cnts[static_cast<unsigned int>(getRealLevel())];
    Lane::Type back_type = m_curr_lane->getType();
    m_river_width = (back_type == Lane::Type::River ? m_river_width + 1 : 0);
    m_cons_nonfields_cnt =
        (back_type == Lane::Type::Road || back_type == Lane::Type::Railway
             ? m_cons_nonfields_cnt + 1
             : 0);
}

unsigned int MapGenerator::getRealLevel() const
{
    GameActivity::GameLevel real_level =
        static_cast<GameActivity::GameLevel>(m_level);
    if (static_cast<GameActivity::GameLevel>(m_level)
        == GameActivity::GameLevel::Endless)
    {
        real_level = (m_level_lanes_cnts[0] < ENDLESS_LEVEL_LANES_CNT[0]
                          ? GameActivity::GameLevel::Easy
                          : (m_level_lanes_cnts[1] < ENDLESS_LEVEL_LANES_CNT[1]
                                 ? GameActivity::GameLevel::Medium
                                 : GameActivity::GameLevel::Hard));
    }
    return static_cast<unsigned int>(real_level);
}
