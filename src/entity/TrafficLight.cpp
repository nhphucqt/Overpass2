#include <TrafficLight.hpp>
#include <AppConfig.hpp>

TrafficLight::TrafficLight(const TextureManager& textures)
: Entity(textures.get(TextureID::TrafficLight)),
red(Duration::Red),
yellow(Duration::Yellow),
green(Duration::Green),
current(Color::Green),
rect(sprite.getLocalBounds())
{
    sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(cellSize);
    sf::FloatRect rect = sprite.getLocalBounds();
    sprite.setTextureRect(sf::IntRect(0, 0, rect.width / 3, rect.height));
    sprite.scale(cellSize.x / (rect.width / 3), cellSize.y / rect.height);
    sprite.scale(0.5f, 0.5f);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height);
    sprite.setPosition(cellSize.x / 2, cellSize.y);
    setHitBox(sprite.getGlobalBounds());
}

TrafficLight::Color TrafficLight::getCurrentColor() {
    return current;
}

void TrafficLight::setDuration(int red, int yellow, int green) {
    this->red = sf::seconds(red);
    this->yellow = sf::seconds(yellow);
    this->green = sf::seconds(green);
}

void TrafficLight::updateCurrent(sf::Time dt) {
    updateCurrentColor(dt);
    sprite.setTextureRect(sf::IntRect(rect.width / 3 * current, 0, rect.width / 3, rect.height));
}

void TrafficLight::updateCurrentColor(sf::Time dt) {
    elapsed += dt;
    if (elapsed < green)
        current = Color::Green;
    else if (elapsed < green + yellow)
        current = Color::Yellow;
    else if (elapsed < red + yellow + green)
        current = Color::Red;
    else
        elapsed %= (red + yellow + green);
}

bool TrafficLight::isRed() {
    return current == Color::Red;
}

bool TrafficLight::isYellow() {
    return current == Color::Yellow;
}

bool TrafficLight::isGreen() {
    return current == Color::Green;
}