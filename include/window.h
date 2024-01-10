#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct Window {
  int width;
  int height;
  const char *windowName;
  GLFWwindow *window;
} Window;

Window *createWindow(int w, int h, const char *name);
void destroyWindow(Window *w);
bool shouldClose(Window *w);

void createWindowSurface(Window *w, VkInstance instance, VkSurfaceKHR *surface);
