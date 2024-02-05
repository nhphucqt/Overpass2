#include <Green.hpp>
#include <AppConfig.hpp>

TextureID Green::toTextureID(Type type) {
	switch (type) {
	case Type::Tree:
		return TextureID::Tree;
	case Type::Bush:
		return TextureID::Bush;
    case Type::CircleBush:
        return TextureID::CircleBush;
	}
	return TextureID::Tree;
}

Green::Green(Type mType, const TextureHolder &textures)
    : type(mType)
    , Entity(textures.get(toTextureID(mType)))
{
    sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(cellSize);
    if (type == Type::Tree)
        sprite.scale(6, 6);
    else if (type == Type::Bush)
        sprite.scale(5, 5);
    else if (type == Type::CircleBush)
        sprite.scale(3, 3);
    sf::FloatRect bounds = sprite.getLocalBounds();
    if (type == Type::Tree)
        sprite.setOrigin(bounds.width / 2.f, bounds.height - 10);
    else
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    sprite.setPosition(getBoundingRect().getSize() / 2.f);
    sf::FloatRect rect = Entity::getBoundingRect();
    rect.width *= 0.6;
    rect.height *= 0.6;
    sf::Vector2f newPos = (getLocalBounds().getSize() - rect.getSize()) / 2.f;
    rect.left = newPos.x;
    rect.top = newPos.y;
    setHitBox(rect);
}

unsigned int Green::getCategory() const {
    return ViewCategory::Green;
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
    setOrigin(getLocalBounds().getSize() / 2.f);
    setPosition(data.x, data.y);
}