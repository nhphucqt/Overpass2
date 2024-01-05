#include <InputFieldFactory.hpp>
#include <Activity.hpp>
#include <EditTextView.hpp>
#include <TextView.hpp>

EditTextView::Ptr InputFieldFactory::create(Activity* context, const sf::Font& font, const std::string& label, EditTextView::InputType inputType) {
    sf::Vector2f size = sf::Vector2f(284, 64);

    EditTextView::Ptr inputField = std::make_unique<EditTextView>(context, font, "", 42, sf::Vector2f(), size);
    inputField->setInputType(inputType);
    inputField->setFocusBackGroundColor(sf::Color(0, 0, 0, 60));
    inputField->setUnFocusBackGroundColor(sf::Color(0, 0, 0, 20));
    inputField->setTextColor(sf::Color::White);
    inputField->setLimit(10);

    TextView::Ptr labelView = std::make_unique<TextView>(context, label, font, sf::Vector2f(0, 0), 42, sf::Color::Black);
    labelView->setFillColor(sf::Color::White);
    labelView->setPosition((size - labelView->getGlobalBounds().getSize()) / 2.f - sf::Vector2f(size.x + labelView->getGlobalBounds().getSize().x, 0) / 2.f);
    labelView->move(-20, 0);

    inputField->attachView(std::move(labelView));
    return std::move(inputField);
}
