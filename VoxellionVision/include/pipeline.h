#pragma once

#include <filesystem>
#include <vector>
#include <string>

#include "device.h"
#include "swapChain.h"

namespace vvision{
    struct PipelineConfigInfo{
        PipelineConfigInfo(const PipelineConfigInfo&) = delete;
        PipelineConfigInfo &operator=(const PipelineConfigInfo&) = delete;

        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineDynamicStateCreateInfo dynamicStateInfo;
        VkPipelineLayout pipelineLayout = (VkPipelineLayout)nullptr;
        VkRenderPass renderPass = (VkRenderPass)nullptr;
        uint32_t subpass = 0;
        static void defaultInfo(PipelineConfigInfo &configInfo);
    };
    class Pipeline{
    private:
        Device &device;
        VkPipeline graphicsPipeline;
        VkShaderModule vertexShaderModule, fragmentShaderModule;
    public:
        Pipeline(Device &device, const std::filesystem::path &shaderPath, const std::string &vertName, const std::string &fragName, const PipelineConfigInfo& configInfo, std::vector<VkVertexInputBindingDescription> &bindingDescriptions,std::vector<VkVertexInputAttributeDescription> &attributeDescriptions);
        ~Pipeline();

        Pipeline(const Pipeline&) = delete;
        Pipeline &operator=(const Pipeline&) = delete;
        
        void bind(VkCommandBuffer commandBuffer);

    private:
        void createShaderModule(std::pair<char*, std::size_t> code, VkShaderModule *shaderModule);
        static std::pair<char*, std::size_t> readFile(const std::filesystem::path &fpath);
    };
}