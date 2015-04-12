#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 vertex_normal;


//Fixed point light properties
vec4 lightPosition = vec4(0.0, 0.0, 7.0, 0.0);
vec3 Ls = vec3(1.0, 1.0, 1.0); //White specular light color
vec3 Ld = vec3(0.7, 0.7, 0.7); //Dull white diffuse light color
vec3 La = vec3(0.2, 0.2, 0.2); //Grey ambient color

//Surface reflectance
vec3 Ks = vec3(1.0, 1.0, 1.0); //Fully reflect specular
vec3 Kd = vec3(1.0, 0.5, 0.0); //Orange diffuse surface reflectance 
vec3 Ka = vec3(1.0, 1.0, 1.0); //Fully reflect ambient
float specularExponent = 50.0; //Specular power

uniform mat4 MVP;
uniform mat4 Model;
uniform mat4 View;

out vec3 color, normal, lightIntensity;

void main () {
  normal = vec3(MVP * vec4(vertex_normal, 0.0));
  vec4 eyeCoords = Model * View * vec4(vertex_position, 1.0);
  
  vec3 s = normalize(vec3(lightPosition - eyeCoords));
  vec3 v = normalize(-eyeCoords.xyz);
  vec3 r = reflect(-s, normal);
  vec3 ambient = La * Ka;
  float sDotN = max(dot(s, normal), 0.0);
  vec3 diffuse = Ld * Kd * sDotN;
  vec3 spec = vec3(0.0);
  if(sDotN > 0.0)
	spec = Ls * Ks * pow(max(dot(r,v), 0.0), specularExponent);

  lightIntensity = ambient + diffuse + spec;
  color = vertex_color;
  gl_Position = MVP * vec4 (vertex_position, 1.0);
}