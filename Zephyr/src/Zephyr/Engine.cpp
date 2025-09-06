#include "zppch.h"
#include "Engine.h"
#include "Log.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Zephyr {

    void Engine::ErrorCallback(int error, const char* description) {
        fprintf(stderr, "Error: %s\n", description);
    }

    void Engine::InitWindow(GLFWwindow*& window, int width, int height, const char* name) {
        if (!glfwInit()) {
            ZP_CORE_ERROR("Failed to initialise glfw");
            return; 
        }

        glfwSetErrorCallback(Engine::ErrorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        window = glfwCreateWindow(width, height, name, NULL, NULL);
        if (!window) {
            ZP_CORE_ERROR("Window or OpenGL context creation failed");
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            ZP_CORE_ERROR("Failed to initialise GLAD");
        }

        glViewport(0, 0, width, height);

            {
                ZP_CORE_TRACE("GLAD and GLFW initialised");
            }
        
       

    }


}