#ifndef VIEWABLE_HPP
#define VIEWABLE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

class Viewable: public sf::Drawable, 
                public sf::Transformable {
friend class ViewGroup;

private:
    Viewable* parent;
    sf::Vector2f dimens;

public:
    Viewable();
    Viewable(Viewable* parent);
    Viewable(Viewable* parent, sf::Vector2f dimens);

    Viewable* getParent();
    void setParent(Viewable* parent);
    sf::Vector2f getDimens();
    void setDimens(sf::Vector2f dimens);
};

#endif