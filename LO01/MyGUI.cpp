//
//  MyGUI.cpp
//  LO01
//
//  Created by 馒馒头 on 2021/3/22.
//

#include "MyGUI.h"

MyGUI::MyGUI()
{
    lightColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    lightPos = ImVec4(-2.0f, 2.0f, 0.5f, 1.00f);
    lightSpecular = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    ambient = ImVec4(0.01f, 0.01f, 0.01f, 1.00f);
    specular = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    shininess = 32.0f;
}

void MyGUI::setup()
{
    ImGui::Begin("My engine!");
    ImGui::Text("Light setting:");
    ImGui::InputFloat3("position", (float*)&lightPos);
    ImGui::ColorEdit3("color", (float*)&lightColor);
    ImGui::InputFloat3("light specular", (float*)&lightSpecular);
    ImGui::Text("Material setting:");
    ImGui::InputFloat3("ambient", (float*)&ambient);
    ImGui::InputFloat3("specular", (float*)&specular);
    ImGui::SliderFloat("shininess", &shininess, 1.0f, 128.0f);

//        if (ImGui::Button("Apply"))
//            counter++;
//        ImGui::SameLine();
//        ImGui::Text("counter = %d", counter);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}


glm::vec3 MyGUI::getLightColor()
{
    return glm::vec3(lightColor.x, lightColor.y, lightColor.z);
}


glm::vec3 MyGUI::getLightPos()
{
    return glm::vec3(lightPos.x, lightPos.y, lightPos.z);
}


glm::vec3 MyGUI::getLightAmbient()
{
    glm::vec3 ambientColor = getLightColor() * glm::vec3(0.5f);
    return ambientColor;
}


glm::vec3 MyGUI::getLightDiffuse()
{
    glm::vec3 diffuseColor = getLightColor() * glm::vec3(1.0f);
    return diffuseColor;
}


glm::vec3 MyGUI::getLightSpecular()
{
    return glm::vec3(lightSpecular.x, lightSpecular.y, lightSpecular.z);
}


glm::vec3 MyGUI::getMatAmbient()
{
    return glm::vec3(ambient.x, ambient.y, ambient.z);
}


glm::vec3 MyGUI::getMatSpecular()
{
    return glm::vec3(specular.x, specular.y, specular.z);
}


float MyGUI::getMatShininess()
{
    return shininess;
}
