#ifndef PLAYERNODE_HPP
#define PLAYERNODE_HPP

#include <Entity.hpp>
#include <Animation.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <Lane.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

class PlayerNode : public Entity {
public:
    enum State {MoveDown, MoveUp, MoveLeft, MoveRight, Idle, Mounted, Free};
    PlayerNode(const TextureManager &textures, std::vector<Lane *>& lanes, int currentLane = 0);
    void move(sf::Vector2f velocity);
    void move(float vx, float vy);
    State getState();
    unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
    int getCurrentLane();
    void moveBack();

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    void updateCurrent(sf::Time delta);
    void adaptPosition();

private:
    State state;
    int curLane;
    std::vector<Lane *>& lanes;
    sf::Sprite sprite;
    Animation moveUp;
    Animation moveDown;
    Animation moveLeft;
    Animation moveRight;
    sf::Vector2f lastPos;
};

#endif
