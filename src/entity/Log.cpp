#include <Log.hpp>
#include <AppConfig.hpp>

TextureID toTextureID(Log::Type type)
{
	switch (type)
	{
	case Log::Wood:
		return TextureID::Wood;

	case Log::Crocodile:
		return TextureID::Crocodile;
	}
	return TextureID::Wood;
}

Log::Log(Type mType, const TextureManager &textures) : type(mType),
													   Entity(textures.get(toTextureID(mType)))
{
	sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
	sf::Vector2f size(cellSize.x * 2, cellSize.y);
	setSize(size);
	sprite.setScale(size.x / sprite.getLocalBounds().width, sprite.getLocalBounds().height);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	sprite.setPosition(size.x / 2.f, size.y / 2.f);
	setHitBox(sprite.getGlobalBounds());

	SeqZone::Ptr zonePtr = std::make_unique<SeqZone>(Zone::Type::Safe, cellSize, 2);
	zonePtr->setPosition(0, 0);
	seqZone = zonePtr.get();
	attachView(std::move(zonePtr));
}

unsigned int Log::getCategory() const
{
	switch (type)
	{
	case Log::Wood:
		return Category::Log;
	case Log::Crocodile:
		return Category::Crocodile;
	default:
		return Category::Log;
	}
}

SeqZone *Log::getSeqZone()
{
	return seqZone;
}

Log::LogData Log::serialize() const
{
	LogData data;
	data.type = static_cast<int>(type);
	data.x = getPosition().x;
	data.y = getPosition().y;
	return data;
}

void Log::deserialize(Log::LogData &data)
{
	type = static_cast<Type>(data.type);
	setPosition(data.x, data.y);
}
