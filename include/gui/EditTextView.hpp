#ifndef EDIT_TEXT_VIEW_HPP
#define EDIT_TEXT_VIEW_HPP

#include <ViewGroup.hpp>
#include <EventListener.hpp>

class EditTextView : public ViewGroup, public EventListener {
public:
    typedef std::unique_ptr<EditTextView> Ptr;

private:
    bool __isFocused;
    int limit;
    int leftPadding;
    sf::RectangleShape mRect;
    sf::Text mText;
public:
    EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& size, const sf::Color& fillColor);
    EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& fillColor);
    EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& fillColor);

    void setLimit(int limit);
    void setLeftPadding(int padding);
    void setBackGroundColor(const sf::Color& color);
    void setTextColor(const sf::Color& color);

    void appendCharacter(char character);
    void removeCharacter();
    void clearText();
    std::string getText() const;

    sf::FloatRect getGlobalBounds() const;

    bool isMouseHovering(const sf::Vector2f& mousePoint) const;

    bool isFocused() const;

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual bool isOnMouseButtonPressed(const sf::Event& event) const override;
    virtual bool isOnTextEntered(const sf::Event& event) const override;

private:
    void setFocused(bool focused);
    void setText(const std::string& text);
};

#endif