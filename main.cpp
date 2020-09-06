#include "lib/glad/glad.h"
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include "debug.h"
#include "shader.h"
#include "shader_program.h"
#include "element_buffer.h"
#include "vertex_array.h"

// initialization functions
void initializeGLFW();
void initializeGLAD();
void EnableGLDebug();
GLFWwindow *initializeWindow();

// runtime
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);


int main() {
    initializeGLFW();

    GLFWwindow *window = initializeWindow();
    initializeGLAD();
    // glew/glad has to be initialized first for it to work
    EnableGLDebug();

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader vertexShader = Shader("res/shaders/vertex.glsl");
    Shader fragmentShader = Shader("res/shaders/fragment.glsl");

    ShaderProgram shaderProgram = ShaderProgram(std::vector<Shader>{vertexShader, fragmentShader});

    float vertices[] = {
            0.5f, 0.5f, 0.0f,   // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f,  // top left
    };
    unsigned int indices[] = {
            0, 1, 3,    // first triangle
            1, 2, 3     // second triangle
    };

    VertexArray vao;
    VertexBuffer vbo = VertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    vao.AddBuffer(vbo, layout);
    ElementBuffer ebo = ElementBuffer(indices, sizeof(indices));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // Input here
        processInput(window);

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw triangle
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void initializeGLFW() {
    /* Initialize the library */
    if (!glfwInit()) {
        spdlog::error("failed to initialize GLFW");
        exit(0);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core profile requires us to create a vertex object array, If we're to resign from it, we need compat profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Chess club", nullptr, nullptr);
    if (!window) {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
        exit(1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // synchronize with vsync/refresh rate
    glfwSwapInterval(1);
    return window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}