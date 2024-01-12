#include "device.h"
#include <stdlib.h>

Device *createDevice(Window *window) {
  Device *device = (Device*)malloc(sizeof(Device));
  device->window = window;
  

#ifdef DEBUG
  device->enableValidationLayers = true;
#else
  device->enableValidationLayers = false;
#endif

  return device;
}

void destroyDevice(Device *device) {
  free(device);
  device = NULL;
}
