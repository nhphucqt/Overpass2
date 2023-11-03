#include <iostream>
#include <string>

#include <DemoActivity.hpp>
#include <ActivityFactory.hpp>
#include <RectangleView.hpp>
#include <TextView.hpp>

void DemoActivity::onCreate()
{
    Intent *intent = getIntent();
    if (intent != nullptr)
    {
        id = intent->getExtra<int>("id", 0);
    }
    else
    {
        id = 0;
    }
    std::cout << "DemoActivity #" << id << " constructor" << std::endl;
    std::unique_ptr<RectangleView> rect = std::make_unique<RectangleView>(100, 100);
    mRect = rect.get();
    attachView(std::move(rect));
    std::unique_ptr<TextView> text = std::make_unique<TextView>("This the #" + std::to_string(id) + " Activity!");
    text->setPosition(50, 50);
    attachView(std::move(text));
    mPlayer.play(MusicID::testMusic);
}

void DemoActivity::onEvent(sf::Event &event)
{
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
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
        if (pos.x >= mRect->getPosition().x && pos.x <= mRect->getPosition().x + mRect->getSize().x && pos.y >= mRect->getPosition().y && pos.y <= mRect->getPosition().y + mRect->getSize().y)
        {
            std::cout << " >> Exit" << std::endl;
            Intent::Ptr result = Intent::Builder()
                                     .putExtra("data", "Hello from Activity #" + std::to_string(id))
                                     .build();
            setResult(RESULT_OK, std::move(result));
            finish();
        }
    }
}

void DemoActivity::onUpdate()
{
    // std::cout << "DemoActivity #" << id << " onUpdate" << std::endl;
}

void DemoActivity::onDraw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // std::cout << "DemoActivity #" << id << " onDraw" << std::endl;
}

void DemoActivity::onAttach()
{
    std::cout << "DemoActivity #" << id << " onAttach" << std::endl;
}

void DemoActivity::onResume()
{
    std::cout << "DemoActivity #" << id << " onResume" << std::endl;
}

void DemoActivity::onPause()
{
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