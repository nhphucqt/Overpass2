#ifndef VIEWABLE_HPP
#define VIEWABLE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

class Viewable: public sf::Drawable, 
                public sf::Transformable {
friend class ViewGroup;

public:
    typedef std::unique_ptr<Viewable> Ptr;

private:
    Viewable* parent;

public:
    Viewable();
    virtual ~Viewable() = default;
    
    Viewable* getParent();
    void setParent(Viewable* parent);

    virtual void update(sf::Time delta);
};

#endif