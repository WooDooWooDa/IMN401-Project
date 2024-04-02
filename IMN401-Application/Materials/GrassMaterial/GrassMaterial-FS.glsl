#version 460

uniform sampler2D albedo;
uniform sampler2D alpha;

in VTF {
vec3 vL;
vec3 vV;
vec3 vN;
vec3 v_UV;
};


layout (location = 0) out vec4 Color;


void main()
{
	vec4 mainTexture = texture2D(albedo, v_UV.xy);
    vec4 alphaTexture = texture2D(alpha, v_UV.xy);

    // Use the alpha value from the alpha mask to control the transparency
    Color = mainTexture;
}