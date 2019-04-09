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
    Canvas logo("cpponsea-logo.png");
    mainWindow.set_base_scale(20);
    logo.set_translucent();

    while (!mainWindow.shouldExit()) {
        mainWindow.clear(Color::Black);
        if (points.size() < 50) 
            points.push_back(Point{(rand() % 32) - 16.0f, (rand() % 20) - 10.0f, rand() % 3 + 3.0f});

        for(size_t j=0; j < points.size();)
        {
            if (points[j].z > 0 && 
                points[j].x / points[j].z > -20 && 
                points[j].x / points[j].z < 20 && 
                points[j].y / points[j].z > -16 && 
                points[j].y / points[j].z < 16) {
                mainWindow.draw(logo, points[j].x / points[j].z, points[j].y / points[j].z, 1.0f / points[j].z);
                points[j].z -= 0.002f;
                ++j;
            } else {
                points[j] = points.back();
                points.pop_back();
            }
        }
        mainWindow.show();
    }
}

