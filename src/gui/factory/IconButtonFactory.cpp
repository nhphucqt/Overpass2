#include <IconButtonFactory.hpp>

#include <EventListener.hpp>
#include <SoundPlayer.hpp>

SpriteButtonView::Ptr IconButtonFactory::create(Activity* context, const sf::Texture& texture, const sf::Font& font, const sf::Vector2f& position, EventListener::EventCallback callback) {
    sf::IntRect textureRect[3] = {
        sf::IntRect(0, 0, 24, 24),
        sf::IntRect(32, 0, 24, 24),
        sf::IntRect(32, 0, 24, 24)
    };

    SpriteButtonView::Ptr buttonView = std::make_unique<SpriteButtonView>(
        context,
        texture,
        font,
        textureRect,
        "",
        64,
        position,
        sf::Vector2f(24, 24) * 3.f
    );

    EventListener::EventDoubleCallback doubleCallback([](EventListener* listener, const sf::Event& event, EventListener::EventCallback callback) {
        SoundPlayer::getInstance().play(SoundBufferID::buttonClick);
        callback(listener, event);       
    });

    buttonView->setOnMouseButtonReleased(std::bind(doubleCallback, std::placeholders::_1, std::placeholders::_2, callback));

    return std::move(buttonView);
}