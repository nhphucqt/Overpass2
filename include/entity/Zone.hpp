#ifndef ZONE_HPP
#define ZONE_HPP

#include <ViewGroup.hpp>
#include <Entity.hpp>

class Zone: public ViewGroup {
public:
    typedef std::unique_ptr<Zone> Ptr;
    enum Type {
        Dead,
        Safe,
    };

private:

    sf::Vector2f size;
    Type type;

public:
    Zone(Type type, const sf::Vector2f& size);
    virtual sf::FloatRect getBoundingRect() const;
    sf::Vector2f getCenter() const;
    void attachView(ViewGroup::Ptr view) override;
    bool isSafe();

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif