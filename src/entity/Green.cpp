#include <Green.hpp>

TextureID toTextureID(Green::Type type) {
	switch (type) {
	case Green::Tree:
		return TextureID::Tree;

	case Green::Bush:
		return TextureID::Bush;

    case Green::CircleBush:
        return TextureID::CircleBush;
	}
	return TextureID::Tree;
}

Green::Green(Type mType, const TextureManager &textures):
type(mType),
Entity(textures.get(toTextureID(mType)))
{
    if (type == Green::Tree)
        sprite.scale(6, 6);
    else if (type == Green::Bush)
        sprite.scale(5, 5);
    else if (type == Green::CircleBush)
        sprite.scale(3, 3);
    sf::FloatRect bounds = sprite.getLocalBounds();
    if (type == Green::Tree)
        sprite.setOrigin(bounds.width / 2.f, bounds.height);
    else
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Green::getCategory() const {
    return Category::Green;
}

sf::FloatRect Green::getBoundingRect() const {
    sf::FloatRect rect = Entity::getBoundingRect();
    if (type == Tree) {
        rect.top += 90;
        rect.height = 128;
    }
    return rect;
}

void Green::setVelocity(sf::Vector2f velocity) {
}

void Green::setVelocity(float vx, float vy) {
}

void Green::accelerate(sf::Vector2f velocity) {
}

void Green::accelerate(float vx, float vy) {
}

Green::GreenData Green::serialize() const {
    Green::GreenData data;
    data.type = static_cast<int>(type);
    data.x = getPosition().x;
    data.y = getPosition().y;
    return data;
}

void Green::deserialize(Green::GreenData& data) {
    type = static_cast<Green::Type>(data.type);
    setPosition(data.x, data.y);
}