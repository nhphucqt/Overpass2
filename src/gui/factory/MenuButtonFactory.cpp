#include <MenuButtonFactory.hpp>

#include <EventListener.hpp>
#include <TextView.hpp>

SpriteButtonView::Ptr MenuButtonFactory::create(Activity* context, const sf::Texture& texture, const sf::Font& font, const std::string& text, const sf::Vector2f& position, EventListener::EventCallback callback) {
    float width = 320;
    float height = 128;
    sf::Vector2f size(width, height);
    int fontSize = 48;

    sf::IntRect buttonRects[3] = {
        sf::IntRect(0, 0, 96, 32),
        sf::IntRect(96, 0, 96, 32),
        sf::IntRect(96, 0, 96, 32)
    };

    TextView::Ptr textView = std::make_unique<TextView>(text, font, sf::Vector2f(), fontSize, sf::Color::White);
    sf::Vector2f textPosition = (size - textView->getGlobalBounds().getSize()) / 2.f;
    sf::Vector2f textPositionNormal(textPosition - sf::Vector2f(0, 8));
    textView->setPosition(textPositionNormal);
    TextView* textViewPtr = textView.get();

    SpriteButtonView::Ptr playButton = std::make_unique<SpriteButtonView>(context, texture, font, buttonRects, "", fontSize, position, size);

    playButton->setOnMouseMoved(context, [textViewPtr, textPosition, textPositionNormal](EventListener* listener, const sf::Event& event) {
        SpriteButtonView* button = dynamic_cast<SpriteButtonView*>(listener);
        if (button->getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
            textViewPtr->setPosition(textPosition);
        } else {
            textViewPtr->setPosition(textPositionNormal);
        }
    });

    playButton->setOnMouseButtonReleased(context, callback);

    playButton->attachView(std::move(textView));

    return std::move(playButton);
}