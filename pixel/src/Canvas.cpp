#include <pixel/Canvas.hpp>
#include <GL/glew.h>
#include <pixel/Color.hpp>

namespace Pixel {
  Canvas::Canvas(uint32_t width, uint32_t height) 
  : width_(width)
  , height_(height)
  {
    canvas_.resize(width*height);
    glGenTextures(1, &texture_id);
  }
  void Canvas::clear(Color color) {
    uint32_t v = color.to_uint32_t();
    for (auto& pixel : canvas_) pixel = v;
  }
  void Canvas::plot(uint32_t x, uint32_t y, Color color) {
    canvas_[width_*y+x] = color.to_uint32_t();
  }
  Canvas::~Canvas() {
    glDeleteTextures(1, &texture_id);
  }
  int Canvas::update_texture() {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, canvas_.data());
    return texture_id;
  }
}


