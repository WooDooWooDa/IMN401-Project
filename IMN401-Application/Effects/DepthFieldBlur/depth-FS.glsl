#version 460
#ifdef GL_ES
precision mediump float;
precision mediump int;
#endif

in VTF {
    vec4 v_Center;
};
uniform float maxDepth;

layout (location = 0) out vec4 Color;

void main() {
    float maxDepth = 100;
    float depth = clamp(abs(v_Center.z)/maxDepth, 0.0, 1.0);
    Color = vec4(vec3(depth), 1.0);
}
