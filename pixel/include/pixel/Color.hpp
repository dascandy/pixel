#pragma once

#include <cstdint>
#include <cstdio>

namespace Pixel {
  class Color {
  private:
    float r, g, b, a;
  public:
    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
    uint32_t to_uint32_t() {
      uint8_t rb = r * 255, gb = g * 255, bb = b * 255, ab = a * 255;
      return ((uint32_t)ab << 24) | (bb << 16) | (gb << 8) | (rb);
    };
    static const Color Blue;
    static const Color Black;
  };
  inline const Color Color::Blue{ 0, 0, 1.0f, 0 };
  inline const Color Color::Black{ 0, 0, 0, 0 };
  
}


