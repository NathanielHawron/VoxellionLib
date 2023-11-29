#pragma once

#include <cstdint>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "cameras/base.h"
#include "cameras/common.h"

namespace vvision{
    namespace cameras{
        class FirstPerson:public Camera{
        public:
            glm::vec3 pos;
            glm::quat rot;
        public:
            FirstPerson(OrthographicData o, float aspect, glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f), glm::quat rot = glm::quat(glm::vec3(0.0f,0.0f,0.0f)));
            FirstPerson(PerspectiveData p, float aspect, glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f), glm::quat rot = glm::quat(glm::vec3(0.0f,0.0f,0.0f)));

            glm::mat4 getVPMat() override;
            glm::mat4 getViewMat() override;
            glm::mat4 getIViewMat() override;
        };
    }
}