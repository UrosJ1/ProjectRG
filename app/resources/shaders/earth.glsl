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
out vec4 FragColorMoon;

uniform vec3 lightPos;
uniform vec3 lightDirection;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 lightPosMoon;
uniform vec3 lightDirectionMoon;
uniform vec3 viewPosMoon;
uniform vec3 lightColorMoon;

uniform sampler2D texture_earth;
uniform sampler2D texture_earth_Moon;

void main(){
    //sun
    vec3 texColor = texture(texture_earth, TexCoords).rgb;

    vec3 ambient = 0.09f * texColor;

    vec3 norm = normalize(Normal);
    vec3 directionOfLight = normalize(-lightDirection);
    float diff = max(dot(norm, directionOfLight), 0.0f);
    vec3 diffuse = diff * texColor * 0.5f;

    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-directionOfLight, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), 1.0f);
    vec3 specular = lightColor * spec;

    vec3 finalLight = ambient + diffuse + specular;
    FragColor = vec4(finalLight, 1.0f);
    //moon
    vec3 texColorMoon = texture(texture_earth_Moon, TexCoords).rgb;

    vec3 ambientMoon = 0.09f * texColorMoon;

    vec3 normMoon = normalize(Normal);
    vec3 directionOfLightMoon = normalize(-lightDirectionMoon);
    float diffMoon = max(dot(normMoon, directionOfLightMoon), 0.0f);
    vec3 diffuseMoon = diffMoon * texColorMoon * 0.5f;

    vec3 viewDirectionMoon = normalize(viewPosMoon - FragPos);
    vec3 reflectDirectionMoon = reflect(-directionOfLightMoon, norm);
    float specMoon = pow(max(dot(viewDirectionMoon, reflectDirectionMoon), 0.0f), 1.0f);
    if (diffMoon <= 0.0f){
        specMoon = 0.0f;
    }
    vec3 specularMoon = lightColorMoon * specMoon;

    vec3 finalLightMoon = ambientMoon + diffuseMoon + specularMoon;
    FragColorMoon = vec4(finalLightMoon, 1.0f);
}