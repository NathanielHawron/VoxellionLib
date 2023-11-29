#pragma once

#include "pipeline.h"
#include "device.h"
#include "gfxObjects/vertex.h"
#include "gfxObjects/renderable.h"
#include "render_systems/base.h"

namespace vvision{
    namespace render_systems{
        class Simple:public RenderSystem{
        private:
            struct PushConstantData{
                glm::mat4 mvp;
            };
        public:
            Simple(Device &device, VkRenderPass renderPass, uint32_t width, uint32_t height, std::filesystem::path shaderPath, std::string vertexName, std::string fragmentName, model::vertex::VertexType vertexType);

            Simple(const Simple&) = delete;
            void operator=(const Simple&) = delete;

            void renderRenderables(VkCommandBuffer commandBuffers, glm::mat4 vpMat) override;
        private:
            VkPipelineLayout createPipelineLayout() override;
            Pipeline *createPipeline(VkRenderPass renderPass, std::filesystem::path shaderPath, std::string vertexName, std::string fragmentName) override;
        };
    }
};