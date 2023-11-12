#ifndef VIEWABLE_HPP
#define VIEWABLE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

class Viewable: public sf::Drawable, 
                public sf::Transformable {
friend class ViewGroup;

private:
    Viewable* parent;

public:
    Viewable();
    virtual ~Viewable() = default;
    
    Viewable* getParent();
    void setParent(Viewable* parent);
};

#endif