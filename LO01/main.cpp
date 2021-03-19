//
//  main.cpp
//  LO01
//
//  Created by 馒馒头 on 2021/2/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

#include <iostream>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

// MARK: Model Data
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};


// MARK: Camera Declare
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));


// MARK: Input Declare
float lastX;
float lastY;
bool firstMouse = true;

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.speedZ = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.speedZ = -1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.speedX = -1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.speedX = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.speedY = -1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.speedY = 1.0f;
    }
    else
    {
        camera.speedX = 0;
        camera.speedY = 0;
        camera.speedZ = 0;
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse == true)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float xOffset, yOffset;
    xOffset = xPos - lastX;
    yOffset = yPos - lastY;
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement(xOffset, yOffset);
}


// MARK: Load Image
unsigned int LoadImageToGPU(const char* fileName, GLint internalFormat, GLenum format, int textureSlot)
{
    unsigned int texBuffer;
    glGenTextures(1, &texBuffer);
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, texBuffer);
    
    int width, height, nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(fileName, &width, &height, &nrChannel, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Load image failed." << std::endl;
    }
    stbi_image_free(data);
    return texBuffer;
}


int main()
{
    // MARK: Open window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);
    
    
    // MARK: Init Shader
    Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
    
    
    // MARK: Init and Load Models to VAO, VBO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(6);
//    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(7);
//    glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(8);
    glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(9);
    
    // MARK: Init and Load Textures
    unsigned int texBufferA;
    texBufferA = LoadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);
    unsigned int texBufferB;
    texBufferB = LoadImageToGPU("awesomeface.jpg", GL_RGBA, GL_RGBA, 3);

    
    // MARK: Prepare MVP Matrices
    glm::mat4 modelMat(1.0f);
    glm::mat4 viewMat(1.0f);
    glm::mat4 projMat(1.0f);
    projMat = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    
    // MARK: Setup lighting
    ImVec4 lightColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    ImVec4 lightPos = ImVec4(10.0f, 10.0f, 5.0f, 1.00f);
    float specularStrength = 1.0f;
    float ambientStrength = 0.5f;
    
    // MARK: Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    
    // MARK: Render loop
    while(!glfwWindowShouldClose(window))
    {
        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
//        int counter = 0;
        ImGui::Begin("My engine!");
        ImGui::InputFloat3("light position", (float*)&lightPos);
        ImGui::ColorEdit3("light color", (float*)&lightColor);
        ImGui::SliderFloat("ambient", &ambientStrength, 0.1f, 2.0f);
        ImGui::SliderFloat("specular", &specularStrength, 1.0f, 10.0f);


//        if (ImGui::Button("Apply"))
//            counter++;
//        ImGui::SameLine();
//        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        
        // Input
        processInput(window);
        
        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        viewMat = camera.GetViewMatrix();

        ImGui::Render();
        for (int i = 0; i < 10; i++)
        {
            // Set model matrix
            modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            
            // Set view and projection matrices if you want.
            //
            
            // Set material -> shader program
            myShader->use();
            // Set material -> textures
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texBufferA);
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, texBufferB);
            // Set material -> uniform
//            glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
//            glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 3);
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 0.5f, 0.31f);
            glUniform1f(glGetUniformLocation(myShader->ID, "specularStrength"), specularStrength);
            glUniform1f(glGetUniformLocation(myShader->ID, "ambientStrength"), ambientStrength);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
            
            // Set model
            glBindVertexArray(VAO);
            
            // Draw call
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Clean up, prepare for next render loop
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera.UpdateCameraPos();
    }
    
    // Optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    // Exit program
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
