#ifndef VIEWABLE_HPP
#define VIEWABLE_HPP

#include <Command.hpp>
#include <CommandQueue.hpp>
#include <memory>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <SFML/Graphics.hpp>

class Viewable: public sf::Drawable, 
                public sf::Transformable {
friend class ViewGroup;

public:
    typedef std::unique_ptr<Viewable> Ptr;

protected:

private:
    Viewable* parent;

public:
    Viewable();
    virtual ~Viewable() = default;
    
    Viewable* getParent() const;
    void setParent(Viewable* parent);

    virtual void update(sf::Time delta);

    sf::Transform getAbsoluteTransform() const;

	virtual unsigned int getCategory() const = 0;
	virtual void onCommand(const Command &command, sf::Time dt);
	
};

#endif