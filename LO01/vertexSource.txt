#version 330 core
layout (location = 6) in vec3 aPos;
layout (location = 7) in vec3 aColor;
layout (location = 8) in vec2 aTexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 vertexColor;
out vec2 texCoord;

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0);
    vertexColor = aColor;
    texCoord = aTexCoord;
}
