#include <pixel/Canvas.hpp>
#include <GL/glew.h>
#include <pixel/Color.hpp>
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Pixel {
  Canvas::Canvas(std::string filename) 
  {
    int x,y,n;
    unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 4);
    if (!data) throw std::runtime_error("Cannot load image; invalid image");
    n = 4;
    width_ = x;
    height_ = y;
    canvas_.resize(width_*height_);
    for (size_t i = 0; i < width_*height_; i++) {
      canvas_[(i%width_) + (height_ - i / width_ - 1) * width_] = Color(data[i*n] / 255.0f, data[i*n+1] / 255.0f, data[i*n+2] / 255.0f, data[i*n+3] / 255.0f).to_uint32_t();
    }
    stbi_image_free(data);
    glGenTextures(1, &texture_id);
  }
  Canvas::Canvas(uint32_t width, uint32_t height) 
  : width_(width)
  , height_(height)
  {
    canvas_.resize(width*height);
    glGenTextures(1, &texture_id);
  }
  void Canvas::set_transparency(Color color) {
    opacity = keyed;
    transparency_key = color;
  }
  void Canvas::set_translucent() {
    opacity = translucent;
  }
  void Canvas::clear(Color color) {
    uint32_t v = color.to_uint32_t();
    for (auto& pixel : canvas_) pixel = v;
  }
  Color Canvas::get(uint32_t x, uint32_t y) const {
    return Color(canvas_[width_*y+x]);
  }
  void Canvas::plot(uint32_t x, uint32_t y, Color color) {
    canvas_[width_*y+x] = color.to_uint32_t();
  }
  Canvas::~Canvas() {
    glDeleteTextures(1, &texture_id);
    if (fbo)
      glDeleteFramebuffers(1, &fbo);
  }
  void Canvas::set_as_target() {
    if (!fbo) 
      glGenFramebuffers(1, &fbo);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);
    glViewport(0, 0, width_, height_);
  }
  void Canvas::read() {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, canvas_.data());
  }
  int Canvas::update_texture() {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_BGRA, GL_UNSIGNED_BYTE, canvas_.data());
    return texture_id;
  }
}


