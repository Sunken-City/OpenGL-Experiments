#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 MVP;

out vec3 color, normal;

void main () {
  color = vertex_color;
  normal = vec3(MVP * vec4(vertex_normal, 0.0));
  gl_Position = MVP * vec4 (vertex_position, 1.0);
}