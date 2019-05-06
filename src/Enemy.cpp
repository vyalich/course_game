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
    Dist = 1000;
    _on_screen = false;
    _chasing = IDLE;
    Width = 64;
    Height = 64;
    AggroRange = 9*TILE_SIZE;
    FleeRange = 12*TILE_SIZE;
    AttackRange = TILE_SIZE+16;
    AttackSpeed = 900;
    AttackPower = 8;
    LastAttack = 0;

    Health = 0;
    MaxHealth = 90;
    HPRegen = 0.04;

    MaxFrames = 8;
    WaitTime  = 0;
    LastFrameTime = SDL_GetTicks();
    State = 0;
    FrameX = 0;
    FrameY = 2*Height;
    Speed = speed;
    LastX = MapX = (MAP_W*TILE_SIZE>>1)-(Width>>1)-8*TILE_SIZE + 12*TILE_SIZE;
    LastY = MapY = (MAP_H*TILE_SIZE>>1)-(Height>>1)+8*TILE_SIZE;

}


void Enemy::OnLoop(double PlayerX, double PlayerY, int CamX, int CamY, SDL_Surface *Surf_Display){
    if(Health < MaxHealth)
        Health += HPRegen;
    else
        Health = MaxHealth;

    if(MapX >= CamX - Width && MapX <= CamX+SCREEN_W && MapY >= CamY - Height && MapY <= CamY+SCREEN_H){
        if(!_on_screen)
            Entity::OnScreen.push_back(this);
        _on_screen = true;
    }
    else{
        if(_on_screen)
            Entity::OnScreen.remove(this);
        _on_screen = false;
    }

    if(!_on_screen)
        return;

    int MouseX, MouseY, ScrX = MapX - CamX, ScrY = MapY - CamY;
    SDL_GetMouseState(&MouseX, &MouseY);
    if(MouseX >= ScrX + 16 && MouseX <= ScrX + Width - 16 &&
       MouseY >= ScrY + 14 && MouseY <= ScrY + Height - 2)
        _mouseover = true;
    else
        _mouseover = false;

    Dist = sqrt((PlayerX-MapX)*(PlayerX-MapX)+(PlayerY-MapY)*(PlayerY-MapY));

    if(Dist <= AggroRange && (_chasing == IDLE || _chasing == FLEE))
        LineOfSight(PlayerX, PlayerY, Surf_Display);

    if(_chasing == ATTACK && FrameX != 0){
        AngleCos = (PlayerX-MapX)/Dist;
        if(MapY - PlayerY > 0)
            SpeedY = -0.000000001;
        else
            SpeedY = 0;
        AnimWalk();
        return;
    }

    if(_chasing != IDLE){
        if(_chasing != ATTACK && Dist <= AttackRange){
            _chasing = ATTACK;
            FrameX = 0;
            MaxFrames = 6;
            WaitTime = AttackSpeed/MaxFrames;
            State = 4;
        }
        else if(_chasing != FLEE && Dist >=FleeRange){
            _chasing = FLEE;

        }
        else if(_chasing == ATTACK && Dist > AttackRange){
            _chasing = CHASE;
            MaxFrames = 8;
            WaitTime = 3000/Speed/MaxFrames;
            State = 0;
        }
    }

    switch(_chasing){
        case CHASE:
            SpeedX = Speed/Dist*(PlayerX-MapX);
            SpeedY = Speed/Dist*(PlayerY-MapY);
            AngleCos = (PlayerX-MapX)/Dist;
            AnimWalk();
            OnMove();
            break;
        case FLEE:
            SetSpeed(LastX, LastY);
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

void Enemy::LineOfSight(double PlayerX, double PlayerY, SDL_Surface *Surf_Display){
    double dx = TILE_SIZE/Dist*(PlayerX-MapX);
    double dy = TILE_SIZE/Dist*(PlayerY-MapY);
    for(double x = MapX+Width/2, y = MapY+Height/2; abs(x-(PlayerX+Width/2))>abs(dx)
        || abs(y - (PlayerY+Height/2))>abs(dy); x+=dx, y+=dy){
        //Draw_FillCircle(Surf_Display, x - Camera::CameraControl.GetX(), y - Camera::CameraControl.GetY(), 2, 0xff0000);
        int ID = (int)x/TILE_SIZE + (int)y/TILE_SIZE*MAP_W;
        if(Map::MapControl.GetTileType(ID) == TILE_TYPE_BLOCK &&
           Map::MapControl.GetTileType(ID + MAP_W) == TILE_TYPE_BLOCK){
            return;
        }
    }
    _chasing = CHASE;
    MaxFrames = 8;
    WaitTime = 3000/Speed/MaxFrames;
    State = 0;
    LastX = MapX;
    LastY = MapY;
}

void Enemy::SetSpeed(double DestX, double DestY){
    Dist = sqrt((DestX-MapX)*(DestX-MapX)+(DestY-MapY)*(DestY-MapY));
    SpeedX = Speed/Dist*(DestX-MapX);
    SpeedY = Speed/Dist*(DestY-MapY);
    AngleCos = (DestX-MapX)/Dist;
}
