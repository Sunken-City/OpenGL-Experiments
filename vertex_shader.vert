#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

out vec3 normal, eyePosition;

void main () {
  normal = vec3(View * Model * vec4(vertex_normal, 0.0));
  eyePosition = vec3(View * Model * vec4(vertex_position, 1.0));
  
  gl_Position = Projection * vec4 (eyePosition, 1.0);
}