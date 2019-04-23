#include "../header/App.h"

void App::OnRender(){
    Map::MapControl.OnRender(Surf_Display, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
    Hero.OnRender(Surf_Display, Inter);
    for(int i = 0; i < ENEMIES; i++)
        Enemy::EnemyList[i]->OnRender(Surf_Display);
    /*.........................*/
    loops++;
    if(SDL_GetTicks()-start>1000){
        fps = loops;
        loops = 0;
    }
    TTF_Init();
    atexit(TTF_Quit);

    SDL_Surface *message;
    TTF_Font *font;
    SDL_Rect dest = {.x = 100, .y = 100};
    SDL_Color textColor = {.r = 0, .g = 0, .b = 0};
    char str[100];

    sprintf(str, "%d", fps);
    font = TTF_OpenFont("CharisSILR.ttf", 20);
    message = TTF_RenderText_Solid( font, str, textColor );
    if(message){
        SDL_BlitSurface(message, NULL, Surf_Display, &dest);
        SDL_FreeSurface(message);
        message = NULL;
    }

    dest.y +=50;
    sprintf(str, "%.10lf", Inter);
    message = TTF_RenderText_Solid( font, str, textColor );
    if(message){
        SDL_BlitSurface(message, NULL, Surf_Display, &dest);
        SDL_FreeSurface(message);
        message = NULL;
    }

    TTF_CloseFont(font);

    /*.........................*/

    SDL_Flip(Surf_Display);
}
