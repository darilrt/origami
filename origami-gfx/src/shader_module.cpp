#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

#include "origami/gfx/shader_module.hpp"

ShaderModule::ShaderModule(const Parameters &parameters)
{
    device = parameters.device;

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

    VkResult result = vkCreateShaderModule((VkDevice)device, &create_info, nullptr, (VkShaderModule *)&id);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("gfx::ShaderModule::ShaderModule(): failed to create shader module!");
    }
}

void ShaderModule::destroy()
{
    vkDestroyShaderModule((VkDevice)device, (VkShaderModule)id, nullptr);
}