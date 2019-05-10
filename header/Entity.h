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
#include <list>

class Entity {
    friend class GUI;
    friend class Spell;
    public:
        //static std::vector<Entity*>    EntityList;

    protected:
        //CAnimation      Anim_Control;

    protected:
        double          MapX;
        double          MapY;
        double          OldX;
        double          OldY;

        int             Width;
        int             Height;

        char            Direction;
        char            State;
        char            StartFrame;
        char            MaxFrames;
        Uint8           WaitTime;
        Uint32          LastFrameTime;
        int             FrameX;
        int             FrameY;
        double          SpeedX;
        double          SpeedY;

    public:
        Entity();

        virtual bool OnLoad(char* File, int Width, int Height);

        virtual void OnLoop();

        virtual void OnRender(SDL_Surface *Surf_Display, int CamX, int CamY, double Inter);

        virtual void OnCleanup();

        friend bool Compare(Entity*, Entity*);

        static std::list<Entity*>   OnScreen;

    private:
        virtual SDL_Surface* GetSpriteSheet() = 0;

        //virtual void OnAnimate();
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
