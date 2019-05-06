#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SDL_draw.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Player.h"
#include "App.h"

enum{   EXP         = 0,
        HEALTH         ,
        MANA           ,
        ENEMY          };

struct Bar{
    int x, y, w, h;
    Uint32 Color;
    double cur;
    std::string info;
    SDL_Color TextColor;
    SDL_Surface *Background;
    bool reversed;

    void Draw(SDL_Surface *Surf_Display);
    //void Draw(SDL_Surface *Surf_Display);
    void RenderText(SDL_Surface *Surf_Display, TTF_Font *Font, int MarginTop);
};

class GUI{
    private:
        Bar                 BarList[4];
        TTF_Font            *Font16;
        TTF_Font            *Font12;
        //Offsets PlayerFrame;
        //Offsets SkillBar;
        //struct { int x};

    public:
        static GUI GUIControl;

        GUI() {};

        void OnInit();
        void OnRender(SDL_Surface *Surf_Display);
        void OnLoop();
        void OnCleanup();

    private:
        void DrawBars(SDL_Surface *Surf_Display);
        void TextRender(SDL_Surface *Surf_Display, SDL_Rect &dest, char* str, SDL_Color &textColor);

};

#endif // GUI_H_INCLUDED
