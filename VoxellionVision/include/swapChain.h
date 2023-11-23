#pragma once

#include "device.h"

#include <vulkan/vulkan.h>

#include <memory>
#include <string>
#include <vector>

namespace vvision{
    class SwapChain{
    public:
        static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
    private:
        VkFormat swapChainImageFormat;
        VkFormat swapChainDepthFormat;
        VkExtent2D swapChainExtent;

        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkRenderPass renderPass;

        std::vector<VkImage> depthImages;
        std::vector<VkDeviceMemory> depthImageMemorys;
        std::vector<VkImageView> depthImageViews;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;

        Device &device;
        VkExtent2D windowExtent;

        VkSwapchainKHR swapChain;
        SwapChain *oldSwapChain;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;

    public:
        SwapChain(Device &device, VkExtent2D windowExtent);
        SwapChain(Device &device, VkExtent2D windowExtent, SwapChain *prev);
        ~SwapChain();

        SwapChain(const SwapChain &) = delete;
        SwapChain &operator=(const SwapChain &) = delete;

        inline VkFramebuffer getFrameBuffer(int index) { return this->swapChainFramebuffers[index]; }
        inline VkRenderPass getRenderPass() { return this->renderPass; }
        inline VkImageView getImageView(int index) { return this->swapChainImageViews[index]; }
        inline size_t imageCount() { return this->swapChainImages.size(); }
        inline VkFormat getSwapChainImageFormat() { return this->swapChainImageFormat; }
        inline VkExtent2D getSwapChainExtent() { return this->swapChainExtent; }
        inline uint32_t getWidth() { return this->swapChainExtent.width; }
        inline uint32_t getHeight() { return this->swapChainExtent.height; }
        bool compareSwapFormats(const SwapChain &swapChain) const{
            return this->swapChainDepthFormat == swapChain.swapChainDepthFormat && this->swapChainImageFormat == swapChain.swapChainImageFormat;
        }

        float extentAspectRatio(){return (float)swapChainExtent.width / (float)swapChainExtent.height;}
        VkFormat findDepthFormat();

        VkResult acquireNextImage(uint32_t *imageIndex);
        VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);


    private:
        void init();
        void createSwapChain();
        void createImageViews();
        void createDepthResources();
        void createRenderPass();
        void createFramebuffers();
        void createSyncObjects();

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
    };
}