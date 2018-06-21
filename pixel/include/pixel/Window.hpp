#pragma once

#include <string>
#include <cstdint>
#include <atomic>

namespace Pixel {
  class Canvas;

  class Window {
  public:
    Window(uint32_t width, uint32_t height, std::string name);
    ~Window();
    bool shouldExit();
    void show(Canvas& canvas);
  private:
    std::atomic<bool> shouldExit_ = false;
    int width, height;
    void* surface;
    void* context;
    int vs, fs, prog;
    unsigned int vao, vbo;
  };
}

