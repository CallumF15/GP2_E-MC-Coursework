#ifndef SkyBox_h
#define SkyBox_h


#include "Material.h"


class SkyBox : public BaseMaterial{

public:

	SkyBox();
	~SkyBox();

	void destroy();
	void bind();
	void unbind();

	void loadCubeTexture(const std::string& PosXFilename,
		const std::string& NegXFilename,
		const std::string& PosYFilename,
		const std::string& NegYFilename,
		const std::string& PosZFilename,
		const std::string& NegZFilename);

	GLuint getCubeTexture();

private:
	GLuint m_cubeTexture;
};

#endif
