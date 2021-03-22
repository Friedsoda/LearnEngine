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

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

