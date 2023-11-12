#include <Obstacle.hpp>

Obstacle::Obstacle(sf::Texture texture, bool animal): Entity(texture), isAnimal(animal) {}

Obstacle::Obstacle(sf::Texture texture, float vx, float vy, bool animal): Entity(texture, vx, vy), isAnimal(animal) {}

Obstacle::Obstacle(sf::Texture texture, sf::Vector2f v, bool animal): Entity(texture, v), isAnimal(animal) {}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

void Obstacle::move() {
    sf::Time timePerFrame = sf::seconds(1.f/(float) FPS);
    Entity::move(timePerFrame);
}

bool Obstacle::checkAnimal() const {
    return isAnimal;
}