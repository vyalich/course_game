#ifndef SPELL_H_INCLUDED
#define SPELL_H_INCLUDED

#include <SDL.h>
#include <SDL_draw.h>
#include <string>
#include <list>
#include "Enemy.h"
#include "Creature.h"
#include "Player.h"

class Spell: public Entity{
    private:
        bool            _exist;
        int             Cost;
        Uint16          Speed;
        double          SpeedX;
        double          SpeedY;
        int             TarX;
        int             TarY;
        Uint16          CoolDown;
        Uint16          Range;
        Uint16          Power;
        SDL_Surface     *DrawSurf;

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
        void OnRender(SDL_Surface *Surf_Display, int CamX, int CamY);
        static void AddCasted();
        //void Cast()
        SDL_Surface* GetSpriteSheet() { return DrawSurf;};


};

#endif // SPELL_H_INCLUDED
