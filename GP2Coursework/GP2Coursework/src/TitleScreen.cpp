///////////////////////////////////////////////////
//This class was implemented by Callum Flannagan.//
///////////////////////////////////////////////////


#include "TitleScreen.h"


#include "Shader.h"

//constructor
TitleScreen::TitleScreen(){

}
//destructor
TitleScreen::~TitleScreen()
{

}
//intialize method
void TitleScreen::init(){	

}

//updates everything for this screen
void TitleScreen::update(SDL_Event event)
{

}


//renders everything for this screen
void TitleScreen::render(SDL_Window *window){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //clears the colour
	glClearDepth(1.0f); 
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	SDL_GL_SwapWindow(window);

}

void TitleScreen::LoadContent(){} //loads all the content for the screen
void TitleScreen::destroy(){}  //destroys all the content for the screen

//used for all keyboard input for this screen
void TitleScreen::keyboardInput(SDL_Event &event)
{

}

//used to clean up anything that this screen uses
void TitleScreen::cleanUp(SDL_Window *window){}