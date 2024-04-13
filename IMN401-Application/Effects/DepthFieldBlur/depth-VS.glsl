#version 460

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

layout (location = 0) in vec3 Position;
out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};
out VTF {
    vec4 v_Center;
};

void main()
{
    vec4 center = View * Model * vec4(Position, 1.0);
	gl_Position = Proj * View * Model * vec4(Position, 1.0);
    v_Center = center;
}
