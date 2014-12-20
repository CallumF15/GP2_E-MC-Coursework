#ifndef ScreenManager_h
#define ScreenManager_h


#include <iostream>
#include "gameScreen.h"
#include "SplashScreen.h"
#include "TitleScreen.h"

#define WIDTH 800
#define HEIGHT 600

class ScreenManager{

public:

	// Default destructor
	~ScreenManager();
	static ScreenManager &getInstance();

	void Initialize();
	void LoadContent(); 
	void Update(SDL_Event event);
	void render(SDL_Window *window);
	void cleanUp();
	void UpdateInput(SDL_Event event);

	void AddScreen(gameScreen *screen);

protected:
private:
	
	ScreenManager();
	ScreenManager(ScreenManager const&);
	void operator=(ScreenManager const&);
	
};

#endif