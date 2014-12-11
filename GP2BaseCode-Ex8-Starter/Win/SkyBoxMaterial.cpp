#include "SkyBoxMaterial.h"
#include "Texture.h"
#include "Vertex.h"

SkyBoxMaterial::SkyBoxMaterial(){

	m_CubeTexture = 0;
}
SkyBoxMaterial::SkyBoxMaterial(){

}
void SkyBoxMaterial::destroy(){

	if (m_CubeTexture){
		glDeleteTextures(1, &m_CubeTexture);
	}
}
void SkyBoxMaterial::bind(){
	glDepthMask(GL_FALSE);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeTexture);

	GLint vertexPosLocation = glGetAttribLocation(m_ShaderProgram, "vertextPosition");
	glVertexAttribPointer(vertexPosLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
}
void SkyBoxMaterial::unbind(){
	glDepthMask(GL_TRUE);
}
void SkyBoxMaterial::loadCubeTexture(const std::string& filenamePosZ, const std::string filenameNegZ, const std::string& filenamePosX, const std::string& filenameNegX, 
	const std::string& filenamePosY, const std::string& filenameNegY);
