#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Creature.h"
#include <SDL.h>
#include <SDL_draw.h>
#include <ctime>
#include <cstdlib>

enum    {FLEE   = -1,
         IDLE   = 0,
         CHASE  = 1,
         ATTACK = 2};

class Enemy: public Creature{
    private:
        bool                    _on_screen;
        char                    _chasing;
        Uint16                  AggroRange;
        Uint16                  FleeRange;
        Uint16                  AttackRange;
        //Uint16
        int                     LastX;
        int                     LastY;
        static SDL_Surface*     SpriteSheet;

        void SetSpeed(double DestX, double DestY);
        virtual SDL_Surface* GetSpriteSheet() { return Enemy::SpriteSheet;};

    public:
        Enemy();
        ~Enemy();
        bool OnLoad(int speed, int width, int height);
        void OnLoop(double PlayerX, double PlayerY, int CamX, int CamY, SDL_Surface *Surf_Display);
        void OnRender(SDL_Surface* Surf_Display, double Inter);
        void LineOfSight(double PlayerX, double PlayerY, double gep, SDL_Surface *Surf_Display);

        static std::vector<Enemy*> EnemyList;

};

#endif // ENEMY_H_INCLUDED
