#include <SettingsActivity.hpp>
#include <AppConfig.hpp>
#include <TextView.hpp>
#include <ButtonView.hpp>

#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>

void SettingsActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
}

void SettingsActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
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
        BackgroundFactory::create(mTextureManager.get(TextureID::mainMenuBackgroundTexture))
    );
}

void SettingsActivity::createTitle() {
    attachView(
        TitlebarFactory::create(
            this,
            mTextureManager,
            mFontManager.get(FontID::defaultFont),
            "Settings",
            TitlebarFactory::TitlebarType::SETTINGS,
            REQUEST_TITLEBAR_BUTTONS
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
