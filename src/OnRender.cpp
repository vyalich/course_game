#include "../header/App.h"

void App::OnRender(){
    Hero.Draw(Surf_Display);
    SDL_Flip(Surf_Display);
}
