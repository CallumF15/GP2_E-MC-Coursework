#version 150

in vec3 vp; 
in vec3 vn; 
uniform mat4 P, V, M; 
out vec3 pos_eye;
out vec3 n_eye;

void main () {
  pos_eye = vec3 (V * M * vec4 (vp, 1.0));
  n_eye = vec3 (V * M * vec4 (vn, 0.0));
  gl_Position = P * V * M * vec4 (vp, 1.0);
}