#version 460



uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform vec3 PosCam;
uniform vec3 PosLum;
uniform float Time;

uniform sampler2D dispMap;
uniform float dispFactor;

 out gl_PerVertex {
        vec4 gl_Position;
        float gl_PointSize;
        float gl_ClipDistance[];
    };
layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 TextureCoord;
layout (location = 4) in vec4 Tangente;



out VTF {
vec3 vL;
vec3 vV;
vec3 vN;
vec3 v_Color;
};



void main()
{
    vec3 Pos = Position;

    //Pos += (0.5*cos(2.0*Time)+0.5)*0.01 * Normal;

    vec4 dv = texture2D(dispMap, TextureCoord.xy);
    float df = 0.30*dv.x + 0.59*dv.y + 0.11*dv.z;
    vec4 newVertexPos = vec4(Normal * df * dispFactor, 0.0);
	gl_Position = Proj * View * Model * vec4(Pos, 1.0);

 	
 	vN =normalize(Normal);

    vec3 vB = cross(vN, Tangente.xyz);

    mat3 TBN = mat3(Tangente.xyz, vB, vN);
    TBN = transpose(TBN);

    vL = TBN * (PosLum-Pos);
    vV = TBN * (PosCam-Pos);
    vN = TBN * vN;

    v_Color = TextureCoord;
}
