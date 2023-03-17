#version 400

in vec4 pEye; 
in vec3 nEye; 

out vec4 FragColor;

void main()
{
   // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
   FragColor = vec4(pEye.x + nEye.x, pEye.y + nEye.y, pEye.z + nEye.z, 1.0);

}
