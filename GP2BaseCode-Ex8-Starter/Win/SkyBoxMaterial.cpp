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


}