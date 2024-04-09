#version 460

uniform sampler2D albedo;

in VTF {
vec3 v_UV;
};


layout (location = 0) out vec4 Color;


void main()
{
	vec4 mainTexture = texture2D(albedo, v_UV.xy);
    Color = mainTexture;
}