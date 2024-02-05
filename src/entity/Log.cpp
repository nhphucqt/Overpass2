#include <Log.hpp>
#include <AppConfig.hpp>

TextureID Log::toTextureID(Type type) {
	switch (type) {
	case Type::WoodL2:
		return TextureID::WoodL2;
	case Type::WoodL3:
		return TextureID::WoodL3;
	case Type::Crocodile:
		return TextureID::Crocodile;
	}
	return TextureID::WoodL2;
}

Log::Log(Type mType, const TextureHolder &textures) 
	: type(mType) 
	, Entity(textures.get(toTextureID(mType)))
{
	int woodLen = 0;
	if (type == Type::WoodL2) {
		woodLen = 2;
	} else if (type == Type::WoodL3) {
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
	case Type::WoodL2:
	case Type::WoodL3:
		return ViewCategory::Log;
	case Type::Crocodile:
		return ViewCategory::Crocodile;
	default:
		return ViewCategory::Log;
	}
}

SeqZone *Log::getSeqZone()
{
	return seqZone;
}

Log::LogData Log::serialize() const {
	LogData data;
	data.type = static_cast<int>(type);
	data.posX = getPosition().x;
	data.posY = getPosition().y;
	data.vx = getVelocity().x;
	data.vy = getVelocity().y;
	data.scaleX = getScale().x;
	data.scaleY = getScale().y;
	return data;
}

void Log::deserialize(Log::LogData& data) {
	type = static_cast<Type>(data.type);
	setPosition(data.posX, data.posY);
	setVelocity(data.vx, data.vy);
	setScale(data.scaleX, data.scaleY);
}
