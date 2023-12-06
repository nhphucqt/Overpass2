#include <EditTextView.hpp>
#include <EventPublisher.hpp>
#include <iostream>

EditTextView::EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& size, const sf::Color& fillColor)
: EditTextView(publisher, font, text, 20, sf::Vector2f(0, 0), size, fillColor) {}

EditTextView::EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& fillColor)
: EditTextView(publisher, font, text, 20, position, size, fillColor) {}

EditTextView::EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& fillColor) 
: limit(0), mRect(size), mText(text, font, characterSize) {
    mRect.setPosition(position);
    mRect.setFillColor(fillColor);
    mText.setFillColor(sf::Color::Black);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(size/2.f);
    leftPadding = 10;

    setOnMouseButtonPressed(publisher, [&](EventListener* listener, const sf::Event& event) {
        if (isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            setFocused(true);
        } else {
            setFocused(false);
        }
    });

    setOnTextEntered(publisher, [&](EventListener* listener, const sf::Event& event) {
        sf::Uint32 unicode = event.text.unicode;
        if (isFocused()) {
            if (unicode == 8) { // Backspace
                removeCharacter();
            } else if (unicode == 13) { // Enter
                setFocused(false);
            } else if (unicode == 27) { // Escape
                setFocused(false);
            } else if (isprint(unicode)) {
                appendCharacter(event.key.code);
            }
        }
    });
}

void EditTextView::setLimit(int limit) {
    this->limit = limit;
}

void EditTextView::setLeftPadding(int padding) {
    leftPadding = padding;
}

void EditTextView::setBackGroundColor(const sf::Color& color) {
    mRect.setFillColor(color);
}

void EditTextView::setTextColor(const sf::Color& color) {
    mText.setFillColor(color);
}

void EditTextView::setText(const std::string& text) {
    mText.setString(text);
    mText.setOrigin(0, 0);
    mText.setPosition(0, 0);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(mRect.getSize()/2.f);
}

void EditTextView::appendCharacter(char character) {
    if (limit == 0 || mText.getString().getSize() < limit) {
        setText(mText.getString() + character);
    }
}

void EditTextView::removeCharacter() {
    if (mText.getString().getSize() > 0) {
        setText(mText.getString().substring(0, mText.getString().getSize() - 1));
    }
}

void EditTextView::clearText() {
    setText("");
}

std::string EditTextView::getText() const {
    return mText.getString();
}

void EditTextView::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mRect, states);
    target.draw(mText, states);
}

sf::FloatRect EditTextView::getGlobalBounds() const {
    return getAbsoluteTransform().transformRect(mRect.getGlobalBounds());
}

bool EditTextView::isOnMouseButtonPressed(const sf::Event& event) const {
    // return getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
    return true;
}

bool EditTextView::isOnTextEntered(const sf::Event& event) const {
    return isFocused();
}

bool EditTextView::isMouseHovering(const sf::Vector2f& mousePoint) const {
    return getGlobalBounds().contains(mousePoint);
}

bool EditTextView::isFocused() const {
    return __isFocused;
}

void EditTextView::setFocused(bool focused) {
    __isFocused = focused;
}