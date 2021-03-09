//
//  Camera.h
//  LO01
//
//  Created by 馒馒头 on 2021/3/9.
//

#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
    Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
    ~Camera();
    
    // camera attributes
    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;
    // euler angles
    float Pitch;
    float Yaw;
    // camera options
    float WKeySensitivity = 0.1;
    float MouseSensitivity = 0.001;
    float speedZ = 0;
    float speedX = 0;
    
    glm::mat4 GetViewMatrix();
    void ProcessMouseMovement(float xOffset, float yOffset);
    void UpdateCameraPos();
    
private:
    void UpdateCameraVectors();
};



