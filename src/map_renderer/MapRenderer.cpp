#include "MapRenderer.hpp"

#include "Field.hpp"
#include "FieldProperties.hpp"
#include "LaneProperties.hpp"
#include "MapGenerator.hpp"
#include "Railway.hpp"
#include "RailwayProperties.hpp"
#include "River.hpp"
#include "RiverProperties.hpp"
#include "Road.hpp"
#include "RoadProperties.hpp"
#include "UserSession.hpp"
#include "UtilitySave.hpp"

#include <memory>

MapRenderer::MapRenderer(TextureManager &textures, ViewGroup &foreground,
                         unsigned int map_width, unsigned int map_max_height,
                         unsigned int level, bool isLoad)
    : m_textures(textures),
      m_foreground(foreground),
      m_sizes(map_width, map_max_height),
      m_width(m_sizes.x),
      m_max_height(m_sizes.y),
      m_level(level)
{
    if (!isLoad)
    {
        initialize();
    }
}

Lane *MapRenderer::createNewLane()
{
    // popLane();
    pushLane(0, 0);
    return m_lanes.back();
}

MapRenderer::LaneList const &MapRenderer::getLanes() const
{
    return m_lanes;
}

void MapRenderer::initialize()
{
    m_map_generator =
        std::make_unique<MapGenerator>(m_width, m_max_height, m_level);
    for (int i = 0; i < m_max_height; ++i)
    {
        pushLane(1, (i == 3));
    }
}

void MapRenderer::pushLane(bool initializing_p, bool spawn_lane_p)
{
    m_map_generator->moveView(initializing_p, spawn_lane_p);
    Lane *newLane = convertPropertiesToLane(m_map_generator->getCurrLane());
    if (!initializing_p)
    {
        for (auto lane : m_lanes)
        {
            lane->move(sf::Vector2f(0.f, newLane->getSize().y));
        }
    }
    m_lanes.push_back(newLane);
}

void MapRenderer::saveLanes(std::ofstream &outf)
{
    outf.write(reinterpret_cast<const char *>(&m_level), sizeof(m_level));

    int laneSize = m_lanes.size();
    outf.write(reinterpret_cast<const char *>(&laneSize), sizeof(laneSize));
    if (m_lanes.size() > 0)
    {
        for (auto it = m_lanes.begin(); it != m_lanes.end(); ++it)
        {
            Lane *lane = *it;
            lane->saveLaneData(outf);
        }
    }
}

void MapRenderer::loadLanes(std::ifstream &inf)
{
    inf.read(reinterpret_cast<char *>(&m_level), sizeof(m_level));

    m_map_generator =
        std::make_unique<MapGenerator>(m_width, m_max_height, m_level);

    int laneSize;
    inf.read(reinterpret_cast<char *>(&laneSize), sizeof(laneSize));
    for (int i = 0; i < laneSize; ++i)
    {
        int laneType;
        bool laneIsReverse;
        inf.read(reinterpret_cast<char *>(&laneType), sizeof(laneType));
        inf.read(reinterpret_cast<char *>(&laneIsReverse),
                 sizeof(laneIsReverse));
        // std::unique_ptr<Lane> lane;
        Lane *lane;
        switch (static_cast<Lane::Type>(laneType))
        {
        case Lane::Type::Road:
            float animalVelocity, vehicleVelocity;
            bool hasAnimal, hasVehicle;
            inf.read(reinterpret_cast<char *>(&animalVelocity),
                     sizeof(animalVelocity));
            inf.read(reinterpret_cast<char *>(&vehicleVelocity),
                     sizeof(vehicleVelocity));
            inf.read(reinterpret_cast<char *>(&hasAnimal), sizeof(hasAnimal));
            inf.read(reinterpret_cast<char *>(&hasVehicle), sizeof(hasVehicle));
            lane = new Road(&m_textures, laneIsReverse, animalVelocity,
                            vehicleVelocity, hasAnimal, hasVehicle, true);
            lane->loadLaneData(inf);
            break;
        case Lane::Type::River:
            float logVelocity;
            inf.read(reinterpret_cast<char *>(&logVelocity),
                     sizeof(logVelocity));
            lane = new River(&m_textures, laneIsReverse, logVelocity, true);
            lane->loadLaneData(inf);
            break;
        case Lane::Type::Field:
            lane = new Field(&m_textures, laneIsReverse, true);
            lane->loadLaneData(inf);
            break;
        case Lane::Type::Railway:
            float trainInterval, trainDelay, trainOffSet;
            inf.read(reinterpret_cast<char *>(&trainInterval),
                     sizeof(trainInterval));
            inf.read(reinterpret_cast<char *>(&trainDelay), sizeof(trainDelay));
            inf.read(reinterpret_cast<char *>(&trainOffSet),
                     sizeof(trainOffSet));
            lane = new Railway(&m_textures, laneIsReverse, trainInterval,
                               trainDelay, trainOffSet, true);
            lane->loadLaneData(inf);
            break;
        default:
            throw std::runtime_error("LOAD ERR: Lane type not found");
        }
        m_lanes.push_back(lane);
    }
}

void MapRenderer::popLane()
{
    m_lanes.pop_front();
}

Lane *
MapRenderer::convertPropertiesToLane(LaneProperties const &properties) const
{
    switch (properties.getType())
    {
    case Lane::Type::Field:
        return convertPropertiesToLane(
            dynamic_cast<FieldProperties const &>(properties));

    case Lane::Type::Railway:
        return convertPropertiesToLane(
            dynamic_cast<RailwayProperties const &>(properties));

    case Lane::Type::Road:
        return convertPropertiesToLane(
            dynamic_cast<RoadProperties const &>(properties));

    case Lane::Type::River:
        return convertPropertiesToLane(
            dynamic_cast<RiverProperties const &>(properties));

    default:
        return nullptr;
    }
}

Field *
MapRenderer::convertPropertiesToLane(FieldProperties const &properties) const
{
    return new Field(&m_textures, false, properties.getGreens());
}

Railway *
MapRenderer::convertPropertiesToLane(RailwayProperties const &properties) const
{
    return new Railway(&m_textures, properties.isReverse(),
                       properties.getTrainInterval(),
                       properties.getTrainDelay(), properties.getTrainOffSet());
}

Road *
MapRenderer::convertPropertiesToLane(RoadProperties const &properties) const
{
    auto road = new Road(&m_textures, properties.isReverse(),
                         properties.getVehicleVelocity(),
                         properties.getAnimalVelocity(),
                         properties.getHasVehicle(), properties.getHasAnimal());
    return road;
}

River *
MapRenderer::convertPropertiesToLane(RiverProperties const &properties) const
{
    auto river = new River(&m_textures, properties.isReverse(),
                           properties.getVelocity());
    river->setLogVelocity(properties.getVelocity());
    return river;
}

int MapRenderer::getLevel() const
{
    return m_level;
}
