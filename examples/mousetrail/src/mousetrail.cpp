#include <pixel.hpp>
#include <deque>
using namespace Pixel;

struct Point {
    int x, y;
};
std::deque<Point> points;

int main() {
    Window mainWindow(640, 480, "Hello world!");
    Canvas canvas(80, 60);

    while (!mainWindow.shouldExit()) {
        canvas.clear(Color::Blue);
        points.push_back(Point{mainWindow.mouseX()/8, mainWindow.mouseY()/8});
        if (points.size() > 99) points.pop_front();
        Color color(0, 0, 0);
        for (auto& p : points) {
            canvas.plot(p.x, p.y, color);
            color.b += 0.01;
            color.g += 0.01;
        }
        mainWindow.show(canvas);
    }
}

