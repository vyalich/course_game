#include "../header/Player.h"

SDL_Surface*    Player::SpriteSheet;

Player::Player(){
    intellect = 0;
}

bool Player::OnLoad(char* File, int width, int height){
    if((SpriteSheet = Surface::OnLoad("./img/Player.bmp")) == false) {
        return false;
    }
    Width = width;
    Height = height;
    MaxFrames = SpriteSheet->w/width;
    FrameRate = 12;
    WaitTime  = 1000/FrameRate;
    LastFrameTime = SDL_GetTicks();
    State = 2;
    Speed = 5;
    MapX = (MAP_W*TILE_SIZE>>1)-(Width>>1);
    MapY = (MAP_H*TILE_SIZE>>1)-(Height>>1);
    Camera::CameraControl.OnInit(MapX-(SCREEN_W>>1)+(Width>>1), MapY-(SCREEN_H>>1)+(Height>>1));
}

void Player::SetSpeed(int DestX, int DestY){
    float ScrX = MapX - Camera::CameraControl.GetX();
    float ScrY = MapY - Camera::CameraControl.GetY();
    if(DestY>=ScrY && DestY<=ScrY+Height && DestX>=ScrX && DestX<=ScrX+Width){
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

void Player::OnLoop(){
    if(SpeedX || SpeedY)
        AnimWalk();
    OnMove();
    Camera::CameraControl.OnMove(MapX - (SCREEN_W>>1) + (Width>>1), MapY - (SCREEN_H>>1) + (Height>>1));
}
