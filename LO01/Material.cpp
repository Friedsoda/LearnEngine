//
//  Material.cpp
//  LO01
//
//  Created by 馒馒头 on 2021/3/22.
//

#include "Material.h"

Material::Material(Shader* _shader, unsigned int _diffuse, glm::vec3 _ambient, glm::vec3 _specular, float _shininess):
    shader(_shader),
    diffuse(_diffuse),
    ambient(_ambient),
    specular(_specular),
    shininess(_shininess)
{

}

Material::~Material()
{
    
}
