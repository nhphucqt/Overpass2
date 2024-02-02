#ifndef VIEW_GROUP_HPP
#define VIEW_GROUP_HPP

#include <SFML/Graphics.hpp>

#include <Command.hpp>
#include <CommandQueue.hpp>
#include <EventListener.hpp>

#include <memory>
#include <vector>
#include <set>
#include <utility>
#include <cmath>


class ViewGroup : 
                public sf::Drawable, 
                public sf::Transformable,
                public EventListener {
public:
    typedef std::unique_ptr<ViewGroup> Ptr;
	typedef std::pair<ViewGroup*, ViewGroup*> Pair;

public:
    ViewGroup();
    ViewGroup(EventPublisher* publisher);
    virtual ~ViewGroup() = default;

    ViewGroup* getParent() const;
    void setParent(ViewGroup* parent);

    void attachView(ViewGroup::Ptr view);
    ViewGroup::Ptr detachView(const ViewGroup &view);
    void detachAllViews();
    const std::vector<ViewGroup::Ptr>& getViews() const;

    void unsubscribeAll();

    void update(sf::Time delta);
	void onCommand(Command &command, sf::Time dt);
    void setReverse(bool reverse = true);
	virtual unsigned int getCategory() const;

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

    void setUpdate(bool isUpdate);
    bool isUpdate();

    void setVisibility(bool isVisible);
    bool isVisible() const;

    void setIsListeningAll(bool isListening);
    
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const = 0;

private:
    bool isReverse, mIsUpdate, mIsVisible;
    ViewGroup* parent;
    std::vector<ViewGroup::Ptr> childViews;

private:
    virtual void updateCurrent(sf::Time delta);
    void updateChildren(sf::Time delta);
};

#endif