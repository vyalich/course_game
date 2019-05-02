#include "../header/Enemy.h"

std::vector<Enemy*> Enemy::EnemyList;

SDL_Surface*        Enemy::SpriteSheet;

Enemy::Enemy(){

}

Enemy::~Enemy(){

}

bool Enemy::OnLoad(int speed){
    if((SpriteSheet = Surface::OnLoad("./img/enemy.bmp")) == false) {

        return false;
    }
    _on_screen = false;
    _chasing = IDLE;
    Width = 64;
    Height = 64;
    AggroRange = 9*TILE_SIZE;
    FleeRange = 12*TILE_SIZE;
    AttackRange = TILE_SIZE;
    AttackSpeed = 300;
    AttackPower = 30;
    LastAttack = 0;

    MaxFrames = 8;
    WaitTime  = 0;
    LastFrameTime = SDL_GetTicks();
    State = 0;
    Speed = speed;
    LastX = MapX = (MAP_W*TILE_SIZE>>1)-(Width>>1)-8*TILE_SIZE + 12*TILE_SIZE;
    LastY = MapY = (MAP_H*TILE_SIZE>>1)-(Height>>1)+8*TILE_SIZE;

}


void Enemy::OnLoop(double PlayerX, double PlayerY, int CamX, int CamY, SDL_Surface *Surf_Display){
    if(MapX >= CamX - Width && MapX <= CamX+SCREEN_W && MapY >= CamY - Height && MapY <= CamY+SCREEN_H)
        _on_screen = true;
    else
        _on_screen = false;

    if(!_on_screen)
        return;

    double gep = sqrt((PlayerX-MapX)*(PlayerX-MapX)+(PlayerY-MapY)*(PlayerY-MapY));

    if(gep <= AggroRange && _chasing == IDLE)
        LineOfSight(PlayerX, PlayerY, gep, Surf_Display);

    if(_chasing != IDLE){
        if(gep <= AttackRange && _chasing != ATTACK){
            _chasing = ATTACK;
            FrameX = 0;
            MaxFrames = 6;
            WaitTime = AttackSpeed/MaxFrames;
            State = 4;
        }
        else if(gep >=FleeRange && _chasing != FLEE){
            _chasing = FLEE;
            SetSpeed(LastX, LastY);
        }
        else if(_chasing != CHASE && gep < FleeRange && gep > AttackRange){
            _chasing = CHASE;
            MaxFrames = 8;
            WaitTime = 3000/MaxFrames/Speed;
            State = 0;
        }
    }

    switch(_chasing){
        case CHASE:
            SpeedX = Speed/gep*(PlayerX-MapX);
            SpeedY = Speed/gep*(PlayerY-MapY);
            AngleCos = (PlayerX-MapX)/gep;
            AnimWalk();
            OnMove();
            break;
        case FLEE:
            OnMove();
            AnimWalk();
            if(abs(MapX - LastX) < TILE_SIZE && abs(MapY - LastY) < TILE_SIZE){
                _chasing = IDLE;
                StopMove();
            }
            break;
        case IDLE:
            StopMove();
            break;
        case ATTACK:
            AnimWalk();
            Attack();
            break;
    }
}

void Enemy::Attack(){
    if(SDL_GetTicks()-LastAttack < AttackSpeed)
        return;
    LastAttack = SDL_GetTicks();
    App::Hero.Health -= AttackPower;
    if(App::Hero.Health < 0)
        App::Hero.Health = 0;
}

void Enemy::LineOfSight(double PlayerX, double PlayerY, double gep, SDL_Surface *Surf_Display){
    double dx = TILE_SIZE/gep*(PlayerX-MapX);
    double dy = TILE_SIZE/gep*(PlayerY-MapY);
    for(double x = MapX+Width/2, y = MapY+Height/2; abs(x-(PlayerX+Width/2))>abs(dx)
        || abs(y - (PlayerY+Height/2))>abs(dy); x+=dx, y+=dy){
        Draw_FillCircle(Surf_Display, x - Camera::CameraControl.GetX(), y - Camera::CameraControl.GetY(), 2, 0xff0000);
        if(Map::MapControl.GetTileType((int)x/TILE_SIZE + (int)y/TILE_SIZE*MAP_W) == TILE_TYPE_BLOCK){
            _chasing = IDLE;
            return;
        }
    }
    _chasing = CHASE;
    LastX = MapX;
    LastY = MapY;
    /*Draw_Circle(Surf_Display, LastX - Camera::CameraControl.GetX(), LastY - Camera::CameraControl.GetY(), 15, 0xff0000);
    Draw_Circle(Surf_Display, LastX - Camera::CameraControl.GetX(), LastY - Camera::CameraControl.GetY(), 14, 0xff0000);
    Draw_Circle(Surf_Display, LastX - Camera::CameraControl.GetX(), LastY - Camera::CameraControl.GetY(), 13, 0xff0000);*/

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
