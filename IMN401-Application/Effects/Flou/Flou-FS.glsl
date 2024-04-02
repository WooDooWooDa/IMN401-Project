#version 460


uniform sampler2D myFBO;
uniform float k;

in vec2 uv;
layout (location = 0) out vec4 Color;
void main()
{
	vec3 c = texture(myFBO,uv).rgb;
	ivec2 size = textureSize(myFBO, 0);

	vec4 blurredColor = vec4(0);
	for (float i = -k; i < k; i++) {
		for (float j= -k; j < k; j++) {
			vec2 offset = vec2(i,j) / size.xy;
			blurredColor += texture(myFBO, uv + offset);
		}
	}

	blurredColor /= (2*k*2*k);
	
	Color = vec4(blurredColor.rgb,1.0);
}