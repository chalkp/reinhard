#pragma once

#include "utils.h"
#include "device.h"
#include <vulkan/vulkan.h>

typedef struct pipeline {
  CharVector vertex_shader_code;
  CharVector fragment_shader_code;

  Device *device;
  VkPipeline vk_pipeline;
  VkShaderModule vertex_shader_module;
  VkShaderModule fragment_shader_module;
} Pipeline;

Pipeline *create_pipeline(// Device *device,
  const char *vertex_file,
  const char *fragment_file
);
void destroy_pipeline(Pipeline *pipeline);
bool create_shader_module(Pipeline *pipeline,
  CharVector *shader_code,
  VkShaderModule *shader_module
);
void setup_shader_stages(Pipeline *pipeline,
  VkPipelineShaderStageCreateInfo *vertex_shader_stage,
  VkPipelineShaderStageCreateInfo *fragment_shader_stage
);


typedef struct pipeline_config_info {
} Pipeline_Config_Info;

// > OK future chalk, listen.
// > This is where present chalk dont know anymore what should chalk do next.
// > When past chalk wrote this, only god and him knows how does these even compile.
// > TODO: setup vulkan pipeline create infos
// > DONT TRY RUNNING IT, IT SEGFAULTS
// > present chalk still dont know how it supposed to be done
// > do your best.
