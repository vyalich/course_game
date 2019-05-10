#include "../header/Spell.h"

std::list<Spell*>   Spell::SpellCasted;

std::string         Spell::Name = "Fireball";

std::string         Spell::Description;

int                 Spell::Cost     = 0;
Uint16              Spell::Range    = 10*TILE_SIZE;
Uint16              Spell::Power    = 14;
Uint16              Spell::CoolDown = 500;
Uint32              Spell::LastUsed = 0;

Spell::Spell(){

}

Spell::~Spell(){

}

void Spell::OnLoad(){
    //_casted = false;


    Speed = 8;
    MapX = App::Hero.GetMapX() + 23;
    MapY = App::Hero.GetMapY() + 32;
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
        temp->TarX += Camera::CameraControl.GetX() - temp->Width/2;
        temp->TarY += Camera::CameraControl.GetY() - temp->Height/2;

        App::Hero.Mana -= temp->Cost;
        LastUsed = SDL_GetTicks();

        temp->SetSpeed();

        SpellCasted.push_back(temp);
    }
    else
        delete temp;

}

void Spell::OnLoop(){
    //Spell::Description = "Cast simple fireball. \nPower: "+std::to_string(Power)+"\nCooldown: "+std::to_string((float)CoolDown/1000)+"\nRange: "+std::to_string(Range/TILE_SIZE);
    if(!_exist)
        SpellCasted.remove(this);
    OnMove();

}

void Spell::OnRender(SDL_Surface *Surf_Display, int CamX, int CamY, double Inter){
    Draw_FillCircle(DrawSurf, 9, 9, 10, 0xff0000);
    Draw_Circle(DrawSurf, 9, 9, 10, 0x000000);
    Surface::OnDraw(Surf_Display, DrawSurf, OldX + SpeedX*Inter - CamX, OldY + SpeedY*Inter - CamY);
    //Surface::OnDraw(Surf_Display, DrawSurf, MapX-CamX, MapY-CamY);
}

void Spell::SetSpeed(){
    double Dist = sqrt((TarX-MapX)*(TarX-MapX)+(TarY-MapY)*(TarY-MapY));
    SpeedX = Speed/Dist*(TarX-MapX);
    SpeedY = Speed/Dist*(TarY-MapY);
    //AngleCos = (TarX-MapX)/Dist;
}

void Spell::OnMove(){
    OldX = MapX;
    MapY += SpeedY;
    if(!PosValidTileY(0, 0, TILE_SIZE, 0)){
        _exist = false;
        SpeedX = SpeedY = 0;
        return;
    }
    OldY = MapY;
    MapX += SpeedX;
    if(!PosValidTileX(0, 0, TILE_SIZE, 0)){
        _exist = false;
        SpeedX = SpeedY = 0;
        return;
    }
}
