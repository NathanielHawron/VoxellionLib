#pragma once

#include "pipeline.h"
#include "device.h"
#include "model.h" 
#include "renderable.h"

namespace vvision{
    namespace render_systems{
        class Simple{
            struct PushConstantData{
                glm::mat4 mvp;
            };
        private:
            std::filesystem::path shaderPath;
            std::string vertexName, fragmentName;
        public:
            Device &device;
            VkPipelineLayout pipelineLayout;
            Pipeline *pipeline;

            Simple(Device &device, VkRenderPass renderPass, uint32_t width, uint32_t height, std::string title, std::filesystem::path shaderPath, std::string vertexName, std::string fragmentName);
            ~Simple();

            Simple(const Simple&) = delete;
            void operator=(const Simple&) = delete;

            void renderRenderables(VkCommandBuffer commandBuffers, std::vector<Renderable> &renderables, glm::mat4 vpMat);
        private:
            VkPipelineLayout createPipelineLayout();
            Pipeline *createPipeline(VkRenderPass renderPass, std::filesystem::path shaderPath, std::string vertexName, std::string fragmentName);
        };
    }
};