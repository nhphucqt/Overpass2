#include <SettingToggleFactory.hpp>
#include <ToggleButtonView.hpp>
#include <TextView.hpp>

ToggleButtonView::Ptr SettingToggleFactory::create(Activity* context, sf::Texture& texture, sf::Font& font, const std::string& label, bool isOn) {
    sf::IntRect textureRects[(int)ToggleButtonView::ButtonType::COUNT];

    float scale = 4.0f;
    sf::Vector2f size(32, 18);
    size *= scale;

    textureRects[(int)ToggleButtonView::ButtonType::OFF] = sf::IntRect(0, 151, 32, 18);
    textureRects[(int)ToggleButtonView::ButtonType::ON] = sf::IntRect(63, 151, 32, 18);

    ToggleButtonView::Ptr toggleButtonView = std::make_unique<ToggleButtonView>(context, texture, font, textureRects, "", 16, sf::Vector2f(0, 0), size);
    toggleButtonView->setState(isOn);

    TextView::Ptr labelView = std::make_unique<TextView>(context, label, font, sf::Vector2f(), 30, sf::Color::White);
    labelView->setPosition((size - labelView->getGlobalBounds().getSize()) / 2.f - sf::Vector2f(size.x + labelView->getGlobalBounds().getSize().x, 0) / 2.f);
    labelView->move(-10, 0);

    toggleButtonView->attachView(std::move(labelView));
    return std::move(toggleButtonView);
}