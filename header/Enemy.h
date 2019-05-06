#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "GUI.h"
#include "Creature.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_draw.h>
#include <ctime>
#include <cstdlib>

enum    {FLEE   = -1,
         IDLE   = 0,
         CHASE  = 1,
         ATTACK = 2};

class Enemy: public Creature{
    friend class GUI;
    friend class Spell;

    private:
        bool                    _on_screen;
        char                    _chasing;
        bool                    _mouseover;

        double                  Dist;
        Uint16                  AggroRange;
        Uint16                  FleeRange;
        Uint16                  AttackRange;
        Uint16                  AttackSpeed;
        Uint32                  LastAttack;
        int                     AttackPower;
        int                     LastX;
        int                     LastY;
        static SDL_Surface*     SpriteSheet;

        void SetSpeed(double DestX, double DestY);
        virtual SDL_Surface* GetSpriteSheet() { return Enemy::SpriteSheet;};

    public:
        Enemy();
        ~Enemy();
        bool OnLoad(int speed);
        void OnLoop(double PlayerX, double PlayerY, int CamX, int CamY, SDL_Surface *Surf_Display);
        void OnRender(SDL_Surface* Surf_Display, double Inter);
        void LineOfSight(double PlayerX, double PlayerY, SDL_Surface *Surf_Display);
        void Attack();
        void AnimAttack();

        static std::vector<Enemy*> EnemyList;

};

#endif // ENEMY_H_INCLUDED
