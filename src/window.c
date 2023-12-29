#include "window.h"
#include <stdlib.h>

Window *createWindow(int w, int h, const char *name) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  Window *ret = (Window *)malloc(sizeof(Window));
  ret->width = w;
  ret->height = h;
  ret->windowName = name;
  ret->window = glfwCreateWindow(w, h, name, NULL, NULL);
  return ret;
}

void destroyWindow(Window *w) {
  glfwDestroyWindow(w->window);
  glfwTerminate();
  free(w);
}

bool shouldClose(Window *w) {
  return glfwWindowShouldClose(w->window);
}
