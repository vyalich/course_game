#include "../header/Entity.h"

//std::vector<Entity*>    Entity::EntityList;

Entity::Entity(){
    MapX    = 0;
    MapY    = 0;

    Width   = 0;
    Height  = 0;

    WaitTime  = 0;
    LastFrame = 0;
    SpriteX = 0;
    SpriteY = 0;
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
    MapX += SpeedX;
    PosValidTileX();
    MapY += SpeedY;
    PosValidTileY();
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

    int raw = 0;


    if(SpeedX < 0)
        raw++;
    SpriteY = raw*Height;
    if(LastFrame + WaitTime > SDL_GetTicks())
        return;
    LastFrame = SDL_GetTicks();
    SpriteX += Width;
    if(SpriteX == 6*Width)
        SpriteX = 0;
}

void Entity::OnRender(SDL_Surface* Surf_Display){
    AnimWalk();
    Surface::OnDraw(Surf_Display,  GetSpriteSheet(), MapX-Camera::CameraControl.GetX(),
                    MapY-Camera::CameraControl.GetY(), SpriteX, SpriteY, Width, Height);
}

void Entity::OnCleanup(){
    if(GetSpriteSheet())
        SDL_FreeSurface(GetSpriteSheet());
}

void Entity::StopMove(){
    SpeedX = SpeedY = 0;
}
