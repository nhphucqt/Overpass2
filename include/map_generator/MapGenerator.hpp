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
    using LanePropertiesList = std::list<std::unique_ptr<LaneProperties>>;

    MapGenerator(unsigned int map_width, unsigned int map_max_height,
                 unsigned int level);

    void moveView();
    LanePropertiesList const &getLanes() const;

private:
    static constexpr unsigned int MAX_RIVER_WIDTH = 5;
    static constexpr unsigned int LEVEL_MAX_CONS_NONFIELDS_CNTS[] = {5, 9, 13};
    static constexpr unsigned int ENDLESS_LEVEL_LANES_CNT[] = {40, 80,
                                                               UINT_MAX};
    static constexpr unsigned int INITIAL_FIELDS_CNT = 2;

    void initialize();
    void updateContext();

    std::unique_ptr<LaneProperties>
    generateLaneProperties(bool initializing_p) const;

    Lane::Type generateLaneType(bool initializing_p) const;

    std::unique_ptr<LaneProperties>
    createLanePropertiesWithType(Lane::Type type, bool initializing_p) const;

    unsigned int getRealLevel() const;

    sf::Vector2u const m_sizes;
    unsigned int const &m_width;
    unsigned int const &m_max_height;
    unsigned int const m_level;

    LanePropertiesList m_lanes_properties;

    unsigned int m_river_width;
    unsigned int m_cons_nonfields_cnt;
    unsigned int m_level_lanes_cnts[3];
};

#endif
