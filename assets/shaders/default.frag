#version 410 core

in vec2 v_TexCoords;

out vec4 f_Color;

uniform sampler2D u_Texture;

uniform float u_AmbientLightStrength;
uniform vec3 u_AmbientLightColor;

void main()
{
    vec4 ambientLight = vec4(u_AmbientLightColor * u_AmbientLightStrength, 1.0);
    f_Color = texture2D(u_Texture, v_TexCoords) * ambientLight;
}
