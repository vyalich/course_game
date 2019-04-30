#include "../header/Enemy.h"

std::vector<Enemy*> Enemy::EnemyList;

SDL_Surface*        Enemy::SpriteSheet;

enum            {STAY       = 0,
                 WALK          ,
                 ATTACK        ,
                 DIE            };

Enemy::Enemy(){

}

Enemy::~Enemy(){

}

bool Enemy::OnLoad(int speed, int width, int height){
    if((SpriteSheet = Surface::OnLoad("./img/enemy.bmp")) == false) {

        return false;
    }
    _on_screen = false;
    Width = width;
    Height = height;
    AggroRange = 16*TILE_SIZE;
    MaxFrames = SpriteSheet->w/width;
    FrameRate = 12;
    WaitTime  = 1000/FrameRate;
    LastFrameTime = SDL_GetTicks();
    State = 2;
    Width = width;
    Height = height;
    Speed = speed;
    MapX = 32+rand() % (MAP_W*TILE_SIZE - 64);
    MapY = 32+rand() % (MAP_H*TILE_SIZE - 64);
}


void Enemy::OnLoop(double PlayerX, double PlayerY, int CamX, int CamY, SDL_Surface *Surf_Display){
    if(MapX >= CamX - Width && MapX <= CamX+SCREEN_W && MapY >= CamY - Height && MapY <= CamY+SCREEN_H)
        _on_screen = true;
    else
        _on_screen = false;

    if(!_on_screen)
        return;
    double gep = sqrt((PlayerX-MapX)*(PlayerX-MapX)+(PlayerY-MapY)*(PlayerY-MapY));
    //Draw_Line(Surf_Display, MapX + Width/2 - CamX, MapY + Height/2 - CamY, PlayerX - CamX, PlayerY-CamY, 0xff0000);



    if(gep < AggroRange){
        State = WALK;
        double dx = TILE_SIZE/gep*(PlayerX-MapX);
        double dy = TILE_SIZE/gep*(PlayerY-MapY);
        for(double x = MapX+Width/2, y = MapY+Height/2; abs(x-(PlayerX+Width/2))>abs(dx) && abs(y - (PlayerY+Height/2))>abs(dy); x+=dx, y+=dy){
            Draw_FillCircle(Surf_Display, x - CamX, y - CamY, 2, 0xff0000);
            if(Map::MapControl.GetTileType((int)x/TILE_SIZE + (int)y/TILE_SIZE*MAP_W) == TILE_TYPE_BLOCK){
                State = STAY;
                break;
            }
        }
    }
    /*else if(gep < AttackRange)
        State = ATTACK;*/
    else
        State = STAY;

    switch(State){
        case WALK:
            SpeedX = Speed/gep*(PlayerX-MapX);
            SpeedY = Speed/gep*(PlayerY-MapY);
            AngleCos = (PlayerX-MapX)/gep;
            AnimWalk();
            OnMove();
            break;
        case STAY:
            AnimStay();
            StopMove();
            break;
        //case ATTACK:

    }
}

void Enemy::SetSpeed(double DestX, double DestY){
    double gep = sqrt((DestX-MapX)*(DestX-MapX)+(DestY-MapY)*(DestY-MapY));
    SpeedX = Speed/gep*(DestX-MapX);
    SpeedY = Speed/gep*(DestY-MapY);
    AngleCos = (DestX-MapX)/gep;
}

void Enemy::OnRender(SDL_Surface* Surf_Display, double Inter){
    if(_on_screen)
        Surface::OnDraw(Surf_Display,  GetSpriteSheet(), MapX-Camera::CameraControl.GetX(),
                        MapY-Camera::CameraControl.GetY(), FrameX, FrameY, Width, Height);
}
