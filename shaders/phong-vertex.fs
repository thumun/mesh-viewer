#version 400

uniform sampler2D diffuseTexture;
uniform bool isTexture; 

in vec3 LightIntensity;
in vec2 uv; 

out vec4 FragColor;

void main()
{
   if (isTexture){
      vec3 c = texture(diffuseTexture, uv*10.0f).xyz;
      vec3 color = LightIntensity*c;
      FragColor = vec4(color, 1.0);
   } else { 
      FragColor = vec4(LightIntensity, 1.0);
   }

   

   
}
