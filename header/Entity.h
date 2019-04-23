#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <cmath>

#include "Tile.h"
#include "Map.h"
//#include "Animation.h"
#include "Camera.h"
#include "FPS.h"
#include "Surface.h"
#include <SDL_ttf.h>
enum {
    ENTITY_TYPE_GENERIC = 0,
    ENTITY_TYPE_PLAYER
};

enum {
    ENTITY_FLAG_NONE     = 0,
    ENTITY_FLAG_GRAVITY    = 0x00000001,
    ENTITY_FLAG_GHOST    = 0x00000002,
    ENTITY_FLAG_MAPONLY    = 0x00000004
};

class Entity {
    public:
        //static std::vector<Entity*>    EntityList;

    protected:
        //CAnimation      Anim_Control;

        SDL_Surface*    Surf_Entity;

    protected:
        double           MapX;
        double           MapY;

        double          ViewX;
        double          ViewY;

        int             Width;
        int             Height;

    public:
        int         Type;
        bool        Dead;
        //int        Flags;

    protected:
        double      Speed;
        double      SpeedX;
        double      SpeedY;


    public:
        Entity();

        virtual ~Entity();

        virtual bool OnLoad(char* File, int Width, int Height);

        virtual void OnLoop();

        virtual void OnRender(SDL_Surface* Surf_Display);

        virtual void OnCleanup();

        //virtual void OnAnimate();

        void     StopMove();

        void    OnMove();

    private:
        void    PosValid();

        void    PosValidTile();

        bool    PosValidEntity(Entity* Entity, int NewX, int NewY);
};

/*class EntityCol {
    public:
        static std::vector<EntityCol>    EntityColList;

    public:
        CEntity* EntityA;
        CEntity* EntityB;

    public:
        EntityCol();
};*/
#endif // PLAYER_H
