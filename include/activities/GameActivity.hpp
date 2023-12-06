#ifndef GAME_ACTIVITY_HPP
#define GAME_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>

class GameActivity : public Activity {
public:
    static const int ACTION_NEW_GAME = 1;
    static const int ACTION_CONTINUE_GAME = 2;

    enum class GameLevel {
        Easy,
        Medium,
        Hard,
        Endless
    };

private:
    FontManager mFontManager;

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
    void createTitle();
    void createBackButton();
    void createGame(GameLevel level);
};

#endif 