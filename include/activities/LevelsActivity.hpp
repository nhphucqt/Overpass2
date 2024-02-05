#ifndef LEVELS_ACTIVITY_HPP
#define LEVELS_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>

#include <GameActivity.hpp>
#include <ButtonView.hpp>

class LevelsActivity : public Activity {
private:
    static const int REQUEST_TITLEBAR_BUTTONS = 126;

    TextureHolder mTextureHolder;
    FontHolder mFontHolder;

    ButtonView* numPlayersText;
    int numPlayers;

protected:
    virtual void onCreate() override;
    virtual void onLoadResources() override;
    virtual void onActivityResult(int requestCode, ResultCode resultCode, Intent::Ptr data) override;

private:
    void createBackground();
    void createTitle();
    void createBackButton();
    void createLevelButtons();

    void enterGame(GameActivity::GameLevel level);
    void setOnePlayer();
    void setTwoPlayers();
};

#endif