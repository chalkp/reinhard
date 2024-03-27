#pragma once

#include "utils.h"
#include <vulkan/vulkan.h>

typedef struct pipeline {
  CharVector vertex_shader_code;
  CharVector fragment_shader_code;
} Pipeline;

Pipeline *create_pipeline(const char *vert_file, const char *frag_file);
void destroy_pipeline(Pipeline *pipeline);