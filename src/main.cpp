#include <Application.hpp>
#include <ActivityFactory.hpp>
#include <DemoActivity.hpp>

int main() {
    Application app(800, 600, "Application");
    app.addLauncher(ActivityFactory<DemoActivity>::createInstance());
    app.run();
    return 0;
}