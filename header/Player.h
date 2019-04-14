#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"

class Player: public Entity{
    private:
        int intellect;
    public:
        Player();
        bool OnLoad(char* File, int Width, int Height);
        void OnLoop();
        void SetSpeed(int X, int Y,SDL_Surface *Surf_Display);
        void OnRender(SDL_Surface *Surf_Display, Uint32 Inter);
};

#endif // PLAYER_H_INCLUDED
