#ifndef HELP_ACTIVITY_HPP
#define HELP_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>

class HelpActivity: public Activity {
private:
    static const int REQUEST_TITLEBAR_BUTTONS = 126;

    FontHolder mFontHolder;
    TextureHolder mTextureHolder;

protected:
    virtual void onEvent(const sf::Event& event) override;
    virtual void onCreate() override;
    virtual void onLoadResources() override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    void updateCurrent(sf::Time dt) override;

private:
    void createBackButton();
    void createBackground();
    void createTitle();
};

#endif