#pragma once

#include "window.h"
#include "device.h"
#include "renderer.h"
#include "model.h" 
#include "renderable.h"
#include "render_systems/simple.h"

namespace vvision{
    class GraphicsHandler{
    private:
        std::filesystem::path shaderPath;
        std::string vertexName, fragmentName;
    public:
        Window window;
        Device device;
        Renderer renderer;

        render_systems::Simple renderSystem;

        std::vector<Model*> models;
        std::vector<Renderable> renderables;

        GraphicsHandler(uint32_t width, uint32_t height, std::string title, std::filesystem::path shaderPath, std::string vertexName, std::string fragmentName);
        ~GraphicsHandler();

        GraphicsHandler(const GraphicsHandler&) = delete;
        void operator=(const GraphicsHandler&) = delete;

        Model* addModel(std::vector<Model::Vertex> vertices){
            Model *m = new Model(this->device, vertices);
            this->models.push_back(m);
            return m;
        };
        Renderable* addRenderable(Model *model, glm::vec3 pos, glm::quat rot, glm::vec3 scale = {1.0f,1.0f,1.0f}){
            this->renderables.push_back(Renderable(model, pos, rot, scale));
            return &this->renderables.at(this->renderables.size()-1);
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