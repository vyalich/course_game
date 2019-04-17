#include "../header/Player.h"

Player::Player(){
    intellect = 0;
}

bool Player::OnLoad(char* File, int width, int height){
    if((Surf_Entity = Surface::OnLoad("./tile/Player.bmp")) == false) {
        return false;
    }
    Width = width;
    Height = height;
    Speed = 10;
    MapX = (SCREEN_W>>1)-(Width>>1);
    MapY = (SCREEN_H>>1)-(Height>>1);
    Camera::CameraControl.OnInit(MapX-(SCREEN_W>>1)+(Width>>1), MapY-(SCREEN_H>>1)+(Height>>1));
}

void Player::SetSpeed(int DestX, int DestY, SDL_Surface *Surf_Display){
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
}

void Player::OnLoop(){

    ViewX = MapX;
    ViewY = MapY;
    MapX += SpeedX;
    MapY += SpeedY;
}

void Player::OnRender(SDL_Surface* Surf_Display, Uint32 Inter){
    ViewX += SpeedX * Inter;
    ViewY += SpeedY * Inter;
    Camera::CameraControl.OnMove(ViewX - (SCREEN_W>>1) + (Width>>1), ViewY - (SCREEN_H>>1) + (Height>>1));
    Surface::OnDraw(Surf_Display, Surf_Entity, ViewX - Camera::CameraControl.GetX(),
                    ViewY - Camera::CameraControl.GetY());
}
