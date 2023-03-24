#version 400

in vec4 pEye; 
in vec3 nEye; 
in vec3 v; 
in vec3 n; 

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

// toon shader guide used: 
// https://www.lighthouse3d.com/tutorials/glsl-12-tutorial/toon-shader-version-ii/

void main()
{
   vec3 tnorm = nEye;
   vec4 eyeCoords = pEye;

   vec3 s = normalize(vec3(Light.Position - eyeCoords));
   
    float intensity = dot(s,tnorm);
    vec4 color; 

	if (intensity > 0.95f){
		color = vec4(1.0,0.5,0.5,1.0);
    }
	else if (intensity > 0.5f){
        color = vec4(0.6,0.3,0.3,1.0);
    }
	else if (intensity > 0.25f){
        color = vec4(0.4,0.2,0.2,1.0);
    }	
	else {
        color = vec4(0.2,0.1,0.1,1.0); 
    }

    // looks bad with the white outline thing 
    // if (dot(normalize(v), normalize(n)) < 0.00001f){
    //     color = vec4(1.0, 1.0, 1.0, 1.0);
    // }

    FragColor = color;

}