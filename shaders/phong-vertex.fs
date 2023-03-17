#version 400

in vec3 ambientColor; 
in vec3 diffuseColor;
in vec3 specularColor;

out vec4 FragColor;

void main()
{
   FragColor = vec4(ambientColor.x + diffuseColor.x + specularColor.x, 
               ambientColor.y + diffuseColor.y + specularColor.y, 
               ambientColor.z + diffuseColor.z + specularColor.z, 1.0);
}
