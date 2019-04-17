#include "../header/Entity.h"

//std::vector<Entity*>    Entity::EntityList;

Entity::Entity(){
    Surf_Entity = NULL;

    MapX = 0;
    MapY = 0;
    FirstID = 0;

    Width     = 0;
    Height     = 0;

    Type =     ENTITY_TYPE_GENERIC;

    Dead = false;
    //Flags = ENTITY_FLAG_GRAVITY;

    Speed  = 0;
    SpeedX = 0;
    SpeedY = 0;

    Col_X = 0;
    Col_Y = 0;

    Col_Width  = 0;
    Col_Height = 0;
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
    MapY += SpeedY;

    int _col_x = 0;
    int _col_y = 0;
    int ID = (int)MapX/TILE_SIZE + (int)MapY/TILE_SIZE*MAP_W;
    int x = (int)MapX/TILE_SIZE*TILE_SIZE;
    int y = (int)MapY/TILE_SIZE*TILE_SIZE;
    int MaxY = MapY + Height;
    int MaxX = MapX + Width;
    int dX = 0;
    int dY = 0;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(Map::MapControl.GetTileType(ID+i*MAP_W+j)){
                if(!(i % 2)){
                    _col_y++;

                }
                if(i == 1)
                    _col_x = 3;
                if(!(j % 2)){
                    _col_x++;

                }
                if(j == 1)
                    _col_y = 3;

            }
            x += TILE_SIZE;
        }
        x = (int)MapX/TILE_SIZE*TILE_SIZE;
        y += TILE_SIZE;
    }
    /*if(_col_x == 1 && _col_y == 1){

    }*/
    if(_col_x > 2){
        MapX = ((SpeedX<0)?ID+1 : ID) % MAP_W * TILE_SIZE;
        SpeedX = 0;
    }
    if(_col_y > 2){
        MapY = ((SpeedY<0)?ID+MAP_W : ID) / MAP_W * TILE_SIZE;
        SpeedY = 0;
    }
}

void Entity::OnRender(SDL_Surface* Surf_Display){
    Surface::OnDraw(Surf_Display, Surf_Entity, MapX-Camera::CameraControl.GetX(), MapY-Camera::CameraControl.GetY());
}

void Entity::OnCleanup(){
    if(Surf_Entity)
        SDL_FreeSurface(Surf_Entity);
}

void Entity::OnCollision(Entity* Entity){

}

void Entity::StopMove(){
    SpeedX = SpeedY = 0;
}
