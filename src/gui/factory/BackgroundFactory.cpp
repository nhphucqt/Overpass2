#include <BackgroundFactory.hpp>
#include <AppConfig.hpp>

SpriteView::Ptr BackgroundFactory::create(const sf::Texture& backgroundTexture) {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    sf::Vector2f size(windowSize.x, windowSize.y);
    sf::Vector2f position(0, 0);
    sf::IntRect rect(0, 0, backgroundTexture.getSize().x, backgroundTexture.getSize().y);

    SpriteView::Ptr background = std::make_unique<SpriteView>(backgroundTexture, position, size, rect);
    return std::move(background);
}