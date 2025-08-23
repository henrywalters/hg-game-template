#version 300 es

precision highp float;

in vec2 TexCoord;
in vec3 FragPos;
in float UseLighting;
in vec4 FragPosLightSpace[10];

uniform mat4 lightSpaceMatrix[10];

uniform sampler2D positionTex;
uniform sampler2D normalTex;
uniform sampler2D albedoTex;
uniform sampler2D diffuseTex;
uniform sampler2D specularTex;
uniform sampler2D emissiveTex;
uniform sampler2D shininessTex;

struct Material {
    vec4 albedo;
    vec4 diffuse;
    vec4 specular;
    vec4 emissive;
    float shininess;
    bool useTexture;
};

out vec4 FragColor;

struct Light {
    vec3 position;
    vec4 color;
    float intensity;
};

uniform int numLights;

uniform Light lights[10];

uniform vec3 viewPos;

const float offset = 1.0 / 1000.0;

// Phong shading function
vec3 CalcLight(Light light, vec3 fragPos, vec3 normal, Material material, float shadow) {

    vec3 ambient = 0.0f  * (light.color * material.albedo).xyz;

    // Diffuse
    vec3 lightDelta = light.position - fragPos;
    vec3 lightDir = normalize(lightDelta);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * (light.color * material.diffuse).xyz;

    // Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specStrength = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // 16 for shininess
    vec3 specular = specStrength * (material.specular * light.color).xyz;

    return ambient + (diffuse + specular) * (1.0 - shadow); // * (light.intensity / length(lightDelta));

    // return specular;
}

void main() {
    float min_light = 0.1f;
    float min_color = 0.0f;
    vec4 light_lb = vec4(min_light, min_light, min_light, 1.0);
    vec4 color_lb = vec4(min_color, min_color, min_color, 1.0);

    vec3 normal = texture(normalTex, TexCoord).xyz;
    vec4 position = texture(positionTex, TexCoord);

    Material material;
    material.albedo = texture(albedoTex, TexCoord);
    material.diffuse = texture(diffuseTex, TexCoord);
    material.specular = texture(specularTex, TexCoord);
    material.emissive = texture(emissiveTex, TexCoord);
    material.shininess = texture(shininessTex, TexCoord).r;

    vec3 lighting = vec3(1.0);

    for (int i = 0; i < numLights; i++) {
        //float shadow = CalcShadow(transpose(lightSpaceMatrix[i]) * position, i, position.xyz, normal, lights[i].position);
        lighting += CalcLight(lights[i], position.xyz, normal, material, 1.0);
    }

    FragColor = vec4(lighting, 1.0);

}