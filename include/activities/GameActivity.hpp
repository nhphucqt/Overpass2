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
        Endless
    };

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
    Player mPlayer;

    bool mIsGameOver;

    LayerView::Ptr effectLayer, statusLayer;
    TextView* scoreText;
    SpriteView* pauseMenu;

    FontManager mFontManager;
    TextureManager mTextures;
    MapRenderer::LaneList const *lanes;

    std::unique_ptr<MapRenderer> mMapRenderer;

    std::array<ViewGroup *, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;
    PlayerNode *mPlayerNode;

    sf::View mWorldView;
    float mScrollSpeed;

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

    bool matchesCategories(ViewGroup::Pair &colliders, Category::Type type1,
                           Category::Type type2);
    void handleCollisions();
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

    void createGameOverBanner();
    void createStatusLayer();

    void updateScore(TextView* scoreText, PlayerNode* playerNode);

    void pushNewLane();
    void popOutOfViewLanes();

    sf::FloatRect getViewBounds() const;
};

#endif
