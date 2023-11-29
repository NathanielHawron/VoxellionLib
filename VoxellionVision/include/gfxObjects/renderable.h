#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "gfxObjects/model.h"

namespace vvision{

    class Renderable{
    private:
        glm::vec3 pos;
        glm::quat rot;
        glm::vec3 scale;
    public:
        model::Model *model;
        Renderable(model::Model *model, glm::vec3 pos, glm::quat rot, glm::vec3 scale = {1.0f,1.0f,1.0f});
        ~Renderable();

        inline void setPos(glm::vec3 nPos){this->pos = nPos;};
        inline void move(glm::vec3 dPos){this->pos += dPos;};
        inline void rotate(glm::quat rot){this->rot *= rot;};
        inline void setScale(glm::vec3 nScale){this->scale = nScale;}
        inline void transform(glm::mat4 mat){this->pos = mat*glm::vec4(this->pos,1.0f); this->scale = mat*glm::vec4(this->scale,1.0f);}

        inline glm::vec3 getPos(){return this->pos;};
        inline glm::vec3 getScale(){return this->scale;};
        inline glm::quat getRot(){return this->rot;};

        glm::mat4 getTransform();
        glm::mat4 getITransform();
    };
}