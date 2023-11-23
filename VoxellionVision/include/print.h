#define VOXELLION_VISION_DEBUG

#ifdef VOXELLION_VISION_DEBUG
    #include <iostream>
    #define VV_RUN_DEBUG(x) x
    #define VV_PRINT_DEBUG(x) std::cout << "[Debug vv]:" << x << std::endl;
#else
    #define VV_RUN_DEBUG(x)
    #define VV_PRINT_DEBUG(x)
#endif