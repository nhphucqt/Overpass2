#include <iostream>
#include <string>

#include <DemoActivity.hpp>
#include <RectangleView.hpp>
#include <TextView.hpp>

DemoActivity::DemoActivity(int id): id(id) {
    std::cout << "DemoActivity #" << id << " constructor" << std::endl;
    std::unique_ptr<RectangleView> rect = std::make_unique<RectangleView>();
    attachView(std::move(rect));
    std::unique_ptr<TextView> text = std::make_unique<TextView>("This the #" + std::to_string(id) + " Activity!");
    text->setPosition(50, 50);
    attachView(std::move(text));
}

void DemoActivity::onEvent(sf::Event& event) {
    // std::cout << "DemoActivity #" << id << " onEvent" << std::endl; 
    if (event.type == sf::Event::KeyPressed) {
        std::cout << " >> Key pressed: " << event.key.code << std::endl;
        switch (event.key.code) {
            case sf::Keyboard::G:
                std::cout << " >> Exit" << std::endl;
                finish();
                break;
            case sf::Keyboard::N:
                std::cout << " >> Create new Activity" << std::endl;
                getActivityManager()->attachActivity(std::make_unique<DemoActivity>(id+1));
                break;
        }
    }
}

void DemoActivity::onUpdate() {
    // std::cout << "DemoActivity #" << id << " onUpdate" << std::endl;
}

void DemoActivity::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    // std::cout << "DemoActivity #" << id << " onDraw" << std::endl;
}

void DemoActivity::onAttach() {
    std::cout << "DemoActivity #" << id << " onAttach" << std::endl;
}

void DemoActivity::onResume() {
    std::cout << "DemoActivity #" << id << " onResume" << std::endl;
}

void DemoActivity::onPause() {
    std::cout << "DemoActivity #" << id << " onPause" << std::endl;
}

void DemoActivity::onDestroy() {
    std::cout << "DemoActivity #" << id << " onDestroy" << std::endl;
}


