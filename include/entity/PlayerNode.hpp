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

#include <fstream>
#include <iostream>

class PlayerNode : public Entity {
public:
    enum State {MoveDown, MoveUp, MoveLeft, MoveRight, Idle, Mounted, Free};
    PlayerNode(const TextureManager &textures, std::vector<Lane *>& lanes, int currentLane = 0, bool isLoad = false);
    void move(sf::Vector2f velocity);
    void move(float vx, float vy);
    State getState();
    unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
    int getCurrentLane();
    void setOnRiver(bool onRiver);
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
    bool onRiver;

private:
    struct PlayerData {
        int state;
        int curLane;
        bool onRiver;
        float x;
    };

public: 
    void savePlayerData(const std::string& filename);
    void loadPlayerData(const std::string& filename);
};

#endif
