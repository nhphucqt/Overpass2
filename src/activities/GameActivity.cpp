#include <ActivityFactory.hpp>
#include <AppConfig.hpp>
#include <ButtonView.hpp>
#include <DemoActivity.hpp>
#include <Field.hpp>
#include <GameActivity.hpp>
#include <SettingsActivity.hpp>
#include <Railway.hpp>
#include <River.hpp>
#include <Road.hpp>
#include <iterator>
#include <UserSession.hpp>
#include <UtilitySave.hpp>

#include <LayerView.hpp>
#include <ButtonView.hpp>
#include <SpriteButtonView.hpp>
#include <TextView.hpp>
#include <IconButtonFactory.hpp>

const std::string GameActivity::GAME_STATE_FILENAME = "save.data";
const std::string GameActivity::PLAYER_STATE_FILENAME = "player.data";

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
    mTextures.load(TextureID::RailwayLightOff, "res/textures/RailwayLightOff.png");
    mTextures.load(TextureID::RailwayLightOn, "res/textures/RailwayLightOn.png");
    // animals
    mTextures.load(TextureID::Bear, "res/textures/Animal/Bear.png");
    mTextures.load(TextureID::Boar, "res/textures/Animal/Boar.png");
    mTextures.load(TextureID::Bunny, "res/textures/Animal/Bunny.png");
    mTextures.load(TextureID::Deer, "res/textures/Animal/Deer.png");
    mTextures.load(TextureID::Fox, "res/textures/Animal/Fox.png");
    mTextures.load(TextureID::Wolf, "res/textures/Animal/Wolf.png");
    // log
    mTextures.load(TextureID::WoodL2, "res/textures/WoodL2.png");
    mTextures.load(TextureID::WoodL3, "res/textures/WoodL3.png");
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
    mTextures.load(TextureID::homeButtonsTexture, "res/textures/ui/buttons/home_button.png");
    mTextures.load(TextureID::pauseButtonsTexture, "res/textures/ui/buttons/pause_button.png");
    mTextures.load(TextureID::continueButtonsTexture, "res/textures/ui/buttons/continue_button.png");
    mTextures.load(TextureID::settingButtonsTexture, "res/textures/ui/buttons/setting_button.png");
    mTextures.load(TextureID::replayButtonsTexture, "res/textures/ui/buttons/replay_button.png");
    mTextures.load(TextureID::mainMenuButtonTexture, "res/textures/ui/UI_Big_Play_Button.png");

    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
}

void GameActivity::onCreate() {
}

void GameActivity::onAttach()
{
    sf::RenderWindow &window = getActivityManager()->getWindow();
    window.setKeyRepeatEnabled(false);
    mWorldView = window.getDefaultView();

    mIsGameOver = false;
    mScrollSpeed = -600.f;

    effectLayer = std::make_unique<LayerView>();
    statusLayer = std::make_unique<LayerView>();

    createStatusLayer();

    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        std::unique_ptr<ViewGroup> layer(new Entity());
        mSceneLayers[i] = layer.get();

        attachView(std::move(layer));
    }
    mSceneLayers[Background]->setReverse(true);

    if (getIntent()->getAction() == ACTION_NEW_GAME) {
        attachLanes();
        attachPlayer();
    }
    else if (getIntent()->getAction() == ACTION_CONTINUE_GAME) {
        loadGame();
    }
    else {
        std::cerr << "Unknown action: " << getIntent()->getAction() << std::endl;
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
    if (!isGameOver()) {
        saveGame();
    } else {
        savePlayerScore();
    }
}

