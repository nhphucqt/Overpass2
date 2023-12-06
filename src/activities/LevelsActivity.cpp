#include <LevelsActivity.hpp>
#include <AppConfig.hpp>

#include <TextView.hpp>
#include <ButtonView.hpp>
#include <ActivityFactory.hpp>
#include <DemoActivity.hpp>
#include <GameActivity.hpp>


void LevelsActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/Consolas-Bold.ttf");
}

void LevelsActivity::onCreate() {
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
    // ...
}

void LevelsActivity::createTitle() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    sf::Color color = sf::Color::Black;
    int fontSize = 50;

    TextView::Ptr title = std::make_unique<TextView>("Levels", mFontManager.get(FontID::defaultFont), sf::Vector2f(), fontSize, color);
    sf::Vector2f position((windowSize.x-title->getGlobalBounds().getSize().x)/2, 50);
    title->setPosition(position);

    attachView(std::move(title));
}

void LevelsActivity::createBackButton() {
    float width = 50;
    float height = 50;
    sf::Vector2f size(width, height);
    sf::Vector2f position(20, 20);
    sf::Color color = sf::Color(150, 150, 150, 255);
    int fontSize = 50;

    ButtonView::Ptr backButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "<", fontSize, position, size, color);
    backButton->setTextColor(sf::Color::Black);
    backButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        finish();
    });
    attachView(std::move(backButton));
}

void LevelsActivity::createLevelButtons() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    float width = 250;
    float height = 75;
    sf::Vector2f size(width, height);
    sf::Vector2f position((windowSize.x-width)/2, 300);
    sf::Color color = sf::Color::Cyan;
    sf::Vector2f spacing(0, height + 20);
    int fontSize = 50;

    ButtonView::Ptr easyButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Easy", fontSize, position, size, color);
    easyButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        enterGame(GameActivity::GameLevel::Easy);
    });

    ButtonView::Ptr mediumButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Medium", fontSize, spacing, size, color);
    mediumButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        enterGame(GameActivity::GameLevel::Medium);
    });

    ButtonView::Ptr hardButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Hard", fontSize, spacing, size, color);
    hardButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        enterGame(GameActivity::GameLevel::Hard);
    });

    ButtonView::Ptr endlessButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Endless", fontSize, spacing, size, color);
    endlessButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        enterGame(GameActivity::GameLevel::Endless);
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