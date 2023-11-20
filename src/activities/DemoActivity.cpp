#include <iostream>
#include <string>

#include <AppConfig.hpp>
#include <DemoActivity.hpp>
#include <ActivityFactory.hpp>
#include <RectangleView.hpp>
#include <TextView.hpp>
#include <ButtonView.hpp>
#include <SpriteButtonView.hpp>

void DemoActivity::onLoadResources() {
    mFonts.load(FontID::defaultFont, "res/fonts/Consolas-Bold.ttf");
    mTextures.load(TextureID::demoButtonTexture, "res/textures/button.png");
    mPlayer.play(MusicID::testMusic);
}

void DemoActivity::onCreate() {
    Intent *intent = getIntent();
    if (intent != nullptr) {
        id = intent->getExtra<int>("id", 0);
    }
    else {
        id = 0;
    }
    std::cout << "DemoActivity #" << id << " constructor" << std::endl;
    sf::Vector2f size = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::WindowSize);
    RectangleView::Ptr rect = std::make_unique<RectangleView>(rand() % int(size.x - 100), rand() % int(size.y - 100), 100, 100);
    rect->setOnMouseButtonPressed(this, [&](EventListener* listener, const sf::Event& event) {
        std::cout << " >> Exit" << std::endl;
        Intent::Ptr result = Intent::Builder()
            .putExtra("data", "Hello from Activity #" + std::to_string(id))
            .build();
        setResult(RESULT_OK, std::move(result));
        finish();
    });
    mRect = rect.get();
    attachView(std::move(rect));

    RectangleView::Ptr rect2 = std::make_unique<RectangleView>(rand() % int(size.x - 200), rand() % int(size.y - 200), 200, 200);
    rect2->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    rect2->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        RectangleView* rect = dynamic_cast<RectangleView*>(listener);
        rect->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    });
    attachView(std::move(rect2));

    TextView::Ptr text = std::make_unique<TextView>(
        "This the #" + std::to_string(id) + " Activity! Click to change color!", 
        mFonts.get(FontID::defaultFont), 
        sf::Vector2f(500, 500), 
        20,
        sf::Color::Red
    );
    text->setOnMouseButtonPressed(this, [&](EventListener* listener, const sf::Event& event) {
        TextView* text = dynamic_cast<TextView*>(listener);
        text->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    });
    attachView(std::move(text));

    sf::Texture& texture = mTextures.get(TextureID::demoButtonTexture);
    sf::IntRect textureRects[] = {
        sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y / 3.f),
        sf::IntRect(0, texture.getSize().y / 3.f, texture.getSize().x, texture.getSize().y / 3.f),
        sf::IntRect(0, texture.getSize().y * 2.f / 3.f, texture.getSize().x, texture.getSize().y / 3.f)
    };
    std::string texts[] = {
        std::string("Normal"),
        std::string("Hover"),
        std::string("Pressed")
    };
    SpriteButtonView::Ptr button = std::make_unique<SpriteButtonView>(
        this,
        texture,
        mFonts.get(FontID::defaultFont),
        textureRects,
        texts,
        20,
        sf::Vector2f(500, 600)
    );
    button->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        if (event.mouseButton.button != sf::Mouse::Left) return;
        sPlayer.play(SoundBufferID::buttonfx);
        std::cerr << " >> Button clicked!" << std::endl;
    });
    attachView(std::move(button));
}

void DemoActivity::onEvent(const sf::Event& event) {
    // std::cout << "DemoActivity #" << id << " onEvent" << std::endl;
    if (event.type == sf::Event::KeyPressed)
    {
        sPlayer.play(SoundBufferID::testSound);
        std::cout << " >> Key pressed: " << event.key.code << std::endl;
        if (event.key.code == sf::Keyboard::G)
        {
            std::cout << " >> Exit" << std::endl;
            Intent::Ptr result = Intent::Builder()
                                     .putExtra("data", "Hello from Activity #" + std::to_string(id))
                                     .build();
            setResult(RESULT_OK, std::move(result));
            finish();
        }
        else if (event.key.code == sf::Keyboard::N)
        {
            std::cout << " >> Create new Activity" << std::endl;
            Intent::Ptr intent = Intent::Builder()
                                     .setRequestCode(123)
                                     .putExtra("id", id + 1)
                                     .build();
            startActivity(ActivityFactory<DemoActivity>::createInstance(), std::move(intent));
        }
    }
}

void DemoActivity::updateCurrent(sf::Time dt)
{
    static int x = 2;
    static int y = 2;
    // std::cout << "DemoActivity #" << id << " onUpdate" << std::endl;
    sf::Vector2f bounds = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::WindowSize);
    if (mRect->getPosition().x + mRect->getSize().x >= bounds.x || mRect->getPosition().x <= 0) {
        x *= -1;
        mRect->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    }
    if (mRect->getPosition().y + mRect->getSize().y >= bounds.y || mRect->getPosition().y <= 0) {
        y *= -1;
        mRect->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    }
    mRect->move(x,y);
}

void DemoActivity::onAttach()
{
    std::cout << "DemoActivity #" << id << " onAttach" << std::endl;
}

void DemoActivity::onResume()
{
    mPlayer.setPaused(false);
    std::cout << "DemoActivity #" << id << " onResume" << std::endl;
}

void DemoActivity::onPause()
{
    mPlayer.setPaused(true);
    std::cout << "DemoActivity #" << id << " onPause" << std::endl;
}

void DemoActivity::onDestroy()
{
    mPlayer.stop();
    std::cout << "DemoActivity #" << id << " onDestroy" << std::endl;
}

void DemoActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data)
{
    std::cout << "DemoActivity #" << id << " onActivityResult" << std::endl;
    std::cout << " >> Request code: " << requestCode << std::endl;
    std::cout << " >> Result code: " << resultCode << std::endl;
    if (data != nullptr)
    {
        std::cout << " >> Data: " << data->getExtra<std::string>("data", "N/A") << std::endl;
    }
}