#version 460

const float pi = 3.14159265;

uniform sampler2D myFBO;
uniform sampler2D depthFBO;
uniform vec2 direction;

in vec2 uv;
layout (location = 0) out vec4 Color;
ivec2 texSize = textureSize(myFBO,0);
void main()
{
    float focus = 0.1;
	float dofSigma = 5.0; 
	float blurSize = 40;
	vec2 texOffset = direction / texSize;

	vec4 depth = texture( depthFBO, uv );
    float dofblur = abs( depth.x - focus );
	float numBlurPixelsPerSide = float(blurSize / 2) * dofblur; 

	vec3 incrementalGaussian;
    incrementalGaussian.x = 1.0 / (sqrt(2.0 * pi) * dofSigma);
    incrementalGaussian.y = exp(-0.5 / (dofSigma * dofSigma));
    incrementalGaussian.z = incrementalGaussian.y * incrementalGaussian.y;
	
	vec4 avgValue = vec4(0.0, 0.0, 0.0, 0.0);
    float coefficientSum = 0.0;

	for (float i = 0; i < numBlurPixelsPerSide; i++) { 
        avgValue += texture(myFBO, uv - i * texOffset) * incrementalGaussian.x;         
        avgValue += texture(myFBO, uv + i * texOffset) * incrementalGaussian.x;         
        coefficientSum += 2.0 * incrementalGaussian.x;
        incrementalGaussian.xy *= incrementalGaussian.yz;
    }

    Color = (avgValue / coefficientSum);
}
