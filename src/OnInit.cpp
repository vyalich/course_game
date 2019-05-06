#include "../header/App.h"

bool App::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }

    if(TTF_Init() < 0){
        return false;
    }

    //if((Surf_Display = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_FULLSCREEN | SDL_ANYFORMAT | SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    if((Surf_Display = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_ANYFORMAT | SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }


    if(Map::MapControl.OnLoad("./misc/1.map") == false) {
        return false;
    }

    Hero.OnLoad();

    Creature::OnScreen.push_back(&Hero);

    //ForDraw = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_W + 100, SCREEN_H + 100, 32, 0, 0, 0, 0);
    //Surface::Transparent(ForDraw, 255, 0, 255);
    //SDL_Rect ClipForDraw = {.x = 50, .y = 50, .w = SCREEN_W, .h = SCREEN_H};

    GUI::GUIControl.OnInit();

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    //Draw_FillRect(Surf_Display, 0, 0, SCREEN_W, SCREEN_H, 0xffffff);
    atexit(SDL_Quit);
    atexit(TTF_Quit);

    return true;
}
