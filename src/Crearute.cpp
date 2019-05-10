#include "../header/Creature.h"

Creature::Creature(){
    Speed   = 0;
    SpeedX  = 0;
    SpeedY  = 0;
    AngleCos = 0;
}

void Creature::OnMove(){
    OldX = MapX;
    OldY = MapY;
    MapY += SpeedY;
    PosValidTileY(16, 16, 42, 2);
    MapX += SpeedX;
    PosValidTileX(16, 16, 42, 2);

}

bool Creature::PosValidTileX(int l, int r, int t, int b){
    int ID;
    double dx = 0;

    if(SpeedX < 0){
        ID = (int)(MapX+l)/TILE_SIZE + (int)(MapY + t)/TILE_SIZE*MAP_W;
    }
    else{
        ID = (int)(MapX-r+Width)/TILE_SIZE + (int)(MapY + t)/TILE_SIZE*MAP_W;
    }
    for(int y = (int)(MapY + t)/TILE_SIZE*TILE_SIZE; y < MapY+Height-b-1; y += TILE_SIZE){
        if(Map::MapControl.GetTileType(ID) == TILE_TYPE_BLOCK){
            MapX = ID % MAP_W * TILE_SIZE;
            if(SpeedX < 0)
                MapX += TILE_SIZE - l;
            else
                MapX -= Width - r;
            SpeedX = 0;
            return false;
        }
        ID += MAP_W;
    }
    return true;
}

bool Creature::PosValidTileY(int l, int r, int t, int b){
    int ID;
    double dy = 0;

    if(SpeedY < 0){
        ID = (int)(MapX+l)/TILE_SIZE + (int)(MapY+t)/TILE_SIZE*MAP_W;
    }
    else{
        ID = (int)(MapX+l)/TILE_SIZE + (int)(MapY+Height)/TILE_SIZE*MAP_W;
    }
    for(int x = (int)(MapX+l)/TILE_SIZE*TILE_SIZE; x < MapX+Width-r-1; x += TILE_SIZE){
        if(Map::MapControl.GetTileType(ID) == TILE_TYPE_BLOCK){
            MapY = ID / MAP_W * TILE_SIZE;
            if(SpeedY < 0)
                MapY += TILE_SIZE - t;
            else
                MapY -= Height - b;
            SpeedY = 0;
            return false;
        }
        ID++;
    }
    return true;
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


    FrameY = (State+Direction)*Height;
    if(LastFrameTime + WaitTime > SDL_GetTicks())
        return;
    LastFrameTime = SDL_GetTicks();
    FrameX += Width;
    if(FrameX >= MaxFrames*Width)
        FrameX = 0;
}

void Creature::StopMove(double Inter){
    SpeedX = SpeedY = 0;
    MapX = OldX;// + SpeedX*Inter;
    MapY = OldY;// + SpeedY*Inter;
    FrameX = 8*Width;
}
