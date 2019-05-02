#include "../header/Entity.h"

Entity::Entity(){

}

bool Entity::OnLoad(char* File, int Width, int Height){

}

void Entity::OnLoop(){

}

void Entity::OnRender(SDL_Surface* Surf_Display, double Inter){
    Surface::OnDraw(Surf_Display,  GetSpriteSheet(), MapX-Camera::CameraControl.GetX(),
                    MapY-Camera::CameraControl.GetY(), FrameX, FrameY, Width, Height);
}

void Entity::OnCleanup(){
    if(GetSpriteSheet())
        SDL_FreeSurface(GetSpriteSheet());
}
