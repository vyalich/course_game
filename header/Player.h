#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"


class Player: public Entity{
    private:
        int intellect;
        static SDL_Surface*    SpriteSheet;
    public:
        Player();
        bool OnLoad(char* File, int Width, int Height);
        void OnLoop();
        void SetSpeed(int X, int Y);
        void OnRender(SDL_Surface *Surf_Display, Uint32 Inter);
        inline double GetMapX() {return MapX;};
        inline double GetMapY() {return MapY;};
};

#endif // PLAYER_H_INCLUDED
