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
    WaitTime  = 1000/(SpriteSheet->w/width)/2;
    LastFrame = SDL_GetTicks();
    Speed = 8;
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
}

void Player::OnLoop(){

    ViewX = MapX;
    ViewY = MapY;
    OnMove();
}

void Player::OnRender(SDL_Surface* Surf_Display, Uint32 Inter){
    AnimWalk();
    ViewX += SpeedX * Inter;
    ViewY += SpeedY * Inter;
    /*.........................
    TTF_Init();
    atexit(TTF_Quit);

    SDL_Surface *message;
    TTF_Font *font;
    SDL_Rect dest = {.x = 100, .y = 100};
    SDL_Color textColor = {.r = 0, .g = 0, .b = 0};
    char str[100];
    sprintf(str, "%lf", Inter);
    font = TTF_OpenFont("CharisSILR.ttf", 20);
    message = TTF_RenderText_Solid( font, str, textColor );
    if(message){
        SDL_BlitSurface(message, NULL, Surf_Display, &dest);
        SDL_FreeSurface(message);
        message = NULL;
    }
    TTF_CloseFont(font);
    /*.........................*/
    Camera::CameraControl.OnMove(ViewX - (SCREEN_W>>1) + (Width>>1), ViewY - (SCREEN_H>>1) + (Height>>1));
    Surface::OnDraw(Surf_Display, SpriteSheet, ViewX - Camera::CameraControl.GetX(),
                    ViewY - Camera::CameraControl.GetY(), SpriteX, SpriteY, Width, Height);
    /*Camera::CameraControl.OnMove(MapX - (SCREEN_W>>1) + (Width>>1), MapY - (SCREEN_H>>1) + (Height>>1));
    Surface::OnDraw(Surf_Display, Surf_Entity, MapX - Camera::CameraControl.GetX(),
                    MapY - Camera::CameraControl.GetY());*/
}
