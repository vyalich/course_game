#ifndef APP_H
#define APP_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_draw.h>
#include <ctime>
#include <cstdlib>
#include "Entity.h"
#include "Player.h"
#include "Define.h"
#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include "GUI.h"
#include "Spell.h"

class Player;

class App
{
    private:
        bool            _running;           //флаг выполнения игры
        bool            _level;             //флаг выполнения уровня
        //char
        bool            _mouse_left;          //флаг нажатия пкм
        bool            _mouse_right;
        double          Inter;
        Uint32          start;
        Uint32          loops;
        Uint16          fps;
        SDL_Surface     *Surf_Display;       //поверхность экрана
        SDL_Rect        ClipForDraw;

    public:
        static Player   Hero;
        static SDL_Surface  *ForDraw;


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
