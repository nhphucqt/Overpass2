#ifndef PLAYERNODE_HPP
#define PLAYERNODE_HPP

#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

class PlayerNode : public Entity {
public:
    PlayerNode(const TextureManager &textures);
    virtual bool checkCollision(Entity &other);
    virtual sf::FloatRect getGlobalBounds();
    virtual sf::Vector2f center();
    virtual unsigned int getCategory() const;

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
};

#endif
