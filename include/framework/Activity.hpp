#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <ActivityManager.hpp>
#include <ViewGroup.hpp>

class ActivityManager;

class Activity: public ViewGroup {
friend class ActivityManager;

private:
    ActivityManager* mManager;

public:
    Activity();
    ~Activity();

    ActivityManager* getActivityManager();
    void setActivityManager(ActivityManager* manager);

    void finish();

protected:
    virtual void onEvent(sf::Event& event);
    virtual void onUpdate();
    virtual void onAttach();
    virtual void onResume();
    virtual void onPause();
    virtual void onDestroy();
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif