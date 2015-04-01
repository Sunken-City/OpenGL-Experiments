#version 410
in vec3 color, normal, lightIntensity;
out vec4 frag_color;

void main () {
  frag_color = vec4 (lightIntensity, 1.0);
}