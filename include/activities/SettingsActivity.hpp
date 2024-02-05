#ifndef SETTINGS_ACTIVITY_HPP
#define SETTINGS_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>

class SettingsActivity : public Activity {
public:
    static const int ACTION_INGAME = 1;

private:
    static const int REQUEST_TITLEBAR_BUTTONS = 126;

    TextureHolder mTextureHolder;
    FontHolder mFontHolder;

protected:
    virtual void onCreate() override;
    virtual void onLoadResources() override;

private:
    void createBackground();
    void createTitle();
    void createBackButton();
    void createMenu();
};

#endif