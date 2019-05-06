#include "../header/Spell.h"

std::list<Spell*>   Spell::SpellCasted;

Uint32              Spell::LastUsed = 0;

std::string         Spell::Name = "Fireball";

std::string         Spell::Description;

Spell::Spell(){

}

Spell::~Spell(){

}

void Spell::OnLoad(){
    //_casted = false;

    Cost = 9;
    Speed = 8;
    MapX = App::Hero.GetMapX() + 23;
    MapY = App::Hero.GetMapY() + 32;
    CoolDown = 500;
    Range = 10*TILE_SIZE;
    Power = 14;
    Width = 19;
    Height = 19;

    DrawSurf = SDL_CreateRGBSurface(SDL_HWSURFACE, Width, Height, 32, 0,0,0,0);
    Draw_FillRect(DrawSurf, 0, 0, Width, Height, 0xff00ff);
    Surface::Transparent(DrawSurf, 255, 0, 255);
}

void Spell::AddCasted(){
    Spell *temp = new Spell;
    temp->OnLoad();

    if(LastUsed + temp->CoolDown < SDL_GetTicks() && App::Hero.Mana >= temp->Cost){
        temp->_exist = true;
        SDL_GetMouseState(&temp->TarX, &temp->TarY);
        App::Hero.Mana -= temp->Cost;
        LastUsed = SDL_GetTicks();

        /*double Dist = sqrt((DestX-MapX)*(DestX-MapX)+(DestY-MapY)*(DestY-MapY));
        SpeedX = Speed/Dist*(DestX-MapX);
        SpeedY = Speed/Dist*(DestY-MapY);
        AngleCos = (DestX-MapX)/Dist;*/

        SpellCasted.push_back(temp);
    }
    else
        delete temp;

}

void Spell::OnLoop(){
    //Spell::Description = "Cast simple fireball. \nPower: "+std::to_string(Power)+"\nCooldown: "+std::to_string((float)CoolDown/1000)+"\nRange: "+std::to_string(Range/TILE_SIZE);



}

void Spell::OnRender(SDL_Surface *Surf_Display, int CamX, int CamY){
    Draw_FillCircle(DrawSurf, 9, 9, 10, 0xff0000);
    Draw_Circle(DrawSurf, 9, 9, 10, 0x000000);
    SDL_Rect coords = {.x = MapX - CamX, .y = MapY - CamY};
    //SDL_Rect coords = {.x = TarX, .y = TarY};
    SDL_BlitSurface(DrawSurf, 0, Surf_Display, &coords);
}
