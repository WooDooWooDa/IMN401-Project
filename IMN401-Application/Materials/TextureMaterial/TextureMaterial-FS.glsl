#version 460



uniform vec4 Phong;
uniform vec3 diffuseAlbedo;
uniform vec3 specularColor;
uniform sampler2D albedo;
uniform sampler2D alpha;
uniform sampler2D normalMap;
uniform bool hasAO;
uniform sampler2D aoMap;

in VTF {
vec3 LightColor;
vec3 vL;
vec3 vV;
vec3 vN;
vec3 v_UV;
};


layout (location = 0) out vec4 Color;


void main()
{
	vec3 L = normalize(vL);
	vec3 V = normalize(vV);
	vec3 N = normalize(vN);

	vec4 mainTexture = texture2D(albedo, v_UV.xy);
	if (hasAO)
		mainTexture *= texture2D(aoMap, v_UV.xy);
	vec4 secondaryTexture = texture2D(alpha, v_UV.xy);
	vec4 normalTexture = texture2D(normalMap, v_UV.xy);
	normalTexture = (normalTexture * 2) - 1;

	float Id = max(0,dot(L,normalTexture.xyz));
	float Is = pow(max(0,dot(reflect(-L,normalTexture.xyz),V)),Phong.w);

	vec3 mixedColor = mix(mainTexture, secondaryTexture, secondaryTexture.w).xyz;
	Color.xyz = Phong.x*mixedColor + (Phong.y*Id*mixedColor + Phong.z*Is) * LightColor;
	Color.w = 1.0;
}