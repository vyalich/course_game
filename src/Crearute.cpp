#include "../header/Creature.h"

Creature::Creature(){
    Speed   = 0;
    SpeedX  = 0;
    SpeedY  = 0;
    AngleCos = 0;
}

void Creature::OnMove(){
    MapY += SpeedY;
    PosValidTileY();
    MapX += SpeedX;
    PosValidTileX();

}

void Creature::PosValidTileX(){
    int ID;

    if(SpeedX < 0){
        ID = (int)MapX/TILE_SIZE + (int)MapY/TILE_SIZE*MAP_W;
    }
    else{
        ID = (int)(MapX+Width)/TILE_SIZE + (int)MapY/TILE_SIZE*MAP_W;
    }
    for(int y = (int)MapY/TILE_SIZE*TILE_SIZE; y < MapY+Height-1; y += TILE_SIZE){
        if(Map::MapControl.GetTileType(ID) == TILE_TYPE_BLOCK){
            MapX = ID % MAP_W * TILE_SIZE;
            if(SpeedX < 0)
                MapX += TILE_SIZE;
            else
                MapX -= Width;
            return;
        }
        ID += MAP_W;
    }
}

void Creature::PosValidTileY(){
    int ID;

    if(SpeedY < 0){
        ID = (int)MapX/TILE_SIZE + (int)MapY/TILE_SIZE*MAP_W;
    }
    else{
        ID = (int)MapX/TILE_SIZE + (int)(MapY+Height)/TILE_SIZE*MAP_W;
    }
    for(int x = (int)MapX/TILE_SIZE*TILE_SIZE; x < MapX+Width-1; x += TILE_SIZE){
        if(Map::MapControl.GetTileType(ID) == TILE_TYPE_BLOCK){
            MapY = ID / MAP_W * TILE_SIZE;
            if(SpeedY < 0)
                MapY += TILE_SIZE;
            else
                MapY -= Height;
            return;
        }
        ID++;
    }
}

void Creature::AnimWalk(){
    if(AngleCos > BOUNDCOS)
        Direction = RIGHT;
    else if(AngleCos < -BOUNDCOS)
        Direction = LEFT;
    else{
        if(SpeedY < 0)
            Direction = TOP;
        else
            Direction = BOTTOM;
    }
    FrameY = Direction*Height;
    if(LastFrameTime + WaitTime > SDL_GetTicks())
        return;
    LastFrameTime = SDL_GetTicks();
    FrameX += Width;
    if(FrameX == MaxFrames*Width)
        FrameX = 0;
}

void Creature::AnimStay(){
    FrameY = Direction*Height;
    FrameX = 0;
}

void Creature::StopMove(){
    SpeedX = SpeedY = 0;
}
