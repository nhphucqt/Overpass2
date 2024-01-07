#include <LevelsActivity.hpp>
#include <AppConfig.hpp>

#include <TextView.hpp>
#include <ButtonView.hpp>
#include <SpriteButtonView.hpp>
#include <ActivityFactory.hpp>

#include <DemoActivity.hpp>
#include <GameActivity.hpp>
#include <SettingsActivity.hpp>
#include <ProfileActivity.hpp>
#include <HelpActivity.hpp>

#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>
#include <MenuButtonFactory.hpp>
#include <SquareButtonFactory.hpp>

void LevelsActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuButtonTexture, "res/textures/ui/UI_Big_Play_Button.png");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
}

void LevelsActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
    createLevelButtons();
}

void LevelsActivity::onAttach() {
    // ...
}

void LevelsActivity::onResume() {
    // ...
}

void LevelsActivity::onPause() {
    // ...
}

void LevelsActivity::onDestroy() {
    // ...
}

void LevelsActivity::onEvent(const sf::Event& event) {
    // ...
}

void LevelsActivity::updateCurrent(sf::Time dt) {
    // ...
}

void LevelsActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    if (requestCode == REQUEST_TITLEBAR_BUTTONS) {
        if (resultCode == (int)ResultCode::RESULT_OK) {
            int titleType = data->getExtra<int>("titleType", -1);
            if (titleType == -1) {
                return;
            }
            Intent::Ptr intent = Intent::Builder()
                .setRequestCode(REQUEST_TITLEBAR_BUTTONS)
                .build();
            if (titleType == (int)TitlebarFactory::TitlebarType::SETTINGS) {
                startActivity(ActivityFactory<SettingsActivity>::createInstance(), std::move(intent));
            } else if (titleType == (int)TitlebarFactory::TitlebarType::HELP) {
                startActivity(ActivityFactory<HelpActivity>::createInstance(), std::move(intent));
            } else if (titleType == (int)TitlebarFactory::TitlebarType::PROFILE) {
                startActivity(ActivityFactory<ProfileActivity>::createInstance(), std::move(intent));
            }
        }
    }
}

void LevelsActivity::createBackground() {
    attachView(
        BackgroundFactory::create(this, mTextureManager.get(TextureID::mainMenuBackgroundTexture))
    );
}

void LevelsActivity::createTitle() {
    attachView(
        TitlebarFactory::create(
            this,
            mTextureManager,
            mFontManager.get(FontID::defaultFont),
            "Levels",
            TitlebarFactory::TitlebarType::NONE,
            REQUEST_TITLEBAR_BUTTONS
        )
    );
}

void LevelsActivity::createBackButton() {
    attachView(
        BackButtonFactory::create(
            this,
            mTextureManager.get(TextureID::squareButtonsTexture),
            mFontManager.get(FontID::defaultFont)
        )
    );
}

void LevelsActivity::createLevelButtons() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    float width = 320;
    float height = 128;
    sf::Vector2f position((windowSize.x-(2*width+30))/2, 300);
    sf::Vector2f spacingX(width + 30, 0);
    sf::Vector2f spacingY(0, height + 5);

    sf::Texture& buttonTexture = mTextureManager.get(TextureID::mainMenuButtonTexture);

    ButtonView::Ptr bannerView = std::make_unique<ButtonView>(
        this,
        buttonTexture,
        mFontManager.get(FontID::defaultFont),
        "",
        64,
        sf::Vector2f(0, 0),
        sf::IntRect(99, 4, 90, 25),
        sf::Vector2f(90, 25) * 4.f
    );
    numPlayersText = bannerView.get();

    SpriteButtonView::Ptr onePlayerButton = SquareButtonFactory::create(
        this, 
        mTextureManager.get(TextureID::squareButtonsTexture), 
        mFontManager.get(FontID::defaultFont), 
        "1", 
        sf::Vector2f(0, 0), 
        [this](EventListener* listener, const sf::Event& event) {
            this->setOnePlayer();
        }
    );
    SpriteButtonView::Ptr twoPlayersButton = SquareButtonFactory::create(
        this, 
        mTextureManager.get(TextureID::squareButtonsTexture), 
        mFontManager.get(FontID::defaultFont), 
        "2", 
        sf::Vector2f(0, 0), 
        [this](EventListener* listener, const sf::Event& event) {
            this->setTwoPlayers();
        }
    );


    sf::Vector2f bannerSize = bannerView->getGlobalBounds().getSize();
    sf::Vector2f buttonSize = onePlayerButton->getGlobalBounds().getSize();
    float paddingX = 0;
    float paddingY = 0;
    float buttonHeight = buttonSize.y + buttonSize.y + paddingY;

    bannerView->setPosition(200, 50);

    onePlayerButton->setPosition(bannerSize.x + paddingX, (bannerSize.y - buttonHeight) / 2);
    twoPlayersButton->setPosition(0, buttonSize.y + paddingY);

    onePlayerButton->attachView(std::move(twoPlayersButton));
    bannerView->attachView(std::move(onePlayerButton));

    SpriteButtonView::Ptr easyButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Easy", position, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::Easy);
    });

    SpriteButtonView::Ptr mediumButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Medium", spacingX, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::Medium);
    });

    SpriteButtonView::Ptr hardButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Hard", spacingY, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::Hard);
    });

    SpriteButtonView::Ptr insaneButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Insane", spacingX, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::Insane);
    });

    SpriteButtonView::Ptr rainButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Rain Day", spacingY, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::RainDay);
    });

    SpriteButtonView::Ptr endlessButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Endless", spacingX, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::Endless);
    });

    rainButton->attachView(std::move(endlessButton));

    hardButton->attachView(std::move(rainButton));
    hardButton->attachView(std::move(insaneButton));

    easyButton->attachView(std::move(hardButton));
    easyButton->attachView(std::move(mediumButton));

    attachView(std::move(easyButton));
    attachView(std::move(bannerView));

    setOnePlayer();
}

void LevelsActivity::enterGame(GameActivity::GameLevel level) {
    Intent::Ptr intent = Intent::Builder()
        .putExtra(GameActivity::EXTRA_GAME_LEVEL, level)
        .putExtra(GameActivity::EXTRA_NUM_PLAYERS, numPlayers)
        .setAction(GameActivity::ACTION_NEW_GAME)
        .build();
    setResult(ResultCode::RESULT_OK, std::move(intent));
    finish();
}

void LevelsActivity::setOnePlayer() {
    numPlayersText->setText("1 Player");
    numPlayers = 1;
}

void LevelsActivity::setTwoPlayers() {
    numPlayersText->setText("2 Players");
    numPlayers = 2;
}