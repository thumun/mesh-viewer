#version 400

uniform sampler2D diffuseTexture;

in vec3 LightIntensity;
in vec2 uv; 

out vec4 FragColor;

void main()
{
   //vec3 c = texture(diffuseTexture, uv).xyz;
   //vec3 color = LightIntensity*c;
   //FragColor = vec4(color, 1.0);

   FragColor = vec4(LightIntensity, 1.0);
}
