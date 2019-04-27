#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Creature.h"


class Player: public Creature{
    private:
        int intellect;
        static SDL_Surface*    SpriteSheet;
    public:
        Player();
        bool OnLoad(char* File, int Width, int Height);
        void OnLoop();
        void SetSpeed(int X, int Y);
        inline double GetMapX() {return MapX;};
        inline double GetMapY() {return MapY;};
        virtual SDL_Surface* GetSpriteSheet() { return Player::SpriteSheet;};
};

#endif // PLAYER_H_INCLUDED
