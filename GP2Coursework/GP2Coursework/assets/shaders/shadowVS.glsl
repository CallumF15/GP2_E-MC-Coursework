#version 150

uniform mat4 ShadowMatrix;

in vec3 vertexPosition;
in vec3 vertexNormals;
in vec2 vertexTexCoords;

out vec3 vertexNormalOut;
out vec3 cameraDirectionOut;
out vec2 texCoordsOut;
out vec3 lightDirectionOut;

uniform mat4 MVP;
uniform mat4 Model;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
	vertexNormalOut = normalize(Model*vec4(vertexNormals, 0.0f)).xyz;
	vec3 worldPos = (Model*vec4(vertexPosition, 1.0)).xyz;
	cameraDirectionOut = normalize(cameraPosition - worldPos);
    lightDirectionOut=normalize(lightPosition-worldPos);
	
	texCoordsOut = vertexTexCoords;
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}