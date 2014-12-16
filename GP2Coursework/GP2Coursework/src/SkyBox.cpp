#include "SkyBox.h"
#include "Texture.h"
#include "Vertex.h"

SkyBox::SkyBox()
{
	m_cubeTexture = 0;
}

SkyBox::~SkyBox()
{

}

void SkyBox::destroy()
{
	if (m_cubeTexture)
	{
		glDeleteTextures(1, &m_cubeTexture);
	}
}

void SkyBox::bind()
{
	glDepthMask(GL_FALSE);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeTexture);

	GLint vertexPosLocation = glGetAttribLocation(m_ShaderProgram, "vertexPosition");
	glBindAttribLocation(m_ShaderProgram, vertexPosLocation, "vertexPosition");

	glEnableVertexAttribArray(vertexPosLocation);
	glVertexAttribPointer(vertexPosLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
}

void SkyBox::unbind()
{
	glDepthMask(GL_TRUE);
}

void SkyBox::loadCubeTexture(const std::string& PosXFilename,
	const std::string& NegXFilename,
	const std::string& PosYFilename,
	const std::string& NegYFilename,
	const std::string& PosZFilename,
	const std::string& NegZFilename){

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_cubeTexture);

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);


	loadCubeMapSide(PosXFilename, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	loadCubeMapSide(NegXFilename, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	loadCubeMapSide(PosYFilename, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	loadCubeMapSide(NegYFilename, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	loadCubeMapSide(PosZFilename, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	loadCubeMapSide(NegZFilename, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
}



//Getters & setters below:

GLuint SkyBox::getCubeTexture(){
	return m_cubeTexture;
}