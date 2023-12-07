#include <TrafficLight.hpp>

TrafficLight::TrafficLight(const TextureManager& textures)
: Entity(textures.get(TextureID::TrafficLight)),
red(Duration::Red),
yellow(Duration::Yellow),
green(Duration::Green),
current(Color::Green),
rect(sprite.getLocalBounds())
{
    sf::FloatRect rect = sprite.getLocalBounds();
    sprite.setTextureRect(sf::IntRect(0, 0, rect.width / 3, rect.height));
    sprite.setScale(0.5, 0.5);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

TrafficLight::Color TrafficLight::getCurrentColor() {
    return current;
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

// unsigned int TrafficLight::getCategory() const
// {
//     return Category::TrafficLight;
// }