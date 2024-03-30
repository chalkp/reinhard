#include "device.h"
#define GLFW_INCLUDE_VULKAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#define P_APPLICATION_NAME "Reinhard"
#define P_ENGINE_NAME "Reinhard"

#pragma GCC diagnostic ignored "-Wunused-parameter"

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
  VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
  VkDebugUtilsMessageTypeFlagsEXT message_type,
  const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
  void *p_user_data
) {
  fprintf(stderr, "validation layer: %s\n", p_callback_data->pMessage);
  return VK_FALSE;
}

Device *create_device(Window *window) {
  Device *device = (Device*)malloc(sizeof(Device));
  if(device == NULL) {
    fprintf(stderr, "malloc: failed to allocate memory for Graphic Device\n");
    return NULL;
  }

  device->window = window;

  if(!create_instance(device)) { return NULL; }
  if(device->enable_validation_layers && !setup_debug_messenger(device)) { return NULL; }
  if(!pick_physical_device(device)) { return NULL; }
  if(!create_logical_device(device)) { return NULL; }
  if(!create_surface(device)) { return NULL; }
  if(!create_command_pool(device)) { return NULL; }

  return device;
}

void destroy_device(Device *device) {
  if(device == NULL) {
    return;
  }

  // TODO:
  // 1. Destroy Command Pool
  // 2. Destroy Surface
  // 3. Destroy Logical Device
  // 4. Destroy Instance

  free(device);
}



bool create_instance(Device *device) {
  if(device->enable_validation_layers && !check_validation_layer_support(device)) {
    fprintf(stderr, "validation layers not available\n");
    return false;
  }

  VkApplicationInfo app_info;
  application_info_setup(&app_info);

  StringArray extensions = get_required_extensions(device);

  VkInstanceCreateInfo create_info;
  VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
  create_info_setup(device, &create_info, &debug_create_info, &app_info, &extensions);

  VkResult result = vkCreateInstance(&create_info, NULL, &device->instance);
  if(result != VK_SUCCESS) {
    fprintf(stderr, "vkCreateInstance: failed to create instance\n");
    return false;
  }

  return true;
}

bool setup_debug_messenger(Device *device) {
  if(!device->enable_validation_layers) {
    return true;
  }
  VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
  debug_create_info_setup(&debug_create_info);

  PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(device->instance, "vkCreateDebugUtilsMessengerEXT");
  if(func == NULL) {
    fprintf(stderr, "Failed to load vkCreateDebugUtilsMessengerEXT\n");
    return false;
  }
  VkResult result = func(device->instance, &debug_create_info, NULL, &device->debug_messenger);
  if(result != VK_SUCCESS) {
    fprintf(stderr, "vkCreateDebugUtilsMessengerEXT: failed to setup debug messenger\n");
    return false;
  }
  return true;
}

bool pick_physical_device(Device *device) {
  uint32_t device_count = 0;
  vkEnumeratePhysicalDevices(device->instance, &device_count, NULL);

  if(device_count == 0) {
    fprintf(stderr, "failed to find GPUs with Vulkan support\n");
    return false;
  }

  VkPhysicalDevice* devices = malloc(device_count * sizeof(VkPhysicalDevice));
  if(devices == NULL) {
    fprintf(stderr, "malloc: failed to allocate memory for devices\n");
    return false;
  }
  
  vkEnumeratePhysicalDevices(device->instance, &device_count, devices);

  bool device_found = false;
  for(uint32_t i = 0; i < device_count; i++) {
    if(is_device_suitable(devices[i], device)) {
      device->physical_device = devices[i];
      device_found = true;
      break;
    }
  }
  free(devices);

  if(!device_found) {
    fprintf(stderr, "failed to find working GPU\n");
  }
  return device_found;
}

bool create_logical_device(Device *device) {
  // QueueFamilyIndices indices;
  // if(find_queue_families(device->physical_device, device, &indices) != 0) {
  //   fprintf(stderr, "Failed to find suitable queue families!\n");
  //   return false;
  // }
  // uint32_t queue_family_indices[] = {indices.graphics_family, indices.present_family};
  // int queue_create_info_count = 1;
  // if(indices.graphics_family != indices.present_family) {
  //   queue_create_info_count = 2;
  // }

  // float queue_priority = 1.0f;
  // VkDeviceQueueCreateInfo queue_create_infos[queue_create_info_count];

  // for(int i=0; i<queue_create_info_count; ++i) {
  //   queue_create_infos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  //   queue_create_infos[i].queueFamilyIndex = queue_family_indices[i];
  //   queue_create_infos[i].queueCount = 1;
  //   queue_create_infos[i].pQueuePriorities = &queue_priority; 
  // }

  // VkPhysicalDeviceFeatures device_features;
  // VkDeviceCreateInfo create_info;
  
  // create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  // create_info.queueCreateInfoCount =  queue_create_info_count;
  // create_info.pQueueCreateInfos = queue_create_infos;
  // create_info.pEnabledFeatures = &device_features;
  // create_info.enabledExtensionCount = 
  return true;
}

