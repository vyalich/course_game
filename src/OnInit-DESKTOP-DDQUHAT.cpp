#include "../header/App.h"

bool App::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }
    if(TTF_Init() < 0){
        return false;
    }
    if((Surf_Display = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)) == NULL) {
        return false;
    }
    if(Map::MapControl.OnLoad("./misc/1.map") == false) {
        return false;
    }
    Hero.OnLoad("./tile/player.bmp", 32, 32);
    //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    Draw_FillRect(Surf_Display, 0, 0, SCREEN_W, SCREEN_H, 0xffffff);
    atexit(SDL_Quit);
    atexit(TTF_Quit);

    return true;
}
