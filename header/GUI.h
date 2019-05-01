#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SDL_draw.h>
#include "Player.h"

struct Bar{
    int x, y, w, h;
    double cur;
};

class GUI{
    friend class Player;

    private:


        Bar HealthBar;
        Bar ExpBar;
        //Offsets PlayerFrame;
        //Offsets SkillBar;
        //struct { int x};

    public:
        static GUI GUIControl;

        GUI() {};

        void OnInit();
        void OnRender(SDL_Surface *Surf_Display);
        void OnLoop();

};

#endif // GUI_H_INCLUDED
