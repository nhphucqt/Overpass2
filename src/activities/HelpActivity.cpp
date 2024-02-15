#include <HelpActivity.hpp>

#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>

void HelpActivity::onLoadResources() {
    mFontHolder.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureHolder.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureHolder.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureHolder.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureHolder.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureHolder.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
}

void HelpActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
}

void HelpActivity::onAttach() {
    // ...
}

void HelpActivity::onResume() {
    // ...
}

void HelpActivity::onPause() {
    // ...
}

void HelpActivity::onDestroy() {
    // ...
}

void HelpActivity::onEvent(const sf::Event& event) {
    // ...
}

void HelpActivity::updateCurrent(sf::Time dt) {
    // ...
}

void HelpActivity::createBackButton() {
    attachView(
        BackButtonFactory::create(
            this,
            mTextureHolder.get(TextureID::squareButtonsTexture),
            mFontHolder.get(FontID::defaultFont)
        )
    );
}

void HelpActivity::createBackground() {
    attachView(
        BackgroundFactory::create(this, mTextureHolder.get(TextureID::mainMenuBackgroundTexture))
    );
}

void HelpActivity::createTitle() {
    attachView(
        TitlebarFactory::create(
            this,
            mTextureHolder,
            mFontHolder.get(FontID::defaultFont),
            "Help",
            TitlebarFactory::TitlebarType::HELP,
            REQUEST_TITLEBAR_BUTTONS
        )
    );
}