bool create_surface(Device *device) {
  return true;
}

bool create_command_pool(Device *device) {
  return true;
}



void application_info_setup(VkApplicationInfo *app_info) {
  app_info->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info->pApplicationName = P_APPLICATION_NAME;
  app_info->applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info->pEngineName = P_ENGINE_NAME;
  app_info->engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info->apiVersion = VK_API_VERSION_1_0;
}

void create_info_setup(Device *device,
  VkInstanceCreateInfo *create_info,
  VkDebugUtilsMessengerCreateInfoEXT *debug_create_info,
  VkApplicationInfo *app_info,
  StringArray *extensions
) {
  create_info->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info->pApplicationInfo = app_info;
  
  create_info->enabledLayerCount = (uint32_t)extensions->size;
  create_info->ppEnabledExtensionNames = (const char* const*)extensions->data;

  
  if(device->enable_validation_layers) {
    create_info->enabledLayerCount = (uint32_t)device->validation_layers.size;
    create_info->ppEnabledLayerNames = (const char* const*)device->validation_layers.data;
    
    debug_create_info_setup(debug_create_info);

    create_info->pNext = debug_create_info;
  } else {
    create_info->enabledLayerCount = 0;
    create_info->ppEnabledLayerNames = NULL;
    create_info->pNext = NULL;
  }
}

void debug_create_info_setup(VkDebugUtilsMessengerCreateInfoEXT *debug_create_info) {
  debug_create_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  debug_create_info->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  debug_create_info->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                   VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  debug_create_info->pfnUserCallback = debug_callback;
  debug_create_info->pUserData = NULL;
}

bool check_validation_layer_support(Device *device) {
  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, NULL);

  VkLayerProperties *available_layers = (VkLayerProperties*)malloc(layer_count*sizeof(VkLayerProperties));
  if(available_layers == NULL) {
    fprintf(stderr, "malloc: failed to allocate memory for vulkan layer properties\n");
    return false;
  }
  vkEnumerateInstanceLayerProperties(&layer_count, available_layers);
  
  for(uint32_t i=0; i<device->validation_layers.size; i++) {
    bool layer_found = false;

    for(uint32_t j=0; j<layer_count; j++) {
      if(strcmp(device->validation_layers.data[i], available_layers[j].layerName) == 0) {
        layer_found = true;
        break;
      }
    }

    if(!layer_found) {
      free(available_layers);
      return false;
    }
  }

  free(available_layers);
  return true;
}

StringArray get_required_extensions(Device *device) {
  StringArray extensions;
  
  uint32_t glfw_extension_count = 0;
  const char **glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  if(glfw_extensions == NULL) {
    fprintf(stderr, "failed to get required glfw extensions\n");
    destroy_string_array(&extensions);
    return extensions;
  }

  for(uint32_t i=0; i<glfw_extension_count; i++) {
    push_string_array(&extensions, glfw_extensions[i]);
  }

  const char *other_extensions[] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
  };
  uint32_t other_extensions_count = sizeof(other_extensions) / sizeof(const char*);

  for(uint32_t i=0; i<other_extensions_count; i++) {
    push_string_array(&extensions, other_extensions[i]);
  }
  return extensions;
}

bool is_device_suitable(VkPhysicalDevice device, Device* device_info) {
  VkPhysicalDeviceProperties device_properties;
  vkGetPhysicalDeviceProperties(device, &device_properties);

  // check discrete GPU
  // bool is_discrete_gpu = device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

  // check vulkan api version 
  // bool supports_required_api = device_properties.apiVersion >= VK_API_VERSION_1_0;
  
  return true;
}


int find_queue_families(VkPhysicalDevice device,
  Device *device_info,
  QueueFamilyIndices *out_indices
) {
  out_indices->graphics_family = -1;
  out_indices->present_family = -1;

  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, NULL);
  
  VkQueueFamilyProperties *queue_families = (VkQueueFamilyProperties*)malloc(queue_family_count*sizeof(VkQueueFamilyProperties));
  if(queue_families == NULL) {
    return -1;
  }

  vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families);

  for(uint32_t i=0; i<queue_family_count; i++) {
    if(queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      out_indices->graphics_family = i;
    }

    VkBool32 present_support = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, device_info->surface, &present_support);

    if(present_support) {
      out_indices->present_family = i;
    }

    if(out_indices->graphics_family > 0 && out_indices->present_family > 0) {
      break;
    }
  }

  free(queue_families);
  return (out_indices->graphics_family > 0 && out_indices->present_family > 0) ? 0 : -1;
}
