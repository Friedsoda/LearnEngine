#version 330 core
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform float ambientStrength;
uniform float specularStrength;

void main()
{
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 norm = normalize(Normal);
    vec3 cameraVec = normalize(cameraPos - FragPos);
    vec3 reflectVec = reflect(-lightDir, norm);
    
    vec3 ambient = ambientStrength * lightColor;
    vec3 diffuse = max(dot(lightDir, norm), 0) * lightColor;
    vec3 specular = specularStrength * pow(max(dot(reflectVec, cameraVec), 0), 64) * lightColor;

    FragColor = vec4((ambient + diffuse + specular) * objColor, 1.0);
}
