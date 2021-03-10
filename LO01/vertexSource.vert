#version 330 core
layout (location = 6) in vec3 aPos;
layout (location = 9) in vec3 aNormal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0);
    FragPos = (modelMat * vec4(aPos, 1.0)).xyz;
    Normal = mat3(transpose(inverse(modelMat))) * aNormal;
}
