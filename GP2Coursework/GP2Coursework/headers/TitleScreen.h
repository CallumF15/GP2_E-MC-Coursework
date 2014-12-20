#ifndef TitleScreen_h
#define TitleScreen_h

#include "gameScreen.h"
#include "GameObject.h"
#include "Component.h"


class TitleScreen : public gameScreen{

public:
	TitleScreen();
	~TitleScreen();

	void init();		//intialize
	void update(SDL_Event event);
	void render(SDL_Window *window);
	void LoadContent();
	void destroy();

	void keyboardInput(SDL_Event &event);
	void cleanUp(SDL_Window *window);

protected:
private:
	std::vector<GameObject*> displayList;
};


#endif