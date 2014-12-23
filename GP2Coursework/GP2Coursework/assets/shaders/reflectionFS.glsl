#version 400

uniform vec3 cameraPosition;

uniform samplerCube cubeTexture;

uniform mat4 view; // view matrix
out vec4 FragColor;

void main() {
	/* reflect ray around normal from eye to surface */
	vec3 incident_eye = normalize(cameraPosition.x);
	vec3 normal = normalize(cameraPosition.y);

	vec3 reflected = reflect(incident_eye, normal);
	// convert from eye to world space
	reflected = vec3(inverse(view) * vec4(reflected, 0.0));

	FragColor = texture(cubeTexture, reflected);
}