#ifndef MAIN_MENU_ACTIVITY_HPP
#define MAIN_MENU_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>

class MainMenuActivity : public Activity {
private:
    int REQUEST_CODE_GAME_LEVEL = 123;
    int REQUEST_CODE_CONTINUE_GAME = 124;
    int REQUEST_LOGIN = 125;
    int REQUEST_TITLEBAR_BUTTONS = 126;

    FontManager mFontManager;
    TextureManager mTextureManager;

protected:
    virtual void onEvent(const sf::Event& event) override;
    virtual void onCreate() override;
    virtual void onLoadResources() override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    void updateCurrent(sf::Time dt) override;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data) override;

private:
    void createBackground();
    void createTitle();
    void createPlayButtons();
};

#endif