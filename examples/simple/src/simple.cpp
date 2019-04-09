#include <pixel.hpp>
#include <thread>
#include <chrono>
using namespace std::literals::chrono_literals;

int main() {
    Pixel::Window mainWindow(1920, 1080, "Simple example!");
    Pixel::Canvas canvas(5, 3);

    canvas.plot(2, 1, Pixel::Color::Pink);

    mainWindow.show(canvas);
    std::this_thread::sleep_for(4000ms);
}

