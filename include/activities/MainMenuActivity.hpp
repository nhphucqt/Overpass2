#ifndef MAIN_MENU_ACTIVITY_HPP
#define MAIN_MENU_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>

class MainMenuActivity : public Activity {
private:
    enum Request {
        REQUEST_CODE_GAME_LEVEL,
        REQUEST_CODE_CONTINUE_GAME,
        REQUEST_CODE_NEW_GAME,
        REQUEST_LOGIN,
        REQUEST_TITLEBAR_BUTTONS
    };

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