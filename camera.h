#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up{};
    glm::vec3 m_Right{};
    glm::vec3 m_WorldUp;

    float m_DeltaTime;
    float m_LastFrame;

    float m_Yaw;
    float m_Pitch;
    float m_MouseLastX;
    float m_MouseLastY;
    bool m_FirstMouseMovement;

    float m_Zoom;

    const unsigned int m_SCR_WIDTH;
    const unsigned int m_SCR_HEIGHT;

    void updateCameraVectors();
public:
    explicit Camera(unsigned int width, unsigned int height);
    ~Camera();

    static void Init(GLFWwindow *window);

    void ProcessKeyboardInput(GLFWwindow *window);
    void ProcessMouseInput(float xPos, float yPos, bool isPitchConstrained = true);
    void ProcessMouseScroll(float yOffset);

    glm::mat4 GetView();
    glm::mat4 GetProjection() const;
};
