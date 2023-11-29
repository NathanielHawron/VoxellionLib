#pragma once

#include "window.h"
#include "device.h"
#include "renderer.h"
#include "gfxObjects/model.h" 
#include "gfxObjects/renderable.h"
#include "render_systems/simple.h"

namespace vvision{
    class GraphicsHandler{
    public:
        Window window;
        Device device;
        Renderer renderer;

        std::vector<render_systems::RenderSystem *> renderSystems;
        std::vector<model::Model*> models;
        std::vector<Renderable> renderables;

        GraphicsHandler(uint32_t width, uint32_t height, std::string title);
        ~GraphicsHandler();

        GraphicsHandler(const GraphicsHandler&) = delete;
        void operator=(const GraphicsHandler&) = delete;

        template<typename R>
        R* addRenderSystem(std::filesystem::path shaderPath, std::string vertexName, std::string fragmentName, model::vertex::VertexType vertexType){
            VkExtent2D extent = this->window.getExtent();
            R* renderSystem = new R(this->device, this->renderer.getSwapChainRenderPass(), extent.width, extent.height, shaderPath, vertexName, fragmentName, vertexType);
            this->renderSystems.push_back(renderSystem);
            return renderSystem;
        }
        template<typename V>
        model::Model* addModel(const V *vertices, uint32_t vertexCount, const uint32_t *indices, uint32_t indexCount){
            model::Model *m = new model::Model(this->device, V::type);
            m->setVertices(vertices, vertexCount);
            m->setIndices(indices, indexCount);
            m->upload<V>();
            m->clear();
            this->models.push_back(m);
            return m;
        };

        void drawFrame();
        void drawFrame(glm::mat4 vpMat);
        inline bool resized(){
            bool res = this->renderer.resize;
            this->renderer.resize = false;
            return res;
        }
    };
};