#include <GameActivity.hpp>
#include <AppConfig.hpp>

#include <TextView.hpp>
#include <ButtonView.hpp>

#include <ActivityFactory.hpp>
#include <DemoActivity.hpp>

void GameActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/Consolas-Bold.ttf");
}

void GameActivity::onCreate() {
    Intent* intent = getIntent();
    int action = intent->getAction();
    int level = intent->getExtra<int>("level", -2);
    std::cout << "action: " << action << std::endl;
    std::cout << "level: " << level << std::endl;
    createTitle();
    createBackButton();
    createGame((GameLevel)level);
}

void GameActivity::onAttach() {
    // ...
}

void GameActivity::onResume() {
    // ...
}

void GameActivity::onPause() {
    // ...
}

void GameActivity::onDestroy() {
    // ...
}

void GameActivity::onEvent(const sf::Event& event) {
    // ...
}

void GameActivity::updateCurrent(sf::Time dt) {
    // ...
}

void GameActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    // ...
}

void GameActivity::createTitle() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    Intent* intent = getIntent();
    int action = intent->getAction();
    int level = intent->getExtra<int>("level", -2);

    sf::Color color = sf::Color::Black;
    int fontSize = 50;

    TextView::Ptr title = std::make_unique<TextView>("Game", mFontManager.get(FontID::defaultFont), sf::Vector2f(), fontSize, color);
    if (action == ACTION_NEW_GAME) {
        switch (level) {
            case 0:
                title->setText("Game - Easy");
                break;
            case 1:
                title->setText("Game - Medium");
                break;
            case 2:
                title->setText("Game - Hard");
                break;
            case 3:
                title->setText("Game - Endless");
                break;
            default:
                title->setText("Game - Unknown");
                break;
        }
    } else {
        title->setText("Game - Continue");
    }
    sf::Vector2f position((windowSize.x-title->getGlobalBounds().getSize().x)/2, 50);
    title->setPosition(position);

    attachView(std::move(title));
}

void GameActivity::createBackButton() {
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

void GameActivity::createGame(GameLevel level) {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    float width = 300;
    float height = 100;
    sf::Vector2f size(width, height);
    sf::Vector2f position((windowSize - size) / 2.f);
    sf::Color color = sf::Color(150, 150, 150, 255);
    int fontSize = 50;

    ButtonView::Ptr playButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Play UwU", fontSize, position, size, color);
    playButton->setTextColor(sf::Color::Black);
    playButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        startActivity(ActivityFactory<DemoActivity>::createInstance(), Intent::Builder().build());       
    });
    attachView(std::move(playButton));
}