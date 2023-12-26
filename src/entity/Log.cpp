#include <Log.hpp>

TextureID toTextureID(Log::Type type) {
	switch (type) {
	case Log::Wood:
		return TextureID::Wood;

	case Log::Crocodile:
		return TextureID::Crocodile;
	}
	return TextureID::Wood;
}

Log::Log(Type mType, const TextureManager& textures):
type(mType),
Entity(textures.get(toTextureID(mType)))
{
	sprite.scale(12, 8);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Log::getCategory() const {
	switch (type) {
	case Log::Wood:
		return Category::Log;
	case Log::Crocodile:
		return Category::Crocodile;
	default:
		return Category::Log;
	}
}

sf::FloatRect Log::getBoundingRect() const {
    sf::FloatRect rect = Entity::getBoundingRect();
	rect.top = rect.top + rect.getSize().y / 2 - 65;
	rect.height = 130;
	return rect;
}

Log::LogData Log::serialize() const {
	LogData data;
	data.type = static_cast<int>(type);
	data.x = getPosition().x;
	data.y = getPosition().y;
	return data;
}

void Log::deserialize(Log::LogData& data) {
	type = static_cast<Type>(data.type);
	setPosition(data.x, data.y);
}
