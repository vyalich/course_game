#include "../header/Entity.h"

//std::vector<Entity*>    Entity::EntityList;

Entity::Entity(){
    MapX    = 0;
    MapY    = 0;

    Width   = 0;
    Height  = 0;

    State           = 0;
    FrameRate       = 0;
    MaxFrames       = 0;
    WaitTime        = 0;
    LastFrameTime   = 0;
    FrameX          = 0;
    FrameY          = 0;
    //Flags = ENTITY_FLAG_GRAVITY;

    Speed   = 0;
    SpeedX  = 0;
    SpeedY  = 0;
}

Entity::~Entity(){

};

bool Entity::OnLoad(char* File, int Width, int Height){

}

void Entity::OnLoop(){
    ViewX = MapX;
    ViewY = MapY;
    OnMove();

}

void Entity::OnMove(){
    MapY += SpeedY;
    PosValidTileY();
    MapX += SpeedX;
    PosValidTileX();

}

void Entity::PosValidTileX(){
    int ID;

    if(SpeedX < 0){
        ID = (int)MapX/TILE_SIZE + (int)MapY/TILE_SIZE*MAP_W;
    }
    else{
        ID = (int)(MapX+Width)/TILE_SIZE + (int)MapY/TILE_SIZE*MAP_W;
    }
    for(int y = MapY; y < MapY+Height; y += TILE_SIZE){
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

void Entity::PosValidTileY(){
    int ID;

    if(SpeedY < 0){
        ID = (int)MapX/TILE_SIZE + (int)MapY/TILE_SIZE*MAP_W;
    }
    else{
        ID = (int)MapX/TILE_SIZE + (int)(MapY+Height)/TILE_SIZE*MAP_W;
    }
    for(int x = MapX; x < MapX+Width; x += TILE_SIZE){
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

void Entity::AnimWalk(){
    if(SpeedX > 0)
        State = 0;
    else
        State = 1;
    FrameY = State*Height;
    if(LastFrameTime + WaitTime > SDL_GetTicks())
        return;
    LastFrameTime = SDL_GetTicks();
    FrameX += Width;
    if(FrameX == MaxFrames*Width)
        FrameX = 0;
}

void Entity::OnRender(SDL_Surface* Surf_Display, double Inter){
    /*ViewX += SpeedX * Inter;
    ViewY += SpeedY * Inter;*/
    Surface::OnDraw(Surf_Display,  GetSpriteSheet(), MapX-Camera::CameraControl.GetX(),
                    MapY-Camera::CameraControl.GetY(), FrameX, FrameY, Width, Height);
}

void Entity::OnCleanup(){
    if(GetSpriteSheet())
        SDL_FreeSurface(GetSpriteSheet());
}

void Entity::StopMove(){
    SpeedX = SpeedY = 0;
}
