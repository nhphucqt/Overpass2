#include <TextView.hpp>
#include <cassert>
// #include <iostream>

TextView::TextView(std::string text) {
    // std::cerr << "TextView constructor" << std::endl;
    this->text.setString(text);
    assert(this->font.loadFromFile("./res/fonts/Consolas-Bold.ttf"));
    this->text.setFont(font);
    this->text.setCharacterSize(20);
    this->text.setFillColor(sf::Color::Black);
}

void TextView::setText(std::string text) {
    this->text.setString(text);
}

std::string TextView::getText() {
    return text.getString();
}

void TextView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(text, states);
}  