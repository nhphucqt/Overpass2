#include <SpriteView.hpp>

SpriteView::SpriteView(const sf::Texture& texture) {
    mSprite.setTexture(texture);
}

SpriteView::SpriteView(const sf::Texture& texture, const sf::Vector2f& position) {
    mSprite.setTexture(texture);
    setPosition(position);
}

SpriteView::SpriteView(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size) {
    mSprite.setTexture(texture);
    setPosition(position);
    mSprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
}

SpriteView::SpriteView(const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& rect) {
    mSprite.setTexture(texture);
    setPosition(position);
    mSprite.setTextureRect(rect);
}

SpriteView::SpriteView(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::IntRect& rect) {
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