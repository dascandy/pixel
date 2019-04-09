#include <pixel.hpp>
#include <thread>
#include <chrono>
using namespace std::literals::chrono_literals;
using namespace Pixel;

static const int npoint = 50;

int main() {
    Window mainWindow(1920, 1080, "Hello world!");
    Canvas canvas("myimage.png");

    while (!mainWindow.shouldExit()) {
        for(int j=0; j < npoint; ++j)
        {
            int x1 = rand() % (canvas.width() - 1);
            int y1 = rand() % canvas.height();
            Color a = canvas.get(x1, y1);
            Color b = canvas.get(x1+1, y1);
            canvas.plot(x1, y1, b);
            canvas.plot(x1+1, y1, a);
        }
        mainWindow.show(canvas);
    }
}