void GameActivity::onDraw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.setView(target.getDefaultView());
    target.draw(*effectLayer, states);
    target.draw(*statusLayer, states);
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
    popOutOfViewLanes();
    scroll(dt);

    // generate new lanes when there are few lanes left
    if (lanes->size() < DEFAULT_MAP_MAX_HEIGHT)
    {
        
        Lane* newLane = mMapRenderer->createNewLane();
        mSceneLayers[Background]->attachView(std::unique_ptr<ViewGroup>(newLane));
        mWorldView.move(0.f, newLane->getSize().y);
        if (mPlayerNode->isMoving()) {
            mPlayerNode->move(0.f, newLane->getSize().y);
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
    // Update score
    updateScore(scoreText, mPlayerNode);
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

    sf::FloatRect viewBounds = getViewBounds();
    sf::FloatRect playerBounds = mPlayerNode->getHitBox();
    if (viewBounds.top + viewBounds.height < playerBounds.top + playerBounds.height ||
        viewBounds.left + viewBounds.width < playerBounds.left ||
        viewBounds.left > playerBounds.left + playerBounds.width) {
        mPlayerNode->setDead();
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

    if (mPlayerNode->getWorldPosition().y - getViewBounds().top < cellSize.y * 5) {
        mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
    }
}

void GameActivity::gameOver()
{
    mIsGameOver = true;
    createGameOverBanner();
    setUpdate(false);
    removeSavedGame();
}

bool GameActivity::isGameOver() const
{
    return mIsGameOver;
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
    float const CELL_HEIGHT = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize).y;
    float const TOTAL_HEIGHT = CELL_HEIGHT * lanes->size();
    for (auto it = lanes->begin(); it != lanes->end(); ++it)
    {
        Lane &lane = **it;
        lane.setPosition(0, TOTAL_HEIGHT - CELL_HEIGHT * (lane_index + 1));
        mSceneLayers[Background]->attachView(std::unique_ptr<ViewGroup>(*it));
        ++lane_index;
    }

    mWorldView.move(0.f, TOTAL_HEIGHT - CELL_HEIGHT * (DEFAULT_SPAWN_LANE_ID - 1) - mWorldView.getSize().y);
}

void GameActivity::attachPlayer()
{
    MapRenderer::LaneList::const_iterator spawnLane = std::next(lanes->begin(), DEFAULT_SPAWN_LANE_ID);

    auto player = std::make_unique<PlayerNode>(mTextures, *lanes, spawnLane);
    mPlayerNode = player.get();
    mPlayerNode->setOrigin(mPlayerNode->getBoundingRect().getSize() / 2.f);
    mPlayerNode->setTransitionLayer(mSceneLayers[Aboveground]);

    (*spawnLane)->spawnPlayer(std::move(player));
}

void GameActivity::saveGameState(const std::string& gameStateFilePath, const std::string& playerStateFilePath)
{
    std::ofstream outf(gameStateFilePath, std::ios::binary);

    float viewCenterX = mWorldView.getCenter().x;
    float viewCenterY = mWorldView.getCenter().y;

    outf.write(reinterpret_cast<const char *>(&viewCenterX), sizeof(viewCenterX));
    outf.write(reinterpret_cast<const char *>(&viewCenterY), sizeof(viewCenterY));

    mMapRenderer->saveLanes(outf);
    outf.close();

    outf.open(playerStateFilePath, std::ios::binary);
    mPlayerNode->savePlayerData(outf); 
    outf.close();
}

void GameActivity::loadGameState(const std::string& gameStateFilePath, const std::string& playerStateFilePath)
{
    std::ifstream inf(gameStateFilePath, std::ios::binary);

    float viewCenterX;
    float viewCenterY;
    inf.read(reinterpret_cast<char *>(&viewCenterX), sizeof(viewCenterX));
    inf.read(reinterpret_cast<char *>(&viewCenterY), sizeof(viewCenterY));

    mWorldView.setCenter(viewCenterX, viewCenterY);

    mMapRenderer = std::make_unique<MapRenderer>(
        mTextures, *mSceneLayers[Layer::Aboveground],
        AppConfig::getInstance().get<int>(ConfigKey::NumLaneCells),
        DEFAULT_MAP_MAX_HEIGHT, 0, true);

    mMapRenderer->loadLanes(inf);

    inf.close();

    lanes = &mMapRenderer->getLanes();
    unsigned int lane_index = 0;
    float const CELL_HEIGHT = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize).y;
    float const TOTAL_HEIGHT = CELL_HEIGHT * lanes->size();
    for (auto it = lanes->begin(); it != lanes->end(); ++it)
    {
        Lane &lane = **it;
        lane.setPosition(0, TOTAL_HEIGHT - CELL_HEIGHT * (lane_index + 1));
        mSceneLayers[Background]->attachView(std::unique_ptr<ViewGroup>(*it));
        ++lane_index;
    }

    loadPlayer(playerStateFilePath);
}

