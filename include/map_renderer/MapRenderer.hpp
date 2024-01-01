#ifndef MAP_RENDERER_HPP
#define MAP_RENDERER_HPP

#include "GameActivity.hpp"
#include "ResourceID.hpp"
#include "ViewGroup.hpp"

#include <list>
#include <memory>

class MapGenerator;

class Lane;
class Field;
class Railway;
class Road;
class River;

class LaneProperties;
class FieldProperties;
class RailwayProperties;
class RoadProperties;
class RiverProperties;

class MapRenderer : public ViewGroup, public sf::NonCopyable
{
public:
    using LaneList = std::list<Lane *>;

    MapRenderer(TextureManager const &m_textures, ViewGroup const &foreground,
                unsigned int map_width, unsigned int map_max_height,
                GameActivity::GameLevel level);

    void moveView();
    LaneList getLanes() const;

private:
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
};

#endif
