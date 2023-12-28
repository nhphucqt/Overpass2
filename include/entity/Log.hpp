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
    unsigned int getCategory() const;
	sf::FloatRect getBoundingRect() const;

private:
    Type type;

public:
    struct LogData {
        int type;
        float posX;
        float posY;
        float vx;
        float vy;
        float scaleX;
        float scaleY;
    };
    
    LogData serialize() const;
    void deserialize(LogData& data);
};

#endif