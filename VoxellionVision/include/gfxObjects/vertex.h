#pragma once

#include <vector>
#include <cstdint>

#include "glm/glm.hpp"
#include "vulkan/vulkan.h"

namespace vvision{
    namespace model{
        namespace vertex{
            enum class VertexType:uint_fast8_t{
                XYZ,
                XYZ_HP,

                COLORVERT,
                COLORVERT_HP,
                COLORVERT_S,
                COLORVERT_HPS
            };
            template <typename T>
            struct xyz_t{
                const static VertexType type;
                static_assert(std::is_same<T,float>::value || std::is_same<T,double>::value, "xyz_t<T>: T must be float or double");
                glm::tvec3<T> pos;

                static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
                static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
            };
            typedef xyz_t<float> xyz;
            typedef xyz_t<double> xyz_hp;

            template <typename T, typename C>
            struct colorVert_t{
                const static VertexType type;
                static_assert(std::is_same<T,float>::value || std::is_same<T,double>::value, "colorVert_t<T>: T must be float or double");
                static_assert(std::is_same<C,float>::value || std::is_same<C,uint8_t>::value, "colorVert_t<C>: C must be float or uint8_t");
                glm::tvec3<T> pos;
                glm::tvec3<C> col;

                static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
                static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
            };
            typedef colorVert_t<float,float> colorVert;
            typedef colorVert_t<double,float> colorVert_hp;
            typedef colorVert_t<float,uint8_t> colorVert_s;
            typedef colorVert_t<double,uint8_t> colorVert_hps;
        }
    }
}