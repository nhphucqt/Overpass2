#ifndef LOG_HPP
#define LOG_HPP
#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Log: public Entity {
public:
    enum Type {Wood, Crocodile};
    Log(Type mType, const TextureManager& textures);
    // virtual unsigned int getCategory() const;

private:
    Type type;
};

#endif