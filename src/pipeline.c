#include "pipeline.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Pipeline *create_pipeline(// Device *device,
  const char *vertex_file,
  const char *fragment_file
) {
  Pipeline *pipeline = (Pipeline*)malloc(sizeof(Pipeline));
  if(pipeline == NULL) {
    fprintf(stderr, "malloc: failed to allocate memory for Pipeline\n");
    return NULL;
  }

  pipeline->vertex_shader_code = read_file(vertex_file);
  if(pipeline->vertex_shader_code.data == NULL) {
    free(pipeline);
    return NULL;
  }
  
  pipeline->fragment_shader_code = read_file(fragment_file);
  if(pipeline->fragment_shader_code.data == NULL) {
    destroy_char_vector(&pipeline->vertex_shader_code);
    free(pipeline);
    return NULL;
  }

  if(!create_shader_module(pipeline, &pipeline->vertex_shader_code, &pipeline->vertex_shader_module)) {
    destroy_char_vector(&pipeline->vertex_shader_code);
    destroy_char_vector(&pipeline->fragment_shader_code);
    free(pipeline);
    return NULL;
  }
  if(!create_shader_module(pipeline, &pipeline->fragment_shader_code, &pipeline->fragment_shader_module)) {
    destroy_char_vector(&pipeline->vertex_shader_code);
    destroy_char_vector(&pipeline->fragment_shader_code);
    free(pipeline);
    return NULL;
  }
  
  VkPipelineShaderStageCreateInfo vertex_shader_stage;
  VkPipelineShaderStageCreateInfo fragment_shader_stage;
  setup_shader_stages(pipeline, &vertex_shader_stage, &fragment_shader_stage);

  // ... vulkan pipeline create info ...
  //
  //
  //

  return pipeline;
}

void destroy_pipeline(Pipeline *pipeline) {
  if(pipeline == NULL) {
    return;
  }

  destroy_char_vector(&pipeline->vertex_shader_code);
  destroy_char_vector(&pipeline->fragment_shader_code);
  free(pipeline);
}

bool create_shader_module(Pipeline *pipeline,
  CharVector *shader_code,
  VkShaderModule *shader_module
) {
  VkShaderModuleCreateInfo create_info;
  create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize = shader_code->size;
  create_info.pCode = (const uint32_t*)shader_code->data;

  VkResult result = vkCreateShaderModule(pipeline->device->device, &create_info, NULL, shader_module);

  if(result != VK_SUCCESS) {
    fprintf(stderr, "failed to create shader module\n");
    return false;
  }
  return true;
}


void setup_shader_stages(Pipeline *pipeline,
  VkPipelineShaderStageCreateInfo *vertex_shader_stage,
  VkPipelineShaderStageCreateInfo *fragment_shader_stage
) {
  vertex_shader_stage->sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertex_shader_stage->stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertex_shader_stage->module = pipeline->vertex_shader_module;
  vertex_shader_stage->pName = "main";
  vertex_shader_stage->flags = 0;
  vertex_shader_stage->pNext = NULL;
  vertex_shader_stage->pSpecializationInfo = NULL;

  fragment_shader_stage->sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragment_shader_stage->stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragment_shader_stage->module = pipeline->fragment_shader_module;
  fragment_shader_stage->pName = "main";
  fragment_shader_stage->flags = 0;
  fragment_shader_stage->pNext = NULL;
  fragment_shader_stage->pSpecializationInfo = NULL;
}
