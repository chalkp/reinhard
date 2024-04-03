#pragma once

#include "window.h"
#include "utils.h"
#include <stdbool.h>
#include <vulkan/vulkan.h>

typedef struct queue_family_indices {
  uint32_t graphics_family;
  uint32_t present_family;
} QueueFamilyIndices;

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

  StringArray validation_layers;
  StringArray device_extensions;
} Device;

Device *create_device(Window *window);
void destroy_device(Device *device);


bool create_instance(Device *device);
bool setup_debug_messenger(Device *device);
bool pick_physical_device(Device *device);
bool create_logical_device(Device *device);
bool create_surface(Device *device);
bool create_command_pool(Device *device);

void application_info_setup(VkApplicationInfo *app_info);
void create_info_setup(Device *device,
  VkInstanceCreateInfo *create_info,
  VkDebugUtilsMessengerCreateInfoEXT *debug_create_info,
  VkApplicationInfo *app_info,
  StringArray *extensions
);
void debug_create_info_setup(VkDebugUtilsMessengerCreateInfoEXT *debug_create_info);
bool check_validation_layer_support(Device *device);
StringArray get_required_extensions(Device *device);
bool is_device_suitable(VkPhysicalDevice device, Device* device_info);


bool find_queue_families(VkPhysicalDevice device,
  Device *device_info,
  QueueFamilyIndices *out_indices
);
bool check_device_extension_support(VkPhysicalDevice device,
  StringArray required_extensions,
  uint32_t required_extensions_count
);
