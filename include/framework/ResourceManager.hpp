#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include "ResourceID.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <map>

template <typename Resource, typename Identifier>
class ResourceManager
{
public:
    void load(Identifier id, const std::string &filename);
    Resource &get(Identifier id);
    const Resource &get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include <ResourceManager.inl>

#endif