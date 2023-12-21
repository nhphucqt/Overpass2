#ifndef VIEW_GROUP_HPP
#define VIEW_GROUP_HPP

#include <Viewable.hpp>

class ViewGroup : public Viewable {
public:
    typedef std::unique_ptr<ViewGroup> Ptr;
	typedef std::pair<ViewGroup*, ViewGroup*> Pair;

public:
    ViewGroup();
    virtual ~ViewGroup() = default;

    void attachView(Viewable::Ptr view);
    Viewable::Ptr detachView(const Viewable &view);
    void detachAllViews();

    void update(sf::Time delta) override;
	void onCommand(const Command &command, sf::Time dt);
    void setReverse(bool reverse = true);
	virtual unsigned int getCategory() const;

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

    void checkSceneCollision(const ViewGroup& sceneGraph, std::set<Pair>& collisionPairs);
	void checkNodeCollision(const ViewGroup& node, std::set<Pair>& collisionPairs);
	// void removeWrecks();
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool isMarkedForRemoval() const;
	virtual bool isDestroyed() const;
	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const = 0;

private:
    bool isReverse;
    std::vector<Viewable::Ptr> childViews;

private:
    virtual void updateCurrent(sf::Time delta);
    void updateChildren(sf::Time delta);
};

bool collision(const ViewGroup& lhs, const ViewGroup& rhs);
float distance(const ViewGroup& lhs, const ViewGroup& rhs);

#endif