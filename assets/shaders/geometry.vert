#version 300 es

precision highp float;

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 Pos;

void main() {
    gl_Position = projection * view * model * vec4(a_vertex, 1.0);
    Pos = vec3(model * vec4(a_vertex, 1.0));
    Normal = normalize((model * vec4(a_normal, 1.0) - (model * vec4(0.0, 0.0, 0.0, 1.0))).xyz);
    FragPos = vec3(gl_Position);
    TexCoord = a_texture;
}