#ifndef RECTANGLE_VIEW_HPP
#define RECTANGLE_VIEW_HPP

#include <Viewable.hpp>

class RectangleView: public Viewable {
private:
    sf::RectangleShape mRect;

public:
    RectangleView(int width, int height);
    sf::Vector2f getSize();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
    

#endif