#include "../header/Entity.h"

std::list<Entity*>   Entity::OnScreen;

Entity::Entity(){

}

bool Entity::OnLoad(char* File, int Width, int Height){

}

void Entity::OnLoop(){

}

void Entity::OnRender(SDL_Surface* Surf_Display, int CamX, int CamY, double Inter){

    Surface::OnDraw(Surf_Display,  GetSpriteSheet(), OldX + SpeedX*Inter - CamX, OldY + SpeedY*Inter - CamY, FrameX, FrameY, Width, Height);
}


void Entity::OnCleanup(){
    if(GetSpriteSheet())
        SDL_FreeSurface(GetSpriteSheet());
}
