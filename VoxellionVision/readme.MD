To get started, import the "graphicsHandler.h" header file. All objects are in the "vvision" namespace.

Create a std::filesystem::path that leads to the shader folder. This folder should have both the vertex and fragment shader, compiled into SPIR-V (.spv files). Then, instantiate a GraphicsHandler. The constructor takes 6 arguments:
width - width of window in pixels
height - height of window in pixels
title - name of window
shaderPath - path that was created earlier
vertexName - name of the vertex shader file
fragmentName - name of the fragment shader file

Note: eventually, the shaders will be moved to renderSystems. When that happens, the shaders will be added in a seperate step.

Next, to add models, use GraphicsHandler::addModel(vertices). The vertices are an std::vector of Model::Vertex. The Model::Vertex includes two glm::vec3, the first one being position and the second one being color. Make sure to keep the pointer that was returned by this function, since you need it to make the renderable (this is useful for reusing models).

Create a renderable using GraphicsHandler::addRenderable(Model*, glm::vec3 pos, glm::quat rot, glm::scale = {1.0f,1.0f,1.0f}). This renderable represents an object with a position, orientation, and scale. Again, make sure to keep the pointer returned by the addRenderable function, since you need it in order to move the object.

At this point, it may be useful to make a reference to the GraphicsHandler::window or the GraphicsHandler::window::cameraManager. Currently, there is only one type of built-in camera, the FirstPerson camera (cameras are found in the cameras namespace). The camera manager has arrays of cameras, and the CamID struct keeps track of the type and index of the camera. To add a camera, use CameraManager::addFirstPersonCamera(cameras::PerspectiveData | cameras::OrthographicData). This returns the CamID that references the added camera. To get a pointer to the actual camera (useful for moving the camera or adding callbacks), use cameraManager::getCamera(CamID). This returns a void*, make sure to cast it to the correct camera type before using it. Cameras will automatically resize when the window resizes.

To make use of a camera, you can change it's rotation and position directly.

Finally, make a loop that contains a glfwPollEvents() and a GraphicsHandler::drawFrame(). The GraphicsHandler object also has a method called window.shouldClose(), which tells you when the x was clicked. It is a good idea to exit the loop when this becomes true.


Next steps:
Render Systems
- Index Buffers
- Uniform Buffers
- Enable multiple different render systems to be used
- Textures
- Offscreen Rendering (Frame Buffers)
Camera System
- Arc Rotate Camera
- Follow Camera
Camera Settings:
- Viewports

Credits:
- GLFW (https://www.glfw.org/)
- Vulkan (https://www.vulkan.org/)