#include "pixel.hh"
#include <thread>
#include <chrono>
using namespace std::literals::chrono_literals;
using namespace Pixel;

struct Point {
    int x, y;
};
static const int npoint = 42;
static const int nstep = 50;
Point point[npoint];

void update_point_positions() {
    for (int j = 0; j < npoint; ++j) {
        point[j].x = rand() % 80;
        point[j].y = rand() % 50;
    }
}

int main() {
    Window mainWindow(640, 480, "Hello world!");
    Canvas canvas(80, 50);

    for(int i=0; i<nstep; ++i) {
        while (!mainWindow.shouldExit()) {
            canvas.clear(Color::Blue);
            update_point_positions();
            for(int j=0; j < npoint; ++j)
            {
                  canvas.plot(point[j].x, point[j].y, Color::Black);
            }
            mainWindow.show(canvas);
            std::this_thread::sleep_for(400ms);
        }
    }
}

