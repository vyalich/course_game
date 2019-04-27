#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Creature.h"
#include <SDL.h>
#include <ctime>
#include <cstdlib>

class Enemy: public Creature{
    private:
        Uint16                  AggroRad;
        static SDL_Surface*     SpriteSheet;

        void SetSpeed(double DestX, double DestY);
        virtual SDL_Surface* GetSpriteSheet() { return Enemy::SpriteSheet;};

    public:
        Enemy();
        ~Enemy();
        bool OnLoad(int speed, int width, int height);
        void OnLoop(double PlayerX, double PlayerY);

        static std::vector<Enemy*> EnemyList;

};

#endif // ENEMY_H_INCLUDED
