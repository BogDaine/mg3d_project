#pragma once
#include "Maths.h"

class Entity;

enum ECameraMovementType
{
    UNKNOWN,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
enum class ECameraMode
{
    FIRST_PERSON,
    THIRD_PERSON,
    STATIONARY_BOUND
};

class Camera
{
private:
    // Default camera values
    const float zNEAR = 0.01f;
    const float zFAR = 500.f;
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float FOV = 45.0f;
    glm::vec3 startPosition;

    ECameraMode m_Mode = ECameraMode::FIRST_PERSON;

    Entity* m_BoundEntity;
    glm::vec3 m_BoundOffset = glm::vec3(4.0f, 0.0f, 0.0f);

public:
    Camera(const int width, const int height, const glm::vec3& position);

    void BindEntity(Entity*);

    void SetMode(const ECameraMode&);

    void Set(const int width, const int height, const glm::vec3& position);

    void Reset(const int width, const int height);

    void Update();

    const glm::mat4 GetViewMatrix() const;

    const glm::vec3 GetPosition() const;

    const glm::mat4 GetProjectionMatrix() const;

    void ProcessKeyboard(ECameraMovementType direction, float deltaTime);
    
    void MouseControl(float xPos, float yPos);
    
    void ProcessMouseScroll(float yOffset);
    
    void SetFirstMouseMove(const bool&);

private:
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

    void UpdateCameraVectors();
   

protected:
    const float cameraSpeedFactor = 20.0f;
    const float mouseSensitivity = 0.1f;

    // Perspective properties
    float zNear;
    float zFar;
    float FoVy;
    int width;
    int height;
    bool isPerspective;

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    // Euler Angles
    float yaw;
    float pitch;

    bool bFirstMouseMove = true;
    float lastX = 0.f, lastY = 0.f;
};
