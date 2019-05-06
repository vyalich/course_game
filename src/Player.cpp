#include "../header/Player.h"

SDL_Surface*    Player::SpriteSheet;

Player::Player(){
    intellect = 0;
}

bool Player::OnLoad(){
    if((SpriteSheet = Surface::OnLoad("./img/Player.bmp")) == false) {
        return false;
    }
    Speed = 5;
    Width = 64;
    Height = 64;

    MaxFrames = 8;
    WaitTime  = 3000/Speed/MaxFrames;
    LastFrameTime = SDL_GetTicks();
    Direction = BOTTOM;

    Health = 80;
    MaxHealth = 80;
    HPRegen = 0.02;
    Mana = 120;
    MaxMana = 120;
    MPRegen = 0.05;
    MapX = (MAP_W*TILE_SIZE>>1)-(Width>>1)-8*TILE_SIZE;
    MapY = (MAP_H*TILE_SIZE>>1)-(Height>>1);
    Camera::CameraControl.OnInit(MapX-(SCREEN_W>>1)+(Width>>1), MapY-(SCREEN_H>>1)+(Height>>1));
}

void Player::SetSpeed(int DestX, int DestY){
    float ScrX = MapX - Camera::CameraControl.GetX() + 16;
    float ScrY = MapY - Camera::CameraControl.GetY() + 10;
    if(DestY>=ScrY && DestY<=ScrY+Height-12 && DestX>=ScrX && DestX<=ScrX+32){
        SpeedX = SpeedY = 0;
        return;
    }
    DestX -= (Width>>1);
    DestY -= (Height>>1);
    double gep = sqrt((DestX-ScrX)*(DestX-ScrX)+(DestY-ScrY)*(DestY-ScrY));
    SpeedX = Speed/gep*(DestX-ScrX);
    SpeedY = Speed/gep*(DestY-ScrY);
    AngleCos = (DestX-ScrX)/gep;
}

void Player::OnLoop(bool _m_b_l){
    if(Health < MaxHealth)
        Health += HPRegen;
    else
        Health = MaxHealth;
    if(Mana < MaxMana)
        Mana += MPRegen;
    else
        Mana = MaxMana;

    int DestX, DestY;
    SDL_GetMouseState(&DestX, &DestY);
    if(_m_b_l){
        if(DestX >= MapX - Camera::CameraControl.GetX() + 16 && DestX <= MapX - Camera::CameraControl.GetX() + Width - 16
           && DestY >= MapY - Camera::CameraControl.GetY() + 10 && DestY <= MapY - Camera::CameraControl.GetY() + Height - 2){
            StopMove();
            return;
        }
        else{
            SetSpeed(DestX, DestY);
        }
    }
    else{
        StopMove();
        return;
    }
    AnimWalk();
    OnMove();
    Camera::CameraControl.OnMove(MapX - (SCREEN_W>>1) + (Width>>1), MapY - (SCREEN_H>>1) + (Height>>1));
}
