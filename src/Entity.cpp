#include "../header/Entity.h"

//std::vector<Entity*>    Entity::EntityList;

Entity::Entity(){
    Surf_Entity = NULL;

    MapX = 0;
    MapY = 0;

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
    if((Surf_Entity = Surface::OnLoad("./tile/Player.bmp")) == false) {
        return false;
    }
    MapX = 320;
    MapY = 240;
    Camera::CameraControl.SetPos(MapX, MapY);
}

void Entity::OnLoop(){

}

void Entity::OnRender(SDL_Surface* Surf_Display){
    Surface::OnDraw(Surf_Display, Surf_Entity, MapX, )
}

void Entity::OnCleanup(){
    if(Surf_Entity)
        SDL_FreeSurface(Surf_Entity);
}

void Entity::OnCollision(Entity* Entity){

}
