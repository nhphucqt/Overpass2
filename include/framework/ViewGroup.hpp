#ifndef VIEW_GROUP_HPP
#define VIEW_GROUP_HPP

#include <list>
#include <Viewable.hpp>

class ViewGroup : public Viewable
{
public:
    typedef std::unique_ptr<Viewable> ViewChild;

private:
    std::list<ViewChild> childViews;

public:
    virtual ~ViewGroup() = default;

    void attachView(ViewChild view);
    ViewChild detachView(const Viewable &view);
    void detachAllViews();

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};

#endif