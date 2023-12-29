#pragma once
#include "window.h"
#include "pipeline.h"

typedef struct Reinhard {
  Window *window;
  Pipeline *pipeline;
} Reinhard;

Reinhard *summonReinhardInstance();
void destroyReinhardInstance(Reinhard *reinhard);
