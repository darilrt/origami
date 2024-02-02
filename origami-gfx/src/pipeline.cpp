#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

#include "origami/gfx/pipeline.hpp"

#ifndef ORIGAMI_VS_MAIN
#define ORIGAMI_VS_MAIN "main"
#endif

#ifndef ORIGAMI_FS_MAIN
#define ORIGAMI_FS_MAIN "main"
#endif

Pipeline Pipeline::create(const PipelineInfo &parameters)
{
    Pipeline pipeline;
    pipeline.bind_point = parameters.bind_point;

    VkPipelineShaderStageCreateInfo vert_shader_stage_info = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_VERTEX_BIT,
        .module = (VkShaderModule)parameters.vs_module.id,
        .pName = ORIGAMI_VS_MAIN,
    };

    VkPipelineShaderStageCreateInfo frag_shader_stage_info = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
        .module = (VkShaderModule)parameters.fs_module.id,
        .pName = ORIGAMI_FS_MAIN,
    };

    VkPipelineShaderStageCreateInfo shader_stages[] = {vert_shader_stage_info, frag_shader_stage_info};

    VkPipelineInputAssemblyStateCreateInfo input_assembly{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE,
    };

    std::vector<VkDynamicState> dynamic_states = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
        VK_DYNAMIC_STATE_LINE_WIDTH,
    };

    VkPipelineDynamicStateCreateInfo dynamic_state_info = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = static_cast<uint32_t>(dynamic_states.size()),
        .pDynamicStates = dynamic_states.data(),
    };

    std::vector<VkVertexInputBindingDescription> binding_description(parameters.binding_descriptions.size());
    for (size_t i = 0; i < parameters.binding_descriptions.size(); i++)
    {
        binding_description[i] = {
            .binding = parameters.binding_descriptions[i].binding,
            .stride = parameters.binding_descriptions[i].stride,
            .inputRate = (VkVertexInputRate)parameters.binding_descriptions[i].input_rate,
        };
    }

    std::vector<VkVertexInputAttributeDescription> attribute_description(parameters.attribute_descriptions.size());
    for (size_t i = 0; i < parameters.attribute_descriptions.size(); i++)
    {
        attribute_description[i] = {
            .location = parameters.attribute_descriptions[i].location,
            .binding = parameters.attribute_descriptions[i].binding,
            .format = (VkFormat)parameters.attribute_descriptions[i].format,
            .offset = parameters.attribute_descriptions[i].offset,
        };
    }

    VkPipelineVertexInputStateCreateInfo vertex_input_info = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = static_cast<uint32_t>(binding_description.size()),
        .pVertexBindingDescriptions = binding_description.data(),
        .vertexAttributeDescriptionCount = static_cast<uint32_t>(attribute_description.size()),
        .pVertexAttributeDescriptions = attribute_description.data(),
    };

    VkPipelineViewportStateCreateInfo viewport_state{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount = 1,
    };

    VkPipelineRasterizationStateCreateInfo rasterizer{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_BACK_BIT,
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable = VK_FALSE,
        .depthBiasConstantFactor = 0.0f,
        .depthBiasClamp = 0.0f,
        .depthBiasSlopeFactor = 0.0f,
        .lineWidth = 1.0f,
    };

    VkPipelineMultisampleStateCreateInfo multisampling{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
        .sampleShadingEnable = VK_FALSE,
        .minSampleShading = 1.0f,
        .pSampleMask = nullptr,
        .alphaToCoverageEnable = VK_FALSE,
        .alphaToOneEnable = VK_FALSE,
    };

    VkPipelineColorBlendAttachmentState color_blend_attachment{
        .blendEnable = VK_FALSE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp = VK_BLEND_OP_ADD,
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    };

    VkPipelineColorBlendStateCreateInfo color_blending{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable = VK_FALSE,
        .logicOp = VK_LOGIC_OP_COPY,
        .attachmentCount = 1,
        .pAttachments = &color_blend_attachment,
        .blendConstants = {0.0f, 0.0f, 0.0f, 0.0f},
    };

    VkPipelineLayoutCreateInfo pipeline_layout_info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 0,
        .pSetLayouts = nullptr,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr,
    };

    VkResult result = vkCreatePipelineLayout(
        (VkDevice)parameters.device,
        &pipeline_layout_info,
        nullptr,
        (VkPipelineLayout *)&pipeline.layout);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create pipeline layout");
    }

    VkGraphicsPipelineCreateInfo pipeline_info{
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = 2,
        .pStages = shader_stages,
        .pVertexInputState = &vertex_input_info,
        .pInputAssemblyState = &input_assembly,
        .pViewportState = &viewport_state,
        .pRasterizationState = &rasterizer,
        .pMultisampleState = &multisampling,
        .pDepthStencilState = nullptr,
        .pColorBlendState = &color_blending,
        .pDynamicState = &dynamic_state_info,
        .layout = reinterpret_cast<VkPipelineLayout>(pipeline.layout),
        .renderPass = reinterpret_cast<VkRenderPass>(parameters.render_pass.id),
        .subpass = 0,
        .basePipelineHandle = VK_NULL_HANDLE,
    };

    result = vkCreateGraphicsPipelines(
        (VkDevice)parameters.device,
        VK_NULL_HANDLE,
        1,
        &pipeline_info,
        nullptr,
        reinterpret_cast<VkPipeline *>(&pipeline.id));

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create graphics pipeline");
    }

    pipeline.device = parameters.device;

    return pipeline;
}

void Pipeline::destroy()
{
    vkDestroyPipelineLayout((VkDevice)device, (VkPipelineLayout)layout, nullptr);
    vkDestroyPipeline((VkDevice)device, (VkPipeline)id, nullptr);
}