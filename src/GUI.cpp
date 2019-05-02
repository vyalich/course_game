#include "../header/GUI.h"

GUI GUI::GUIControl;

void Bar::Draw(SDL_Surface *Surf_Display, Uint32 color, bool reversed){
    if(reversed)
        Draw_FillRound(Surf_Display, x+w*(1-cur), y, w*cur, h, 5, color);
    else
        Draw_FillRound(Surf_Display, x, y, w*cur, h, 5, color);
    for(int i = 0; i < 3; i++)
        Draw_Round(Surf_Display, x+i, y+i, w-i*2, h-i*2, 5-i, 0x000000);
    for(int i = 2; i < 5; i++)
        Draw_Rect(Surf_Display, x+i, y+i, w-i*2, h-i*2, 0x000000);

}

void Bar::RenderText(SDL_Surface *Surf_Display, TTF_Font *Font){
    SDL_Surface *message;


    message = TTF_RenderText_Blended( Font, info.c_str(), TextColor );
    SDL_Rect dest = {.x = x+w/2-message->w/2, .y = y+1};
    if(message){
        SDL_BlitSurface(message, 0, Surf_Display, &dest);
        SDL_FreeSurface(message);
        message = NULL;
    }
}

void GUI::OnInit(){
    Font = TTF_OpenFont("CharisSILR.ttf", 16);

    SDL_Color Black = {.r = 0, .g = 0, .b = 0};

    ExpBar = {.x = 0, .y = SCREEN_H-8, .w = SCREEN_W, .h = 6, .cur = 0.7135436};
    ExpBar.TextColor = Black;
    HealthBar = {.x = SCREEN_W/2 - SCREEN_W/5, .y = SCREEN_H-40, .w = SCREEN_W/5, .h = 30, .cur = 0.6};
    HealthBar.TextColor = Black;
    ManaBar = {.x = SCREEN_W/2, .y = SCREEN_H-40, .w = SCREEN_W/5, .h = 30, .cur = 0.3};
    ManaBar.TextColor = Black;

    SDL_Surface *Temp;
    Temp = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_W, SCREEN_H, 32, 0, 0, 0, 0);
    Surface::Transparent(Temp, 255, 0, 255);
    SDL_SetAlpha(Temp, SDL_SRCALPHA, 0xa0);
    BackGround = SDL_DisplayFormat(Temp);
    SDL_FreeSurface(Temp);

    Draw_FillRect(BackGround, 0, 0, SCREEN_W, SCREEN_W, 0xff00ff);
    Draw_FillRect(BackGround, ExpBar.x, ExpBar.y, ExpBar.w, ExpBar.h, 0xd2f7a5);
    Draw_FillRound(BackGround, HealthBar.x, HealthBar.y, HealthBar.w, HealthBar.h, 5, 0xff6d6d);
    Draw_FillRound(BackGround, ManaBar.x, ManaBar.y, ManaBar.w, ManaBar.h, 5, 0x5f9bfc);
}

void GUI::OnLoop(){

}

void GUI::OnRender(SDL_Surface *Surf_Display){
    DrawBars(Surf_Display);
}

void GUI::DrawBars(SDL_Surface *Surf_Display){
    SDL_BlitSurface(BackGround, 0, Surf_Display, 0);

    HealthBar.cur = (double)App::Hero.Health/App::Hero.MaxHealth;

    int dx = ExpBar.w/10;
    Draw_FillRect(Surf_Display, ExpBar.x, ExpBar.y, ExpBar.w*ExpBar.cur, ExpBar.h, 0x72ff00);
    for(int x = ExpBar.x; x < ExpBar.x+ExpBar.w; x += dx){
        Draw_Round(Surf_Display, x, ExpBar.y-1, dx, ExpBar.h+2, 2, 0x000000);
        Draw_Round(Surf_Display, x, ExpBar.y-2, dx, ExpBar.h+4, 3, 0x000000);
    }
    HealthBar.Draw(Surf_Display, 0xff0000, true);
    ManaBar.Draw(Surf_Display, 0x0000ff, false);

    HealthBar.info = std::to_string(App::Hero.Health) + " / " + std::to_string(App::Hero.MaxHealth);
    HealthBar.RenderText(Surf_Display, Font);

}


