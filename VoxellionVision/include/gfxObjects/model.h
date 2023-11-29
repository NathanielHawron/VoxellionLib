#pragma once

#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"

#include "device.h"
#include "gfxObjects/vertex.h"

namespace vvision{
    namespace model{
        class Model{
        private:
            struct Buffer{
                VkBuffer buff;
                VkDeviceMemory mem;
                uint32_t count;
                
                void create(Device &device, uint32_t size, VkBufferUsageFlagBits useFlags, VkMemoryPropertyFlagBits propertyFlags = (VkMemoryPropertyFlagBits)(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
                void pushData(Device &device, const void *data, uint32_t size);
                void destroy(Device &device);
            };
        private:
            Device &device;

            Buffer vbo;
            Buffer ibo;

            void *vertices;
            uint32_t *indices;
        public:
            const vertex::VertexType vertexType;
            Model(Device &device, vertex::VertexType vertexType);
            ~Model();

            Model(const Model&) = delete;
            Model &operator=(const Model&) = delete;

            template<class V>
            inline V *getVertices(){return this->vertices;};
            inline uint32_t *getIndices(){return this->indices;};

            inline uint32_t getVertexCount()const{return this->vbo.count;};
            inline uint32_t getIndexCount()const{return this->ibo.count;};

            template<class V>
            V* allocateVertices(uint32_t vertexCount);
            uint32_t* allocateIndices(uint32_t indexCount);

            template<class V>
            void setVertices(const V *vertices, uint32_t vertexCount){
                this->allocateVertices<V>(vertexCount);
                memcpy(this->vertices,vertices,sizeof(V)*vertexCount);
            }
            void setIndices(const uint32_t *indices, uint32_t indexCount){
                this->allocateIndices(indexCount);
                memcpy(this->indices,indices,sizeof(uint32_t)*indexCount);
            }

            template<class V>
            void upload();
            void clear();

            void bind(VkCommandBuffer commandBuffer);
            void draw(VkCommandBuffer commandBuffer);
        };
    }
}