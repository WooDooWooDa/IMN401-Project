#version 460

uniform sampler2D albedo;

in VTF {
vec3 v_UV;
};


layout (location = 0) out vec4 Color;


void main()
{
	vec4 mainTexture = texture2D(albedo, v_UV.xy);
	if(mainTexture.a <0.5)
		discard;
    Color = mainTexture * 0.8;
	Color.a = 1.0;
}