#include <SquareButtonFactory.hpp>

#include <EventListener.hpp>
#include <TextView.hpp>

#include <SoundPlayer.hpp>

SpriteButtonView::Ptr SquareButtonFactory::create(Activity* context, const sf::Texture& texture, const sf::Font& font, const std::string& text, const sf::Vector2f& position, EventListener::EventCallback callback) {
    float width = 64;
    float height = 64;
    sf::Vector2f size(width, height);
    int fontSize = 48;

    sf::IntRect buttonRects[3] = {
        sf::IntRect(8, 154, 32, 32),
        sf::IntRect(56, 104, 32, 32),
        sf::IntRect(56, 152, 32, 32),
    };

    TextView::Ptr textView = std::make_unique<TextView>(context, text, font, sf::Vector2f(), fontSize, sf::Color::White);
    sf::Vector2f textPosition = (size - textView->getGlobalBounds().getSize()) / 2.f;
    sf::Vector2f textPositionNormal(textPosition - sf::Vector2f(0, 4));
    textView->setPosition(textPositionNormal);
    TextView* textViewPtr = textView.get();

    SpriteButtonView::Ptr playButton = std::make_unique<SpriteButtonView>(context, texture, font, buttonRects, "", fontSize, position, size);

    playButton->setOnMouseMoved([textViewPtr, textPosition, textPositionNormal](EventListener* listener, const sf::Event& event) {
        SpriteButtonView* button = dynamic_cast<SpriteButtonView*>(listener);
        if (button->getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
            textViewPtr->setPosition(textPosition);
        } else {
            textViewPtr->setPosition(textPositionNormal);
        }
    });

    EventListener::EventDoubleCallback doubleCallback([](EventListener* listener, const sf::Event& event, EventListener::EventCallback callback) {
        SoundPlayer::getInstance().play(SoundBufferID::buttonClick);
        callback(listener, event);       
    });

    playButton->setOnMouseButtonReleased(std::bind(doubleCallback, std::placeholders::_1, std::placeholders::_2, callback));

    playButton->attachView(std::move(textView));

    return std::move(playButton);
}