#ifndef DEMO_ACTIVITY_HPP
#define DEMO_ACTIVITY_HPP

#include <Activity.hpp>
#include <RectangleView.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

class DemoActivity : public Activity
{
private:
    int id;
    RectangleView *mRect;

    MusicPlayer mPlayer;
    SoundPlayer sPlayer;

protected:
    virtual void onEvent(const sf::Event& event) override;
    virtual void onCreate() override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    void updateCurrent(sf::Time dt) override;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data) override;
};

#endif