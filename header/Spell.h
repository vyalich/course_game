#ifndef SPELL_H_INCLUDED
#define SPELL_H_INCLUDED

#include <SDL.h>
#include <SDL_draw.h>
#include <string>
#include <list>
#include "Enemy.h"
#include "Creature.h"
#include "Player.h"

class Spell{
    private:
        bool            _exist;
        std::string     Name;
        std::string     Description;
        int             Cost;
        Uint16          Speed;
        Uint16          MapX;
        Uint16          MapY;
        int             TarX;
        int             TarY;
        Uint16          CoolDown;
        static Uint32   LastUsed;
        Uint16          Range;
        Uint16          Power;
        SDL_Surface     *DrawSurf;

    public:
        Spell();
        ~Spell();
        void OnLoad();
        void OnLoop();
        void OnRender(SDL_Surface *Surf_Display);
        bool CanCast();
        //void Cast()

        static std::list<Spell*> SpellCasted;

};

#endif // SPELL_H_INCLUDED
