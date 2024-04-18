#include "window.h"
#include <stdio.h> 
#include <stdlib.h>
#include "utils.h"

Window *create_window(int width, int height, const char *title) {
  if(!glfwInit()) {
    fprintf(stderr, "glfwInit: Error Initialize GLFW\n");
    return NULL;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No Open-GL API context
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Not yet.
  
  Window *window;
  pointer_memory_allocate(window, Window, 1, "Window");

  window->width = width;
  window->height = height;
  window->title = title;
  window->glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);
  
  if(window->glfw_window == NULL) {
    fprintf(stderr, "glfwCreateWindow: returned NULL\n");
    free(window);
    return NULL;
  }

  return window;
}

void destroy_window(Window *window) {
  if(window != NULL) {
    glfwDestroyWindow(window->glfw_window);
    free(window);
  }
  glfwTerminate();
}

void create_window_surface(Window *window,
  VkInstance instance,
  VkSurfaceKHR *surface
) {
  VkResult result = glfwCreateWindowSurface(instance, window->glfw_window, NULL, surface);
  if(result != VK_SUCCESS) {
    fprintf(stderr, "glfwCreateWindowSurface: failed to create window surface\n");
    exit(1);
  }
}
