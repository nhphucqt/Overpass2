#ifndef LANE_HPP
#define LANE_HPP
#include <ResourceManager.hpp>
#include <ResourceID.hpp>
#include <ViewGroup.hpp>
#include <TrafficLight.hpp>
#include <Animal.hpp>
#include <Vehicle.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Lane: public ViewGroup {
public:
    Lane(const TextureManager* textures);

private:
    sf::Sprite sprite;
    TextureManager* laneTexture;
	std::vector<Vehicle *> cars;
    TrafficLight* trafficlight;

    void updateCurrent(sf::Time dt);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void loadTextures();
    void buildLane();
};

#endif