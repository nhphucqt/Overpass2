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
                std::cerr << " >> MainMenuActivity::onActivityResult: titleType is not set" << std::endl;
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
        BackgroundFactory::create(mTextureManager.get(TextureID::mainMenuBackgroundTexture))
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
    sf::Vector2f position((windowSize.x-width)/2, 300);
    sf::Vector2f spacing(0, height + 2);

    sf::Texture& buttonTexture = mTextureManager.get(TextureID::mainMenuButtonTexture);

    SpriteButtonView::Ptr easyButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Easy", position, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::Easy);
    });

    SpriteButtonView::Ptr mediumButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Medium", spacing, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::Medium);
    });

    SpriteButtonView::Ptr hardButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Hard", spacing, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::Hard);
    });

    SpriteButtonView::Ptr endlessButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Endless", spacing, [this](EventListener* listener, const sf::Event& event) {
        this->enterGame(GameActivity::GameLevel::Endless);
    });

    hardButton->attachView(std::move(endlessButton));
    mediumButton->attachView(std::move(hardButton));
    easyButton->attachView(std::move(mediumButton));
    attachView(std::move(easyButton));
}

void LevelsActivity::enterGame(GameActivity::GameLevel level) {
    Intent::Ptr intent = Intent::Builder()
        .putExtra("level", level)
        .setAction(GameActivity::ACTION_NEW_GAME)
        .build();
    setResult(ResultCode::RESULT_OK, std::move(intent));
    finish();
}