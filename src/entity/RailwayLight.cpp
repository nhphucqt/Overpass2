#include <RailwayLight.hpp>
#include <AppConfig.hpp>

RailwayLight::RailwayLight(TextureManager& textures):
    onTexture(textures.get(TextureID::RailwayLightOn)),
    offTexture(textures.get(TextureID::RailwayLightOff)) 
{
    sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(cellSize);
    animation.scale(5, 5);
    animation.setFrameSize(sf::Vector2i(16, 16));
    animation.setNumFrames(2);
    animation.setDuration(sf::seconds(0.2));
    animation.setRepeating(true);
    sf::FloatRect bounds = animation.getLocalBounds();
    animation.setOrigin(bounds.getSize().x / 2.f, bounds.getSize().y);
    animation.setPosition(cellSize.x / 2.f, cellSize.y);
    setHitBox(animation.getGlobalBounds());
    turnOff();
}

void RailwayLight::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(animation, states);
}

void RailwayLight::turnOn() {
    isOn = true;
    animation.setTexture(onTexture);
}

void RailwayLight::turnOff() {
    isOn = false;
    animation.setTexture(offTexture);
}

void RailwayLight::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    animation.update(dt);
}

RailwayLight::RailwayLightData RailwayLight::serialize() const {
    RailwayLightData data;
    data.animationData = animation.serialize();
    data.isOn = isOn;
    return data;
}

void RailwayLight::deserialize(const RailwayLightData& data) {
    animation.deserialize(data.animationData);
    isOn = data.isOn;
    if (isOn) {
        turnOn();
    } else {
        turnOff();
    }
}