#pragma once

#include <cstdint>
#include <vector>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace vvision{
    namespace cameras{
        struct FirstPerson;
        enum class ProjectionType: uint_fast8_t{
            PERSPECTIVE,
            ORTHOGRAPHIC
        };
        struct OrthographicData{
            // Left and right will be scaled by the aspect ratio
            float left = -1.0f, right = 1.0f, bottom = -1.0f, top = 1.0f;
        };
        struct PerspectiveData{
            float fov = 0.5f*3.1415927f, near = 0.01f, far = 1000.0f;
        };
        union ProjectionData{
            OrthographicData o;
            PerspectiveData p;
        };
        typedef void(keyCallback)(int key, int scancode, int action, int mods);
        typedef void(mousePosCallback)(double xpos, double ypos);
        class CameraManager{
        public:
            enum class CameraType:uint_fast8_t{
                NULL_CAMERA,
                FIRST_PERSON
            };
            struct CamID{
                CameraType type;
                uint_fast8_t index;
            };
        private:
            float aspect;
            CamID primaryCamera;
            std::vector<FirstPerson> firstPersonCameras;
        public:
            CameraManager(float aspect);

            CamID addFirstPersonCamera(PerspectiveData p, glm::vec3 pos = {0,0,0}, glm::quat rot = glm::quat(glm::vec3(0,0,0)));
            CamID addFirstPersonCamera(OrthographicData p, glm::vec3 pos = {0,0,0}, glm::quat rot = glm::quat(glm::vec3(0,0,0)));

            void setPrimaryCamera(CamID id);
            CamID getPrimaryCameraId();
            void* getCamera(CamID id);

            glm::mat4 getPrimaryVPMat();
            glm::mat4 getPrimaryViewMat();
            glm::mat4 getPrimaryIViewMat();

            void frameBufferResizeCallback(int width, int height);
            void keyCallback(int key, int scancode, int action, int mods);
            void mouseButtonCallback(int button, int action, int mods);
            void cursorPositionCallback(double xpos, double ypos);
            void scrollCallback(double xoffset, double yoffset);
        };
    }
}

#include <cameras/firstPerson.h>