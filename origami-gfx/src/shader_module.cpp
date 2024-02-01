#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

#include "origami/gfx/shader_module.hpp"

ShaderModule ShaderModule::create(const Parameters &parameters)
{
    ShaderModule shader_module;
    shader_module.device = parameters.device;

    std::ifstream file(parameters.file_path, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open shader \"" + parameters.file_path + "\"");
    }

    size_t file_size = (size_t)file.tellg();

    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), file_size);
    file.close();

    const VkShaderModuleCreateInfo create_info{
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = buffer.size(),
        .pCode = (uint32_t *)buffer.data(),
    };

    VkResult result = vkCreateShaderModule((VkDevice)shader_module.device, &create_info, nullptr, (VkShaderModule *)&shader_module.id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::ShaderModule::ShaderModule(): failed to create shader module!");
    }

    return shader_module;
}

void ShaderModule::destroy()
{
    vkDestroyShaderModule((VkDevice)device, (VkShaderModule)id, nullptr);
}