#pragma once

#include <filesystem>
#include <cassert>

#include "window.h"
#include "device.h"
#include "swapChain.h"

namespace vvision{
    class Renderer{
    private:
        uint32_t currentImageIndex;
        int currentFrameIndex;
        bool isFrameStarted;
    public:
        bool resize;
        Window &window;
        Device &device;
        SwapChain *swapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        Renderer(Window &window, Device &device, uint32_t width, uint32_t height, std::string title);
        ~Renderer();

        Renderer(const Renderer&) = delete;
        void operator=(const Renderer&) = delete;

        int getFrameIndex() const{
            assert(this->isFrameStarted && "Cannot get frame index when frame not in progress");
            return this->currentFrameIndex;
        }

        VkCommandBuffer beginFrame();
        void endFrame();
        inline bool getIsFrameStarted() const {return this->isFrameStarted;};

        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);
        inline VkRenderPass getSwapChainRenderPass() const { return this->swapChain->getRenderPass();}

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(this->isFrameStarted && "Cannot get command buffer when frame not in progress");
            return this->commandBuffers[this->currentFrameIndex];
        }
    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();
    };
};