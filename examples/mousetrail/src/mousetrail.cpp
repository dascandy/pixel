#include <pixel.hpp>
#include <deque>
using namespace Pixel;

struct Point {
    int x, y;
};
std::deque<Point> points;

int main() {
    Window mainWindow(1920, 1080, "Hello world!");
    Canvas canvas(240, 135);

    while (!mainWindow.shouldExit()) {
        canvas.clear(Color::Blue);
        points.push_back(Point{mainWindow.mouseX()/8, mainWindow.mouseY()/8});
        if (points.size() > 999) points.pop_front();
        Color color(0, 0, 0);
        for (auto& p : points) {
            canvas.plot(p.x, p.y, color);
            color.b += 0.001;
            color.g += 0.001;
        }
        mainWindow.show(canvas);
    }
}

