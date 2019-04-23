#include "../header/Entity.h"

//std::vector<Entity*>    Entity::EntityList;

Entity::Entity(){
    Surf_Entity = NULL;

    MapX = 0;
    MapY = 0;
    LastID = 0;

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
    if(SpeedX || SpeedY){
        MapX += SpeedX;
        MapY += SpeedY;
        PosValidTile();
    }
}

void Entity::PosValidTile(){
    int ID = (int)MapX/TILE_SIZE + (int)MapY/TILE_SIZE*MAP_W;

    int _col_x = 0;
    int _col_y = 0;
    int _last_x = 0;
    int _last_y = 0;
    int x = (int)MapX/TILE_SIZE*TILE_SIZE;
    int y = (int)MapY/TILE_SIZE*TILE_SIZE;
    int dx = 0;
    int dy = 0;

    int i = 0, j = 0;
    //проверка коллизии по У
    if(SpeedY > 0){
        i = 2;
    }
    else{
        i = 0;
        y += TILE_SIZE;
    }
    for(j = 0; j < 3; j++){
        if(Map::MapControl.GetTileType(ID+i*MAP_W+j)){
            dy = MapY - y;
            _col_y++;
            _last_y = ID+i*MAP_W+j;
        }
    }
    //проверка коллизии по Х
    if(SpeedX > 0){
        j = 2;
    }
    else{
        j = 0;
        x += TILE_SIZE;
    }
    for(i = 0; i < 3; i++){
        if(Map::MapControl.GetTileType(ID+i*MAP_W+j)){
            dx = MapX - x;
            _col_x++;
            _last_x = ID+i*MAP_W+j;
        }
    }

    if(!(_col_x | _col_y))      //если коллизий не было - выход
        return;

    //отталкивание от тайлов
    if(_col_x == 1 && _col_y > 1 && _last_x/MAP_W == _last_y/MAP_W)
            MapY -= dy;
    else if(_col_x > 1 && _col_y == 1 && _last_x%MAP_W == _last_y%MAP_W)
            MapX -= dx;
    else if(_col_x == 1 && _col_y == 1)
        if(_last_x == _last_y)
            if(abs(dx)<abs(dy))
                MapX -= dx;
            else
                MapY -= dy;
        else{
            MapX -= dx;
            MapY -= dy;
        }
    else{
        if(_col_x)
            MapX -= dx;
        if(_col_y)
            MapY -= dy;
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
