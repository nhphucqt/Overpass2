#include <ActivityFactory.hpp>
#include <AppConfig.hpp>
#include <ButtonView.hpp>
#include <DemoActivity.hpp>
#include <Field.hpp>
#include <GameActivity.hpp>
#include <Railway.hpp>
#include <River.hpp>
#include <Road.hpp>
#include <TextView.hpp>
#include <iterator>

void GameActivity::onLoadResources()
{
    // lanes
    mTextures.load(TextureID::Road, "res/textures/Lane/Road.png");
    mTextures.load(TextureID::River, "res/textures/Lane/River.png");
    mTextures.load(TextureID::Rail, "res/textures/Lane/Rail.png");
    mTextures.load(TextureID::Field, "res/textures/Lane/Field.png");
    // vehicles
    mTextures.load(TextureID::Car, "res/textures/Vehicle/Car.png");
    mTextures.load(TextureID::Ambulance, "res/textures/Vehicle/Ambulance.png");
    mTextures.load(TextureID::Taxi, "res/textures/Vehicle/Taxi.png");
    mTextures.load(TextureID::Police, "res/textures/Vehicle/Police.png");
    // traffic light
    mTextures.load(TextureID::TrafficLight, "res/textures/TrafficLight.png");
    // animals
    mTextures.load(TextureID::Bear, "res/textures/Animal/Bear.png");
    mTextures.load(TextureID::Boar, "res/textures/Animal/Boar.png");
    mTextures.load(TextureID::Bunny, "res/textures/Animal/Bunny.png");
    mTextures.load(TextureID::Deer, "res/textures/Animal/Deer.png");
    mTextures.load(TextureID::Fox, "res/textures/Animal/Fox.png");
    mTextures.load(TextureID::Wolf, "res/textures/Animal/Wolf.png");
    // log
    mTextures.load(TextureID::Wood, "res/textures/Wood.png");
    // greens aka plants
    mTextures.load(TextureID::Tree, "res/textures/Green/Tree.png");
    mTextures.load(TextureID::Bush, "res/textures/Green/Bush.png");
    mTextures.load(TextureID::CircleBush, "res/textures/Green/CircleBush.png");
    // train
    mTextures.load(TextureID::Train, "res/textures/Train.png");
    // character animation panes
    mTextures.load(TextureID::CharacterUp, "res/textures/Character/Cat-Up.png");
    mTextures.load(TextureID::CharacterDown,
                   "res/textures/Character/Cat-Down.png");
    mTextures.load(TextureID::CharacterLeft,
                   "res/textures/Character/Cat-Left.png");
    mTextures.load(TextureID::CharacterRight,
                   "res/textures/Character/Cat-Right.png");
    mTextures.load(TextureID::CharacterIdle,
                   "res/textures/Character/Cat-Idle.png");
    // game over banner
    mTextures.load(TextureID::GameOver, "res/textures/Lane/GameOver.png");

    mFontManager.load(FontID::defaultFont, "res/fonts/Consolas-Bold.ttf");
}

void GameActivity::onCreate() {}

void GameActivity::onAttach()
{
    sf::RenderWindow &window = getActivityManager()->getWindow();
    window.setKeyRepeatEnabled(false);
    mWorldView = window.getDefaultView();
    mWorldBounds = sf::FloatRect(0.f, 0.f, mWorldView.getSize().x,
                                 mWorldView.getSize().y * 10);
    mSpawnPosition =
        sf::Vector2f(mWorldView.getSize().x / 2.f,
                     mWorldBounds.height - mWorldView.getSize().y / 2.f);
    mScrollSpeed = -600.f;
    clock = sf::Clock();
    stop = false;
    playerLaneIndex = 3;
    scrollDistance = 0;
    actualScrollDistance = 0;

    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        std::unique_ptr<ViewGroup> layer(new Entity());
        mSceneLayers[i] = layer.get();

        attachView(std::move(layer));
    }
    mSceneLayers[Background]->setReverse(true);

    attachLanes();
    attachPlayer();
}

void GameActivity::onResume()
{
    // ...
}

void GameActivity::onPause()
{
    // ...
}

void GameActivity::onDestroy()
{
    // ...
}

void GameActivity::onEvent(const sf::Event &event)
{
    CommandQueue &commands = getCommandQueue();
    mPlayer.handleEvent(event, commands);
}

void GameActivity::onEventProcessing()
{
    // mPlayer.handleRealtimeInput(getCommandQueue());
}

void GameActivity::updateCurrent(sf::Time dt)
{
    // Scroll the world
    scroll(dt);

    // generate new lane every 25 lanes passsed
    if (playerLaneIndex % 25 == 0)
    {
        for (int i = 1; i <= 25; ++i)
        {
            mMapRenderer->moveView();
            mSceneLayers[Background]->attachView(
                std::unique_ptr<ViewGroup>(lanes->back()));
        }
    }

    // Forward commands to scene graph, adapt velocity (scrolling, diagonal
    // correction)
    while (!mCommandQueue.isEmpty())
    {
        Command command = mCommandQueue.pop();
        onCommand(command, dt);
    }

    handleCollisions();
    // Apply movements
}

