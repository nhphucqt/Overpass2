#ifndef SPRITE_BUTTON_VIEW_HPP
#define SPRITE_BUTTON_VIEW_HPP

#include <EventPublisher.hpp>
#include <ButtonView.hpp>

class SpriteButtonView : public ButtonView {
public:
    typedef std::unique_ptr<SpriteButtonView> Ptr;

public: 
    enum class ButtonType {
        NORMAL,
        HOVERING,
        PRESSED,
        COUNT
    };

private:
    std::string mTexts[3];
    sf::IntRect mTextureRects[3];

public:
    // @Params 0: normal | 1: hovering | 2: pressed
    SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string* texts, unsigned int characterSize, const sf::Vector2f& position);

    void setOnMouseButtonPressed(EventPublisher* publisher, EventCallback onMouseButtonPressed) override;
    void setOnMouseButtonReleased(EventPublisher* publisher, EventCallback onMouseButtonReleased) override;
    void setOnMouseMoved(EventPublisher* publisher, EventCallback onMouseMoved) override;
};

#endif