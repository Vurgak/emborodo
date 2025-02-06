#version 410 core

in vec2 v_TexCoords;

out vec4 o_Color;

uniform sampler2D u_Texture;

void main()
{
    o_Color = vec4(1.0, 0.0, 0.0, 1.0); //texture2D(u_Texture, v_TexCoords);
}
