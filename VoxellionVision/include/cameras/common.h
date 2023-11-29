#pragma once

#include <cstdint>
#include <vector>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace vvision{
    namespace cameras{
        struct Camera;
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
        namespace callbacks{
            typedef void(frameBuffer)(int width, int height);
            typedef void(key)(int key, int scancode, int action, int mods, double dt);
            typedef void(mouseButton)(int button, int action, int mods, double dt);
            typedef void(cursorPos)(double xpos, double ypos, double dt);
            typedef void(scroll)(double xoffset, double yoffset, double dt);
        }
        class CameraManager{
        public:
            enum class CameraType:uint_fast8_t{
                NULL_CAMERA,
                FIRST_PERSON
            };
            typedef uint16_t CamID;
            static constexpr CamID NULL_CAMERA = UINT16_MAX;
        private:
            float aspect;
            CamID primaryCameraID;
            Camera* primaryCamera;
            std::vector<Camera*> cameras;
        public:
            CameraManager(float aspect);

            CamID addCamera(Camera *cam);

            void setPrimaryCamera(CamID id);
            CamID getPrimaryCameraId();
            Camera *getCamera(CamID id);
            Camera *getPrimaryCamera();
            inline bool isCamIDValid(CamID id);

            glm::mat4 getPrimaryVPMat();
            glm::mat4 getPrimaryViewMat();
            glm::mat4 getPrimaryIViewMat();
            float getAspect()const{return this->aspect;};

            void frameBufferResizeCallback(int width, int height);
            void keyCallback(int key, int scancode, int action, int mods, double dt);
            void mouseButtonCallback(int button, int action, int mods, double dt);
            void cursorPositionCallback(double xpos, double ypos, double dt);
            void scrollCallback(double xoffset, double yoffset, double dt);
        };
    }
}

#include "cameras/base.h"