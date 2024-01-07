#include <Train.hpp>
#include <AppConfig.hpp>

Train::Train(const TextureManager &textures) 
	: Entity(textures.get(TextureID::Train))
{
	sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
	// sprite.setOrigin(0, sprite.getGlobalBounds().height);
	// scale(0.5, 0.5);
	sprite.scale(1.5f, 1.5f);
	sf::FloatRect rect = sprite.getGlobalBounds();
	// rect.top = rect.top + 150;
	// rect.height = 128;
	rect.top = 0;
	setHitBox(rect);
	sf::Vector2f size(rect.width, cellSize.y);
	setSize(size);
}

unsigned int Train::getCategory() const
{
	return Category::Train;
}

Train::TrainData Train::serialize() const
{
	TrainData data;
	data.posX = getPosition().x;
	data.posY = getPosition().y;
	data.vx = getVelocity().x;
	data.vy = getVelocity().y;
	data.scaleX = getScale().x;
	data.scaleY = getScale().y;
	data.isReversed = isReverseSprite();

	return data;
}

void Train::deserialize(Train::TrainData &data)
{
	setPosition(data.posX, data.posY);
	setVelocity(data.vx, data.vy);
	setScale(data.scaleX, data.scaleY);
	if (data.isReversed) {
		reverseSprite();
	}
}

void Train::reverseSprite() {
	sprite.setOrigin(sprite.getLocalBounds().width, 0.f);
	Entity::reverseSprite();
}