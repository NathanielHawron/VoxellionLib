#pragma once

#include <cstdint>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "cameras/common.h"

namespace vvision{
    namespace cameras{
        class FirstPerson{
        private:
            ProjectionType projType;
            ProjectionData projData;
            glm::mat4 projMat;
        public:
            glm::vec3 pos;
            glm::quat rot;
        public:
            FirstPerson(OrthographicData o, float aspect, glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f), glm::quat rot = glm::quat(glm::vec3(0.0f,0.0f,0.0f)));
            FirstPerson(PerspectiveData p, float aspect, glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f), glm::quat rot = glm::quat(glm::vec3(0.0f,0.0f,0.0f)));
            void resize(float aspect);
            glm::mat4 getVPMat();
            glm::mat4 getViewMat();
            glm::mat4 getIViewMat();
        };
    }
}