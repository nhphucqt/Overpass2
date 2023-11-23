#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include <memory>

#include "LaneProperties.hpp"
#include "StreetProperties.hpp"
#include "RiverProperties.hpp"
#include "PavementProperties.hpp"
#include "RailProperties.hpp"

class MapGenerator
{
public:
    using LaneQueue = std::queue<std::unique_ptr<LaneProperties>>;
    
    MapGenerator(int map_width, innt map_height, Level level);

    void moveView();
    LaneQueue const& getLanes() const;
    
private:
    static std::unique_ptr<LaneProperties> createLane(Lane::Type type,
                                                      int width,
                                                      Level::Type level);
    
    void initialize();
    std::unique_ptr<LaneProperties> generateLane() const;
    Lane::Type generateLaneType() const;

    sf::Vector2u m_sizes;
    int &m_width, &m_height;
    Level::Type m_level;
    LaneQueue m_lanes;
};

#endif
