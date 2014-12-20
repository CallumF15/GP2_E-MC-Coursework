
#include "TitleScreen.h"


#include "Shader.h"

TitleScreen::TitleScreen(){

}
TitleScreen::~TitleScreen()
{

}

void TitleScreen::init(){	

}//intialize
void TitleScreen::update(SDL_Event event)
{

}



void TitleScreen::render(SDL_Window *window){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	SDL_GL_SwapWindow(window);

}
void TitleScreen::LoadContent(){}
void TitleScreen::destroy(){}

void TitleScreen::keyboardInput(SDL_Event &event){}
void TitleScreen::cleanUp(SDL_Window *window){}