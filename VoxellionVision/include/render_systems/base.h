#pragma once

#include <vector>

#include "pipeline.h"
#include "device.h"
#include "gfxObjects/vertex.h"
#include "gfxObjects/renderable.h"

namespace vvision{
    namespace render_systems{
        class RenderSystem{
        protected:
            std::filesystem::path shaderPath;
            std::string vertexName, fragmentName;
            std::vector<Renderable*> renderables;
        public:
            const model::vertex::VertexType vertexType;
            Device &device;
            VkPipelineLayout pipelineLayout;
            Pipeline *pipeline;

            RenderSystem(Device &device, VkRenderPass renderPass, uint32_t width, uint32_t height, std::filesystem::path shaderPath, std::string vertexName, std::string fragmentName, model::vertex::VertexType vertexType);
            virtual ~RenderSystem();

            RenderSystem(const RenderSystem&) = delete;
            void operator=(const RenderSystem&) = delete;

            Renderable* addRenderable(model::Model *model, glm::vec3 pos, glm::quat rot, glm::vec3 scale = {1.0f,1.0f,1.0f}){
                if(this->isCompatable(model)){
                    this->renderables.push_back(new Renderable(model, pos, rot, scale));
                    return this->renderables.at(this->renderables.size()-1);
                }else{
                    return nullptr;
                }
            };
            bool isCompatable(model::Model *model);
            bool moveRenderable(Renderable *renderable, RenderSystem &dest);
            virtual void renderRenderables(VkCommandBuffer commandBuffers, glm::mat4 vpMat) = 0;
        private:
            virtual VkPipelineLayout createPipelineLayout() = 0;
            virtual Pipeline *createPipeline(VkRenderPass renderPass, std::filesystem::path shaderPath, std::string vertexName, std::string fragmentName) = 0;
        };
    }
};