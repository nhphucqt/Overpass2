#include <TitlebarFactory.hpp>
#include <AppConfig.hpp>

#include <Activity.hpp>
#include <ActivityFactory.hpp>
#include <SettingsActivity.hpp>
#include <ProfileActivity.hpp>
#include <HelpActivity.hpp>

#include <SpriteButtonView.hpp>
#include <TextView.hpp>
#include <SpriteView.hpp>
#include <SpriteSheetView.hpp>

#include <SoundPlayer.hpp>

SpriteView::Ptr TitlebarFactory::create(Activity* context, TextureHolder& mTextureHolder, const sf::Font& font, const std::string& title, TitlebarType titleType, int requestCode) {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    sf::Texture& backgroundTexture = mTextureHolder.get(TextureID::titleBackgroundTexture);
    sf::Texture& characterTexture = mTextureHolder.get(TextureID::characterTitleBarTexture);
    sf::Texture& squareButtonsTexture = mTextureHolder.get(TextureID::squareButtonsTexture);
    sf::Texture& iconsTexture = mTextureHolder.get(TextureID::iconsTexture);

    float scale = 3.f;
    float buttonScale = 2.f;
    sf::Vector2f title_position(sf::Vector2f(13, 22) * scale);
    sf::Vector2f title_size(sf::Vector2f(99, 27) * scale);
    sf::Vector2f size(sf::Vector2f(backgroundTexture.getSize()) * scale);
    sf::Vector2f position(windowSize.x - size.x - 32 * buttonScale, 0);

    SpriteView::Ptr titleBar = std::make_unique<SpriteView>(context, backgroundTexture, position, size);

    sf::Color color = sf::Color::White;
    int fontSize = 64;

    TextView::Ptr titleView = std::make_unique<TextView>(context, title, font, sf::Vector2f(), fontSize, color);
    titleView->setPosition((title_size - titleView->getGlobalBounds().getSize()) / 2.f + title_position);

    sf::Vector2f character_position(sf::Vector2f(128, 15) * scale);
    sf::Vector2f character_size(sf::Vector2f(32, 32) * scale);
    sf::Time frameTime = sf::seconds(0.15f);
    int columns = 5;
    int rows = 1;
    SpriteSheetView::Ptr characterView = std::make_unique<SpriteSheetView>(context, characterTexture, columns, rows, frameTime, character_position, character_size);

    titleBar->attachView(std::move(titleView));
    titleBar->attachView(std::move(characterView));

    if (requestCode == -1) {
        return std::move(titleBar);
    }

    sf::IntRect buttonRects[3] = {
        sf::IntRect(8, 154, 32, 32),
        sf::IntRect(56, 104, 32, 32),
        sf::IntRect(56, 152, 32, 32),
    };

    sf::IntRect buttonRects2[3] = {
        sf::IntRect(56, 152, 32, 32),
        sf::IntRect(56, 152, 32, 32),
        sf::IntRect(56, 152, 32, 32),
    };

    sf::Vector2f buttonSize(sf::Vector2f(32, 32) * buttonScale);
    sf::Vector2f iconSize(sf::Vector2f(16, 16) * 2.f);
    sf::Vector2f iconPosition((buttonSize - iconSize) / 2.f);
    sf::Vector2f iconPositionNormal(iconPosition - sf::Vector2f(0, 2) * buttonScale);

    SpriteButtonView::Ptr settingButton = std::make_unique<SpriteButtonView>(
        context, 
        squareButtonsTexture,
        font,
        titleType == TitlebarType::SETTINGS ? buttonRects2 : buttonRects,
        "", 32, 
        sf::Vector2f(titleBar->get().getGlobalBounds().getSize().x, 0),
        buttonSize
    );
    SpriteView::Ptr settingIcon = std::make_unique<SpriteView>(
        context,
        iconsTexture,
        titleType == TitlebarType::SETTINGS ? iconPosition : iconPositionNormal,
        iconSize,
        sf::IntRect(16 * 3, 16 * 0, 16, 16)
    );
    SpriteView* settingIconPtr = settingIcon.get();

    SpriteButtonView::Ptr profButton = std::make_unique<SpriteButtonView>(
        context, 
        squareButtonsTexture,
        font,
        titleType == TitlebarType::PROFILE ? buttonRects2 : buttonRects,
        "", 32, 
        sf::Vector2f(0, 32) * buttonScale, 
        buttonSize
    );
    SpriteView::Ptr profIcon = std::make_unique<SpriteView>(
        context,
        iconsTexture,
        titleType == TitlebarType::PROFILE ? iconPosition : iconPositionNormal,
        iconSize,
        sf::IntRect(16 * 0, 16 * 0, 16, 16)
    );
    SpriteView* profIconPtr = profIcon.get();

    SpriteButtonView::Ptr helpButton = std::make_unique<SpriteButtonView>(
        context, 
        squareButtonsTexture,
        font,
        titleType == TitlebarType::HELP ? buttonRects2 : buttonRects,
        "", 32, 
        sf::Vector2f(0, 32) * buttonScale, 
        buttonSize
    );
    SpriteView::Ptr helpIcon = std::make_unique<SpriteView>(
        context,
        iconsTexture,
        titleType == TitlebarType::HELP ? iconPosition : iconPositionNormal,
        iconSize,
        sf::IntRect(16 * 4, 16 * 0, 16, 16)
    );
    SpriteView* helpIconPtr = helpIcon.get();

    if (titleType != TitlebarType::SETTINGS) {
        settingButton->setOnMouseMoved([settingIconPtr, iconPosition, iconPositionNormal](EventListener* listener, const sf::Event& event) {
            SpriteButtonView* button = dynamic_cast<SpriteButtonView*>(listener);
            if (button->isMouseHovering(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                settingIconPtr->setPosition(iconPosition);
            } else {
                settingIconPtr->setPosition(iconPositionNormal);
            }
        });
        settingButton->setOnMouseButtonReleased([context, titleType, requestCode](EventListener* listener, const sf::Event& event) {
            SoundPlayer::getInstance().play(SoundBufferID::buttonClick);
            if (titleType == TitlebarType::NONE) {
                Intent::Ptr intent = Intent::Builder()
                    .setRequestCode(requestCode)
                    .build();
                context->startActivity(ActivityFactory<SettingsActivity>::createInstance(), std::move(intent));
            } else {
                Intent::Ptr resIntent = Intent::Builder()
                    .putExtra("titleType", TitlebarType::SETTINGS)
                    .build();
                context->setResult(Activity::ResultCode::RESULT_OK, std::move(resIntent));
                context->finish();
            }
        });
    }

    if (titleType != TitlebarType::PROFILE) {
        profButton->setOnMouseMoved([profIconPtr, iconPosition, iconPositionNormal](EventListener* listener, const sf::Event& event) {
            SpriteButtonView* button = dynamic_cast<SpriteButtonView*>(listener);
            if (button->isMouseHovering(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                profIconPtr->setPosition(iconPosition);
            } else {
                profIconPtr->setPosition(iconPositionNormal);
            }
        });
        profButton->setOnMouseButtonReleased([context, titleType, requestCode](EventListener* listener, const sf::Event& event) {
            SoundPlayer::getInstance().play(SoundBufferID::buttonClick);
            if (titleType == TitlebarType::NONE) {
                Intent::Ptr intent = Intent::Builder()
                    .setRequestCode(requestCode)
                    .build();
                context->startActivity(ActivityFactory<ProfileActivity>::createInstance(), std::move(intent));
            } else {
                Intent::Ptr resIntent = Intent::Builder()
                    .putExtra("titleType", TitlebarType::PROFILE)
                    .build();
                context->setResult(Activity::ResultCode::RESULT_OK, std::move(resIntent));
                context->finish();
            }
        });
    }
    
    if (titleType != TitlebarType::HELP) {
        helpButton->setOnMouseMoved([helpIconPtr, iconPosition, iconPositionNormal](EventListener* listener, const sf::Event& event) {
            SpriteButtonView* button = dynamic_cast<SpriteButtonView*>(listener);
            if (button->isMouseHovering(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                helpIconPtr->setPosition(iconPosition);
            } else {
                helpIconPtr->setPosition(iconPositionNormal);
            }
        });
        helpButton->setOnMouseButtonReleased([context, titleType, requestCode](EventListener* listener, const sf::Event& event) {
            SoundPlayer::getInstance().play(SoundBufferID::buttonClick);
            if (titleType == TitlebarType::NONE) {
                Intent::Ptr intent = Intent::Builder()
                    .setRequestCode(requestCode)
                    .build();
                context->startActivity(ActivityFactory<HelpActivity>::createInstance(), std::move(intent));
            } else {
                Intent::Ptr resIntent = Intent::Builder()
                    .putExtra("titleType", TitlebarType::HELP)
                    .build();
                context->setResult(Activity::ResultCode::RESULT_OK, std::move(resIntent));
                context->finish();
            }
        });
    }

    settingButton->attachView(std::move(settingIcon));
    profButton->attachView(std::move(profIcon));
    helpButton->attachView(std::move(helpIcon));

    profButton->attachView(std::move(helpButton));
    settingButton->attachView(std::move(profButton));
    titleBar->attachView(std::move(settingButton));

    return std::move(titleBar);
}