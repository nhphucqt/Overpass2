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
    std::string mTexts[(int)ButtonType::COUNT];
    sf::IntRect mTextureRects[(int)ButtonType::COUNT];

public:
    // @Params 0: normal | 1: hovering | 2: pressed
    
    SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string* texts, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size);
    SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string* texts, unsigned int characterSize, const sf::Vector2f& position);

    SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size);
    SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const char* text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size);
    SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string& text, unsigned int characterSize, const sf::Vector2f& position);
    SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const char* text, unsigned int characterSize, const sf::Vector2f& position);

    void setOnMouseButtonPressed(EventCallback onMouseButtonPressed) override;
    void setOnMouseButtonReleased(EventCallback onMouseButtonReleased) override;
    void setOnMouseMoved(EventCallback onMouseMoved) override;
};

#endif