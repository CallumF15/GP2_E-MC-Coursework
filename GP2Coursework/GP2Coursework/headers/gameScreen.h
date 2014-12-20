#ifndef gameScreen_h
#define gameScreen_h

#include "SDL.h"

class gameScreen{

public:
	gameScreen();
	~gameScreen();

	virtual void LoadContent();
	virtual void cleanUp();
	virtual void Update(SDL_Event event);
	virtual void render(SDL_Window *window);
	virtual void UpdateInput(SDL_Event event);

protected:
private:


};


#endif