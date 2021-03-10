#version 330 core
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 ambient;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

void main()
{
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 reflectVec = reflect(-lightDir, Normal);
    vec3 cameraVec = normalize(cameraPos - FragPos);
    
    vec3 diffuse = max(dot(lightDir, Normal), 0) * lightColor;
    vec3 specular = pow(max(dot(reflectVec, cameraVec), 0), 1) * lightColor;

    FragColor = vec4((ambient + diffuse + specular) * objColor, 1.0);
}
