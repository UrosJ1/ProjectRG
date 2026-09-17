//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = aNormal;
    TexCoords = aTexCoords;
    gl_Position = projection * view * vec4(FragPos, 1.0f);
}

//#shader fragment
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightDirection;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform sampler2D texture_earth;

void main(){

    vec3 texColor = texture(texture_earth, TexCoords).rgb;

    vec3 ambient = 0.09f * texColor;

    vec3 norm = normalize(Normal);
    vec3 directionOfLight = normalize(-lightDirection);
    float diff = max(dot(norm, directionOfLight), 0.0f);
    vec3 diffuse = diff * texColor * 0.5f;

    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-directionOfLight, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), 1.0f);
    if (diff <= 0.0f){
        spec = 0.0f;
    }
    vec3 specular = lightColor * spec;

    vec3 finalLight = ambient + diffuse + specular;
    FragColor = vec4(finalLight, 1.0f);
}