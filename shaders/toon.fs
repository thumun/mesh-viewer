#version 400

uniform vec3 LightPosition;
in vec3 norm;
in float vecPos; 

out vec4 FragColor;

// toon shader guide used: 
// https://www.lighthouse3d.com/tutorials/glsl-12-tutorial/toon-shader-version-ii/

void main()
{
    float intensity;
	vec4 color;

	intensity = dot(LightPosition,norm);

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

    // trying the white outline thing 
    // nope logic wrong somewhere 
    // if (vecPos < 0.2f){
    //     color = vec4(1.0, 1.0, 1.0, 1.0);
    // }

    FragColor = color;
}