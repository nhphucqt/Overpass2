#ifndef RANKING_ACTIVITY_HPP
#define RANKING_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>

#include <RectangleView.hpp>
#include <ButtonView.hpp>

class RankingActivity : public Activity {
private:
    static const int REQUEST_TITLEBAR_BUTTONS = 126;

    TextureHolder mTextureHolder;
    FontHolder mFontHolder;

    RectangleView* rankingView;
    ButtonView* rankingTitle;
    int currentGameMode;
    int limitRanking;
    sf::Vector2f barSize;
    int barFontSize;

protected:
    virtual void onCreate() override;
    virtual void onLoadResources() override;
    virtual void onActivityResult(int requestCode, ResultCode resultCode, Intent::Ptr data) override;

private:
    void createBackground();
    void createTitle();
    void createBackButton();
    void createBoard();
    void updateRanking();
};

#endif