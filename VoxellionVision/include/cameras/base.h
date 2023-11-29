#pragma once

#include "glm/gtc/matrix_transform.hpp"

#include "cameras/common.h"

namespace vvision{
    namespace cameras{
        class CameraManager;
        class Camera{
        friend CameraManager;
        protected:
            ProjectionType projType;
            ProjectionData projData;
            glm::mat4 projMat;
        public:
            Camera(OrthographicData o, float aspect);
            Camera(PerspectiveData p, float aspect);
            void resize(float aspect);
            virtual glm::mat4 getVPMat() = 0;
            virtual glm::mat4 getViewMat() = 0;
            virtual glm::mat4 getIViewMat() = 0;

        protected:
            callbacks::frameBuffer *frameBufferCB;
            callbacks::key *keyCB;
            callbacks::mouseButton *mouseButtonCB;
            callbacks::cursorPos *cursorPosCB;
            callbacks::scroll *scrollCB;

        public:
            void setFrameBufferCB(callbacks::frameBuffer cb);
            void setKeyCB(callbacks::key cb);
            void setMouseButtonCB(callbacks::mouseButton cb);
            void setCursorPosCB(callbacks::cursorPos cb);
            void setScrollCB(callbacks::scroll cb);
        };
    }
}