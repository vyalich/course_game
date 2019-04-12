#include "../header/App.h"

App::App()
{
    _running = true;
    _level = false;
    _mouse_key = 0;
}

App::~App()
{
    //dtor
}

int App::OnExecute() {
    #define FPS 25
    if(OnInit() == false) {
        return -1;
    }

    Uint32 start;
    SDL_Event event;
    //основной игровой цикл
    while(_running){
        LevelInit();
        //основной игровой цикл уровня
        while(_level){
            start = SDL_GetTicks();
            while(SDL_PollEvent(&event)) {
                OnEvent(&event);
            }
            OnLoop();
            OnRender();
            if(SDL_GetTicks()-start < 1000/FPS)
                SDL_Delay(1000/FPS-(SDL_GetTicks()-start));     //ограничение в 25 фпс
        }
        LevelCleanup();
    }
    OnCleanup();
    return 0;
}

int main(int argc, char* argv[]){
    App Game;
    return Game.OnExecute();
}
