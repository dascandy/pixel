#include <pixel.hpp>
#include <thread>
#include <chrono>
using namespace std::literals::chrono_literals;
using namespace Pixel;


struct Point {
  float x, y, z;
};

std::vector<Point> points;

int main() {
    Window mainWindow(1920, 1080, "Hello world!");
    Canvas canvas(320, 200);

    while (!mainWindow.shouldExit()) {
        points.push_back(Point{(rand() % 3200) - 1600.0f, (rand() % 2000) - 1000.0f, rand() % 20 + 1.0f});
        canvas.clear(Color::Black);
        for(size_t j=0; j < points.size();)
        {
            if (points[j].z > 0 && 
                points[j].x / points[j].z > -160 && 
                points[j].x / points[j].z < 160 && 
                points[j].y / points[j].z > -100 && 
                points[j].y / points[j].z < 100) {
                canvas.plot(points[j].x / points[j].z + 160, points[j].y / points[j].z + 100, Color::White);
                points[j].z -= 0.02f;
                ++j;
            } else {
                points[j] = points.back();
                points.pop_back();
            }
        }
        mainWindow.show(canvas);
    }
}

