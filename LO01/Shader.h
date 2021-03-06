//
//  Shader.hpp
//  LO01
//
//  Created by 馒馒头 on 2021/3/4.
//

#ifndef Shader_h
#define Shader_h

#include <string>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    std::string vertexString;
    std::string fragmentString;
    const char* vertexSource;
    const char* fragmentSource;
    unsigned int ID;   // Shader program ID
    void use();
    
private:
    void checkCompileErrors(unsigned int ID, std::string type);
};

#endif /* Shader_h */
