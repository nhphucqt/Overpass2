#include <Animal.hpp>
#include <AppConfig.hpp>

TextureID Animal::toTextureID(Type type) {
	switch (type) {
    case Type::Bear:
        return TextureID::Bear;
    case Type::Boar:
        return TextureID::Boar;
    case Type::Bunny:
        return TextureID::Bunny;
    case Type::Deer:
        return TextureID::Deer;
    case Type::Fox:
        return TextureID::Fox;
    case Type::Wolf:
        return TextureID::Wolf;
	}
	return TextureID::Fox;
}

Animal::Animal(Type mType, const TextureHolder& textures)
    :  type(mType)
    , animation(textures.get(toTextureID(mType)))
{
    if (type == Type::Bear) {
        animation.setFrameSize(sf::Vector2i(26, 12));
        animation.setNumFrames(6);
    }
    else if (type == Type::Boar) {
        animation.setFrameSize(sf::Vector2i(16 , 10));
        animation.setNumFrames(4);
    }
    else if (type == Type::Bunny) {
        animation.setFrameSize(sf::Vector2i(11 , 9));
        animation.setNumFrames(4);
    }
    else if (type == Type::Deer) {
        animation.setFrameSize(sf::Vector2i(17 , 18));
        animation.setNumFrames(4);
    }
    else if (type == Type::Fox) {
        animation.setFrameSize(sf::Vector2i(17, 11));
        animation.setNumFrames(4);
    }
    else if (type == Type::Wolf) {
        animation.setFrameSize(sf::Vector2i(19 , 12));
        animation.setNumFrames(6);
    }
    animation.setDuration(sf::seconds(1));
    animation.scale(5, 5);
    animation.setRepeating(true);

    sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(cellSize);
    sf::FloatRect bounds = animation.getLocalBounds();
    animation.setOrigin(bounds.getSize() / 2.f);
    animation.setPosition(cellSize / 2.f);
    setHitBox(animation.getGlobalBounds());
	// sf::FloatRect bounds = animation.getLocalBounds();
	// animation.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Animal::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(animation, states);

    drawBoundingRect(target, states);
}

void Animal::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    animation.update(dt);
}

unsigned int Animal::getCategory() const {
    return ViewCategory::Animal;
}

Animal::AnimalData Animal::serialize() const {
    AnimalData data;
    data.type = static_cast<int>(type);
	data.posX = getPosition().x;
	data.posY = getPosition().y;
	data.vx = getVelocity().x;
	data.vy = getVelocity().y;
	data.scaleX = getScale().x;
	data.scaleY = getScale().y;
    data.isReverse = isReverseSprite();

    return data;
}

void Animal::deserialize(Animal::AnimalData& data) {
    type = static_cast<Type>(data.type);
    setPosition(data.posX, data.posY);
	setVelocity(data.vx, data.vy);
	setScale(data.scaleX, data.scaleY);
    if (data.isReverse) {
        reverseSprite();
    }
}
void Animal::reverseSprite() {
    animation.reverseSprite();
    Entity::reverseSprite();
}
