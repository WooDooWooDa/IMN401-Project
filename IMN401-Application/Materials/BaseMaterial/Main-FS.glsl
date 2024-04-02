#version 460


in vec3 NormalValue;
layout (location = 0) out vec4 Color;

void main()
{
	
	Color = vec4(NormalValue, 1.0);
}