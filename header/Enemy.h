#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Entity.h"
#include <SDL.h>
#include <ctime>
#include <cstdlib>

class Enemy: public Entity{
    private:
        Uint16      AggroRad;

        void SetSpeed(double DestX, double DestY);
    public:
        Enemy();
        ~Enemy();
        bool OnLoad(int speed, int width, int height);
        void OnLoop(double PlayerX, double PlayerY);


        static std::vector<Enemy*> EnemyList;

};

#endif // ENEMY_H_INCLUDED
