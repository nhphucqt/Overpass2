#include <SettingsActivity.hpp>
#include <AppConfig.hpp>
#include <TextView.hpp>
#include <ButtonView.hpp>
#include <ToggleButtonView.hpp>
#include <SpriteView.hpp>

#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>
#include <SettingToggleFactory.hpp>

#include <GameSetting.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

void SettingsActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
    mTextureManager.load(TextureID::toggleButtonsTexture, "res/textures/ui/UI_Settings_Buttons.png");
    mTextureManager.load(TextureID::settingMenuTexture, "res/textures/ui/Setting menu.png");
}

void SettingsActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
    createMenu();
}

void SettingsActivity::onAttach() {
    // ...
}

void SettingsActivity::onResume() {
    // ...
}

void SettingsActivity::onPause() {
    // ...
}

void SettingsActivity::onDestroy() {
    // ...
}

void SettingsActivity::onEvent(const sf::Event& event) {
    // ...
}

void SettingsActivity::updateCurrent(sf::Time dt) {
    // ...
}

void SettingsActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    // ...
}

void SettingsActivity::createBackground() {
    attachView(
        BackgroundFactory::create(this, mTextureManager.get(TextureID::mainMenuBackgroundTexture))
    );
}

void SettingsActivity::createTitle() {
    int requestCode = getIntent()->getAction() == ACTION_INGAME ? -1 : REQUEST_TITLEBAR_BUTTONS;
    attachView(
        TitlebarFactory::create(
            this,
            mTextureManager,
            mFontManager.get(FontID::defaultFont),
            "Settings",
            TitlebarFactory::TitlebarType::SETTINGS,
            requestCode
        )
    );
}

void SettingsActivity::createBackButton() {
    attachView(
        BackButtonFactory::create(
            this,
            mTextureManager.get(TextureID::squareButtonsTexture),
            mFontManager.get(FontID::defaultFont)
        )
    );
}

void SettingsActivity::createMenu() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    SpriteView::Ptr menu = std::make_unique<SpriteView>(
        this,
        mTextureManager.get(TextureID::settingMenuTexture),
        sf::Vector2f(0, 0),
        sf::Vector2f(106, 122) * 4.f,
        sf::IntRect(139, 12, 106, 122)
    );
    menu->setPosition((windowSize - menu->get().getGlobalBounds().getSize()) / 2.f + sf::Vector2f(0, 100));

    ToggleButtonView::Ptr musicToggle = SettingToggleFactory::create(
        this,
        mTextureManager.get(TextureID::toggleButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        "Music",
        false
    );
    musicToggle->setPosition((menu->get().getGlobalBounds().getSize() - musicToggle->getGlobalBounds().getSize() - sf::Vector2f(0, musicToggle->getGlobalBounds().getSize().y + 20)) / 2.f);
    musicToggle->move(30, 0);

    ToggleButtonView::Ptr soundToggle = SettingToggleFactory::create(
        this,
        mTextureManager.get(TextureID::toggleButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        "Sound",
        false
    );
    soundToggle->move(0, musicToggle->getGlobalBounds().getSize().y + 20);

    MusicPlayer& musicPlayer = MusicPlayer::getInstance();
    SoundPlayer& soundPlayer = SoundPlayer::getInstance();

    // assert(musicPlayer.getVolume() == 0 || musicPlayer.getVolume() == 100);
    // assert(soundPlayer.getVolume() == 0 || soundPlayer.getVolume() == 100);

    // musicToggle->setState(musicPlayer.getVolume() != 0);
    // soundToggle->setState(soundPlayer.getVolume() != 0);
    musicToggle->setState(!musicPlayer.isMuted());
    soundToggle->setState(!soundPlayer.isMuted());

    musicToggle->setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {
        ToggleButtonView* button = dynamic_cast<ToggleButtonView*>(listener);
        if (button->getState()) {
            musicPlayer.setMute(false);
            // musicPlayer.setVolume(100);
        } else {
            musicPlayer.setMute(true);
            // musicPlayer.setVolume(0);
        }
        GameSetting::getInstance().saveSettingState();
    });

    soundToggle->setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {
        ToggleButtonView* button = dynamic_cast<ToggleButtonView*>(listener);
        if (button->getState()) {
            soundPlayer.setMute(false);
            // soundPlayer.setVolume(100);
        } else {
            soundPlayer.setMute(true);
            // soundPlayer.setVolume(0);
        }
        GameSetting::getInstance().saveSettingState();
    });
    
    musicToggle->attachView(std::move(soundToggle));
    menu->attachView(std::move(musicToggle));
    attachView(std::move(menu));
}