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

    MapRenderer(TextureManager &textures, ViewGroup &foreground,
                unsigned int map_width, unsigned int map_max_height,
                unsigned int level);

    void moveView();
    LaneList const &getLanes() const;

private:
    void initialize();
    void pushLane();
    void popLane();

    std::unique_ptr<Lane>
    convertPropertiesToLane(LaneProperties const &properties) const;

    std::unique_ptr<Field>
    convertPropertiesToLane(FieldProperties const &properties) const;

    std::unique_ptr<Railway>
    convertPropertiesToLane(RailwayProperties const &properties) const;

    std::unique_ptr<Road>
    convertPropertiesToLane(RoadProperties const &properties) const;

    std::unique_ptr<River>
    convertPropertiesToLane(RiverProperties const &properties) const;

    TextureManager &m_textures;
    ViewGroup &m_foreground;
    std::unique_ptr<MapGenerator> m_map_generator;
    LaneList m_lanes;
};

#endif
