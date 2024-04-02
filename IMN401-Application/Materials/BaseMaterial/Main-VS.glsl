#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform float timePassed;

 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };
layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;

out vec3 NormalValue;

void main()
{
    float timeMixed = mix(0.0, 0.005, abs(sin(timePassed)));
    vec3 positionModif = Position + Normal * timeMixed;

	gl_Position = Proj * View* Model * vec4(positionModif,1.0);
 	NormalValue = abs(Normal);
 	
}