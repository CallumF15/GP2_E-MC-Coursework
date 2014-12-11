#ifndef SKYBOXMATERIAL_H
#define SKYBOXMATERIAL_H
#include "Material.h"

class SkyBoxMaterial : public BaseMaterial{

public:
	SkyBoxMaterial();
	~SkyBoxMaterial();
	void destroy();
	void bind();
	void unbind();

	void loadCubeTexture(const std::string& filenamePosZ, const std::string filenameNegZ, const std::string& filenamePosX, cosnt std::string& filenameNegX, const std::string& filenameNegX,
		const std::string& filenamePosY, const std::string& filenameNegY);
	GLunit getCubeTexture();

private:
	GLunit m_CubeTexture;

};

#endif