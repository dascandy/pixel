#pragma once

#include <cstdint>
#include <vector>
#include "Color.hpp"

namespace Pixel {
  class Canvas {
  public:
    Canvas(uint32_t width, uint32_t height);
    ~Canvas();
    void set_transparency(Color color);
    void set_translucent();
    void clear(Color color);
    void plot(uint32_t x, uint32_t y, Color color);
    int update_texture();
    uint32_t width() { return width_; }
    uint32_t height() { return height_; }
  private:
    uint32_t width_, height_;
    std::vector<uint32_t> canvas_;
    unsigned int texture_id;
    Color transparency_key;
    enum {
      solid,
      keyed,
      translucent
    } opacity = solid;
    friend class Window;
  };

  class Subcanvas {
  public:
    Subcanvas(Canvas& canvas) : canvas_(&canvas), x(0), y(0), width(canvas.width()), height(canvas.height()) {}
    Subcanvas(Canvas& canvas, uint32_t x, uint32_t y, uint32_t width, uint32_t height) : canvas_(&canvas), x(x), y(y), width(width), height(height) {}
  private:
    Canvas* canvas_;
    uint32_t x, y;
    uint32_t width, height;
    friend class Window;
  };
}


