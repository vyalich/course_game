#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

#include "Entity.h"
#include <list>
#include <SDL_draw.h>

enum    {BOTTOM = 2,
         TOP    = 0,
         LEFT   = 1,
         RIGHT  = 3};

class Creature: public Entity{
    friend class GUI;
    friend class Spell;

    protected:
        double          Health;
        int             MaxHealth;
        double          HPRegen;
        double          Mana;
        int             MaxMana;
        double          MPRegen;

        double          AngleCos;
        double          Speed;

    public:
        Creature();

        void    StopMove(double Inter);

        virtual void    OnMove();

        void    AnimWalk();

        void    AnimDie();

    private:
        void    PosValid();

        bool    PosValidTileX(int l, int r, int t, int d);

        bool    PosValidTileY(int l, int r, int t, int d);

        bool    PosValidEntity(Entity* Entity, int NewX, int NewY);

        virtual SDL_Surface* GetSpriteSheet() = 0;
};

#endif // CREATURE_H_INCLUDED
