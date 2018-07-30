#include <pixel.hpp>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std::literals::chrono_literals;
using namespace Pixel;

std::vector<Color> colors = {
  Color(0xFF0000),
  Color(0xFF4000),
//  Color(0xFF8000),
  Color(0xFFC000),
  Color(0xFFFF00),
  Color(0xC0FF00),
  Color(0x80FF00),
  Color(0x40FF00),
  Color(0x00FF00),
  Color(0x00FF40),
//  Color(0x00FF80),
  Color(0x00FFC0),
  Color(0x00FFFF),
  Color(0x00C0FF),
  Color(0x0080FF),
  Color(0x0040FF),
  Color(0x0000FF),
  Color(0x4000FF),
//  Color(0x8000FF),
  Color(0xC000FF),
  Color(0xFF00FF),
  Color(0xFF00C0),
  Color(0xFF0080),
  Color(0xFF0040),
};

void init(Canvas& target) {
    for (size_t y = 0; y < target.height(); y++) {
        for (size_t x = 0; x < target.width(); x++) {
            target.plot(x, y, colors[rand() % colors.size()]);
        }
    }
}

void step(Canvas& target, const Canvas& source) {
    for (size_t y = 0; y < target.height(); y++) {
        for (size_t x = 0; x < target.width(); x++) {
            auto current = std::find(colors.begin(), colors.end(), source.get(x, y));
            auto next = current;
            ++next;
            if (next == colors.end()) next = colors.begin();
            bool found = false;
            if (source.get((x + target.width() - 1) % target.width(), y) == *next) found = true;
            if (source.get((x + target.width() + 1) % target.width(), y) == *next) found = true;
            if (source.get(x, (y + target.height() - 1) % target.height()) == *next) found = true;
            if (source.get(x, (y + target.height() + 1) % target.height()) == *next) found = true;
            target.plot(x, y, found ? *next : *current);
        }
    }
}

int main() {
    Window mainWindow(640, 480, "Color cycles");
    Canvas A(320, 240), B(320, 240);
    init(A);

    srand(38);
    while (!mainWindow.shouldExit()) {
        step(B, A);
        mainWindow.show(B);
        std::this_thread::sleep_for(40ms);

        step(A, B);
        mainWindow.show(A);
        std::this_thread::sleep_for(40ms);
    }
}

