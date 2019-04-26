#include "../header/Enemy.h"

std::vector<Enemy*> Enemy::EnemyList;

SDL_Surface*        Enemy::SpriteSheet;

Enemy::Enemy(){

}

Enemy::~Enemy(){

}

bool Enemy::OnLoad(int speed, int width, int height){
    if((SpriteSheet = Surface::OnLoad("./img/Enemy.bmp")) == false) {
        return false;
    }
    Width = width;
    Height = height;
    MaxFrames = SpriteSheet->w/width;
    FrameRate = 12;
    WaitTime  = 1000/FrameRate;
    LastFrameTime = SDL_GetTicks();
    Width = width;
    Height = height;
    Speed = speed;
    MapX = rand() % (MAP_W*TILE_SIZE);
    MapY = rand() % (MAP_H*TILE_SIZE);
}


void Enemy::OnLoop(double PlayerX, double PlayerY){

    //double gep = sqrt((DestX-MapX)*(DestX-MapX)+(DestY-MapY)*(DestY-MapY));
    SetSpeed(PlayerX, PlayerY);
    if(SpeedX || SpeedY)
        AnimWalk();
    ViewX = MapX;
    ViewY = MapY;
    OnMove();
}

void Enemy::SetSpeed(double DestX, double DestY){
    if(DestY>=MapY && DestY<=MapY+Height && DestX>=MapX && DestX<=MapX+Width){
        SpeedX = SpeedY = 0;
        return;
    }
    double gep = sqrt((DestX-MapX)*(DestX-MapX)+(DestY-MapY)*(DestY-MapY));
    SpeedX = Speed/gep*(DestX-MapX);
    SpeedY = Speed/gep*(DestY-MapY);
}
