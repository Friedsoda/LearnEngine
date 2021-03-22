//
//  Material.hpp
//  LO01
//
//  Created by 馒馒头 on 2021/3/22.
//

#ifndef Material_h
#define Material_h

#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Material
{
public:
    Shader* shader;
    unsigned int diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
    float shininess;
    
    Material(Shader* _shader, unsigned int _diffuse, glm::vec3 _ambient, glm::vec3 _specular, float _shininess);
    ~Material();
};


#endif /* Material_h */