void GameActivity::loadPlayer(const std::string& playerStateFilePath)
{
    std::ifstream inf(playerStateFilePath, std::ios::binary);

    auto player = std::make_unique<PlayerNode>(mTextures, *lanes);
    mPlayerNode = player.get();
    mPlayerNode->setOrigin(mPlayerNode->getBoundingRect().getSize() / 2.f);

    mPlayerNode->loadPlayerData(inf);
    mPlayerNode->setTransitionLayer(mSceneLayers[Aboveground]);
    mSceneLayers[Aboveground]->attachView(std::move(player));

    MapRenderer::LaneList::const_iterator spawnLane;
    float minDistance = std::numeric_limits<float>::max();
    for (auto it = lanes->begin(); it != lanes->end(); ++it) {
        float distance = (*it)->getNearestDistance(mPlayerNode);
        if (distance < minDistance) {
            minDistance = distance;
            spawnLane = it;
        }
    }

    mPlayerNode->setCurrentLane(spawnLane);
    (*spawnLane)->receivePlayer(mPlayerNode);
}

void GameActivity::createStatusLayer() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    TextView::Ptr pointView = std::make_unique<TextView>(
        this,
        "0",
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(10, 10),
        64
    );
    pointView->setFillColor(sf::Color::White);
    scoreText = pointView.get();

    SpriteView::Ptr menuView = std::make_unique<SpriteView>(
        this,
        mTextures.get(TextureID::mainMenuButtonTexture),
        sf::Vector2f(0, 0),
        sf::Vector2f(90, 25) * 5.f,
        sf::IntRect(99, 4, 90, 25)
    );
    sf::Vector2f menuSize = menuView->get().getGlobalBounds().getSize();
    menuView->setOrigin(menuSize / 2.f);
    menuView->setPosition(windowSize / 2.f);
    menuView->setVisibility(false);
    pauseMenu = menuView.get();

    SpriteButtonView::Ptr pauseButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::pauseButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            this->setUpdate(false);
            this->pauseMenu->setVisibility(true);
            this->pauseMenu->setIsListeningAll(true);
        }
    );
    pauseButton->setOrigin(pauseButton->getGlobalBounds().getSize().x, 0);
    pauseButton->setPosition(windowSize.x - 10.f, 10.f);

    SpriteButtonView::Ptr continueButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::continueButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            this->setUpdate(true);
            this->pauseMenu->setVisibility(false);
            this->pauseMenu->setIsListeningAll(false);
        }
    );

    SpriteButtonView::Ptr homeButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::homeButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            this->finish();
        }
    );
    homeButton->setOrigin(homeButton->getGlobalBounds().getSize() / 2.f);

    SpriteButtonView::Ptr settingButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::settingButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            Intent::Ptr intent = Intent::Builder()
                    .setAction(SettingsActivity::ACTION_INGAME)
                    .build();
            this->startActivity(ActivityFactory<SettingsActivity>::createInstance(), std::move(intent));
        }
    );

    float padding = 125;
    continueButton->setPosition(-padding, 0);
    settingButton->setPosition(padding, 0);
    homeButton->setPosition(menuSize / 2.f);

    homeButton->attachView(std::move(continueButton));
    homeButton->attachView(std::move(settingButton));
    menuView->attachView(std::move(homeButton));

    statusLayer->attachView(std::move(pointView));
    statusLayer->attachView(std::move(pauseButton));
    statusLayer->attachView(std::move(menuView));
}

void GameActivity::createGameOverBanner() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    ButtonView::Ptr bannerView = std::make_unique<ButtonView>(
        this,
        mTextures.get(TextureID::mainMenuButtonTexture),
        mFontManager.get(FontID::defaultFont),
        "Game Over",
        64,
        sf::Vector2f(0, 0),
        sf::IntRect(99, 4, 90, 25),
        sf::Vector2f(90, 25) * 5.f
    );
    sf::Vector2f bannerSize = bannerView->getGlobalBounds().getSize();
    bannerView->setOrigin(bannerSize.x / 2.f, bannerSize.y / 2.f);
    bannerView->setPosition(windowSize.x / 2.f, windowSize.y / 2.f);

    SpriteButtonView::Ptr replayButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::replayButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            Intent* intent = this->getIntent();
            Intent::Ptr resIntent = Intent::Builder()
                .setAction(GameActivity::ACTION_NEW_GAME)
                .putExtra("level", intent->getExtra<int>("level", -1))
                .build();
            this->setResult(RESULT_OK, std::move(resIntent));
            this->finish();
        }
    );
    replayButton->setOrigin(replayButton->getGlobalBounds().getSize().x, 0);

    SpriteButtonView::Ptr homeButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::homeButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            this->finish();
        }
    );
    homeButton->setOrigin(homeButton->getGlobalBounds().getSize().x / 2.f, 0);

    float paddingX = 100;
    float paddingY = 10;
    replayButton->setPosition(bannerSize.x / 2.f - paddingX, bannerSize.y + paddingY);
    homeButton->setPosition(bannerSize.x / 2.f + paddingX, bannerSize.y + paddingY);

    bannerView->attachView(std::move(replayButton));
    bannerView->attachView(std::move(homeButton));
    statusLayer->attachView(std::move(bannerView));
}

