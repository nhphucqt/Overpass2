#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include <memory>
#include <queue>
#include <SFML/System/Vector2.hpp>

#include "LaneProperties.hpp"
#include "StreetProperties.hpp"
#include "RiverProperties.hpp"
#include "PavementProperties.hpp"
#include "RailProperties.hpp"

class MapGenerator
{
public:
    using LaneQueue = std::queue<std::unique_ptr<LaneProperties>>;
    
    MapGenerator(int map_width, int map_height, Level::Type level);

    void moveView();
    LaneQueue const& getLanes() const;
    
private:
    static const int MAX_RIVER_WIDTH;
    static const int LEVEL_MAX_CONSECUTIVE_LANES_CNT[Level::TYPES_CNT];
    
    static std::unique_ptr<LaneProperties> createLane(Lane::Type type,
                                                      int width,
                                                      Level::Type level);
    
    void initialize();
    std::unique_ptr<LaneProperties> generateLane() const;
    Lane::Type generateLaneType() const;
    void updateContext();

    sf::Vector2i m_sizes;
    int &m_width, &m_height;
    Level::Type m_level;
    int m_river_width, m_consecutive_lanes_cnt;
    LaneQueue m_lanes;
};

#endif
