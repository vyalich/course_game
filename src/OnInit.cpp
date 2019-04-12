#include "../header/App.h"

bool App::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }
    if(TTF_Init() < 0){
        return false;
    }
    if((Surf_Display = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    Draw_FillRect(Surf_Display, 0, 0, Surf_Display->w, Surf_Display->h, 0x00ff00);
    SDL_Flip(Surf_Display);
    atexit(SDL_Quit);
    atexit(TTF_Quit);

    return true;
}
