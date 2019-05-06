#include "../header/Spell.h"

std::list<Spell*> Spell::SpellCasted;
//std::queue<

Spell::Spell(){

}

Spell::~Spell(){

}

void Spell::OnLoad(){
    //_casted = false;
    Name = "Fireball";
    Description = "Cast simple fireball. \nPower: "+std::to_string(Power)+"\nCooldown: "+std::to_string((float)CoolDown/1000)+"\nRange: "+std::to_string(Range/TILE_SIZE);
    Cost = 9;
    Speed = 8;
    MapX = 0;
    MapY = 0;
    CoolDown = 500;
    LastUsed = 0;
    Range = 10*TILE_SIZE;
    Power = 14;
}

bool Spell::CanCast(){
    if(LastUsed + CoolDown < SDL_GetTicks() && App::Hero.Mana >= Cost){
        SDL_GetMouseState(&TarX, &TarY);
        App::Hero.Mana -= Cost;
        //SetSpeed();
        return true;
    }
    return false;
}

void Spell::OnLoop(){



}

void Spell::OnRender(SDL_Surface *Surf_Display){
    Draw_FillCircle(Surf_Display, TarX, TarY, 50, 0xff0000);
}
