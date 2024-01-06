// Basic Texture Shader
// Compatible with Exodia Game Engine

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec2 v_ScreenCoord;

void main()
{
    v_TexCoord = a_TexCoord;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
    v_ScreenCoord = gl_Position.xy;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec2 v_ScreenCoord;

uniform vec4 u_Color;
uniform float u_TilingFactor;
uniform sampler2D u_Texture;

void main()
{
    float dist = 1.0f - distance(v_ScreenCoord * 0.8f, vec2(0.0f));

    dist = clamp(dist, 0.0f, 1.0f);
    dist = sqrt(dist);

    color = texture(u_Texture, v_TexCoord * u_TilingFactor) * u_Color * dist;
}
