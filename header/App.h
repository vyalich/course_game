#ifndef APP_H
#define APP_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_draw.h>
#include "Entity.h"
#include "Player.h"
#include "Define.h"
#include "Map.h"
#include "Camera.h"

class App
{
    private:
        bool            _running;           //флаг выполнения игры
        bool            _level;             //флаг выполнения уровня
        //char
        Sint8            _mouse_key;          //флаг нажатия пкм
        SDL_Surface     *Surf_Display;       //поверхность экрана
        Player          Hero;


    public:
        App();
        ~App();
        int OnExecute();                //основной цикл игры
        bool OnInit();                  //инициализация игры
        void LevelInit();               //инициализация уровня
        void OnEvent(SDL_Event*);       //обработка событий
        void OnLoop();                  //произведение расчетов
        void OnRender();                //отрисовка кадра
        void LevelCleanup();            //очистка уровня
        void OnCleanup();               //очистка игры
        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
};

#endif // APP_H
