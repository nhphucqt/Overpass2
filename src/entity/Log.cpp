#include <Log.hpp>
#include <AppConfig.hpp>

TextureID toTextureID(Log::Type type) {
	switch (type) {
	case Log::WoodL2:
		return TextureID::WoodL2;
	case Log::WoodL3:
		return TextureID::WoodL3;
	case Log::Crocodile:
		return TextureID::Crocodile;
	}
	return TextureID::WoodL2;
}

Log::Log(Type mType, const TextureManager& textures):
type(mType),
Entity(textures.get(toTextureID(mType)))
{
	int woodLen = 0;
	if (type == Log::WoodL2) {
		woodLen = 2;
	} else if (type == Log::WoodL3) {
		woodLen = 3;
	} else {
		throw std::runtime_error("Invalid log type");
	}
	sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
	sf::Vector2f size(cellSize.x * woodLen, cellSize.y);
	setSize(size);
	sprite.setScale(size.x / sprite.getLocalBounds().width, size.y / sprite.getLocalBounds().height);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	sprite.setPosition(size.x / 2.f, size.y / 2.f);
	setHitBox(sprite.getGlobalBounds());

	SeqZone::Ptr zonePtr = std::make_unique<SeqZone>(Zone::Type::Safe, cellSize, woodLen);
	zonePtr->setPosition(0, 0);
	seqZone = zonePtr.get();
	attachView(std::move(zonePtr));
}

unsigned int Log::getCategory() const {
	switch (type) {
	case Log::WoodL2:
	case Log::WoodL3:
		return Category::Log;
	case Log::Crocodile:
		return Category::Crocodile;
	default:
		return Category::Log;
	}
}

SeqZone* Log::getSeqZone() {
	return seqZone;
}