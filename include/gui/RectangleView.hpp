#ifndef RECTANGLE_VIEW_HPP
#define RECTANGLE_VIEW_HPP

#include <Viewable.hpp>
#include <random>

class RectangleView: public Viewable {
private:
    sf::RectangleShape rect;

public:
    RectangleView();

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
    

#endif