#version 460 core

in vec4 v_Color;
in vec2 v_TexCoords;
in float v_TexIndex;

uniform sampler2D u_Textures[32];

out vec4 FragColor;

void main()
{
	FragColor = texture(u_Textures[int(v_TexIndex)], v_TexCoords) * v_Color;
}
