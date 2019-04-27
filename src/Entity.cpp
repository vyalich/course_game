#include "../header/Entity.h"

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
