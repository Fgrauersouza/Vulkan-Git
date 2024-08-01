#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//#include <vulkan/vulkan.h> - não se esqueça de implementar GLFW

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;


//implementação de Validation Layers
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;    
#endif


class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private: 
    GLFWwindow* window;
    VkInstance instance;
    
    void initWindow() { 
    
        glfwInit();
    
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);   
     
    }    

    void initVulkan() {
        createInstance();

    }

    void mainLoop() {
    
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();

    }
    
    void createInstance() {
    
         VkApplicationInfo appInfo{};
         appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
         appInfo.pApplicationName = "Hello Triangle";
         appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
         appInfo.pEngineName = "No Engine";
         appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
         appInfo.apiVersion = VK_API_VERSION_1_0;
    
         VkInstanceCreateInfo createInfo{};
         createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
         createInfo.pApplicationInfo = &appInfo;
         
         uint32_t glfwExtensionCount = 0;
         const char** glfwExtensions;

         glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

         createInfo.enabledExtensionCount = glfwExtensionCount;
         createInfo.ppEnabledExtensionNames = glfwExtensions;
         
         createInfo.enabledLayerCount = 0;

         if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    throw std::runtime_error("failed to create instance!");
    }
       
    }
    
    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        
        return false;
    }
     
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
