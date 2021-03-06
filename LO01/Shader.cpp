//
//  Shader.cpp
//  LO01
//
//  Created by 馒馒头 on 2021/3/4.
//

#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::ifstream vertexFile;
    std::ifstream fragmentFile;
    std::stringstream vertexStream;
    std::stringstream fragmentStream;
    
    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        if(!vertexFile.is_open() || !fragmentFile.is_open())
        {
            throw std::exception();
        }
        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();
        
        vertexString = vertexStream.str();
        fragmentString = fragmentStream.str();
        
        vertexSource = vertexString.c_str();
        fragmentSource = fragmentString.c_str();
        
        unsigned int vertex, fragment;
        
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSource, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSource, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
    }
    catch(const std::exception& ex)
    {
        printf(ex.what());
    }
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
    int success;
    char infoLog[512];
    
    if (type != "PROGRAM")
    {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
           glGetShaderInfoLog(ID, 512, NULL, infoLog);
           std::cout << "Shader compile error: " << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
          glGetProgramInfoLog(ID, 512, NULL, infoLog);
          std::cout << "Program linking error: " << infoLog << std::endl;
        }
    }
}

//Shader::~Shader()
//{
//    
//}
