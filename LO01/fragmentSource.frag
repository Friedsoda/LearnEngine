#version 330 core
in vec3 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;

void main()
{
    FragColor = mix(texture(ourTexture, texCoord), texture(ourFace, texCoord), 0.2);
}
