#ifndef RECTANGLE_VIEW_HPP
#define RECTANGLE_VIEW_HPP

#include <Viewable.hpp>
#include <EventListener.hpp>

class RectangleView: public Viewable, public EventListener {
private:
    sf::RectangleShape mRect;

public:
    RectangleView(int width, int height);
    sf::Vector2f getSize();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setFillColor(sf::Color color);

protected:
    virtual bool isOnMouseButtonPressed(const sf::Event& event) const override;
    virtual bool isOnMouseButtonReleased(const sf::Event& event) const override;
};
    

#endif