#include <SpriteView.hpp>

SpriteView::SpriteView(EventPublisher* publisher, const sf::Texture& texture)
: SpriteView(publisher, texture, sf::Vector2f(0, 0)) {}

SpriteView::SpriteView(EventPublisher* publisher, const sf::Texture& texture, const sf::Vector2f& position)
: ViewGroup(publisher) {
    mSprite.setTexture(texture);
    setPosition(position);
}

SpriteView::SpriteView(EventPublisher* publisher, const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size)
: ViewGroup(publisher) {
    mSprite.setTexture(texture);
    setPosition(position);
    mSprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
}

SpriteView::SpriteView(EventPublisher* publisher, const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& rect)
: ViewGroup(publisher) {
    mSprite.setTexture(texture);
    setPosition(position);
    mSprite.setTextureRect(rect);
}

SpriteView::SpriteView(EventPublisher* publisher, const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::IntRect& rect)
: ViewGroup(publisher) {
    mSprite.setTexture(texture);
    setPosition(position);
    mSprite.setScale(size.x / rect.getSize().x, size.y / rect.getSize().y);
    mSprite.setTextureRect(rect);
}

sf::Sprite& SpriteView::get() {
    return mSprite;
}

void SpriteView::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}