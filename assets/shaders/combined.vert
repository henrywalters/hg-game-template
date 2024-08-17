#version 300 es

precision highp float;

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float useLighting;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out float UseLighting;

void main() {
    gl_Position = projection * view * model * vec4(a_vertex, 1.0);
    Normal = a_normal;
    FragPos = vec3(gl_Position);
    TexCoord = a_texture;
    UseLighting = useLighting;
}