void GameActivity::updateScore(TextView* scoreText, PlayerNode* playerNode) {
    scoreText->setText(std::to_string(playerNode->getScore()));
}

void GameActivity::pushNewLane() {

}

void GameActivity::popOutOfViewLanes() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
    float threshold = cellSize.y * 5;

    sf::FloatRect worldBounds = getViewBounds();
    while (!lanes->empty() && lanes->front()->getPosition().y > worldBounds.top + worldBounds.height + threshold) {
        mMapRenderer->popLane();
    }
}

sf::FloatRect GameActivity::getViewBounds() const {
    sf::FloatRect rt;
    rt.left = mWorldView.getCenter().x - mWorldView.getSize().x/2.f;
    rt.top  = mWorldView.getCenter().y - mWorldView.getSize().y/2.f;
    rt.width  = mWorldView.getSize().x;
    rt.height = mWorldView.getSize().y;
    return rt;
}

void GameActivity::saveGame() {
    UserSession& userSession = UserSession::getInstance();
    if (!userSession.isLoggedin()) {
        std::cerr << "User not logged in.\n";
        return;
    }
    AppConfig& config = AppConfig::getInstance();
    std::string dataPath = config.get<std::string>(ConfigKey::DATA_PATH);
    std::string username = userSession.getCurrentUser().getUsername();
    std::string dirPath = dataPath + username;

    UtilitySave::DeleteDirContent(dirPath);
    std::error_code err;
    if (!UtilitySave::CreateDirectoryRecursive(dirPath, err)) {
        std::cerr << "SAVE FAILURE, ERR: " << err << std::endl;
    }

    std::string gameStateFilePath = dirPath + "/" + GAME_STATE_FILENAME;
    std::string playerStateFilePath = dirPath + "/" + PLAYER_STATE_FILENAME;
    saveGameState(gameStateFilePath, playerStateFilePath);
}

void GameActivity::loadGame() {
    UserSession& userSession = UserSession::getInstance();
    if (!userSession.isLoggedin()) {
        std::cerr << "User not logged in.\n";
        return;
    }
    AppConfig& config = AppConfig::getInstance();
    std::string dataPath = config.get<std::string>(ConfigKey::DATA_PATH);
    std::string username = userSession.getCurrentUser().getUsername();
    std::string gameStateFilePath = dataPath + username + "/" + GAME_STATE_FILENAME;
    std::string playerStateFilePath = dataPath + username + "/" + PLAYER_STATE_FILENAME;
    loadGameState(gameStateFilePath, playerStateFilePath);
}

void GameActivity::removeSavedGame() {
    UserSession& userSession = UserSession::getInstance();
    if (!userSession.isLoggedin()) {
        std::cerr << "User not logged in.\n";
        return;
    }
    AppConfig& config = AppConfig::getInstance();
    std::string dataPath = config.get<std::string>(ConfigKey::DATA_PATH);
    std::string username = userSession.getCurrentUser().getUsername();
    std::string dirPath = dataPath + username;

    UtilitySave::DeleteDirContent(dirPath);
}

void GameActivity::savePlayerScore() {
    UserSession& userSession = UserSession::getInstance();
    if (!userSession.isLoggedin()) {
        std::cerr << "User not logged in.\n";
        return;
    }
    UserData& user = userSession.getCurrentUser();
    GameLevel level = (GameLevel)mMapRenderer->getLevel();
    UserData::GameMode mode;

    switch(level) {
        case GameLevel::Easy:
            mode = UserData::GameMode::easy;
        break;
        case GameLevel::Medium:
            mode = UserData::GameMode::medium;
        break;
        case GameLevel::Hard:
            mode = UserData::GameMode::hard;
        break;
        case GameLevel::Endless:
            mode = UserData::GameMode::endless;
        break;
    }
    user.updateHighscore(mPlayerNode->getScore(), mode);

    UserRepo& userRepo = UserRepo::getInstance();
    userRepo.updateUser(user);
}