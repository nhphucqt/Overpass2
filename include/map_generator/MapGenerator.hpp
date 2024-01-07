#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include "LaneProperties.hpp"

#include <SFML/System/Vector2.hpp>
#include <climits>
#include <list>
#include <memory>

class MapGenerator : public sf::NonCopyable
{
public:
    MapGenerator(unsigned int map_width, unsigned int map_max_height,
                 unsigned int level);

    void moveView(bool initializing_p, bool spawn_lane_p);
    LaneProperties const &getPrevLane() const;
    LaneProperties const &getCurrLane() const;

private:
    static constexpr unsigned int NUM_LEVELS = 5;
    static constexpr unsigned int MAX_RIVER_WIDTH = 5;
    static constexpr unsigned int LEVEL_MAX_CONS_NONFIELDS_CNTS[NUM_LEVELS] = {5, 5, 9, 13, 5};
    static constexpr unsigned int ENDLESS_LEVEL_LANES_CNT[NUM_LEVELS] = {40, 40, 80, UINT_MAX, UINT_MAX};
    static constexpr unsigned int INITIAL_FIELDS_CNT = 5;

    void updateContext(bool initializing_p);

    std::unique_ptr<LaneProperties>
    generateLaneProperties(bool initializing_p, bool spawn_lane_p) const;

    Lane::Type generateLaneType(bool initializing_p) const;

    std::unique_ptr<LaneProperties>
    createLanePropertiesWithType(Lane::Type type, bool initializing_p,
                                 bool spawn_lane_p) const;

    unsigned int getRealLevel() const;

    sf::Vector2u const m_sizes;
    unsigned int const &m_width;
    unsigned int const &m_max_height;
    unsigned int const m_level;

    std::unique_ptr<LaneProperties const> m_prev_lane, m_curr_lane;

    unsigned int m_initial_lanes_cnt;
    unsigned int m_river_width;
    unsigned int m_cons_nonfields_cnt;
    unsigned int m_level_lanes_cnts[NUM_LEVELS];
};

#endif
