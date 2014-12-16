#ifndef SkyBox_h
#define SkyBox_h


#include "Material.h"
#include "SDL_image.h"
#include "Texture.h"

class SkyBox : public Material{

public:

	SkyBox();
	~SkyBox();

	void destroy();
	void bind();
	void unbind();

	void drawSkyBox();

	void loadCubeTexture(const std::string& PosXFilename,
		const std::string& NegXFilename,
		const std::string& PosYFilename,
		const std::string& NegYFilename,
		const std::string& PosZFilename,
		const std::string& NegZFilename);

	GLuint getCubeTexture();

protected:

private:
	GLuint cubeTexture;
};

#endif
