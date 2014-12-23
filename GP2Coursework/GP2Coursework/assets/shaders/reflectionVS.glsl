#version 400

in vec3 vertexPosition;
in vec3 vertexNormals;

uniform vec3 cameraPosition;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 Model;

void main() {
	cameraPosition.x = vec3(view * Model * vec4(vertexPosition, 1.0));
	cameraPosition.y = vec3(view * Model * vec4(vertexNormals, 0.0));
	gl_Position = projection * view * Model * vec4(vertexPosition, 1.0);
}