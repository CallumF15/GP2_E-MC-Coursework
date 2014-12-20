

#include "ScreenManager.h"


gameScreen *currentScreen, *newScreen;

ScreenManager::ScreenManager(){

}

ScreenManager::~ScreenManager(){}


ScreenManager &ScreenManager::getInstance(){

	static ScreenManager instance;
	return instance;
}

void ScreenManager::Initialize(){
	currentScreen = new TitleScreen(); //starting screen goes here;
}


void ScreenManager::LoadContent(){
	currentScreen->LoadContent();
}

void ScreenManager::Update(SDL_Event event){
	currentScreen->Update(event);
}

void ScreenManager::render(SDL_Window *window){
	currentScreen->render(window);
}

void ScreenManager::AddScreen(gameScreen *screen){
	currentScreen->cleanUp();
	delete currentScreen;
	currentScreen = screen;
	currentScreen->LoadContent();
}

void ScreenManager::cleanUp(){
	currentScreen->cleanUp();
}

void ScreenManager::UpdateInput (SDL_Event event){
	currentScreen->UpdateInput(event);
}
