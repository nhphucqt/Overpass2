#include <EditTextView.hpp>
#include <EventPublisher.hpp>
#include <iostream>

EditTextView::EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& size)
: EditTextView(publisher, font, text, 20, sf::Vector2f(0, 0), size) {}

EditTextView::EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size)
: EditTextView(publisher, font, text, 20, position, size) {}

EditTextView::EditTextView(EventPublisher* publisher, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size) 
: ViewGroup(publisher), limit(0), mRect(size), mText(text, font, characterSize), mCursor("|", font, characterSize), __isFocused(false) {
    mString = text;

    setPosition(position);
    setTextColor(sf::Color::Black);
    updateTextPosition();

    setFocusBackGroundColor(sf::Color(200, 200, 200, 255));
    setUnFocusBackGroundColor(sf::Color(220, 220, 220, 255));

    setBackGroundColor(mUnFocusBackGroundColor);

    setBlinkTime(sf::seconds(0.5f));
    resetBlink();

    setInputType(InputType::TEXT);

    setOnMouseButtonPressed([&](EventListener* listener, const sf::Event& event) {
        if (isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            setFocused(true);
            setBackGroundColor(mFocusBackGroundColor);
            resetBlink();
        } else {
            setFocused(false);
            setBackGroundColor(mUnFocusBackGroundColor);
        }
    });

    setOnTextEntered([&](EventListener* listener, const sf::Event& event) {
        sf::Uint32 unicode = event.text.unicode;
        if (isFocused()) {
            resetBlink();
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

void EditTextView::setInputType(InputType type) {
    mInputType = type;
    setText(mString);
}

void EditTextView::updateTextPosition() {
    mText.setOrigin(0, 0);
    mText.setPosition(0, 0);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(mRect.getSize()/2.f);
    mCursor.setOrigin(0, 0);
    mCursor.setPosition(0, 0);
    mCursor.setOrigin(mCursor.getGlobalBounds().getPosition() + sf::Vector2f(0, mCursor.getGlobalBounds().getSize().y / 2.f));
    mCursor.setPosition(mText.getPosition() + sf::Vector2f(mText.getGlobalBounds().getSize().x / 2.f + 2, 0.f));
}

void EditTextView::setLimit(int limit) {
    this->limit = limit;
}

void EditTextView::setBackGroundColor(const sf::Color& color) {
    mRect.setFillColor(color);
}

void EditTextView::setFocusBackGroundColor(const sf::Color& color) {
    mFocusBackGroundColor = color;
    updateBackgroundColor();
}

void EditTextView::setUnFocusBackGroundColor(const sf::Color& color) {
    mUnFocusBackGroundColor = color;
    updateBackgroundColor();
}

void EditTextView::updateBackgroundColor() {
    if (isFocused()) {
        setBackGroundColor(mFocusBackGroundColor);
    } else {
        setBackGroundColor(mUnFocusBackGroundColor);
    }
}

void EditTextView::setTextColor(const sf::Color& color) {
    mText.setFillColor(color);
    mCursor.setFillColor(color);
}

void EditTextView::setText(const std::string& text) {
    if (limit != 0 && text.size() > limit) {
        return;
    }
    if (mInputType == InputType::PASSWORD) {
        std::string password(text.size(), '*');
        mText.setString(password);
    } else if (mInputType == InputType::TEXT) {
        mText.setString(text);
    }
    mString = text;
    updateTextPosition();
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

const std::string& EditTextView::getText() const {
    return mString;
}

void EditTextView::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mRect, states);
    target.draw(mText, states);
    if (mCursorVisible && isFocused()) {
        target.draw(mCursor, states);
    }
}

sf::FloatRect EditTextView::getGlobalBounds() const {
    return getWorldTransform().transformRect(mRect.getGlobalBounds());
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
    updateBackgroundColor();
}

void EditTextView::updateCurrent(sf::Time delta) {
    mCurrentTime += delta;
    if (mCurrentTime >= mCursorBlinkTime) {
        mCurrentTime -= mCursorBlinkTime;
        mCursorVisible = !mCursorVisible;
    }
}

void EditTextView::setBlinkTime(sf::Time time) {
    mCursorBlinkTime = time;
}

void EditTextView::resetBlink() {
    mCurrentTime = sf::Time::Zero;
    mCursorVisible = true;
}