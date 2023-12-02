#include <MainMenuActivity.hpp>

#include <AppConfig.hpp>

#include <ButtonView.hpp>
#include <TextView.hpp>

#include <ActivityFactory.hpp>
#include <LevelsActivity.hpp>
#include <SettingsActivity.hpp>
#include <RankingActivity.hpp>
#include <DemoActivity.hpp>

void MainMenuActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/Consolas-Bold.ttf");
}

void MainMenuActivity::onCreate() {
    createTitle();
    createPlayButtons();
}

void MainMenuActivity::onAttach() {
    // ...
}

void MainMenuActivity::onResume() {
    // ...
}

void MainMenuActivity::onPause() {
    // ...
}

void MainMenuActivity::onDestroy() {
    // ...
}

void MainMenuActivity::onEvent(const sf::Event& event) {
    // ...
}

void MainMenuActivity::updateCurrent(sf::Time dt) {
    // ...
}

void MainMenuActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    if (requestCode == REQUEST_CODE_GAME_LEVEL) {
        if (resultCode == (int)ResultCode::RESULT_OK) {
            startActivity(ActivityFactory<GameActivity>::createInstance(), std::move(data));
        }
    }
}

void MainMenuActivity::createTitle() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    sf::Color color = sf::Color::Black;
    int fontSize = 50;

    TextView::Ptr title = std::make_unique<TextView>("Main Menu", mFontManager.get(FontID::defaultFont), sf::Vector2f(), fontSize, color);
    sf::Vector2f position((windowSize.x-title->getGlobalBounds().getSize().x)/2, 50);
    title->setPosition(position);

    attachView(std::move(title));
}

void MainMenuActivity::createPlayButtons() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    float width = 250;
    float height = 75;
    sf::Vector2f size(width, height);
    sf::Vector2f position((windowSize.x-width)/2, 300);
    sf::Color color = sf::Color::Cyan;
    sf::Vector2f spacing(0, height + 20);
    int fontSize = 50;

    ButtonView::Ptr playButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "New game", fontSize, position, size, color);
    playButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        Intent::Ptr intent = Intent::Builder()
            .setRequestCode(REQUEST_CODE_GAME_LEVEL)
            .build();
        startActivity(ActivityFactory<LevelsActivity>::createInstance(), std::move(intent));
    });

    ButtonView::Ptr continueButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Continue", fontSize, spacing, size, color);
    continueButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        Intent::Ptr intent = Intent::Builder()
            .setRequestCode(REQUEST_CODE_CONTINUE_GAME)
            .setAction(GameActivity::ACTION_CONTINUE_GAME)
            .build();
        startActivity(ActivityFactory<GameActivity>::createInstance(), std::move(intent));
    });

    ButtonView::Ptr rankingsButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Rankings", fontSize, spacing, size, color);
    rankingsButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        startActivity(ActivityFactory<RankingActivity>::createInstance(), Intent::Builder().build());
    });

    ButtonView::Ptr settingsButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Settings", fontSize, spacing, size, color);
    settingsButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        startActivity(ActivityFactory<SettingsActivity>::createInstance(), Intent::Builder().build());
    });

    ButtonView::Ptr exitButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Exit", fontSize, spacing, size, color);
    exitButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        std::cerr << " >> Exit" << std::endl;
        finish();
    });

    settingsButton->attachView(std::move(exitButton));
    rankingsButton->attachView(std::move(settingsButton));
    continueButton->attachView(std::move(rankingsButton));
    playButton->attachView(std::move(continueButton));
    attachView(std::move(playButton));
}