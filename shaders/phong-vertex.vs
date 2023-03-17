#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;

out vec3 ambientColor; 
out vec3 diffuseColor;
out vec3 specularColor;

void main()
{

   // maybe change it 
   vec3 lightPos = vec3(10, 0, 0);

   vec3 lightDir = normalize(lightPos); 

   vec3 eNor = normalize(NormalMatrix * vNormals); 
   vec4 eyeCoords = ModelViewMatrix*vec4(vPos, 1.0);

   vec3 lightColor = vec3(0.1, 0.1, 0.1);
   vec3 materialColor = vec3(0, 0, 1); // maybe change

   vec3 blendAmbient = vec3(0.7, 0.7, 0.7); 
   vec3 blendDiffuse = vec3(0.7, 0.7, 0.7); 
   vec3 blendSpecular = vec3(0.7, 0.7, 0.7); 

   float alpha = 0.3; 

   ambientColor = blendAmbient * lightColor; 
   
   vec3 temp = vec3(eyeCoords.x, eyeCoords.y, eyeCoords.z);

   diffuseColor = blendDiffuse * 
                  max(dot(normalize(lightDir-temp),eNor), 0.0) * 
                  lightColor*materialColor;

   vec3 r = 2*dot(lightDir, eNor)*eNor - lightDir;
   specularColor = blendSpecular * 
                  lightColor * 
                  pow(dot(normalize(temp-vPos), normalize(r)), alpha);

   gl_Position = MVP * vec4(vPos, 1.0);

}
