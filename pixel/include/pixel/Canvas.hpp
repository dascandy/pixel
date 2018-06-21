#pragma once

#include <cstdint>
#include <vector>

namespace Pixel {
  class Color;

  class Canvas {
  public:
    Canvas(uint32_t width, uint32_t height);
    ~Canvas();
    void clear(Color color);
    void plot(uint32_t x, uint32_t y, Color color);
    int update_texture();
  private:
    uint32_t width_, height_;
    std::vector<uint32_t> canvas_;
    unsigned int texture_id;
  };
}

