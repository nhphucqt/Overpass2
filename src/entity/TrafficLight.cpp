#include <TrafficLight.hpp>

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