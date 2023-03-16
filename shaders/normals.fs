#version 400

in vec3 normalOutput; 
out vec4 FragColor;
void main()
{
   FragColor = vec4(normalOutput.x, normalOutput.y, normalOutput.z, 1.0);

}
