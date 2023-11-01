#include <Application.hpp>
#include <DemoActivity.hpp>

int main()
{
    std::unique_ptr<Activity> launcher = std::make_unique<DemoActivity>(0);
    Application app(800, 600, "Application", std::move(launcher));
    app.run();
    return 0;
}