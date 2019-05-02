#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SDL_draw.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Player.h"
#include "App.h"

struct Bar{
    int x, y, w, h;
    double cur;
    std::string info;
    SDL_Color TextColor;

    void Draw(SDL_Surface *Surf_Display, Uint32 color, bool reversed);
    void RenderText(SDL_Surface *Surf_Display, TTF_Font *Font);
};

class GUI{
    private:

        SDL_Surface     *BackGround;
        Bar             HealthBar;
        Bar             ExpBar;
        Bar             ManaBar;
        TTF_Font        *Font;
        //Offsets PlayerFrame;
        //Offsets SkillBar;
        //struct { int x};

    public:
        static GUI GUIControl;

        GUI(): BackGround(0) { };

        void OnInit();
        void OnRender(SDL_Surface *Surf_Display);
        void OnLoop();

    private:
        void DrawBars(SDL_Surface *Surf_Display);
        void TextRender(SDL_Surface *Surf_Display, SDL_Rect &dest, char* str, SDL_Color &textColor);

};

#endif // GUI_H_INCLUDED
