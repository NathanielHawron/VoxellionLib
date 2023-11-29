VoxellionVision V0.0.0.a0.16

To get started, import the "graphicsHandler.h" header file. All objects are in the "vvision" namespace.

First, instantiate a GraphicsHandler(uint32_t width, uint32_t height, std::string title), where width and height are the window dimentions and the title is the name of the window. It may be useful to make a reference to the window and camera manager (GraphicsHandler::window and GraphicsHandler::CameraManager), since you will probably access them a lot.

Next, use GraphicsHandler::addModel(V *vertices, uint32_t vertexCount, uint32_t *indices, uint32_t indexCount) to add a model to the graphics handler, where V is any type in the vvision::model::vertex namespace. Make sure to keep the pointer to the model that is returned, you need it to modify the model.

Then, add a renderSystem with GraphicsHandler::addRenderSystem<\T>(std::filesystem::path shaderPath, std::string vertexName, std::string fragmentName, vvision::model::vertex::VertexType vertexType), which needs a path to the shader files, the name of the shaders (including the .spv extension), and the type of vertex. Note that only models with the same vertex type can be added to a render system. As with the model, make sure to keep a pointer to the render system that is returned, you need it to add renderables. To add a renderable, use RenderSystem::addRenderable(vvision::model::Model *model, glm::vec3 pos, glm::quat rot, glm::vec3 scale). Again, keep the pointer that is returned, since you need it to transform the renderable.

A model represents a mesh on the GPU. Since different vertex types have different memory layouts, it needs to match the layout that the render system uses. A renderable contains extra data about how to render a model, including its transformation. This distinction is useful since multiple renderables can use the same model (ex. a few tree models can be drawn hundreds of times each in a forest).

Currently, there is only one type of built-in camera, the FirstPerson camera (cameras are found in the cameras namespace). The camera manager has arrays of cameras. To add a camera, first construct a camera (such as with the vvision::cameras::FirstPerson constructor), then use CameraManager::addCamera(vvision::camera::Camera* cam). Keep the CamID that is returned, it can be used to manage the camera. To set which camera to render from, call CameraManager::setCamera(CamID).

Finally, make a loop that contains a glfwPollEvents() and a GraphicsHandler::drawFrame(). The GraphicsHandler::window also has a method called window.shouldClose(), which tells you when the x was clicked. It is a good idea to exit the loop when this becomes true.


Next steps:
Render Systems
- Uniform Buffers
- Textures
- Offscreen Rendering (Frame Buffers)
Camera System
- Arc Rotate Camera
- Follow Camera
Camera Settings:
- Viewports
Interaction:
- Raycasting
Assets:
- Load models from files
    - .obj
    - .stl

Credits:
- GLFW (https://www.glfw.org/)
- Vulkan (https://www.vulkan.org/)