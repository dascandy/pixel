#include <pixel.hpp>
#include <thread>
#include <chrono>
using namespace std::literals::chrono_literals;

using namespace Pixel;

void init(Canvas& target) {
    target.clear(Color::Black);
    // Initial state from Wikipedia at https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life, "indefinitely growing pattern with minimal live cells"
    target.plot(35, 27, Color::White);
    target.plot(37, 27, Color::White);
    target.plot(37, 26, Color::White);
    target.plot(39, 25, Color::White);
    target.plot(39, 24, Color::White);
    target.plot(39, 23, Color::White);
    target.plot(41, 24, Color::White);
    target.plot(41, 23, Color::White);
    target.plot(41, 22, Color::White);
    target.plot(42, 23, Color::White);
}

void conway(Canvas& target, const Canvas& source) {
    target.clear(Color::Black);
    for (size_t y = 0; y < target.height(); y++) {
        for (size_t x = 0; x < target.width(); x++) {
            int sum = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue; // Skip the cell itself
                    if (source.get((x + target.width() + dx) % target.width(), (y + target.height() + dy) % target.height()) == Color::White) sum++;
                }
            }
            if (source.get(x, y) == Color::White) {
                // Any live cell with fewer than two live neighbors dies, as if by under population.
                // Any live cell with two or three live neighbors lives on to the next generation.
                // Any live cell with more than three live neighbors dies, as if by overpopulation.
                if (sum == 3 || sum == 2) target.plot(x, y, Color::White);
            } else {
                // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
                if (sum == 3) target.plot(x, y, Color::White);
            }
        }
    }
}

int main() {
    Window mainWindow(640, 480, "Conway's Game of Life");
    Canvas A(80, 50), B(80, 50);
    init(A);

    while (!mainWindow.shouldExit()) {
        conway(B, A);
        mainWindow.show(B);
        std::this_thread::sleep_for(40ms);

        conway(A, B);
        mainWindow.show(A);
        std::this_thread::sleep_for(40ms);
    }
}

