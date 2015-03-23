#version 410
in vec3 color, normal;
out vec4 frag_color;

//Fixed point light properties
vec3 light_position_world = vec3(0.0, 0.0, 2.0);
vec3 Ls = vec3(1.0, 1.0, 1.0); //White specular light color
vec3 Ld = vec3(0.7, 0.7, 0.7); //Dull white diffuse light color
vec3 La = vec3(0.2, 0.2, 0.2); //Grey ambient color

//Surface reflectance
vec3 Ks = vec3(1.0, 1.0, 1.0); //Fully reflect specular
vec3 Kd = vec3(1.0, 0.5, 0.0); //Orange diffuse surface reflectance 
vec3 Ka = vec3(1.0, 1.0, 1.0); //Fully reflect ambient
float specular_exponent = 100.0; //Specular power



void main () {
  // ambient Intensity
  vec3 Ia = La * Ka;

  vec3 Id = Ld * Kd;

  vec3 Is = Ls * Ks;

  frag_color = vec4 (color, 1.0);
}