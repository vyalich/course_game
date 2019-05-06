#include "../header/App.h"

Player App::Hero;
SDL_Surface* App::ForDraw;

App::App()
{
    _running = true;
    _level = false;
    _mouse_left = false;
    _mouse_right = false;
    Inter = 0;
    start = 0;
    loops = 0;
}

App::~App()
{
    //dtor
}

int App::OnExecute() {
    #define LPS 50
    #define SKIP 1000/LPS
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event event;
    //основной игровой циклSurf_Display
    while(_running){
        LevelInit();
        Uint32 next_game_tick = SDL_GetTicks();
        //основной игровой цикл уровня
        while(_level){
            if(loops == 0)
                start = SDL_GetTicks();
            while(SDL_GetTicks() > next_game_tick){

                while(SDL_PollEvent(&event)) {
                    OnEvent(&event);
                }
                OnLoop();
                next_game_tick += SKIP;


            }
            OnRender();
            Inter = double(SDL_GetTicks() - next_game_tick + SKIP)/SKIP*10;

        }
        LevelCleanup();
    }
    OnCleanup();
    return 0;
}

int main(int argc, char* argv[]){
    srand(time(0));
    App Game;
    return Game.OnExecute();
}
