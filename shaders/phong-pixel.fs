#version 400

in vec4 pEye; 
in vec3 nEye; 

struct LightInfo {
 vec4 Position; // Light position in eye coords.
 vec3 La; // Ambient light intensity
 vec3 Ld; // Diffuse light intensity
 vec3 Ls; // Specular light intensity
};

uniform LightInfo Light;

struct MaterialInfo {
 vec3 Ka; // Ambient reflectivity
 vec3 Kd; // Diffuse reflectivity
 vec3 Ks; // Specular reflectivity
 float Shininess; // Specular shininess factor
};

uniform MaterialInfo Material;

out vec4 FragColor;

void main()
{
   // FragColor = vec4(1.0, 0.0, 0.0, 1.0);

   // vec3 blendAmbient = vec3(0.7, 0.7, 0.7); 
   // vec3 blendDiffuse = vec3(0.7, 0.7, 0.7); 
   // vec3 blendSpecular = vec3(0.7, 0.7, 0.7); 

   // float alpha = 0.7; 

   // vec3 lightColor = vec3(0.1, 0.1, 0.1);
   // vec4 lightPos = vec4(20, 20, 20, 1);

   // vec3 tnorm = normalize(nEye);
   // vec4 eyeCoords = pEye;

   // vec4 lightDir = normalize(lightPos - eyeCoords);

   // vec3 s = normalize(vec3(lightDir - eyeCoords));
   // vec3 v = normalize(-eyeCoords.xyz);
   // vec3 r = reflect(-s, tnorm);

   // vec3 ambient = lightColor * blendAmbient;
   // float sDotN = max( dot(s,tnorm), 0.0 );
   // vec3 diffuse = lightColor * blendDiffuse * sDotN;
   // vec3 spec = vec3(0.0);
   // if( sDotN > 0.0 ){
   //    spec = lightColor * blendSpecular *
   //             pow( max(dot(r,v), 0.0 ), alpha);
   // }
   
   // vec3 LightIntensity = ambient + diffuse + spec;

   vec3 tnorm = nEye;
   vec4 eyeCoords = pEye;

   vec3 s = normalize(vec3(Light.Position - eyeCoords));
   vec3 v = normalize(-eyeCoords.xyz);
   vec3 r = reflect( -s, tnorm );

   vec3 ambient = Light.La * Material.Ka;

   float sDotN = max( dot(s,tnorm), 0.0 );

   vec3 diffuse = Light.Ld * Material.Kd * sDotN;
   
   vec3 spec = vec3(0.0);
   if( sDotN > 0.0 )
      spec = Light.Ls * Material.Ks *
            pow( max( dot(r,v), 0.0 ), Material.Shininess);
   
   vec3 LightIntensity = ambient + diffuse + spec;

   FragColor = vec4(LightIntensity, 1.0);

}
