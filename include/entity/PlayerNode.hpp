#ifndef PLAYERNODE_HPP
#define PLAYERNODE_HPP

#include <Entity.hpp>
#include <Animation.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

class PlayerNode : public Entity {
public:
    enum State {MoveDown, MoveUp, MoveLeft, MoveRight, Idle, Free};
    PlayerNode(const TextureManager &textures, sf::Vector2f initPos);
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    State getState();
    virtual unsigned int getCategory() const;

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    void updateCurrent(sf::Time delta);

private:
    State state;
    sf::Sprite sprite;
    Animation moveUp;
    Animation moveDown;
    Animation moveLeft;
    Animation moveRight;
    sf::Vector2f lastPos;
};

#endif
