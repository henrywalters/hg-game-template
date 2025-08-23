#version 300 es

precision highp float;

struct Material {
    vec4 albedo;
    vec4 diffuse;
    vec4 specular;
    vec4 emissive;
    float shininess;
    bool useTexture;
};

uniform Material material;

in vec2 TexCoord;
in vec3 Pos;
in vec3 FragPos;
in vec3 Normal;

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out vec4 gDiffuse;
layout (location = 4) out vec4 gSpecular;
layout (location = 5) out vec4 gEmissive;
layout (location = 6) out vec4 gShininess;

uniform sampler2D albedo;

void main() {
    gPosition = vec4(Pos.xyz, 1.0f);
    gNormal = vec4(normalize(Normal).rgb, 1.0f);

    if (material.useTexture) {
        gAlbedo = texture(albedo, TexCoord);
    } else {
        gAlbedo = material.albedo;
    }

    gDiffuse = material.diffuse;
    gSpecular = material.specular;
    gEmissive = material.emissive;
    gShininess = vec4(material.shininess, 0.0, 0.0, 1.0);
}