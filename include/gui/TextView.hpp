#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include <ViewGroup.hpp>
#include <SFML/Graphics.hpp>
#include <EventListener.hpp>

class TextView: public ViewGroup,
                public EventListener {
public:
    typedef std::unique_ptr<TextView> Ptr;

private:
    sf::Text text;

public:
    TextView(const std::string& text, const sf::Font& font);
    TextView(const std::string& text, const sf::Font& font, const sf::Vector2f& position);
    TextView(const std::string& text, const sf::Font& font, const sf::Vector2f& position, unsigned int characterSize);
    TextView(const std::string& text, const sf::Font& font, const sf::Vector2f& position, unsigned int characterSize, const sf::Color& color);

    sf::FloatRect getGlobalBounds() const;

    int getCharacterSize() const;

    void setText(const std::string& text);
    void setFillColor(const sf::Color& color);
    std::string getText() const;
    bool isMouseHovering(const sf::Vector2f& mousePoint) const;

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual bool isOnMouseButtonPressed(const sf::Event& event) const override;
    virtual bool isOnMouseButtonReleased(const sf::Event& event) const override;
};

#endif