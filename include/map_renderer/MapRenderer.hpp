#ifndef MAP_RENDERER_HPP
#define MAP_RENDERER_HPP

#include "Field.hpp"
#include "FieldProperties.hpp"
#include "Lane.hpp"
#include "LaneProperties.hpp"
#include "MapGenerator.hpp"
#include "Railway.hpp"
#include "RailwayProperties.hpp"
#include "ResourceID.hpp"
#include "River.hpp"
#include "RiverProperties.hpp"
#include "Road.hpp"
#include "RoadProperties.hpp"
#include "ViewGroup.hpp"

#include <list>
#include <memory>

class MapRenderer : public sf::NonCopyable
{
public:
    using LaneList = std::list<Lane *>;

    MapRenderer(TextureHolder &textures, ViewGroup &foreground,
                unsigned int map_width, unsigned int map_max_height,
                unsigned int level, bool isLoad = false);

    Lane *createNewLane();
    void popLane();
    LaneList const &getLanes() const;
    void loadLanes(std::ifstream &outf);
    void saveLanes(std::ofstream &inf);

    int getLevel() const;

private:
    void initialize();
    void pushLane(bool initializing_p, bool spawn_lane_p);

    Lane *convertPropertiesToLane(LaneProperties const &properties) const;

    Field *convertPropertiesToLane(FieldProperties const &properties) const;

    Railway *convertPropertiesToLane(RailwayProperties const &properties) const;

    Road *convertPropertiesToLane(RoadProperties const &properties) const;

    River *convertPropertiesToLane(RiverProperties const &properties) const;

    TextureHolder &m_textures;
    ViewGroup &m_foreground;
    std::unique_ptr<MapGenerator> m_map_generator;
    LaneList m_lanes;

    sf::Vector2u const m_sizes;
    unsigned int const &m_width;
    unsigned int const &m_max_height;
    unsigned int m_level;
};

#endif
