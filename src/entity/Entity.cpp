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

// void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     states.transform *= getTransform();
//     target.draw(sprite, states);
// }

sf::Vector2f Entity::center() {
    return sf::Vector2f(sprite.getGlobalBounds().getSize().x/2, sprite.getGlobalBounds().getSize().y/2);
}

Entity::EntityType Entity::getType() {
    return TYPE;
}

void Entity::move(sf::Time delta) {
    sprite.move(velocity * delta.asSeconds());
}

// TODO: research about how to move an entity properly.
