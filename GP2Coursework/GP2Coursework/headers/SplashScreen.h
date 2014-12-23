#ifndef SplashScreen_h
#define SplashScreen_h

#include "gameScreen.h"
#include "GameObject.h"
#include "Component.h"
#include "PostProcessing.h"
#include "ColourFilters.h"



class SplashScreen : public gameScreen{

public:
	SplashScreen();
	~SplashScreen();


	void init();		//intialize
	void Update(SDL_Event event);
	void UpdateInput(SDL_Event event);
	void render(SDL_Window *window);
	void LoadContent();

	void renderGameObject(GameObject * pObject);

	void createSkyBox();
	void renderSkyBox();
	void FilterChanger();


	void cleanUp();

protected:
private:
	std::vector<GameObject*> displayList;
};


#endif