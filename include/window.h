#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace reinhard {

  class Window {
  public:
    Window(int w, int h, std::string name);
    ~Window();
    
    Window(const Window &) = delete;
    Window &operator = (const Window w) = delete;

    bool shouldClose();

  private:
    void initWindow();
    
    int width;
    int height;
    std::string windowName;
    GLFWwindow *window;
  };
}
