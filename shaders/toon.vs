#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;

out vec3 norm;

void main(void)
{
    //vec3 norm = normalize(NormalMatrix * gl_Normal);
    //gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;
    //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    norm = normalize(NormalMatrix * vNormals);
    gl_Position = MVP * vec4(vPos, 1.0);
}