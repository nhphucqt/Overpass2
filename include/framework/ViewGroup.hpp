#ifndef VIEW_GROUP_HPP
#define VIEW_GROUP_HPP

#include <list>
#include <Viewable.hpp>

class ViewGroup : public Viewable {
private:
    std::list<Viewable::Ptr> childViews;

public:
    virtual ~ViewGroup() = default;

    void attachView(Viewable::Ptr view);
    Viewable::Ptr detachView(const Viewable &view);
    void detachAllViews();

    void update(sf::Time delta) override;
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const = 0;

private:
    virtual void updateCurrent(sf::Time delta);
    void updateChildren(sf::Time delta);
};

#endif