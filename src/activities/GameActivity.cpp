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
#include <UserSession.hpp>
#include <UtilitySave.hpp>

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

    if (getIntent()->getAction() == ACTION_NEW_GAME)
    {
        attachLanes();
        attachPlayer();
    }
    else
    {
        // load game
        loadGameState("data/" + UserSession::getInstance().getCurrentUser().getUsername());
    }
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
    // std::cout << "scroll is fine1\n";
    scroll(dt);
    // std::cout << "scroll is fine2\n";
    // Forward commands to scene graph, adapt velocity (scrolling, diagonal
    // correction)
    while (!mCommandQueue.isEmpty())
    {
        Command command = mCommandQueue.pop();
        onCommand(command, dt);
    }
    // std::cout << "command is fine\n";

    handleCollisions();
    // std::cout << "collision is fine\n";
    // Apply movements

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        std::cout << "Save data.\n";
        saveGameState("data/" + UserSession::getInstance().getCurrentUser().getUsername());
    }
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
        if (matchesCategories(pair, Category::Player, Category::Vehicle) || matchesCategories(pair, Category::Player, Category::Animal) || matchesCategories(pair, Category::Player, Category::Train))
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
    int currentLaneIndex = std::distance(lanes->begin(), mPlayerNode->getCurrentLane());
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
        mMapRenderer->moveView();
        mSceneLayers[Background]->attachView(
            std::unique_ptr<ViewGroup>(lanes->back()));
    }
}

void GameActivity::gameOver()
{
    std::unique_ptr<Entity> banner(
        new Entity(mTextures.get(TextureID::GameOver)));
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
                             mWorldView.getSize());
    banner->setPosition(viewBounds.getPosition().x,
                        viewBounds.getPosition().y + 300);
    mSceneLayers[Aboveground]->attachView(std::move(banner));
    setUpdate(false);
    DeleteDirContent("data/" + UserSession::getInstance().getCurrentUser().getUsername());
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
        lane.setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height - CELL_HEIGHT * lane_index);
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
    Lane *spawnLane = *std::next(lanes->begin(), 1);
    std::cout << "spawn lane type: " << spawnLane->getType() << std::endl;
    // mSceneLayers[Aboveground]->attachView(std::move(player));
    // createTitle();

    mWorldView.setCenter(mSpawnPosition);
}

void GameActivity::saveGameState(const std::string &filepath)
{
    DeleteDirContent("data/" + UserSession::getInstance().getCurrentUser().getUsername());
    std::error_code err;
    if (!CreateDirectoryRecursive(filepath, err))
    {
        std::cerr << "SAVE FAILURE, ERR: " << err << std::endl;
    }
    std::ofstream outf(filepath + "/save.data", std::ios::binary);
    int laneSize = lanes->size();
    outf.write(reinterpret_cast<const char *>(&laneSize), sizeof(laneSize));
    if (lanes->size() > 0)
    {
        for (auto it = lanes->begin(); it != lanes->end(); ++it)
        {
            Lane *lane = *it;
            lane->saveLaneData(outf);
        }
    }
    if (mPlayerNode)
    {
        mPlayerNode->savePlayerData(outf);
    }
}

void GameActivity::loadGameState(const std::string &filepath)
{
    std::ifstream inf(filepath + "/save.data", std::ios::binary);
    if (!inf)
    {
        std::cerr << filepath + "/save.data not found.\n";
        // tell player to create new game instead
    }

    int laneSize;
    inf.read(reinterpret_cast<char *>(&laneSize), sizeof(laneSize));
    // MapRenderer::LaneList moddedLane;
    for (int i = 0; i < laneSize; ++i)
    {
        int laneType;
        bool laneIsReverse;
        inf.read(reinterpret_cast<char *>(&laneType), sizeof(laneType));
        inf.read(reinterpret_cast<char *>(&laneIsReverse), sizeof(laneIsReverse));

        std::unique_ptr<Lane> lane;
        switch (static_cast<Lane::Type>(laneType))
        {
        case Lane::Type::Road:
            unsigned int vehiclesCnt, animalsCnt, vehicleType, animalType;
            float velocity;
            inf.read(reinterpret_cast<char *>(&vehiclesCnt), sizeof(vehiclesCnt));
            inf.read(reinterpret_cast<char *>(&animalsCnt), sizeof(animalsCnt));
            inf.read(reinterpret_cast<char *>(&vehicleType), sizeof(vehicleType));
            inf.read(reinterpret_cast<char *>(&animalType), sizeof(animalType));
            inf.read(reinterpret_cast<char *>(&velocity), sizeof(velocity));

            lane.reset(new Road(&mTextures, laneIsReverse, vehiclesCnt, animalsCnt, static_cast<Vehicle::Type>(vehicleType), static_cast<Animal::Type>(animalType), velocity, true));
            lane->loadLaneData(inf);
            break;
        case Lane::Type::River:
            float logVelocity;
            inf.read(reinterpret_cast<char *>(&logVelocity), sizeof(logVelocity));
            lane.reset(new River(&mTextures, laneIsReverse, logVelocity, true));
            lane->loadLaneData(inf);
            break;
        case Lane::Type::Field:
            lane.reset(new Field(&mTextures, laneIsReverse, true));
            lane->loadLaneData(inf);
            break;
        case Lane::Type::Railway:
            lane.reset(new Railway(&mTextures, mSceneLayers[Aboveground], laneIsReverse, true));
            lane->loadLaneData(inf);
            break;
        default:
            throw std::runtime_error("LOAD ERR: Lane type not found");
        }
        moddedLane.push_back(lane.get());
        float const CELL_HEIGHT = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize).y;
        // lane->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height - CELL_HEIGHT * i);
        lane->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height - 128 * i);
        mSceneLayers[Background]->attachView(std::move(lane));
    }
    lanes = &moddedLane;
    int playerCurrentLane;
    inf.read(reinterpret_cast<char *>(&playerCurrentLane), sizeof(playerCurrentLane));
    auto player = std::make_unique<PlayerNode>(mTextures, *lanes, std::next(lanes->begin(), playerCurrentLane));
    mPlayerNode = player.get();
    mPlayerNode->setOrigin(mPlayerNode->getBoundingRect().getSize() / 2.f);
    mPlayerNode->setTransitionLayer(mSceneLayers[Aboveground]);

    mPlayerNode->loadPlayerData(inf);
    playerLaneIndex = playerCurrentLane;
    (*std::next(lanes->begin(), playerCurrentLane))->spawnPlayer(std::move(player));
    mWorldView.setCenter(mWorldView.getSize().x / 2.f, mPlayerNode->getPosition().y);
}
