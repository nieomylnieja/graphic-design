#include <GLFW/glfw3.h>
#include "camera.h"

// default values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

Camera::Camera(const unsigned int scrWidth, const unsigned int scrHeight) : m_Position({0.0f, 0.0f, 3.0f}),
                                                                            m_Front({0.0f, 0.0f, -1.0f}),
                                                                            m_WorldUp({0.0f, 1.0f, 0.0f}),
                                                                            m_DeltaTime(0.0f),
                                                                            m_LastFrame(0.0f), m_Yaw(YAW),
                                                                            m_Pitch(PITCH),
                                                                            m_FirstMouseMovement(true), m_Zoom(ZOOM),
                                                                            m_SCR_HEIGHT(scrHeight),
                                                                            m_SCR_WIDTH(scrWidth) {
    m_MouseLastX = (float) m_SCR_WIDTH / 2.0f;
    m_MouseLastY = (float) m_SCR_HEIGHT / 2.0f;
    updateCameraVectors();
}

Camera::~Camera() = default;

void Camera::Init(GLFWwindow *window) {
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Camera::ProcessKeyboardInput(GLFWwindow *window) {
    auto currentFrame = (float) glfwGetTime();
    m_DeltaTime = currentFrame - m_LastFrame;
    m_LastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = SPEED * m_DeltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_Position += cameraSpeed * m_Front;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_Position -= cameraSpeed * m_Front;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_Position -= cameraSpeed * m_Right;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_Position += cameraSpeed * m_Right;
    }
}

void Camera::ProcessMouseInput(float xPos, float yPos, bool isPitchConstrained) {
    if (m_FirstMouseMovement) {
        m_MouseLastX = xPos;
        m_MouseLastY = yPos;
        m_FirstMouseMovement = false;
    }

    float xOffset = xPos - m_MouseLastX;
    float yOffset = m_MouseLastY - yPos; // reversed since y-coordinates go from bottom to top

    m_MouseLastX = xPos;
    m_MouseLastY = yPos;

    xOffset *= SENSITIVITY;
    yOffset *= SENSITIVITY;

    m_Yaw += xOffset;
    m_Pitch += yOffset;

    if (isPitchConstrained) {
        if (m_Pitch > 89.0f) {
            m_Pitch = 89.0f;
        }
        if (m_Pitch < -89.0f) {
            m_Pitch = -89.0f;
        }
    }
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void Camera::ProcessMouseScroll(float yOffset) {
    m_Zoom -= yOffset;
    if (m_Zoom < 1.0f)
        m_Zoom = 1.0f;
    if (m_Zoom > 45.0f)
        m_Zoom = 45.0f;
}

glm::mat4 Camera::GetView() {
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::GetProjection() const {
    return glm::perspective(glm::radians(m_Zoom), (float) m_SCR_WIDTH / (float) m_SCR_HEIGHT, 0.1f, 100.0f);
}
