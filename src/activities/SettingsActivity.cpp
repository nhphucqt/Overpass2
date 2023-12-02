#include <SettingsActivity.hpp>
#include <AppConfig.hpp>
#include <TextView.hpp>
#include <ButtonView.hpp>

void SettingsActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/Consolas-Bold.ttf");
}

void SettingsActivity::onCreate() {
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

void SettingsActivity::createTitle() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    sf::Color color = sf::Color::Black;
    int fontSize = 50;

    TextView::Ptr title = std::make_unique<TextView>("Settings", mFontManager.get(FontID::defaultFont), sf::Vector2f(), fontSize, color);
    sf::Vector2f position((windowSize.x-title->getGlobalBounds().getSize().x)/2, 50);
    title->setPosition(position);

    attachView(std::move(title));
}

void SettingsActivity::createBackButton() {
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
