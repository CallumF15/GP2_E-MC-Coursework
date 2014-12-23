

#include "ScreenManager.h"


gameScreen *currentScreen, *newScreen;

//constructor
ScreenManager::ScreenManager(){

}
//destructor
ScreenManager::~ScreenManager(){}

//Static method so we can access without intializing class
//allows us to get an instance of ScreenManager methods
ScreenManager &ScreenManager::getInstance(){

	static ScreenManager instance;
	return instance;
}


//Assigns the first screen that will display
void ScreenManager::Initialize(){
	currentScreen = new TitleScreen(); //starting screen goes here;
}

//loads content for current screen
void ScreenManager::LoadContent(){
	currentScreen->LoadContent();
}

//updates current screen
void ScreenManager::Update(SDL_Event event){
	currentScreen->Update(event);
}

//renders current screen
void ScreenManager::render(SDL_Window *window){
	currentScreen->render(window);
}

//assigns the new screen and deleted the old screen and
//then loads content for the new screen
void ScreenManager::AddScreen(gameScreen *screen){
	currentScreen->cleanUp();
	delete currentScreen;
	currentScreen = screen;
	currentScreen->LoadContent();
}
//cleans up the current screen
void ScreenManager::cleanUp(){
	currentScreen->cleanUp();
}
//updates input for current screen.
void ScreenManager::UpdateInput (SDL_Event event){
	currentScreen->UpdateInput(event);
}
