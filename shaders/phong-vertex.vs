#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;

//out vec3 ambientColor; 
out float ambientColor; 
out vec3 diffuseColor;
out vec3 specularColor;

void main()
{

   // maybe change it 
   vec3 lightPos = vec3(10, 0, 0);

   vec3 lightColor = vec3(0.1, 0.1, 0.1);
   vec3 materialColor = vec3(0, 0, 1); // maybe change

   vec3 blendAmbient = vec3(0.7, 0.7, 0.7); 
   vec3 blendDiffuse = vec3(0.7, 0.7, 0.7); 
   vec3 blendSpecular = vec3(0.7, 0.7, 0.7); 

   float alpha = 0.3; 

   ambientColor = dot(blendAmbient,lightColor); 

   vec4 a = ModelViewMatrix*vec4(vPos, 1.0);
   vec3 temp = vec3(a.x, a.y, a.z);

   diffuseColor = blendDiffuse*(dot((lightPos-temp),vNormals))*lightColor*materialColor;

   vec3 r = 2*(dot(lightPos, vNormals))*vNormals - lightPos;
   specularColor = blendSpecular*lightColor*pow((dot((temp-vPos), r)), alpha);

   gl_Position = MVP * vec4(vPos, 1.0);

}
