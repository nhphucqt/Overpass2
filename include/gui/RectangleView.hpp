#ifndef RECTANGLE_VIEW_HPP
#define RECTANGLE_VIEW_HPP

#include <Viewable.hpp>
#include <random>

class RectangleView: public Viewable {
private:
    sf::RectangleShape rect;

public:
    RectangleView();
    RectangleView(Viewable* parent);
    RectangleView(Viewable* parent, sf::Vector2f dimens);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
    

#endif