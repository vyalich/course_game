#include "../header/App.h"

void App::OnRender(){
    Hero.MoveCam(Inter);
    Map::MapControl.OnRender(Surf_Display, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());

    int CamX = Camera::CameraControl.GetX();
    int CamY = Camera::CameraControl.GetY();

    for(auto entity : Entity::OnScreen){
        entity->OnRender(Surf_Display, CamX, CamY, Inter);
    }

    for(auto spell : Spell::SpellCasted){
        spell->OnRender(Surf_Display, CamX, CamY, Inter);
    }

    GUI::GUIControl.OnRender(Surf_Display);

    /*.........................*/
    loops++;
    if(SDL_GetTicks()-start>1000){
        fps = loops;
        loops = 0;
    }

    SDL_Surface *message;
    TTF_Font *font;
    SDL_Rect dest = {.x = 100, .y = 100};
    SDL_Color textColor = {.r = 255, .g = 255, .b = 255};
    std::string str;

    str = std::to_string(fps);
    font = TTF_OpenFont("CharisSILR.ttf", 20);
    message = TTF_RenderText_Solid( font, str.c_str(), textColor );
    if(message){
        SDL_BlitSurface(message, NULL, Surf_Display, &dest);
        SDL_FreeSurface(message);
        message = NULL;
    }

    TTF_CloseFont(font);

    /*.........................*/

    SDL_Flip(Surf_Display);
}
