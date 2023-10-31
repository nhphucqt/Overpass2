#include "SFML/System/Vector2.hpp"
#include <entity/Entity.hpp>

const float INTERVAL = 3600; // use for default interval of existence Vehicle
const int FPS = 60;

Entity::Entity(sf::Texture texture): sprite(texture), velocity(0, 0) {}

Entity::Entity(sf::Texture texture, float vx, float vy): sprite(texture), velocity(vx, vy) {}

Entity::Entity(sf::Texture texture, sf::Vector2f v): sprite(texture), velocity(v) {}

void Entity::setVelocity(sf::Vector2f velocity) {
    this->velocity = velocity;
}

bool Entity::checkCollision(Entity& other) {
   return sprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

sf::FloatRect Entity::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

// void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     states.transform *= getTransform();
//     target.draw(sprite, states);
// }

sf::Vector2f Entity::center() {
    return sf::Vector2f(sprite.getGlobalBounds().getSize().x/2, sprite.getGlobalBounds().getSize().y/2);
}

void Entity::move(sf::Time delta) {
    sprite.move(velocity * delta.asSeconds());
}

Obstacle::Obstacle(sf::Texture texture, bool animal): Entity(texture), isAnimal(animal) {}

Obstacle::Obstacle(sf::Texture texture, float vx, float vy, bool animal): Entity(texture, vx, vy), isAnimal(animal) {}

Obstacle::Obstacle(sf::Texture texture, sf::Vector2f v, bool animal): Entity(texture, v), isAnimal(animal) {}

void Obstacle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

void Obstacle::move() {
    sf::Time timePerFrame = sf::seconds(1.f/(float) FPS);
    move(timePerFrame);
}

void TrafficLight::initInterval(float r, float y, float g) {
    red = sf::seconds(r);
    yellow = sf::seconds(y);
    green = sf::seconds(g);
}

TrafficLight::TrafficLight(sf::Texture texture, float interval): Entity(texture) {
    clock.restart();
    initInterval(interval, interval, interval);
}

TrafficLight::TrafficLight(sf::Texture texture, TrafficColor initColor, float interval): Entity(texture), current(initColor) {
    clock.restart();
    initInterval(interval, interval, interval);
}

TrafficLight::TrafficLight(sf::Texture texture, float r, float y, float g): Entity(texture) {
    clock.restart();
    initInterval(r, y, g);
}

TrafficLight::TrafficLight(sf::Texture texture, TrafficColor initColor, float r, float y, float g): Entity(texture), current(initColor) {
    clock.restart();
    initInterval(r, y, g);
}

void TrafficLight::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

bool TrafficLight::trafficAllow(const Entity& other) {
    return trafficAllow();
}

bool TrafficLight::trafficAllow() {
    sf::Time elapsed = clock.getElapsedTime();
    elapsed %= (red + yellow + green);
    sf::Time interval;
    while (elapsed > sf::Time::Zero) {
        switch (current) {
            case TrafficColor::Red:
                interval = red;
                current = TrafficColor::Green;
                break;
            case TrafficColor::Yellow:
                interval = yellow;
                current = TrafficColor::Yellow;
                break;
            case TrafficColor::Green:
                interval = green;
                current = TrafficColor::Green;
                break;
        }
        elapsed -= interval;
    }
    if (current == TrafficColor::Red)
        return false;
    return true;
}

bool TrafficLight::trafficAllow(const Obstacle& other) {
    if (other.checkAnimal())
        return true;
    return trafficAllow();
}

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
