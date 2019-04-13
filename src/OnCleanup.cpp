#include "../header/App.h"

void App::OnCleanup(){
    Map::MapControl.OnCleanup();
    SDL_Quit();
    TTF_Quit();
}
