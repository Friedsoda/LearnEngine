//
//  Camera.cpp
//  LO01
//
//  Created by 馒馒头 on 2021/3/9.
//

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
    Position = position;
    WorldUp = worldup;
    Forward = glm::normalize(target - position);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Right, Forward));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
    Position = position;
    WorldUp = worldup;
    Pitch = pitch;
    Yaw = yaw;
    UpdateCameraVectors();
}

Camera::~Camera()
{
    ;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset)
{
    Pitch += yOffset * MouseSensitivity;
    Yaw += xOffset * MouseSensitivity;
    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
    Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right));
}

void Camera::UpdateCameraPos()
{
    Position += (Forward * speedZ + Right * speedX + Up * speedY) * KeySensitivity;
}
