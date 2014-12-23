#version 150

out vec4 FragColor;
in vec2 textureCoords;

uniform sampler2D texture0;

vec2 boxFilter[4] = vec2[4](vec2(0.0002f, 0.002f), vec2(-0.002f, 0.002f), vec2(0.002f, -0.002f), vec2(-0.002f, -0.002f));

void main()
{
	vec3 colour = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 4; i++)
	{
		colour += texture(texture0, textureCoords + boxFilter[i]).xyz;
	}
	FragColor = vec4(colour, 1.0);
}

float exposure;
float decay;
float density;
float weight;

uniform vec2 lightPosition;
uniform sampler2D firstPass;
const int NUM_SAMPLES = 100;

void main()
{
	vec2 deltaTextCoord = vec2(gl_TexCoord[0].st - lightPositionOnScreen.xy);
	vec2 textCoo = gl_TexCoord[0].st;
	deltaTextCoord *= 1.0 / float(NUM_SAMPLES) * density;
	float illuminationDecay = 1.0;


	for (int i = 0; i < NUM_SAMPLES; i++)
	{
		textCoo -= deltaTextCoord;
		vec4 sample = texture2D(firstPass, textCoo);

		sample *= illuminationDecay * weight;

		gl_FragColor += sample;

		illuminationDecay *= decay;
	}
	gl_FragColor *= exposure;
}