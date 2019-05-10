#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Creature.h"
#include "Enemy.h"
#include "GUI.h"

//class Enemy;

class Player: public Creature{
    friend class GUI;
    friend class Enemy;
    friend class Spell;

    private:
        int intellect;
        SDL_Surface*    SpriteSheet;

    public:
        Player();
        bool OnLoad();
        void OnLoop(bool _m_b_l, double Inter);
        void SetSpeed(int X, int Y);
        inline double GetMapX() {return MapX;};
        inline double GetMapY() {return MapY;};
        virtual SDL_Surface* GetSpriteSheet() { return SpriteSheet;};
        void MoveCam(double Inter);
};

#endif // PLAYER_H_INCLUDED
