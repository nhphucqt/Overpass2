#include <BackgroundFactory.hpp>
#include <AppConfig.hpp>

SpriteView::Ptr BackgroundFactory::create(Activity* context, const sf::Texture& backgroundTexture) {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    sf::Vector2f size(windowSize.x, windowSize.y);
    sf::Vector2f position(0, 0);
    float scale = std::min(backgroundTexture.getSize().x / windowSize.x, backgroundTexture.getSize().y / windowSize.y);
    sf::IntRect rect(0, 0, windowSize.x * scale, windowSize.y * scale);

    SpriteView::Ptr background = std::make_unique<SpriteView>(context, backgroundTexture, position, size, rect);
    return std::move(background);
}