#include "lib/glad/glad.h"
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "debug.h"
#include "shader.h"
#include "shader_program.h"
#include "element_buffer.h"
#include "vertex_array.h"
#include "renderer.h"
#include "texture.h"

// initialization functions
void initializeGLFW();
void initializeGLAD();
void EnableGLDebug();
GLFWwindow *initializeWindow();

// runtime
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int pgnTest();


int main() {
    initializeGLFW();

    GLFWwindow *window = initializeWindow();
    initializeGLAD();
    // glew/glad has to be initialized first for it to work
    EnableGLDebug();

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);

    Shader vertexShader("res/shaders/vertex.glsl");
    Shader fragmentShader("res/shaders/fragment.glsl");

    ShaderProgram shaderProgram(std::vector<Shader>{vertexShader, fragmentShader});

    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };

//    unsigned int indices[] = {
//            0, 1, 3, // first triangle
//            1, 2, 3  // second triangle
//    };
//
    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2, 3);
    vao.AddBuffer(vbo, layout);
//    ElementBuffer ebo(indices, sizeof(indices));

    Texture texture1({"res/textures/container.jpg", GL_RGB, GL_RGB, false});
    Texture texture2({"res/textures/awesomeface.png", GL_RGB, GL_RGBA, true});

    texture1.Bind(0);
    texture2.Bind(1);

    shaderProgram.Use();
    fragmentShader.SetUniform(shaderProgram.GetID(), "texture1", 0);
    fragmentShader.SetUniform(shaderProgram.GetID(), "texture2", 1);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // Input here
        processInput(window);

        // Render here
        Renderer::Clear();

        texture1.Bind(0);
        texture2.Bind(1);

        shaderProgram.Use();

        // draw triangle
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // pass transformation matrices to the shader
        vertexShader.SetUniform(shaderProgram.GetID(), "projection",
                                projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        vertexShader.SetUniform(shaderProgram.GetID(), "view", view);

        vao.Bind();
        // render boxes
        for (unsigned int i = 0; i < 10; i++) {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            vertexShader.SetUniform(shaderProgram.GetID(), "model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
//            Renderer::Draw(shaderProgram, vao, 36);
        }

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