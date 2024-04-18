#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <vulkan/vulkan.h>

typedef struct window {
  int width;
  int height;
  const char *title;
  GLFWwindow *glfw_window;
} Window;

Window *create_window(int width, int height, const char *title);
void destroy_window(Window *window);
bool should_close(Window *window);

void create_window_surface(Window *window,
  VkInstance instance,
  VkSurfaceKHR *surface
);
