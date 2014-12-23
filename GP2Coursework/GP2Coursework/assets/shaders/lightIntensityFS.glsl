#version 150

float exposure;
float decay;
float density;
float weight;

in vec2 texCoordsOut;

uniform vec2 lightPosition;


uniform sampler2D firstPass;
const int NUM_SAMPLES = 100;

void main()
{
	vec2 deltaTextCoord = vec2(texCoordsOut.st - lightPosition.xy);
	vec2 textCoo = texCoordsOut.st;
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