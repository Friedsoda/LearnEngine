//
//  MyGUI.hpp
//  LO01
//
//  Created by 馒馒头 on 2021/3/22.
//

#ifndef MyGUI_h
#define MyGUI_h

#include "imgui.h"
#include <glm.hpp>
#include "Material.h"

class MyGUI
{
public:
    ImVec4 lightColor;
    ImVec4 lightPos;
    ImVec4 lightAmbient;
    ImVec4 lightDiffuse;
    ImVec4 lightSpecular;
    ImVec4 ambient;
    ImVec4 specular;
    float shininess;
    
    MyGUI();
    ~MyGUI();
    void setup();
    glm::vec3 getLightPos();
    glm::vec3 getLightColor();
    glm::vec3 getLightAmbient();
    glm::vec3 getLightDiffuse();
    glm::vec3 getLightSpecular();
    glm::vec3 getMatAmbient();
    glm::vec3 getMatSpecular();
    float getMatShininess();
};

#endif /* MyGUI_h */
