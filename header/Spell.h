#ifndef SPELL_H_INCLUDED
#define SPELL_H_INCLUDED

#include <SDL.h>
#include <SDL_draw.h>
#include <string>
#include <list>
#include "Enemy.h"
#include "Creature.h"
#include "Player.h"

class Spell: public Creature{
    private:
        double                  OldX;
        double                  OldY;
        bool                    _exist;
        static  int             Cost;
        int                     TarX;
        int                     TarY;
        static Uint16           CoolDown;
        static Uint16           Range;
        static Uint16           Power;
        SDL_Surface             *DrawSurf;

        static Uint32           LastUsed;
        static std::string      Name;
        static std::string      Description;

    public:
        static std::list<Spell*> SpellCasted;

    public:
        Spell();
        ~Spell();
        void OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface *Surf_Display, int CamX, int CamY, double Inter);
        static void AddCasted();
        //void Cast()
        SDL_Surface* GetSpriteSheet() { return DrawSurf;};
        void SetSpeed();
        void OnMove() override;


};

#endif // SPELL_H_INCLUDED
