#ifndef RECTANGLE_VIEW_HPP
#define RECTANGLE_VIEW_HPP

#include <ViewGroup.hpp>
#include <EventListener.hpp>

class RectangleView: public ViewGroup, public EventListener {
public:
    typedef std::unique_ptr<RectangleView> Ptr;

private:
    sf::RectangleShape mRect;

public:
    RectangleView(float left, float top, float width, float height);
    RectangleView(float left, float top, float width, float height, const sf::Color& color);
    RectangleView(const sf::Vector2f& size, const sf::Vector2f& position);
    RectangleView(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);

    sf::Vector2f getSize();
    void setSize(const sf::Vector2f& size);
    void setFillColor(sf::Color color);

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual bool isOnMouseButtonPressed(const sf::Event& event) const override;
    virtual bool isOnMouseButtonReleased(const sf::Event& event) const override;
};
    

#endif