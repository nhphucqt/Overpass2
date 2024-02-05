#ifndef EDIT_TEXT_VIEW_HPP
#define EDIT_TEXT_VIEW_HPP

#include <ViewGroup.hpp>
#include <EventListener.hpp>

class EditTextView : public ViewGroup {
public:
    typedef std::unique_ptr<EditTextView> Ptr;
    enum class InputType {
        TEXT,
        PASSWORD
    };

private:
    bool __isFocused;
    int limit;
    sf::RectangleShape mRect;
    sf::Text mCursor;
    sf::Text mText;
    std::string mString;
    sf::Time mCursorBlinkTime, mCurrentTime;
    bool mCursorVisible;
    InputType mInputType;
    sf::Color mFocusBackGroundColor, mUnFocusBackGroundColor;

public:
    EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& size);
    EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size);
    EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size);

    void setInputType(InputType type);

    void setLimit(int limit);
    void setFocusBackGroundColor(const sf::Color& color);
    void setUnFocusBackGroundColor(const sf::Color& color);
    void setTextColor(const sf::Color& color);

    void appendCharacter(char character);
    void removeCharacter();
    void clearText();
    const std::string& getText() const;

    sf::FloatRect getGlobalBounds() const;

    bool isMouseHovering(const sf::Vector2f& mousePoint) const;

    bool isFocused() const;
    void setFocused(bool focused);

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual bool isOnMouseButtonPressed(const sf::Event& event) const override;
    virtual bool isOnTextEntered(const sf::Event& event) const override;

private:
    void setText(const std::string& text);

    void updateTextPosition();
    void updateBackgroundColor();

    virtual void updateCurrent(sf::Time delta) override;
    void setBlinkTime(sf::Time time);
    void resetBlink();

    void setBackGroundColor(const sf::Color& color);
};

#endif