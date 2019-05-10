#include "../header/App.h"

Player App::Hero;

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
    #define SKIP 20.0
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event event;
    //основной игровой цикл


    Uint32 next_game_tick = SDL_GetTicks();

    while(_running){
        LevelInit();

        //основной игровой цикл уровня
        out.open("log.txt");
        if(!out)
            return -10;
        while(_level){
            if(loops == 0)
                start = SDL_GetTicks();
            while(SDL_GetTicks() > next_game_tick){

                while(SDL_PollEvent(&event)) {
                    OnEvent(&event);
                }
                OnLoop();
                next_game_tick = SDL_GetTicks() + 20;

            }
            Inter = (SDL_GetTicks() + 20 - next_game_tick)/ SKIP;

            out << std::fixed << std::setprecision(6) << Inter << " = " << SDL_GetTicks() << " + 20 - " << next_game_tick << " / " << SKIP << std::endl;;

            OnRender();


        }
        LevelCleanup();
    }
    OnCleanup();

    out.close();


    return 0;
}

int main(int argc, char* argv[]){
    srand(time(0));
    App Game;
    return Game.OnExecute();
}
