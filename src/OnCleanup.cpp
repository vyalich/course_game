#include "../header/App.h"

void App::OnCleanup(){
    Map::MapControl.OnCleanup();


    GUI::GUIControl.OnCleanup();

    SDL_Quit();
    TTF_Quit();
}
