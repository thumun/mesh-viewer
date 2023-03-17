#version 400

// in vec3 ambientColor; 
// in vec3 diffuseColor;
// in vec3 specularColor;

in vec3 LightIntensity;

out vec4 FragColor;

void main()
{
   // FragColor = vec4(ambientColor.x + diffuseColor.x + specularColor.x, 
   //             ambientColor.y + diffuseColor.y + specularColor.y, 
   //             ambientColor.z + diffuseColor.z + specularColor.z, 1.0);
   FragColor = vec4(LightIntensity, 1.0);
}