void GameActivity::drawCurrent(sf::RenderTarget &target,
                               sf::RenderStates states) const
{
    target.setView(mWorldView);
}

void GameActivity::onActivityResult(int requestCode, int resultCode,
                                    Intent::Ptr data)
{
    // ...
}

bool GameActivity::matchesCategories(ViewGroup::Pair &colliders,
                                     Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    // Make sure first pair entry has category type1 and second has type2
    if (type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}

void GameActivity::handleCollisions()
{
    std::set<ViewGroup::Pair> collisionPairs;
    mPlayerNode->checkSceneCollision(**mPlayerNode->getCurrentLane(),
                                     collisionPairs);
    if (lanes->end() != std::next(mPlayerNode->getCurrentLane()))
    {
        mPlayerNode->checkSceneCollision(
            **std::next(mPlayerNode->getCurrentLane()), collisionPairs);
    }
    mPlayerNode->checkSceneCollision(**std::prev(mPlayerNode->getCurrentLane()),
                                     collisionPairs);

    bool onRiver = false;
    for (ViewGroup::Pair pair : collisionPairs)
    {
        if (matchesCategories(pair, Category::Player, Category::Vehicle)
            || matchesCategories(pair, Category::Player, Category::Animal)
            || matchesCategories(pair, Category::Player, Category::Train))
        {
            mPlayerNode->setDead();
        }
        else if (matchesCategories(pair, Category::Player, Category::Green))
        {
            mPlayerNode->moveBack();
        }
    }

    if (mPlayerNode->isDead())
    {
        gameOver();
    }
}

void GameActivity::scroll(sf::Time dt)
{
    AppConfig &config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
    int currentLaneIndex =
        std::distance(lanes->begin(), mPlayerNode->getCurrentLane());
    if (currentLaneIndex > playerLaneIndex)
    {
        scrollDistance += 128.f;
        ++playerLaneIndex;
    }
    else if (currentLaneIndex < playerLaneIndex)
    {
        scrollDistance -= 128.f;
        --playerLaneIndex;
    }

    float scrollStep = mScrollSpeed * dt.asSeconds();

    if (scrollDistance > 0)
    {
        scrollDistance += scrollStep;
        mWorldView.move(0.f, scrollStep);
    }
}

void GameActivity::gameOver()
{
    std::unique_ptr<Entity> banner(
        new Entity(mTextures.get(TextureID::GameOver)));
    sf::FloatRect viewBounds(mWorldView.getCenter()
                                 - mWorldView.getSize() / 2.f,
                             mWorldView.getSize());
    banner->setPosition(viewBounds.getPosition().x,
                        viewBounds.getPosition().y + 300);
    mSceneLayers[Aboveground]->attachView(std::move(banner));
    setUpdate(false);
}

CommandQueue &GameActivity::getCommandQueue()
{
    return mCommandQueue;
}

void GameActivity::attachLanes()
{
    Intent *intent = getIntent();
    unsigned int level = intent->getExtra<int>("level", -1);

    mMapRenderer = std::make_unique<MapRenderer>(
        mTextures, *mSceneLayers[Layer::Aboveground],
        AppConfig::getInstance().get<int>(ConfigKey::NumLaneCells),
        DEFAULT_MAP_MAX_HEIGHT, level);
    lanes = &mMapRenderer->getLanes();
    unsigned int lane_index = 0;
    for (auto it = lanes->begin(); it != lanes->end(); ++it)
    {
        Lane &lane = **it;
        float const CELL_HEIGHT =
            AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize).y;
        lane.setPosition(mWorldBounds.left, mWorldBounds.top
                                                + mWorldBounds.height
                                                - CELL_HEIGHT * lane_index);
        mSceneLayers[Background]->attachView(std::unique_ptr<ViewGroup>(*it));
        ++lane_index;
    }
}

void GameActivity::attachPlayer()
{
    auto player = std::make_unique<PlayerNode>(
        mTextures, *lanes,
        std::next(lanes->begin(),
                  1)); // last argument must be consistent with playerLaneIndex
    mPlayerNode = player.get();
    mPlayerNode->setOrigin(mPlayerNode->getBoundingRect().getSize() / 2.f);
    mPlayerNode->setTransitionLayer(mSceneLayers[Aboveground]);
    (*std::next(lanes->begin(), 1))->spawnPlayer(std::move(player));
    // mSceneLayers[Aboveground]->attachView(std::move(player));
    // createTitle();

    mWorldView.setCenter(mSpawnPosition);
}
