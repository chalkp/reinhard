#pragma once
#include "window.h"
#include "pipeline.h"

typedef struct reinhard {
  Window *window;
  Pipeline *pipeline;
} Reinhard;

Reinhard *create_reinhard_instance();
void destroy_reinhard_instance(Reinhard *reinhard);
