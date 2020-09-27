#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "debug.h"
#include "shader.h"
#include "shader_program.h"
#include "camera.h"
#include "model.h"
#include "chessboard.h"

#include <iostream>

// initialization functions
void initializeGLFW();
void initializeGLAD();
void EnableGLDebug();
GLFWwindow *initializeWindow();

// runtime
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(SCR_WIDTH, SCR_HEIGHT);

int main() {
    initializeGLFW();

    GLFWwindow *window = initializeWindow();
    initializeGLAD();
    // glew/glad has to be initialized first for it to work
    EnableGLDebug();

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    Camera::Init(window);

    glEnable(GL_DEPTH_TEST);

    Shader vertexShader("res/shaders/material_vertex.glsl");
    Shader fragmentShader("res/shaders/material_fragment.glsl");

    ShaderProgram shaderProgram(std::vector<Shader>{vertexShader, fragmentShader});

    shaderProgram.Use();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    Chessboard chessboard(shaderProgram);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // Input here
        camera.ProcessKeyboardInput(window);

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();
        // pass transformation matrices to the shader
        shaderProgram.SetUniform("projection", camera.GetProjection());
        shaderProgram.SetUniform("view", camera.GetView());

        // draw teh whole chess
        chessboard.Draw(shaderProgram);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void initializeGLFW() {
    // Initialize the library
    if (!glfwInit()) {
        spdlog::error("failed to initialize GLFW");
        exit(0);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core profile requires us to create a vertex object array, If we're to resign from it, we need compat profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void initializeGLAD() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("Failed to initialize GLAD");
        exit(1);
    }
    // print gl version
    spdlog::info(glGetString(GL_VERSION));
}

void EnableGLDebug() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, nullptr);
}

GLFWwindow *initializeWindow() {
    GLFWwindow *window;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Chess club", nullptr, nullptr);
    if (!window) {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
        exit(1);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    // synchronize with vsync/refresh rate
    glfwSwapInterval(1);
    return window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    camera.ProcessMouseInput((float) xpos, (float) ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll((float) yoffset);
}
