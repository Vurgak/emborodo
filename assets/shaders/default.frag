#version 430 core

in vec3 v_Normal;
in vec2 v_TexCoord;

out vec4 f_Color;

uniform sampler2D u_Texture;

uniform vec3 u_AmbientLightColor;
uniform float u_AmbientLightStrength;

uniform vec3 u_DirectionalLightDirection;

void main()
{
    vec3 ambientLight = u_AmbientLightColor * u_AmbientLightStrength;

    float directionalLightStrength = max(dot(normalize(v_Normal), normalize(-u_DirectionalLightDirection)), 0.0);
    vec3 directionalLight = u_AmbientLightColor * directionalLightStrength;

    f_Color = texture2D(u_Texture, v_TexCoord) * vec4(ambientLight + directionalLight, 1.0);
}
