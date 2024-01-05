#include <BackButtonFactory.hpp>
#include <TextView.hpp>
#include <SpriteButtonView.hpp>
#include <Activity.hpp>

#include <SoundPlayer.hpp>

SpriteButtonView::Ptr BackButtonFactory::create(Activity* context, const sf::Texture& texture, const sf::Font& font) {
    float width = 64;
    float height = 64;
    sf::Vector2f size(width, height);
    sf::Vector2f position(20, 20);
    int fontSize = 64;

    sf::IntRect buttonRects[3] = {
        sf::IntRect(8, 154, 32, 32),
        sf::IntRect(56, 104, 32, 32),
        sf::IntRect(56, 152, 32, 32),
    };

    SpriteButtonView::Ptr backButton = std::make_unique<SpriteButtonView>(context, texture, font, buttonRects, "", 32, position, size);

    TextView::Ptr textView = std::make_unique<TextView>(context, "<", font, sf::Vector2f(), fontSize, sf::Color::White);
    sf::Vector2f textPosition((size - textView->getGlobalBounds().getSize()) / 2.f);
    sf::Vector2f textPositionNormal(textPosition - sf::Vector2f(0, 4));
    textView->setPosition(textPositionNormal);
    TextView* textViewPtr = textView.get();

    backButton->setOnMouseMoved([textViewPtr, textPosition, textPositionNormal](EventListener* listener, const sf::Event& event) {
        SpriteButtonView* button = static_cast<SpriteButtonView*>(listener);
        if (button->getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
            textViewPtr->setPosition(textPosition);
        } else {
            textViewPtr->setPosition(textPositionNormal);
        }
    });

    backButton->setOnMouseButtonReleased([context](EventListener* listener, const sf::Event& event) {
        SoundPlayer::getInstance().play(SoundBufferID::buttonClick);
        context->finish();
    });

    backButton->attachView(std::move(textView));

    return std::move(backButton);
}