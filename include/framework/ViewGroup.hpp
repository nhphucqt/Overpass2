#ifndef VIEW_GROUP_HPP
#define VIEW_GROUP_HPP

#include <Viewable.hpp>

class ViewGroup : public Viewable {
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

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const = 0;

private:
    bool isReverse;
    virtual void updateCurrent(sf::Time delta);
    void updateChildren(sf::Time delta);
};

#endif