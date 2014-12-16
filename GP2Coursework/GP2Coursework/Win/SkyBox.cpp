#include "SkyBox.h"

SkyBox::SkyBox()
{

}

SkyBox::~SkyBox()
{

}

void SkyBox::destroy(){
	glDeleteTextures(1, &cubeTexture);
}

void SkyBox::drawSkyBox(){
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &cubeTexture);

	glBindTexture(GL_TEXTURE_2D, cubeTexture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	
}

void SkyBox::loadCubeTexture(const std::string& PosXFilename,
	const std::string& NegXFilename,
	const std::string& PosYFilename,
	const std::string& NegYFilename,
	const std::string& PosZFilename,
	const std::string& NegZFilename){


	LoadCubeSides(PosXFilename, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	LoadCubeSides(NegXFilename, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	LoadCubeSides(PosYFilename, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	LoadCubeSides(NegYFilename, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	LoadCubeSides(PosZFilename, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	LoadCubeSides(NegZFilename, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
}



//Getters & setters below:

GLuint SkyBox::getCubeTexture(){
	return cubeTexture;
}