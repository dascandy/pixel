#include <pixel.hpp>
#include <thread>
#include <chrono>
using namespace std::literals::chrono_literals;
using namespace Pixel;

// Using tiles from https://opengameart.org/content/generic-platformer-tiles - CC0
// Using hero character from https://opengameart.org/content/classic-hero - CC0
// Both modified to make for a more compact spritesheet

class Hero {
public:
    Hero() {
        hero.set_translucent();
    }
    enum State {
        Still,
        Moving,
        Jumping
    };
    Subcanvas get(State state) {
        return Subcanvas(hero, state, 0, hero.width() / 4, hero.height());
    }
    Canvas hero = Canvas("hero.png");
} hero;

class Tiles {
public:
    Tiles() {
        tiles.set_translucent();
    }
    Subcanvas getTile(int id) {
        return Subcanvas(tiles, id % 8, id / 8, tiles.width() / 8, tiles.height() / 16);
    }
    Canvas tiles = Canvas("tiles.png");
} tiles;

std::array<std::string, 10> world = {
"                                                                                                                                                                                                        ",
"                                                                                                                                                                                                        ",
"                                                                                                                                                                                                        ",
"                                                                                                                                                                                                        ",
"                                                                                                                                                                                                        ",
"              vw                                                                                                                                                                                        ",
"              no                                                                                                                                                                                        ",
"[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[",
"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS",
"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS",
};

int main() {
    Window mainWindow(1920, 1080, "Jumpman 2.0");
    mainWindow.set_base_scale(10);
    
    std::vector<int> groundFillTiles = { 32, 32, 32, 32, 32, 32, 32, 64, 72, 80, 96, 104, 101, 96, 96, 96, 64, 64, 64, 72 };
    for (auto& e : world[6]) {
        e = groundFillTiles[rand() % groundFillTiles.size()];
    }
    float heroX = 2.0f, heroY = 3.0f;
    float heroDy = 0;
    float worldX = 2.0f;

    while (!mainWindow.shouldExit()) {
        mainWindow.clear(Color::Black);
        for (size_t row = 0; row < world.size(); row++) {
            for (size_t cell = 0; cell < world[row].size(); cell++) {
                mainWindow.draw(tiles.getTile(world[row][cell]), 2*cell - 2*worldX - 7.0f, 9.0 - 2*row);
                if (cell > 12) break;
            }
        }

        if (mainWindow.isPressed('w')) heroDy = 0.4;
        if (mainWindow.isPressed('d')) heroX += 0.125;
        if (mainWindow.isPressed('a')) heroX -= 0.125;
        heroDy -= 0.03;
        heroY += heroDy;

        if (heroY < 3.0f) {
            heroY = 3.0f; 
            heroDy = 0.0;
        }
        if (worldX < heroX - 4.0f) worldX = heroX - 4.0f;
        if (worldX > heroX) worldX = heroX;

        mainWindow.draw(hero.get(Hero::Still), 2*heroX - 2*worldX - 9.0f, 2*heroY - 9.0f);
        mainWindow.show();
    }
}


