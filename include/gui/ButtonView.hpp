#ifndef BUTTON_VIEW_HPP
#define BUTTON_VIEW_HPP

#include <ViewGroup.hpp>
#include <EventListener.hpp>

class ButtonView: public ViewGroup {
public:
    typedef std::unique_ptr<ButtonView> Ptr;

private:
    sf::RectangleShape mRect;
    sf::Sprite mSprite;
    sf::Text mText;

public:
    ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text);
    ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, const sf::Vector2f& position);
    ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size);
    ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size);
    ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::IntRect& textureRect);
    ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::IntRect& textureRect, const sf::Vector2f& size);

    ButtonView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& size, const sf::Color& fillColor);
    ButtonView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& fillColor);
    ButtonView(EventPublisher* publisher, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& fillColor);

    void setTexture(const sf::Texture& texture, bool resetRect = false);
    void setTextureRect(const sf::IntRect& rect);
    void setText(const std::string& text);
    void setBackGroundColor(const sf::Color& color);
    void setTextColor(const sf::Color& color);
    bool isMouseHovering(const sf::Vector2f& mousePoint) const;

    sf::FloatRect getGlobalBounds() const;

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual bool isOnMouseButtonPressed(const sf::Event& event) const override;
    virtual bool isOnMouseButtonReleased(const sf::Event& event) const override;
    virtual bool isOnMouseMoved(const sf::Event& event) const override;
};

#endif