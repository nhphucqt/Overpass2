#ifndef GAME_ACTIVITY_HPP
#define GAME_ACTIVITY_HPP

#include <Activity.hpp>
#include <Command.hpp>
#include <CommandQueue.hpp>
#include <Green.hpp>
#include <Log.hpp>
#include <MapRenderer.hpp>
#include <Player.hpp>
#include <PlayerNode.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <Train.hpp>
#include <ViewGroup.hpp>

#include <LayerView.hpp>
#include <TextView.hpp>
#include <SpriteView.hpp>

#include <array>
#include <list>

class Lane;

class GameActivity : public Activity
{
public:
    enum Action {
        ACTION_NEW_GAME,
        ACTION_CONTINUE_GAME
    };

    enum class GameLevel
    {
        Easy,
        Medium,
        Hard,
        Insane,
        RainDay,
        Endless
    };

    static const std::string EXTRA_GAME_LEVEL;
    static const std::string EXTRA_NUM_PLAYERS;

private:
    static const std::string GAME_STATE_FILENAME;
    static const std::string PLAYER_STATE_FILENAME;

    static const int REQUEST_TITLEBAR_BUTTONS = -1;

    enum Layer
    {
        Background,
        Aboveground,
        LayerCount
    };

private:
    bool mIsMutedBefore;

    std::vector<Player> mPlayers;
    std::vector<PlayerNode*> mPlayerNodes;
    std::vector<TextView*> mScoreTexts;

    bool mIsGameOver;

    LayerView::Ptr effectLayer, statusLayer;
    SpriteView* pauseMenu;

    FontManager mFontManager;
    TextureManager mTextures;
    MapRenderer::LaneList const *lanes;

    std::unique_ptr<MapRenderer> mMapRenderer;

    std::array<ViewGroup *, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;

    sf::View mWorldView;
    float mScrollSpeed;

    MyTimer mEffectTimer[2];

public:
    CommandQueue &getCommandQueue();

protected:
    virtual void onEvent(const sf::Event &event) override;
    virtual void onEventProcessing() override;
    virtual void onCreate() override;
    virtual void onLoadResources() override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    virtual void onDraw(sf::RenderTarget &target,
                        sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt) override;
    virtual void onActivityResult(int requestCode, int resultCode,
                                  Intent::Ptr data) override;
    virtual void drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const override;

private:
    static constexpr unsigned int DEFAULT_MAP_MAX_HEIGHT = 20;
    static constexpr unsigned int DEFAULT_SPAWN_LANE_ID = 3;

    static constexpr sf::Keyboard::Key ACTION_KEYS[2][4] = {
        {sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S},
        {sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down}
    };

    static constexpr float RAIN_EFFECT_DURATION[6][2][2] = {
        {{1e5f, 1e6f}, { 0.f,  0.f}}, // Easy
        {{15.f, 25.f}, { 5.f, 10.f}}, // Medium
        {{15.f, 20.f}, { 5.f, 10.f}}, // Hard
        {{15.f, 25.f}, {15.f, 25.f}}, // Insane
        {{ 0.f,  0.f}, {1e5f, 1e6f}}, // RainDay
        {{15.f, 25.f}, { 5.f, 10.f}}  // Endless
    };

    bool matchesCategories(ViewGroup::Pair &colliders, unsigned int type1, unsigned int type2);
    void handleCollisions(PlayerNode* playerNode);
    void scroll(sf::Time dt);

    void gameOver();
    bool isGameOver() const;

    void attachLanes();
    void attachPlayer();

    void saveGame();
    void loadGame();
    void removeSavedGame();
    void saveGameState(const std::string &gameStateFilePath, const std::string &playerStateFilePath);
    void loadGameState(const std::string &gameStateFilePath, const std::string &playerStateFilePath);
    void loadPlayer(const std::string& playerStateFilePath);
    void savePlayerScore();

    void initEffectTimer();

    void createGameOverBanner();
    void createStatusLayer();
    void createEffectLayer();

    void showEffect();
    void hideEffect();
    void toggleEffect();
    bool isEffectShown() const;

    void updateScore();

    void ensureEnoughLanes();
    void popOutOfViewLanes();

    int getLevel() const;
    int getNumPlayers() const;

    sf::FloatRect getViewBounds() const;
};

#endif
