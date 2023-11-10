#include <Vehicle.hpp>

Vehicle::Vehicle(sf::Texture texture): Entity(texture), interval(sf::seconds(INTERVAL)), health(1) {}

Vehicle::Vehicle(sf::Texture texture, float t): Entity(texture), interval(sf::seconds(t)), health(1) {}

Vehicle::Vehicle(sf::Texture texture, int hp): Entity(texture), interval(sf::seconds(INTERVAL)), health(hp) {}

bool Vehicle::isRidden(Entity& other) {
    return checkCollision(other) && this->getGlobalBounds().contains(other.center());
}

void Vehicle::move() {
    sf::Time timePerFrame = sf::seconds(1.f/(float) FPS);
    move(timePerFrame);
}

bool Vehicle::isDestroyed() {
    return health <= 0 && interval <= sf::Time::Zero;
}

bool Vehicle::collides() {
    --health;
    return isDestroyed();
}

void Vehicle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}