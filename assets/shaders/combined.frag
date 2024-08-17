#version 300 es

precision highp float;

in vec2 TexCoord;
in vec3 FragPos;
in float UseLighting;

uniform sampler2D colorTex;
uniform sampler2D lightTex;
uniform sampler2D debugTex;
uniform sampler2D uiTex;

out vec4 FragColor;

const float offset = 1.0 / 1000.0;

void main() {

    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

    float kernel[9] = float[](
        1.0 / 16., 2.0 / 16., 1.0 / 16.,
        2.0 / 16., 4.0 / 16., 2.0 / 16.,
        1.0 / 16., 2.0 / 16., 1.0 / 16.
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(lightTex, TexCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    col += sampleTex[i] * kernel[i];

    float min_light = 0.02f;
    float min_color = 0.0f;
    vec4 light_lb = vec4(min_light, min_light, min_light, 1.0);
    vec4 color_lb = vec4(min_color, min_color, min_color, 1.0);

    vec4 raw_color = texture(colorTex, TexCoord);
    vec4 color = min(max(vec4(raw_color.rgb, 1.0f), color_lb), vec4(1.0f));
    vec4 light = min(max(vec4(col.rgb, 1.0f), light_lb), vec4(1.0));
    vec4 debug = texture(debugTex, TexCoord);
    vec4 ui = texture(uiTex, TexCoord);

    vec3 diffuse = UseLighting * color.rgb * light.rgb + (1. - UseLighting) * raw_color.rgb;
    FragColor = vec4(diffuse, color.a) + ui + debug;
}