#version 400

in float ambientColor; 
in vec3 diffuseColor;
in vec3 specularColor;

out vec4 FragColor;

void main()
{
   FragColor = vec4(ambientColor + diffuseColor.x + specularColor.x, 
               ambientColor + diffuseColor.y + specularColor.y, 
               ambientColor + diffuseColor.z + specularColor.z, 1.0);
}
