#version 410 core

in vec2 v_TexCoords;

out vec4 o_Color;

uniform sampler2D u_Texture;

void main()
{
    o_Color = texture2D(u_Texture, v_TexCoords);
}
