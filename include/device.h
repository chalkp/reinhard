#pragma once

#include "window.h"
#include <stdbool.h>
#include <vulkan/vulkan.h>

typedef struct device {
  Window *window;

  VkInstance instance;
  VkDebugUtilsMessengerEXT debug_messenger;
  VkPhysicalDevice physical_device;
  VkCommandPool command_pool;

  VkDevice device;
  VkSurfaceKHR surface;
  VkQueue graphics_queue;
  VkQueue present_queue;

  bool enable_validation_layers;
  VkPhysicalDeviceProperties properties;
} Device;

Device *create_device(Window *window);
void destroy_device(Device *device);  // more consistent parameter naming
