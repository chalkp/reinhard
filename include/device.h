#pragma once

#include "window.h"
#include <stdbool.h>
#include <vulkan/vulkan.h>

typedef struct Device {
  Window *window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice;
  VkCommandPool commandPool;

  VkDevice device_;
  VkSurfaceKHR surface_;
  VkQueue graphicsQueue_;
  VkQueue presentQueue_;

  bool enableValidationLayers;
  VkPhysicalDeviceProperties properties;
} Device;

// TODO: implement everything under this
