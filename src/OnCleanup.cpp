#include "../header/App.h"

void App::OnCleanup(){
    SDL_Quit();
    TTF_Quit();
    Area::AreaControl.OnCleanup();
}
