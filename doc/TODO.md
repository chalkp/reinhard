## device.c :

bool create_logical_device(Device *device);
bool create_surface(Device *device);
bool create_command_pool(Device *device);

bool check_validation_layer_support(Device *device);
CharVector get_required_extensions(Device *device);
bool is_device_suitable(VkPhysicalDevice device, Device* device_info);