#pragma once

#include <string>
#include <cstdint>
#include <atomic>

namespace Pixel {
  class Canvas;
  class Subcanvas;

  class Window {
  public:
    Window(uint32_t width, uint32_t height, std::string name);
    ~Window();
    void set_base_scale(float base) { baseScale = base; }
    bool shouldExit();
    void show(const Subcanvas& canvas);
    void draw(const Subcanvas& canvas, uint32_t x, uint32_t y, float scale = 1, float rotation = 0);
    void text(std::string_view str, uint32_t x, uint32_t y, float scale = 1, float rotation = 0);
    void show();
  private:
    std::atomic<bool> shouldExit_ = false;
    int width, height;
    void* surface;
    void* context;
    int vs, fs, prog;
    unsigned int vao, vbo;
    float baseScale = 1.0;
  };
}
/*
- Drawing text (ascii monospace)
- some screen effects
*/

