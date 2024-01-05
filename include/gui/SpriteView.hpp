#ifndef SPRITE_VIEW_HPP
#define SPRITE_VIEW_HPP

#include <ViewGroup.hpp>

class SpriteView : public ViewGroup {
public:
    typedef std::unique_ptr<SpriteView> Ptr;
private:
    sf::Sprite mSprite;
public:
    SpriteView(EventPublisher* publisher, const sf::Texture& texture);
    SpriteView(EventPublisher* publisher, const sf::Texture& texture, const sf::Vector2f& position);
    SpriteView(EventPublisher* publisher, const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size);
    SpriteView(EventPublisher* publisher, const sf::Texture& texture, const sf::Vector2f& position, const sf::IntRect& rect);
    SpriteView(EventPublisher* publisher, const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::IntRect& rect);
    sf::Sprite& get();

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif