#include "Camera.h"
#include "Entity.h"

Camera::Camera(const int width, const int height, const glm::vec3& position)

{
    startPosition = position;
    Set(width, height, position);
}

void Camera::ColisionCheck()
{
    std::vector<Vertex>* HeightMap;
    int imgWidth, imgHeight;
    m_SceneRef->HeightmapInfo(HeightMap, imgWidth, imgHeight);

    //std::cout << HeightMap->size() << std::endl;
    float TerrainHeight;
    //auto TerrainPos = 

    float terrainX = (position.x / m_SceneRef->TerrainScale().x) * imgWidth - m_SceneRef->TerrainTranslation().x / m_SceneRef->TerrainScale().x * imgWidth;
    float terrainZ = (position.z / m_SceneRef->TerrainScale().z) * imgHeight - m_SceneRef->TerrainTranslation().z / m_SceneRef->TerrainScale().z * imgHeight;

    //std::cout << terrainX << "   " << terrainZ << " " << std::endl;

    if (terrainX < imgWidth && terrainX >= 0 && terrainZ < imgHeight && terrainZ > 0)
    {
        TerrainHeight = HeightMap->operator[]((int)terrainX* imgWidth + terrainZ).Position.y * m_SceneRef->TerrainScale().y;
        //std::cout << TerrainHeight << std::endl;
        if (position.y < TerrainHeight + 0.2)
            position.y = TerrainHeight + 0.2;
    }

}

void Camera::BindEntity(Entity* entity)
{
    m_BoundEntity = entity;
}

void Camera::SetSceneRef(Scene *scene)
{
    m_SceneRef = scene;
}

void Camera::CycleModes()
{
    m_Mode = static_cast<ECameraMode>(static_cast<int>(m_Mode) + 1);
    if (m_Mode == ECameraMode::MAX)
        m_Mode = static_cast<ECameraMode>(static_cast<int>(0));
}

void Camera::SetMode(const ECameraMode &mode)
{
    m_Mode = mode;
}

void Camera::Set(const int width, const int height, const glm::vec3& position)

{
    this->isPerspective = true;
    this->yaw = YAW;
    this->pitch = PITCH;

    this->FoVy = FOV;
    this->width = width;
    this->height = height;
    this->zNear = zNEAR;
    this->zFar = zFAR;

    this->worldUp = glm::vec3(0, 1, 0);
    this->position = position;

    lastX = width / 2.0f;
    lastY = height / 2.0f;
    bFirstMouseMove = true;

    UpdateCameraVectors();
}

void Camera::Reset(const int width, const int height)

{
    Set(width, height, startPosition);
}

void Camera::SetSonar(const bool& val)
{
    m_Sonar = val;
}

bool Camera::Sonar() const
{
    return m_Sonar;
}

void Camera::Update()
{
    UpdateCameraVectors();
    if (m_Mode != ECameraMode::FIRST_PERSON && m_SceneRef && m_SceneRef->HasTerrain())
    {
    }
        ColisionCheck();

}

const glm::mat4 Camera::GetViewMatrix() const
{
    // Returns the View Matrix
    if(m_Mode == ECameraMode::STATIONARY_BOUND)
        return glm::lookAt(position, position + glm::normalize(m_BoundEntity->Position() - position), up);
    return glm::lookAt(position, position + forward, up);
}

const glm::vec3 Camera::GetPosition() const
{
    return position;
}

const glm::mat4 Camera::GetProjectionMatrix() const
{
    glm::mat4 Proj = glm::mat4(1);
    if (isPerspective) {
        float aspectRatio = ((float)(width)) / height;
        Proj = glm::perspective(glm::radians(FoVy), aspectRatio, zNear, zFar);
    }
    else {
        float scaleFactor = 2000.f;
        Proj = glm::ortho<float>(
            -width / scaleFactor, width / scaleFactor,
            -height / scaleFactor, height / scaleFactor, -zFar, zFar);
    }
    return Proj;
}

void Camera::ProcessKeyboard(ECameraMovementType direction, float deltaTime)
{
    float increment;
    switch (m_Mode)
    {
    case ECameraMode::FIRST_PERSON:

        increment = (float)(cameraSpeedFactor * deltaTime);
        switch (direction) {
        case ECameraMovementType::FORWARD:
            position += forward * increment;
            break;
        case ECameraMovementType::BACKWARD:
            position -= forward * increment;
            break;
        case ECameraMovementType::LEFT:
            position -= right * increment;
            break;
        case ECameraMovementType::RIGHT:
            position += right * increment;
            break;
        case ECameraMovementType::UP:
            position += up * increment;
            break;
        case ECameraMovementType::DOWN:
            position -= up * increment;
            break;
        }
        break;

    case ECameraMode::THIRD_PERSON:

        increment = (float)(m_ThirdPersonSpeed * deltaTime);

        switch (direction) {
        case ECameraMovementType::FORWARD:
            m_BoundOffset.y += increment;
            break;
        case ECameraMovementType::BACKWARD:
            m_BoundOffset.y -= increment;
            break;
        case ECameraMovementType::LEFT:
            m_BoundOffset.x -= increment;
            break;
        case ECameraMovementType::RIGHT:
            m_BoundOffset.x += increment;
            break;
        case ECameraMovementType::UP:
            m_BoundOffset.z += increment;
            break;
        case ECameraMovementType::DOWN:
            m_BoundOffset.z -= increment;
            break;
        }

        break;
    }
}

void Camera::MouseControl(float xPos, float yPos)
{
    if (bFirstMouseMove) {
        lastX = xPos;
        lastY = yPos;
        bFirstMouseMove = false;
    }

    float xChange = xPos - lastX;
    float yChange = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    if (fabs(xChange) <= 1e-6 && fabs(yChange) <= 1e-6) {
        return;
    }
    xChange *= mouseSensitivity;
    yChange *= mouseSensitivity;

    ProcessMouseMovement(xChange, yChange);
}

void Camera::ProcessMouseScroll(float yOffset)
{
    if (FoVy >= 1.0f && FoVy <= 90.0f) {
        FoVy -= yOffset;
    }
    if (FoVy <= 1.0f)
        FoVy = 1.0f;
    if (FoVy >= 90.0f)
        FoVy = 90.0f;
}

void Camera::SetFirstMouseMove(const bool&value)
{
    bFirstMouseMove = value;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
    yaw += xOffset;
    pitch += yOffset;

    //std::cout << "yaw = " << yaw << std::endl;
    //std::cout << "pitch = " << pitch << std::endl;

    // Avem grijã sã nu ne dãm peste cap
    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // Se modificã vectorii camerei pe baza unghiurilor Euler
    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 newForward;

    this->forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->forward.y = sin(glm::radians(pitch));
    this->forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->forward = glm::normalize(this->forward);

    // Calculate the new forward vector
    switch (m_Mode)
    {
    case ECameraMode::STATIONARY_BOUND:
    case ECameraMode::FIRST_PERSON:
        
        break;

    //case ECameraMode::STATIONARY_BOUND:
       /* newForward = m_BoundEntity->Position() - position;
       if (glm::length(newForward) == 0)
            break;
        this->forward = glm::normalize(newForward);*/
        //break;

    case ECameraMode::THIRD_PERSON:
        position = m_BoundEntity->Position() + m_BoundEntity->Forward() * m_BoundOffset.z +
            m_BoundEntity->Up() * m_BoundOffset.y +
            m_BoundEntity->Right() * m_BoundOffset.x;
        newForward = m_BoundEntity->Position() - position;

        if (glm::length(newForward) == 0)
            break;

        this->forward = glm::normalize(newForward);
        break;
    }
        // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(forward, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, forward));
}