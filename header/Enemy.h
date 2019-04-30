#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Creature.h"
#include <SDL.h>
#include <SDL_draw.h>
#include <ctime>
#include <cstdlib>

class Enemy: public Creature{
    private:
        bool                    _on_screen;
        bool                    _chasing;
        Uint16                  AggroRange;
        static SDL_Surface*     SpriteSheet;

        void SetSpeed(double DestX, double DestY);
        virtual SDL_Surface* GetSpriteSheet() { return Enemy::SpriteSheet;};

    public:
        Enemy();
        ~Enemy();
        bool OnLoad(int speed, int width, int height);
        void OnLoop(double PlayerX, double PlayerY, int CamX, int CamY, SDL_Surface *Surf_Display);
        void OnRender(SDL_Surface* Surf_Display, double Inter);

        static std::vector<Enemy*> EnemyList;

};

#endif // ENEMY_H_INCLUDED
