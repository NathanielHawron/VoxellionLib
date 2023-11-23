#pragma once

#include <string>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "cameras/common.h"

namespace vvision{
    class Window{
    private:
        GLFWwindow *window;
        int width, height;
        bool frameBufferResize;
        std::string name;
    public:
        cameras::CameraManager cameraManager;
        
    private:
        static void frameBufferResizeCallback(GLFWwindow *window, int width, int height);
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    public:
        Window(int width, int height, std::string name);
        ~Window();
        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;

        inline bool shouldClose(){return glfwWindowShouldClose(this->window);};
        inline bool resize(){return this->frameBufferResize;};
        inline void resetWindowResizeFlag(){this->frameBufferResize = false;};
        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

        VkExtent2D getExtent(){return {(uint32_t)width,(uint32_t)height};};
    };
}