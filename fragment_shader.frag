#version 410
in vec3 normal;
in vec4 eyeCoords;
out vec4 frag_color;


//Fixed point light properties
vec4 lightPosition = vec4(-10, 10, 10.0, 0.0);
vec3 Ls = vec3(1.0, 1.0, 1.0); //White specular light color
vec3 Ld = vec3(0.7, 0.7, 0.7); //Dull white diffuse light color
vec3 La = vec3(0.2, 0.2, 0.2); //Grey ambient color

//Surface reflectance
vec3 Ks = vec3(1.0, 1.0, 1.0); //Fully reflect specular
vec3 Kd = vec3(1.0, 0.5, 0.0); //Orange diffuse surface reflectance 
vec3 Ka = vec3(1.0, 1.0, 1.0); //Fully reflect ambient
float specularExponent = 100.0; //Specular power


void main () 
{
  vec3 s = normalize(vec3(lightPosition - eyeCoords));
  vec3 v = normalize(-eyeCoords.xyz);
  vec3 r = reflect(-s, normal);
  vec3 ambient = La * Ka;
  float sDotN = max(dot(s, normal), 0.0);
  vec3 diffuse = Ld * Kd * sDotN;
  vec3 spec = vec3(0.0);
  if(sDotN > 0.0)
	spec = Ls * Ks * pow(max(dot(r,v), 0.0), specularExponent);

  vec3 lightIntensity = ambient + diffuse + spec;

  frag_color = vec4 (lightIntensity, 1.0);
}