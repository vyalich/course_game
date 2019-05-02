#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Creature.h"
#include "Enemy.h"
#include "GUI.h"

//class Enemy;

class Player: public Creature{
    friend class GUI;
    friend class Enemy;

    private:
        int intellect;
        static SDL_Surface*    SpriteSheet;
    public:
        Player();
        bool OnLoad();
        void OnLoop();
        void SetSpeed(int X, int Y);
        inline double GetMapX() {return MapX;};
        inline double GetMapY() {return MapY;};
        virtual SDL_Surface* GetSpriteSheet() { return Player::SpriteSheet;};
        //friend void Enemy::Attack();
};

#endif // PLAYER_H_INCLUDED
