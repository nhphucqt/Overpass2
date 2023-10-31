#include <Application.hpp>
#include <DemoActivity.hpp>

int main() {
    Application app(800, 600, "Application");
    app.addLauncher<DemoActivity>();
    app.run();
    return 0;
}