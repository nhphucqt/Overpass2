#include "SFML/System/Vector2.hpp"
#include <entity/Entity.hpp>

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

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite, states);
}

sf::Vector2f Entity::center() {
    return sf::Vector2f(sprite.getGlobalBounds().getSize().x/2, sprite.getGlobalBounds().getSize().y/2);
}

Obstacle::Obstacle(sf::Texture texture): Entity(texture) {}

Obstacle::Obstacle(sf::Texture texture, float vx, float vy): Entity(texture, vx, vy) {}

Obstacle::Obstacle(sf::Texture texture, sf::Vector2f v): Entity(texture, v) {}

void Obstacle::move() {
    sf::Time timePerFrame = sf::seconds(1.f/60.f);
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

const float INTERVAL = 3600;

Vehicle::Vehicle(sf::Texture texture): Entity(texture), interval(sf::seconds(INTERVAL)), health(1) {}

Vehicle::Vehicle(sf::Texture texture, float t): Entity(texture), interval(sf::seconds(t)), health(1) {}

Vehicle::Vehicle(sf::Texture texture, int hp): Entity(texture), interval(sf::seconds(INTERVAL)), health(hp) {}

bool Vehicle::isRidden(Entity& other) {
    return checkCollision(other) && this->getGlobalBounds().contains(other.center());
}

bool Vehicle::isDestroyed() {
    return health <= 0 && interval <= sf::Time::Zero;
}

bool Vehicle::collides() {
    --health;
    return isDestroyed();
}
