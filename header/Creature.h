#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

#include "Entity.h"

enum    {BOTTOM = 2,
         TOP    = 0,
         LEFT   = 1,
         RIGHT  = 3};

class Creature: public Entity{
    protected:
        int             Health;
        int             MaxHealth;

        double          AngleCos;
        double          Speed;
        double          SpeedX;
        double          SpeedY;

    public:
        Creature();

        void    StopMove();

        void    OnMove();

        void    AnimWalk();

        void    AnimStay();

        void    AnimAttack();

        void    AnimDie();

    private:
        void    PosValid();

        void    PosValidTileX();

        void    PosValidTileY();

        bool    PosValidEntity(Entity* Entity, int NewX, int NewY);
};

#endif // CREATURE_H_INCLUDED
